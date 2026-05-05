k = 2.4528; %rad/s
tau = 0.1402;
Ts = 0.001;

Ws = 50; %PI 속도제어 극점 -50
s = tf('s'); 
G = k / (tau*s + 1)

% PI 이득 계산 (극점-영점 상쇄 기법)
Kp = (tau * Ws) / k;
Ki = Kp / tau;

% P 위치제어 이득 (극점-5)
K1 = 5;
