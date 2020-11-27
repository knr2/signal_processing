function sp_proc1

%
% 音声処理
% 横軸は時間
%
%

[x,fs]=audioread('1_1.m4a');
t=(0:length(x)-1)/fs;

plot(t,x);
xlabel('Time [s]');
ylabel('Amplitude');