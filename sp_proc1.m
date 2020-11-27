function sp_proc1

%()内にファイル名表記
[x,fs]=audioread('1_1.m4a');
t=(0:length(x)-1)/fs;

plot(t,x);
xlabel('Time [s]');
ylabel('Amplitude');
