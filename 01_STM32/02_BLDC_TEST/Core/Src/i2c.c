#include "i2c.h"
#define AS5600_ADDR_7BIT 0x36
int debug_1_i2c = 0;
void I2C1_DMA_Init(){
	RCC->AHB1ENR |= (1 << 1);
	RCC->APB1ENR |= (1 << 21);

	GPIOB->MODER &= ~((3 << (2*8)) | (3 << (2*9)));
	GPIOB->MODER |= ((2 << (2*8)) | (2 << (2*9)));

	GPIOB->OTYPER |= ((1 << 8) | (1 << 9)); //open-drain

	GPIOB->PUPDR &= ~((3 << (2 * 8)) | (3 << (2 * 9)));

	GPIOB->AFR[1] &= ~((0xF << 0 * 4) | (0xF << 1 * 4));
	GPIOB->AFR[1] |=  ((4 << 0 * 4) | (4 << 1 * 4));

	DMA1->S[0].CR &= ~(1 << 0); //일단 끄기
	DMA1->S[6].CR &= ~(1 << 0);
	while (DMA1->S[0].CR & (1 << 0));
	while (DMA1->S[6].CR & (1 << 0));

	// DMA1 Stream 0 설정 : I2C1_RX (Channel 1)
	DMA1->S[0].CR = 0;
	DMA1->S[0].CR |= (1 << 25); // CHSEL = 1 (Channel 1 지정)
	DMA1->S[0].CR |= (1 << 10); // MINC = 1 (메모리 주소 자동 증가)
	DMA1->S[0].PAR = (uint32_t)&(I2C1->RXDR); // 송수신 데이터 레지스터 주소 지정

	// DMA1 Stream 6 설정 : I2C1_TX (Channel 1)
	DMA1->S[6].CR = 0;
	DMA1->S[6].CR |= (1 << 25); // CHSEL = 1 (Channel 1 지정)
	DMA1->S[6].CR |= (1 << 10); // MINC = 1 (메모리 주소 자동 증가)
	DMA1->S[6].CR |= (1 << 6);  // DIR = 01 (Memory-to-peripheral, 메모리 -> 주변장치)
	DMA1->S[6].PAR = (uint32_t)&(I2C1->TXDR);

	I2C1->TIMINGR = 0x40912732;
	// I2C 내부 DMA 활성화 및 기본 타이밍 설정
	I2C1->CR1 |= (1 << 14) | (1 << 15);     // DMAEN = 1 (I2C 내부에서 DMA 요청을 던지도록 허용)

	// 기본 I2C 활성화 (PE=1)
	I2C1->CR1 |= (1 << 0);
}

#define AS5048B_ADDR_WRITE    (0x36 << 1)       //
#define AS5048B_ADDR_READ     ((0x36 << 1) | 1) //

void I2C1_ReadReg_DMA(uint8_t reg_addr, uint8_t *pBuffer, uint16_t size) {
    while (I2C1->ISR & (1 << 15)); // 버스 BUSY 체크
    I2C1->ICR |= 0x3F38;           // 이전 통신 에러 플래그 클리어

    // SADD = 0x36, NBYTES = 1, START = 1, RD_WRN = 0(Write)
    I2C1->CR2 = (AS5600_ADDR_7BIT << 1) | (1 << 16) | (1 << 13);

    uint32_t timeout = 100000;
    while (!(I2C1->ISR & (1 << 1))) { // TXIS 대기
        if (I2C1->ISR & (1 << 4)) {   // NACK 발생 (센서 응답 안 함)
            I2C1->ICR |= (1 << 4);
            I2C1->CR2 |= (1 << 14);   // STOP 발생
            return;
        }
        if (--timeout == 0) return;   // 하드웨어 타임아웃
    }

    I2C1->TXDR = reg_addr;
    while (!(I2C1->ISR & (1 << 6)));  // TC(Transfer Complete) 대기

    DMA1->S[0].CR &= ~(1 << 0);
    while (DMA1->S[0].CR & (1 << 0));

    DMA1->S[0].M0AR = (uint32_t)pBuffer;
    DMA1->S[0].NDTR = size;
    DMA1->LIFCR = (0x3D << 0);
    DMA1->S[0].CR |= (1 << 0);

    // SADD = 0x36, NBYTES = size, RD_WRN = 1(Read), START = 1, AUTOEND = 1
    I2C1->CR2 = (AS5600_ADDR_7BIT << 1) | ((uint32_t)size << 16) | (1 << 10) | (1 << 13) | (1 << 25);

    while (!(DMA1->LISR & (1 << 5)));    // DMA 수신 완료 대기 (TCIF0)

    while (!(I2C1->ISR & (1 << 5)));     // AUTOEND에 의한 STOP 대기
    I2C1->ICR |= (1 << 5);               // STOPF 클리어

    DMA1->S[0].CR &= ~(1 << 0);          // DMA 후처리
}

float Process_Encoder_Data(void) {
    uint8_t raw_buffer[2] = {0};
    uint8_t status_val = 0;

    // STATUS 레지스터 (0x0B) 읽기
    I2C1_ReadReg_DMA(0x0B, &status_val, 1);
    debug_1_i2c = status_val;
//    if ((status_val & (1 << 5)) == 0 || (status_val & (3 << 3)) != 0) {
//        // 자석이 없거나 거리가 불량한 경우 예외 처리
//        return 0.0f;
//    }

    // ANGLE 레지스터 (0x0E, 0x0F) 2바이트 연속 DMA 읽기
    I2C1_ReadReg_DMA(0x0E, raw_buffer, 2);

    // 12비트 복원
    // 0x0E 레지스터의 하위 4비트가 상위 데이터, 0x0F 레지스터가 하위 데이터
    uint16_t raw_angle = ((uint16_t)(raw_buffer[0] & 0x0F) << 8) | raw_buffer[1];

    // 라디안(Radian) 변환
    // 12비트(0~4095) 기준: 2 * PI / 4096 = 0.00153398078f
    float radian_angle = raw_angle * 0.00153398078f;

    return radian_angle;
}
