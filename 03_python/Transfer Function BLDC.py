import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# 1. 데이터 로드 (파일 포맷에 따라 구분자 확인 필요)
# 메모장에 '시간, 속도' 형태로 저장되어 있다고 가정합니다.
file_name = 'BLDC_motor_transfer.txt'
try:
    data = np.loadtxt(r'C:\Users\leesc\Desktop\rtos-can-bldc-motor-control\03_python\BLDC_TF4.txt', delimiter=',') 
except:
    data = np.loadtxt(r'C:\Users\leesc\Desktop\rtos-can-bldc-motor-control\03_python\BLDC_TF4.txt')

t_data = data[:, 0]  # 시간 (s)
y_data = data[:, 1]  # 출력 속도 (rad/s)

# 입력값 정의 (BLDC 모터의 q축 전류 지령값)
Iq_ref = 0.2

# 2. 1차 시스템 계단 응답 함수 정의
# y(t) = K * Iq_ref * (1 - exp(-t / tau))
# (BLDC 모터의 기계적 동특성: J*dw/dt + B*w = Kt*Iq 를 1차 시스템으로 근사)
def first_order_step(t, k, tau):
    return k * Iq_ref * (1 - np.exp(-t / tau))

# 3. Curve Fitting (k와 tau 추정)
# p0는 초기 추측값 [k, tau] 입니다.
initial_guess = [y_data[-1] / Iq_ref, 0.5] 
popt, pcov = curve_fit(first_order_step, t_data, y_data, p0=initial_guess)

k_est, tau_est = popt
print(f"추정된 이득 (k): {k_est:.4f} [(rad/s)/A]")
print(f"추정된 시상수 (tau): {tau_est:.4f} [s]")
print(f"전달함수 G(s) = {k_est:.4f} / ({tau_est:.4f}s + 1)")

# 4. 결과 시각화
plt.figure(figsize=(10, 6))
plt.plot(t_data, y_data, 'b.', label='Experimental Data', alpha=0.5)
plt.plot(t_data, first_order_step(t_data, *popt), 'r-', 
         label=f'Fitted Model: k={k_est:.2f}, tau={tau_est:.2f}', linewidth=2)

# 정상상태 및 시상수 지점 표시 (약 63.2% 도달 지점)
steady_state = k_est * Iq_ref
plt.axhline(y=steady_state, color='g', linestyle='--', label='Steady State')
plt.axvline(x=tau_est, color='orange', linestyle='--', label='Time Constant (tau)')

plt.title('BLDC Motor Speed Step Response (Iq_ref = 0.1 A)')
plt.xlabel('Time [s]')
plt.ylabel('Speed [rad/s]')
plt.legend()
plt.grid(True)
plt.show()