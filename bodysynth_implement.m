clock = 9600000;
%% Sample Rate (SR)
SR = 96000;
%SR = clock / timperiod;
%% Timer
%timperiod = 167;
timperiod = clock / SR;
%SR = clock / timperiod;
%% Signal
stuetz = 20;
fsignal = 4186;         % C8
fmax = clock / (timperiod * stuetz);
%fmin = SR / blocksize;
fmin = 5.0;


OS = SR / fsignal;
delta = (1-cos(pi/(SR/fmax)))*100;

%blocksize = 8100;


blocksize = SR / fmin;
DAC_max = 0;


%% Filter
cutoff = 100;
PI = 3.14159;
Q = 0.7072;

w0 = tan(PI * cutoff / SR);
N = 1 / (w0 * w0 + w0 / Q + 1);

b0 = N * w0 * w0;
b1 = 2 * b0;
b2 = b0;
a1 = 2 * N * (w0 * w0 - 1);
a2 = N * (w0 * w0 - w0 / Q + 1);



