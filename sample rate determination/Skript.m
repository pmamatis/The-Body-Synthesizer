figure(1)
plot(beginning.Times,beginning.Channel1V_begin);
title('anfang');
grid;
grid minor
figure(2)
plot(xEnd.Times,xEnd.Channel1V_end);
title('ende');
grid;
grid minor

time_beginn = 0.001034;
time_end = 0.2003;
time = time_end - time_beginn;
f = 1/time;
f_soll = 96000;
blocksize = 19200;
SR = blocksize*f;
Fehler = (1-f_soll/SR)*100