close all; clc

hh_length    = 20000;
kick_length  = 20000;
snare_length = 20000;
ride_length  = 20000;

SR = 48000;

%% HIHAT
[hh,hh_SR] = audioread('Rock_loud_Hihat.wav');

[P,Q] = rat(SR/hh_SR);
hh = resample(hh,P,Q);

hh_cut = zeros(1,20000);
for i = 1:length(hh)
   
    hh_cut(i) = hh(i);
end

sound(hh_cut,SR);
hh_cut = hh_cut(1,1:hh_length);
hh_cut = hh_cut(1:2:end);
hh_cut = hh_cut + 1;
figure(1);
plot(hh_cut'); grid on
title('Hihat');
pause(1)

%% KICK
[kick,kick_SR] = audioread('Rock_loud_Kick.wav');

[P,Q] = rat(SR/kick_SR);
kick = resample(kick,P,Q);

kick_cut = zeros(1,20000);
for i = 1:length(kick)
   
    kick_cut(i) = kick(i);
end

%sound(kick_cut,kick_cut_SR);
kick_cut = kick_cut(1,1:kick_length);
kick_cut = kick_cut(1:2:end);
kick_cut = kick_cut + 1;
figure(2);
plot(kick_cut'); grid on
title('Kick');
pause(1)

%% Ride
[ride,ride_SR] = audioread('Rock_loud_Ride.wav');

[P,Q] = rat(SR/ride_SR);
ride = resample(ride,P,Q);

ride_cut = zeros(1,20000);
for i = 1:length(ride)
   
    ride_cut(i) = ride(i);
end

%sound(ride_cut,ride_cut_SR);
ride_cut = ride_cut(1,1:ride_length);
ride_cut = ride_cut(1:2:end);
ride_cut = ride_cut + 1;
figure(3);
plot(ride_cut'); grid on
title('Hihat');
pause(1)

%% Snare
[snare,snare_SR] = audioread('Rock_loud_Snare.wav');

[P,Q] = rat(SR/snare_SR);
snare = resample(snare,P,Q);

snare_cut = zeros(1,20000);
for i = 1:length(snare)
   
    snare_cut(i) = snare(i);
end

%sound(snare_cut,snare_cut_SR);
snare_cut = snare_cut(1,1:snare_length);
snare_cut = snare_cut(1:2:end);
snare_cut = snare_cut + 1;
figure(4);
plot(snare_cut'); grid on
title('Snare');
pause(1)


%% Dummy txt

fid = fopen('DummyZero.txt','w');

for i = 1:20000/2
    
    a = fprintf(fid,'%.f',0);
    fprintf(fid,',');
end

fclose(fid);

% fid = fopen('Dummy_20000.txt','w');
% 
% for i = 1:20000/4
%     
%     a = fprintf(fid,'%.f',0);
%     fprintf(fid,',');
% end
% 
% fclose(fid);
% 
% fid = fopen('Dummy_10000.txt','w');
% 
% for i = 1:10000/4
%     
%     a = fprintf(fid,'%.f',0);
%     fprintf(fid,',');
% end
% 
% fclose(fid);
% %%%%%%
% 
%% TXT-file

hh_length    = 20000/2;
kick_length  = 20000/2;
snare_length = 20000/2;
ride_length  = 20000/2;


%% Hihat
fid = fopen('Rock_loud_Hihat.txt','w');

for i = 1:hh_length
    
    a = fprintf(fid,'%1.8f',hh_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Kick
fid = fopen('Rock_loud_Kick.txt','w');

for i = 1:kick_length
    
    a = fprintf(fid,'%1.8f',kick_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Ride
fid = fopen('Rock_loud_Ride.txt','w');

for i = 1:ride_length
    
    a = fprintf(fid,'%1.8f',ride_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Snare
fid = fopen('Rock_loud_Snare.txt','w');

for i = 1:snare_length
    
    a = fprintf(fid,'%1.8f',snare_cut(i));
    %fprintf(fid,',');
end

 fclose(fid);

%%  
% 
% precision = 8;
% 
% %% C-file
% dlmwrite('wav_LUT.c','#include "wav_LUT.h"','delimiter','', 'precision', precision);
% 
% % Clap
% dlmwrite('wav_LUT.c','float clap_LUT[] __attribute__ ((section("clap"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',clap,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % Closed Hihat
% dlmwrite('wav_LUT.c','float closed_hh_LUT[] __attribute__ ((section("closed_hihat"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',closed_hh,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % Open Hihat
% dlmwrite('wav_LUT.c','float open_hh_LUT[] __attribute__ ((section("open_hihat"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',open_hh,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % Kick
% dlmwrite('wav_LUT.c','float kick_LUT[] __attribute__ ((section("kick"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',kick,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % Rimshot
% dlmwrite('wav_LUT.c','float rimshot_LUT[] __attribute__ ((section("rimshot"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',rimshot,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % HiTom
% dlmwrite('wav_LUT.c','float hitom_LUT[] __attribute__ ((section("hitom"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',hitom,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % MidTom
% dlmwrite('wav_LUT.c','float midtom_LUT[] __attribute__ ((section("midtom"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',midtom,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % LowTom
% dlmwrite('wav_LUT.c','float lowtom_LUT[] __attribute__ ((section("lowtom"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',lowtom,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% %% H-file
% %include Guard
% dlmwrite('wav_LUT.h','#ifndef INC_WAV_LUT_H_','delimiter','', 'precision', precision);
% dlmwrite('wav_LUT.h','#define INC_WAV_LUT_H_','delimiter','', 'precision', precision,'-append')
% dlmwrite('wav_LUT.h','//includes ','delimiter','', 'precision', precision,'-append');
% 
% % defines
% dlmwrite('wav_LUT.h','//defines ','delimiter','', 'precision', precision,'-append');
% % Clap SR
% dlmwrite('wav_LUT.h',['#define CLAP_SR ',num2str(clap_SR)],'delimiter','', 'precision', precision,'-append');
% % Closed Hihat SR
% dlmwrite('wav_LUT.h',['#define CLOSED_HH_SR ',num2str(closed_hh_SR)],'delimiter','', 'precision', precision,'-append');
% % Open Hihat SR
% dlmwrite('wav_LUT.h',['#define OPEN_HH_SR ',num2str(open_hh_SR)],'delimiter','', 'precision', precision,'-append');
% % Kick SR
% dlmwrite('wav_LUT.h',['#define KICK_SR ',num2str(kick_SR)],'delimiter','', 'precision', precision,'-append');
% 
% %variables
% dlmwrite('wav_LUT.h','//variables','delimiter','', 'precision', precision,'-append');
% % Clap LUT
% dlmwrite('wav_LUT.h',['float clap_LUT[',num2str(length(clap)),'];'],'delimiter','', 'precision', precision,'-append');
% % Closed Hihat LUT
% dlmwrite('wav_LUT.h',['float closed_hh_LUT[',num2str(length(closed_hh)),'];'],'delimiter','', 'precision', precision,'-append');
% % Open Hihat LUT
% dlmwrite('wav_LUT.h',['float open_hh_LUT[',num2str(length(open_hh)),'];'],'delimiter','', 'precision', precision,'-append');
% % Kick LUT
% dlmwrite('wav_LUT.h',['float kick_LUT[',num2str(length(kick)),'];'],'delimiter','', 'precision', precision,'-append');
% % Rimshot LUT
% dlmwrite('wav_LUT.h',['float rimshot_LUT[',num2str(length(rimshot)),'];'],'delimiter','', 'precision', precision,'-append');
% % Hi Tom LUT
% dlmwrite('wav_LUT.h',['float hitom_LUT[',num2str(length(hitom)),'];'],'delimiter','', 'precision', precision,'-append');
% % Mid Tom LUT
% dlmwrite('wav_LUT.h',['float midtom_LUT[',num2str(length(midtom)),'];'],'delimiter','', 'precision', precision,'-append');
% % Low Tom LUT
% dlmwrite('wav_LUT.h',['float lowtom_LUT[',num2str(length(lowtom)),'];'],'delimiter','', 'precision', precision,'-append');
% 
% dlmwrite('wav_LUT.h','#endif','delimiter','', 'precision', precision,'-append');
