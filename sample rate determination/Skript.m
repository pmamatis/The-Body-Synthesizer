
f_soll = 96000;
blocksize = 19200;

%% 9.6MHz
% figure(1)
% plot(beginning9_6.Times,beginning9_6.Channel1V);
% title('anfang');
% grid;
% grid minor
% figure(2)
% plot(end9_6.Times,end9_6.Channel1V);
% title('ende');
% grid;
% grid minor

time_beginn_96 = 0.2003;
time_end_96 = 0.3994;
time_96 = time_end - time_beginn;
f_96 = 1/time;

SR_96 = blocksize*f;
Fehler_96 = (1-f_soll/SR_96)*100
%% 108MHz
% figure(1)
% plot(beginning.Times,beginning.Channel1V_begin);
% title('anfang');
% grid;
% grid minor
% figure(2)
% plot(xEnd.Times,xEnd.Channel1V_end);
% title('ende');
% grid;
% grid minor


time_beginn = 0.001034;
time_end = 0.2003;
time = time_end - time_beginn;
f = 1/time;
SR = blocksize*f;
Fehler = (1-f_soll/SR)*100