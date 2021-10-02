close all; clc

Error_length           = 20000;
Chord_length           = 20000;
Critical_Stop_length   = 20000;
Recycle_length         = 20000;
Hardware_Remove_length = 20000;
Background_length      = 20000;

SR = 48000;

%% Windows Error
[Error,Error_SR] = audioread('Windows_Error.wav');

[P,Q] = rat(SR/Error_SR);
Error = resample(Error,P,Q);

startval = 2*260;
Error = Error(startval:length(Error));

Error_cut = zeros(1,20000);

for i = 1:length(Error)
   
    Error_cut(i) = Error(i);
end

Error_cut = Error_cut(1,1:Error_length);
Error_cut = Error_cut(1:2:end);
Error_cut = Error_cut + 1;

endval = 9989;
Error_cut(endval:length(Error_cut)) = 0;


% sound(Error_cut,SR/2);

figure(1);
plot(Error_cut'); grid on
title('Error');
pause(1)

%% Windows Chord
[Chord,Chord_SR] = audioread('Windows_Chord.wav');

[P,Q] = rat(SR/Chord_SR);
Chord = resample(Chord,P,Q);

startval = 2*470;
Chord = Chord(startval:length(Chord));

Chord_cut = zeros(1,20000);

for i = 1:length(Chord)
   
    Chord_cut(i) = Chord(i);
end

Chord_cut = Chord_cut(1,1:Chord_length);
Chord_cut = Chord_cut(1:2:end);
Chord_cut = Chord_cut + 1;

% sound(Chord_cut,SR/2);

figure(1);
plot(Chord_cut'); grid on
title('Chord');
pause(1)

%% Windows Critical Stop
[Critical_Stop,Critical_Stop_SR] = audioread('Windows_Critical_Stop.wav');

[P,Q] = rat(SR/Critical_Stop_SR);
Critical_Stop = resample(Critical_Stop,P,Q);

startval = 2*610;
Critical_Stop = Critical_Stop(startval:length(Critical_Stop));
Critical_Stop(1) = 0;

Critical_Stop_cut = zeros(1,20000);

for i = 1:length(Critical_Stop)
   
    Critical_Stop_cut(i) = Critical_Stop(i);
end

Critical_Stop_cut = Critical_Stop_cut(1,1:Critical_Stop_length);
Critical_Stop_cut = Critical_Stop_cut(1:2:end);
Critical_Stop_cut = Critical_Stop_cut + 1;

endval = 9956;
Critical_Stop_cut(endval:length(Critical_Stop_cut)) = 0;

% sound(Critical_Stop_cut,SR/2);

figure(1);
plot(Critical_Stop_cut'); grid on
title('Critical_Stop');
pause(1)

%% Windows Recycle
[Recycle,Recycle_SR] = audioread('Windows_Recycle.wav');

[P,Q] = rat(SR/Recycle_SR);
Recycle = resample(Recycle,P,Q);

startval = 2*120;
Recycle = Recycle(startval:length(Recycle));

Recycle_cut = zeros(1,20000);

for i = 1:length(Recycle)
   
    Recycle_cut(i) = Recycle(i);
end

Recycle_cut = Recycle_cut(1,1:Recycle_length);
Recycle_cut = Recycle_cut(1:2:end);
Recycle_cut = Recycle_cut + 1;

% sound(Recycle_cut,SR/2);

figure(1);
plot(Recycle_cut'); grid on
title('Recycle');
pause(1)

%% Windows Hardware Remove
[Hardware_Remove,Hardware_Remove_SR] = audioread('Windows_Hardware_Remove.wav');

[P,Q] = rat(SR/Hardware_Remove_SR);
Hardware_Remove = resample(Hardware_Remove,P,Q);

startval = 2*264;
Hardware_Remove = Hardware_Remove(startval:length(Hardware_Remove));

Hardware_Remove_cut = zeros(1,20000);

for i = 1:length(Hardware_Remove)
   
    Hardware_Remove_cut(i) = Hardware_Remove(i);
end

Hardware_Remove_cut = Hardware_Remove_cut(1,1:Hardware_Remove_length);
Hardware_Remove_cut = Hardware_Remove_cut(1:2:end);
Hardware_Remove_cut = Hardware_Remove_cut + 1;

endval = 9979;
Hardware_Remove_cut(endval:length(Hardware_Remove_cut)) = 0;

% sound(Hardware_Remove_cut,SR/2);

figure(1);
plot(Hardware_Remove_cut'); grid on
title('Hardware_Remove');
pause(1)

%% Windows Background
[Background,Background_SR] = audioread('Windows_Background.wav');

[P,Q] = rat(SR/Background_SR);
Background = resample(Background,P,Q);

startval = 2*890;
Background(2*890) = 0;
Background = Background(startval:length(Background));

Background_cut = zeros(1,20000);

for i = 1:length(Background)
   
    Background_cut(i) = Background(i);
end

Background_cut = Background_cut(1,1:Background_length);
Background_cut = Background_cut(1:2:end);
Background_cut = Background_cut + 1;

endval = 9982;
Background_cut(endval:length(Background_cut)) = 0;

% sound(Background_cut,SR/2);

figure(1);
plot(Background_cut'); grid on
title('Background');
pause(1)

%% Dummy txt

fid = fopen('DummyZero.txt','w');

for i = 1:20000/2
    
    a = fprintf(fid,'%.f',0);
    fprintf(fid,',');
end

fclose(fid);

%% TXT-file

Error_length           = 20000/2;
Chord_length           = 20000/2;
Critical_Stop_length   = 20000/2;
Recycle_length         = 20000/2;
Hardware_Remove_length = 20000/2;
Background_length      = 20000/2;

%% Windows Error
fid = fopen('Windows_Error.txt','w');

for i = 1:Error_length
    
    a = fprintf(fid,'%1.8f',Error_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Windows Chord
fid = fopen('Windows_Chord.txt','w');

for i = 1:Chord_length
    
    a = fprintf(fid,'%1.8f',Chord_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Windows Critical Stop
fid = fopen('Windows_Critical_Stop.txt','w');

for i = 1:Critical_Stop_length
    
    a = fprintf(fid,'%1.8f',Critical_Stop_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Windows Recycle
fid = fopen('Windows_Recycle.txt','w');

for i = 1:Recycle_length
    
    a = fprintf(fid,'%1.8f',Recycle_cut(i));
    %fprintf(fid,',');
end

fclose(fid);
%% Windows Hardware Remove
fid = fopen('Windows_Hardware_Remove.txt','w');

for i = 1:Hardware_Remove_length
    
    a = fprintf(fid,'%1.8f',Hardware_Remove_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%% Windows Background
fid = fopen('Windows_Background.txt','w');

for i = 1:Background_length
    
    a = fprintf(fid,'%1.8f',Background_cut(i));
    %fprintf(fid,',');
end

fclose(fid);

%%
%% WRITE OUT HEADER / C
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
% dlmwrite('wav_LUT.c','float closed_Error_LUT[] __attribute__ ((section("closed_hihat"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',closed_Error,'delimiter',',', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c','};','delimiter','', 'precision', precision,'-append');
% 
% % Open Hihat
% dlmwrite('wav_LUT.c','float open_Error_LUT[] __attribute__ ((section("open_hihat"))) = {','delimiter','', 'precision', precision,'-append');
% dlmwrite('wav_LUT.c',open_Error,'delimiter',',', 'precision', precision,'-append');
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
% dlmwrite('wav_LUT.h',['#define CLOSED_Error_SR ',num2str(closed_Error_SR)],'delimiter','', 'precision', precision,'-append');
% % Open Hihat SR
% dlmwrite('wav_LUT.h',['#define OPEN_Error_SR ',num2str(open_Error_SR)],'delimiter','', 'precision', precision,'-append');
% % Kick SR
% dlmwrite('wav_LUT.h',['#define KICK_SR ',num2str(kick_SR)],'delimiter','', 'precision', precision,'-append');
% 
% %variables
% dlmwrite('wav_LUT.h','//variables','delimiter','', 'precision', precision,'-append');
% % Clap LUT
% dlmwrite('wav_LUT.h',['float clap_LUT[',num2str(length(clap)),'];'],'delimiter','', 'precision', precision,'-append');
% % Closed Hihat LUT
% dlmwrite('wav_LUT.h',['float closed_Error_LUT[',num2str(length(closed_Error)),'];'],'delimiter','', 'precision', precision,'-append');
% % Open Hihat LUT
% dlmwrite('wav_LUT.h',['float open_Error_LUT[',num2str(length(open_Error)),'];'],'delimiter','', 'precision', precision,'-append');
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
