clear all; close all; clc

% clap_length = 20000;
% closed_hh_length = 10000;
% open_hh_length = 10000;
% kick_length = 40000;
% rimshot_length = 10000;
% hitom_length = 40000;
% midtom_length = 40000;
% lowtom_length = 40000;
volume = 0.3;

clap_length      = 40000;
closed_hh_length = 40000;
open_hh_length   = 40000;
kick_length      = 40000;
rimshot_length   = 40000;
hitom_length     = 40000;
midtom_length    = 40000;
lowtom_length    = 40000;



%% CLAP
[clap,clap_SR] = audioread('909_Clap.wav');
% sound(clap,clap_SR);
clap = clap';
clap = clap(1,1:clap_length);
clap = clap(1:4:end);
%sound(clap,clap_SR/4);

startval = 200;
clap = clap(startval:length(clap));
clap(1) = 0;

clap(10000-startval:10000) = 0;

max_clap = max(clap);
clap = volume*(clap/max_clap);
clap = clap + 1;
figure(1);
plot(clap); grid on
title('Clap');
pause(1);

%% CLOSED HIHAT
[closed_hh,closed_hh_SR] = audioread('909_ClosedHihat.wav');
%sound(closed_hh,closed_hh_SR);
closed_hh = closed_hh';
closed_hh = closed_hh(1,1:closed_hh_length);
closed_hh = closed_hh(1:4:end);

startval = 138;
closed_hh = closed_hh(startval:length(closed_hh));
closed_hh(1) = 0;
closed_hh(10000-startval:10000) = 0;

max_closed_hh = max(closed_hh);
closed_hh = volume*(closed_hh/max_closed_hh);
closed_hh = closed_hh + 1;
figure(2);
plot(closed_hh); grid on
title('Closed Hihat');
pause(1)

%% OPEN HIHAT
[open_hh,open_hh_SR] = audioread('909_OpenHihat.wav');
%sound(open_hh,open_hh_SR);
open_hh = open_hh';
open_hh = open_hh(1,1:open_hh_length);
open_hh = open_hh(1:4:end);

startval = 190;
open_hh = open_hh(startval:length(open_hh));
open_hh(1) = 0;
open_hh(10000-startval:10000) = 0;

max_open_hh = max(open_hh);
open_hh = volume*(open_hh/max_open_hh);
open_hh = open_hh + 1;
figure(3);
plot(open_hh); grid on
title('Open Hihat');
pause(1)

%% KICK
[kick,kick_SR] = audioread('909_Kick.wav');
% sound(kick,kick_SR);
kick = kick';
kick = kick(1,1:kick_length);
kick = kick(1:4:end);

startval = 100;
kick = kick(startval:length(kick));
kick(1) = 0;
kick(10000-startval:10000) = 0;

max_kick = max(kick);
kick = 2*volume*(kick/max_kick);
kick = kick + 1;
figure(4);
plot(kick); grid on
title('Kick');
pause(1)

%% RIMSHOT
[rimshot,rimshot_SR] = audioread('909_Rimshot.wav');
% sound(rimshot,rimshot_SR);
rimshot = rimshot';
rimshot = rimshot(1,1:rimshot_length);
rimshot = rimshot(1:4:end);

startval = 181;
rimshot = rimshot(startval:length(rimshot));
rimshot(1) = 0;
rimshot(10000-startval:10000) = 0;

max_rimshot = max(rimshot);
rimshot = volume*(rimshot/max_rimshot);
rimshot = rimshot + 1;
figure(5);
plot(rimshot); grid on
title('Rimshot');
pause(1)

%% HITOM
[hitom,hitom_SR] = audioread('909_HiTom.wav');
% sound(hitom,hitom_SR);
hitom = hitom';
hitom = hitom(1,1:hitom_length);
hitom = hitom(1:4:end);

startval = 148;
hitom = hitom(startval:length(hitom));
hitom(1) = 0;
hitom(10000-startval:10000) = 0;

max_hitom = max(hitom);
hitom = volume*(hitom/max_hitom);
hitom = hitom + 1;
figure(6);
plot(hitom); grid on
title('Hi-Tom');
pause(1)

%% MIDTOM
[midtom,midtom_SR] = audioread('909_MidTom.wav');
% sound(midtom,midtom_SR);
midtom = midtom';
midtom = midtom(1,1:midtom_length);
midtom = midtom(1:4:end);

startval = 173;
midtom = midtom(startval:length(midtom));
midtom(1) = 0;
midtom(10000-startval:10000) = 0;

max_midtom = max(midtom);
midtom = volume*(midtom/max_midtom);
midtom = midtom + 1;
figure(7);
plot(midtom); grid on
title('Mid-Tom');
pause(1)

%% LOWTOM
[lowtom,lowtom_SR] = audioread('909_LowTom.wav');
% sound(lowtom,lowtom_SR);
lowtom = lowtom';
lowtom = lowtom(1,1:lowtom_length);
lowtom = lowtom(1:4:end);

startval = 174;
lowtom(startval) = 0;
lowtom = lowtom(startval:length(lowtom));
lowtom(1) = 0;
lowtom(10000-startval:10000) = 0;

max_lowtom = max(lowtom);
lowtom = volume*(lowtom/max_lowtom);
lowtom = lowtom + 1;
figure(8);
plot(lowtom); grid on
title('Low-Tom');
pause(1)

%% Dummy txt

fid = fopen('Dummy_40000.txt','w');

for i = 1:40000/4
    
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


%% TXT-file

% clap_length = 20000/4;
% closed_hh_length = 10000/4;
% open_hh_length = 10000/4;
% kick_length = 40000/4;
% rimshot_length = 10000/4;
% hitom_length = 40000/4;
% midtom_length = 40000/4;
% lowtom_length = 40000/4;

clap_length      = 40000/4;
closed_hh_length = 40000/4;
open_hh_length   = 40000/4;
kick_length      = 40000/4;
rimshot_length   = 40000/4;
hitom_length     = 40000/4;
midtom_length    = 40000/4;
lowtom_length    = 40000/4;

%% Rimshot
fid = fopen('909_Rimshot.txt','w');

for i = 1:rimshot_length
    
    a = fprintf(fid,'%1.8f',rimshot(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Kick
fid = fopen('909_Kick.txt','w');

for i = 1:kick_length
    
    a = fprintf(fid,'%1.8f',kick(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Hihat open
fid = fopen('909_OpenHihat.txt','w');

for i = 1:open_hh_length
    
    a = fprintf(fid,'%1.8f',open_hh(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Hihat closed
fid = fopen('909_ClosedHihat.txt','w');

for i = 1:closed_hh_length
    
    a = fprintf(fid,'%1.8f',closed_hh(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Clap
fid = fopen('909_Clap.txt','w');

for i = 1:clap_length
    
    a = fprintf(fid,'%1.8f',clap(i));
    %fprintf(fid,',');
end

fclose(fid);

%% HiTom
fid = fopen('909_HiTom.txt','w');

for i = 1:hitom_length
    
    a = fprintf(fid,'%1.8f',hitom(i));
    %fprintf(fid,',');
end

fclose(fid);


%% MidTom
fid = fopen('909_MidTom.txt','w');

for i = 1:midtom_length
    
    a = fprintf(fid,'%1.8f',midtom(i));
    %fprintf(fid,',');
end

fclose(fid);

%% LowTom
fid = fopen('909_LowTom.txt','w');

for i = 1:lowtom_length
    
    a = fprintf(fid,'%1.8f',lowtom(i));
    %fprintf(fid,',');
end

fclose(fid);

precision = 8;

%% C-file
dlmwrite('wav_LUT.c','#include "wav_LUT.h"','delimiter','', 'precision', precision);

% Clap
dlmwrite('wav_LUT.c','float clap_LUT[] __attribute__ ((section("clap"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',clap,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% Closed Hihat
dlmwrite('wav_LUT.c','float closed_hh_LUT[] __attribute__ ((section("closed_hihat"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',closed_hh,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% Open Hihat
dlmwrite('wav_LUT.c','float open_hh_LUT[] __attribute__ ((section("open_hihat"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',open_hh,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% Kick
dlmwrite('wav_LUT.c','float kick_LUT[] __attribute__ ((section("kick"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',kick,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% Rimshot
dlmwrite('wav_LUT.c','float rimshot_LUT[] __attribute__ ((section("rimshot"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',rimshot,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% HiTom
dlmwrite('wav_LUT.c','float hitom_LUT[] __attribute__ ((section("hitom"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',hitom,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% MidTom
dlmwrite('wav_LUT.c','float midtom_LUT[] __attribute__ ((section("midtom"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',midtom,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

% LowTom
dlmwrite('wav_LUT.c','float lowtom_LUT[] __attribute__ ((section("lowtom"))) = {','delimiter','', 'precision', precision,'-append');
dlmwrite('wav_LUT.c',lowtom,'delimiter',',', 'precision', precision,'-append');
dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');

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
