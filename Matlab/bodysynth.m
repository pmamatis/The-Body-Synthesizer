clock = 108000000;
stuetz = 20;
SR = 96000;
timperiod = clock / SR;

fsignal = 4186;         % C8 
fmax = clock / (timperiod * stuetz);
SR = clock / timperiod;

OS = SR / fsignal;
delta = (1-cos(pi/(SR/fmax)))*100;

fmin = 5;
blocksize = SR / fmin;



