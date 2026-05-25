import time
import threading
import struct
import can

# -------------------------------------------------------------------------
# [Windows candleLight 설정]
# -------------------------------------------------------------------------
BITRATE = 500000            # STM32와 맞춘 통신 속도 (500kbps)

# CAN ID 정의 (STM32 코드와 일치해야 함)
TX_ID_TARGET_ANGLE = 0x100  # PC -> MCU (지령 송신 ID)
RX_ID_MOTOR_STATUS = 0x200  # MCU -> PC (상태 수신 ID)


def can_receive_thread(bus):
    """
    STM32로부터 모터 상태 정보를 실시간으로 수신하는 쓰레드 함수
    """
    print("[Rx Thread] 수신 대기 시작...")
    while True:
        try:
            # 메시지 수신 대기 (타임아웃 없음)
            msg = bus.recv()
            
            if msg is not None and msg.arbitration_id == RX_ID_MOTOR_STATUS:
                # 데이터가 정확히 8바이트인지 확인 (float 2개 = 8바이트)
                if len(msg.data) == 8:
                    # STM32가 보낸 Little-Endian(<) 형태의 float 2개(ff) 파싱
                    # msg.data[:4] -> 현재 위치, msg.data[4:] -> 현재 속도
                    current_pos, current_spd = struct.unpack('<ff', msg.data)
                    
                    print(f"[수신] 현재 위치: {current_pos:6.2f}° | 현재 속도: {current_spd:6.2f} rpm")
                else:
                    print(f"[경고] 잘못된 데이터 길이 수신: {len(msg.data)} 바이트")
                    
        except Exception as e:
            print(f"[Rx Error] 수신 오류 발생: {e}")
            break


def main():
    # 1. usb.core를 거치지 않고 python-can 내장 gs_usb 드라이버로 직접 연결 시도
    print("candleLight 장치에 직접 연결을 시도합니다...")
    try:
        # channel=0은 시스템이 인식한 첫 번째 gs_usb 장치를 의미합니다.
        bus = can.Bus(
            interface="gs_usb",
            channel=0,
            bitrate=BITRATE
        )
        print(f"CAN 버스 연결 성공! (gs_usb @ {BITRATE/1000}kbps)")
    except Exception as e:
        print(f"\n[CAN 연결 실패]: {e}")
        print("="*60)
        print("💡 해결 방법:")
        print("1. Zadig 프로그램에서 candleLight 장치를 선택한 뒤,")
        print("   Driver 대상을 'WinUSB'로 지정하고 [Replace Driver]를 완료했는지 확인하세요.")
        print("2. USB 케이블을 뽑았다가 다시 꽂은 뒤 실행해 보세요.")
        print("="*60)
        return

    # 2. 백그라운드 수신 쓰레드 시작
    rx_thread = threading.Thread(target=can_receive_thread, args=(bus,), daemon=True)
    rx_thread.start()

    # 테스트용 가상 목표 각도 시나리오
    target_angles = [0.0, 45.5, 90.0, 180.0, -45.5]
    angle_index = 0

    print("Main 루프 시작: 1초마다 모터 지령(float) 송신...")
    try:
        while True:
            # 3. 송신할 목표 각도 선택
            angle_to_send = target_angles[angle_index]
            
            # float 데이터를 Little-Endian 바이트 스트림(4바이트)으로 변환
            # '<f'의 의미: < (Little-Endian), f (float)
            packed_data = struct.pack('<f', angle_to_send)
            
            # 4. CAN 메시지 생성 (ID: 0x100, 데이터 길이: 4바이트)
            msg = can.Message(
                arbitration_id=TX_ID_TARGET_ANGLE,
                data=packed_data,
                is_extended_id=False  # Standard ID 사용
            )
            
            # 5. 전송
            bus.send(msg)
            print(f"\n[송신] 목표 각도 지령 전송 완료 -> {angle_to_send}° (바이트: {packed_data.hex()})")
            
            # 다음 지령 준비 및 1초 대기
            angle_index = (angle_index + 1) % len(target_angles)
            time.sleep(1.0)
            
    except KeyboardInterrupt:
        print("\n사용자에 의해 프로그램이 종료되었습니다.")
    finally:
        # 6. CAN 버스 안전하게 닫기
        bus.shutdown()
        print("CAN 버스가 안전하게 종료되었습니다.")


if __name__ == "__main__":
    main()