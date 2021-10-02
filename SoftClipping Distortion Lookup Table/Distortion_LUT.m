clear all; close all; clc

% atan lookup-table generation
blocksize = 8192;
max_distortion_gain = 10;
values = linspace(-max_distortion_gain, max_distortion_gain, blocksize);
aquidistance = (2*max_distortion_gain) / (blocksize-1);
atan_LUT = atan(values);
atan_LUT_rounded = round(atan_LUT,4);  % runden und transponieren
tt = 1:blocksize;
figure(1)
plot(tt, atan_LUT_rounded); grid on
csvwrite('atan_LUT_y.txt',atan_LUT_rounded)
csvwrite('atan_LUT_x.txt',values)
dlmwrite('aquidistance.txt', aquidistance, 'delimiter', ',', 'precision', 15);