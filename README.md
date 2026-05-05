# STM32 Register-Level DC Motor Control

이 프로젝트는 STM32 MCU를 활용하여 하드웨어 추상화 계층(HAL) 없이 **레지스터 직접 제어(Register-Level Control)**를 통해 모터 제어 시스템을 구축하는 연구 프로젝트입니다.

## 📌 Project Overview
모터 제어 시스템의 응답 속도 최적화와 MCU 내부 구조의 깊이 있는 이해를 위해 모든 드라이버를 직접 설계했습니다. 현재 DC 모터의 물리적 특성을 파악하기 위한 **시스템 식별(System Identification)** 단계를 진행 중입니다.
FreeRTOS 기반 RTOS 아키텍처로 이관하고, CAN 지령 기반 BLDC FOC(Field-Oriented Control)까지 확장할 계획입니다.

## 🛠 Core Tech Stack
- **Hardware**: STM32F767ZI (Cortex-M7)
- **Programming**: C (Register-level)
- **Peripherals**: GPIO, TIM (PWM, Encoder), UART, SPI
- **Control Theory**: System Identification, Transfer Function Analysis

## 🚀 Key Features (Custom Libraries)
모든 라이브러리는 데이터시트를 참조하여 레지스터 단위로 직접 구현되었습니다.

*   **Clock Configuration**: 시스템 클록(216MHz) 및 버스 클록 최적화 설정
*   **PWM Control (TIM5)**: 모터 드라이버 제어를 위한 고정밀 PWM 신호 생성
*   **Encoder Interface**: 타이머 하드웨어 카운터를 이용한 QEI(Quadrature Encoder Interface) 구현
*   **Communication**: 
    *   **UART**: 디버깅 및 데이터 모니터링용 인터럽트 기반 통신
    *   **SPI**: 고속 센서 데이터 수집을 위한 통신 드라이버
*   **GPIO**: 고속 스위칭을 위한 최적화된 I/O 제어

## 📈 Current Progress: System Identification
단순한 구동을 넘어, 제어 공학적 접근을 통해 시스템을 분석하고 있습니다.

1.  **Step Response Test**: DC 모터에 6V 스텝 입력을 인가하여 실시간 속도 응답 데이터 수집 완료
2.  **Modeling**: 수집된 데이터를 기반으로 시스템의 **전달함수(Transfer Function)** 도출 진행 중
3.  **Goal**: 도출된 모델을 바탕으로 최적의 PID 제어기 파라미터를 설계할 예정입니다.

## 📂 Project Structure
```text
├── Drivers/
│   ├── GPIO/          # Register-level GPIO Drivers
│   ├── TIM/           # PWM & Encoder Mode Configuration
│   ├── UART/          # Interrupt-based Communication
│   └── SPI/           # High-speed Sensor Interface
├── Docs/              # Step Response Data & Analysis
└── main.c             # System Initialization & Control Loop
