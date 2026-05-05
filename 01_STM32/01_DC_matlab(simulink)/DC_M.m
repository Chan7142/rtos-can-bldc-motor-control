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

%관측기 설계 (전차원)
A = [ 0 1 0; 0 -1/tau 1; 0 0 0];
B = [0; k/tau; 0];
C = [1 0 0]; D = 0;
pole = [ -50, -50, -50];
L = acker(A', C', pole)'
Ao = A-L*C; Bo = [B, L]; Co = eye(3); Do = zeros(3, 2);
sys_cont = ss(Ao, Bo, Co, Do);

sys_disc = c2d(sys_cont, Ts, 'zoh');

Ad = sys_disc.A;
Bd = sys_disc.B;

