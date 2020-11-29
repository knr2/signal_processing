function sp_proc3

%()内にファイル名表記
[x,fs] = audioread("2_3.m4a");
y = fft(x);
n = length(x);
f = (0:n-1)*(fs/n);
power = abs(y).^2/n;

plot(f,power)
xlabel('Frequency')
ylabel('Power')