clock = 108000000;
stuetz = 10;
SR = 48000;
timperiod = clock / SR;

fsignal = 4186;         % C8
fmax = clock / (timperiod * stuetz);
SR = clock / timperiod;

OS = SR / fsignal;
delta = (1-cos(pi/(SR/fmax)))*100;

%blocksize = 8100;
%fmin = SR / blocksize;

fmin = 5.0184;
blocksize = SR / fmin;

DAC_max = 0;


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



