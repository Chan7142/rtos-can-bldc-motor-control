import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# 1. 데이터 로드 (파일 포맷에 따라 구분자 확인 필요)
# 메모장에 '시간, 속도' 형태로 저장되어 있다고 가정합니다.
# 구분자가 공백이면 delimiter=None, 쉼표면 delimiter=','
try:
    data = np.loadtxt('DC_motor_transfer.txt', delimiter=',') 
except:
    data = np.loadtxt('DC_motor_transfer.txt')

t_data = data[:, 0]  # 시간 (0.01, 0.02, ...)
y_data = data[:, 1]  # 출력 속도 (rad/s)

# 입력값 정의 (motor_input(6) 이었으므로 6으로 설정)
u_input = 6.0

# 2. 1차 시스템 계단 응답 함수 정의
# y(t) = K * u * (1 - exp(-t / tau))
def first_order_step(t, k, tau):
    return k * u_input * (1 - np.exp(-t / tau))

# 3. Curve Fitting (k와 tau 추정)
# p0는 초기 추측값 [k, tau] 입니다.
initial_guess = [y_data[-1]/u_input, 0.5] 
popt, pcov = curve_fit(first_order_step, t_data, y_data, p0=initial_guess)

k_est, tau_est = popt
print(f"추정된 이득 (k): {k_est:.4f}")
print(f"추정된 시상수 (tau): {tau_est:.4f}")
print(f"전달함수 G(s) = {k_est:.4f} / ({tau_est:.4f}s + 1)")

# 4. 결과 시각화
plt.figure(figsize=(10, 6))
plt.plot(t_data, y_data, 'b.', label='Experimental Data', alpha=0.5)
plt.plot(t_data, first_order_step(t_data, *popt), 'r-', 
         label=f'Fitted Model: k={k_est:.2f}, tau={tau_est:.2f}', linewidth=2)

# 시상수 지점 표시 (약 63.2% 도달 지점)
steady_state = k_est * u_input
plt.axhline(y=steady_state, color='g', linestyle='--', label='Steady State')
plt.axvline(x=tau_est, color='orange', linestyle='--', label='Time Constant (tau)')

plt.title('Motor Speed Step Response & System Identification')
plt.xlabel('Time [s]')
plt.ylabel('Speed [rad/s]')
plt.legend()
plt.grid(True)
plt.show()