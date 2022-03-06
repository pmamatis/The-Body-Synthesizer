%% Plot options
options = bodeoptions;
options.PhaseVisible = 'off';
options.FreqUnits = 'Hz';
options.Title.FontSize = 24;
options.XLabel.FontSize = 20;
options.YLabel.FontSize = 20;
options.TickLabel.FontSize = 20;
options.XLim = [1, 5000];
options.YLim = [-60 30];

%% 1) Lowpass

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Güte
alpha = s / (2 * Q);

% Filterkoeffizienten
b0 = (1 - c) / 2;
b1 = 1 - c;
b2 = b0;
a0 = 1 + alpha;
a1 = -2 * c;
a2 = 1 - alpha;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H = tf(numerator,denominator,ts);

% Plot
f1 = figure(1);
%f1.Position = [10 10 1500 750];
subplot(2,2,1)
options.Title.String = 'Tiefpass';
bode(H, options);
grid on

%% 2) Highpass

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Güte
alpha = s / (2 * Q);

% Filterkoeffizienten
b0 = (1 + c) / 2;
b1 = -(1 + c);
b2 = b0;
a0 = 1 + alpha;
a1 = -2 * c;
a2 = 1 - alpha;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H = tf(numerator,denominator,ts);

% Plot
subplot(2,2,2)
options.Title.String = 'Hochpass';
bode(H,options);
grid on

%% 3) BandpassCPG

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Güte
alpha = s / (2 * Q);

% Filterkoeffizienten
b0 = alpha;
b1 = 0;
b2 = -alpha;
a0 = 1 + alpha;
a1 = -2 * c;
a2 = 1 - alpha;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H = tf(numerator,denominator,ts);

% Plot
subplot(2,2,3)
options.Title.String = 'Bandpass CPG';
bode(H,options);
grid on

%% 4) Bandpass CSG

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Güte
alpha = s / (2 * Q);

% Filterkoeffizienten
b0 = Q*alpha;
b1 = 0;
b2 = -Q*alpha;
a0 = 1 + alpha;
a1 = -2 * c;
a2 = 1 - alpha;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H = tf(numerator,denominator,ts);

% Plot
subplot(2,2,4)
options.Title.String = 'Bandpass CSG';
bode(H,options);
grid on

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 5) Notch

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Güte
alpha = s / (2 * Q);

% Filterkoeffizienten
b0 = 1;
b1 = -2 * c;
b2 = 1;
a0 = 1 + alpha;
a1 = -2 * c;
a2 = 1 - alpha;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H = tf(numerator,denominator,ts);

% Plot
f2 = figure(3);
% f2.Position = [10 10 500 250];
subplot(2,2,1)
options.Title.String = 'Notch';
options.YLim = [-45 45];
bode(H,options);
grid on

%% 6) Peaking EQ pos. Gain

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;
dBGain = 20;

% Gain umrechnen
exp = (dBGain) / 40.0;
A = 10^(exp);

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Güte
alpha = s / (2 * Q);

% Filterkoeffizienten
b0 = 1 + alpha * A;
b1 = -2 * c;
b2 = 1 - alpha * A;
a0 = 1 + alpha / A;
a1 = -2 * c;
a2 = 1 - alpha / A;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H1 = tf(numerator,denominator,ts);


%% 6) Peaking EQ neg. Gain

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;
dBGain = -20;

% Gain umrechnen
exp = (dBGain) / 40.0;
A = 10^(exp);

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Güte
alpha = s / (2 * Q);

% Filterkoeffizienten
b0 = 1 + alpha * A;
b1 = -2 * c;
b2 = 1 - alpha * A;
a0 = 1 + alpha / A;
a1 = -2 * c;
a2 = 1 - alpha / A;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H2 = tf(numerator,denominator,ts);

% Plot
subplot(2,2,2)
options.Title.String = 'Peaking EQ';
bode(H1, H2, options);
legend('G = +20dB', 'G = -20dB');
grid on

%% 7) Lowshelf pos. Gain

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;
dBGain = 20;

% Gain umrechnen
exp = (dBGain) / 40.0;
A = 10^(exp);

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Gain / Güte
beta  = sqrt(A)/Q;

% Filterkoeffizienten
b0 =     A * ((A + 1) - (A - 1) * c + beta * s);
b1 = 2 * A * ((A - 1) - (A + 1) * c);
b2 =     A * ((A + 1) - (A - 1) * c - beta * s);
a0 =          (A + 1) + (A - 1) * c + beta * s;
a1 =    -2 * ((A - 1) + (A + 1) * c);
a2 =          (A + 1) + (A - 1) * c - beta * s;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H1 = tf(numerator,denominator,ts);


%% 7) Lowshelf neg. Gain

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;
dBGain = -20;

% Gain umrechnen
exp = (dBGain) / 40.0;
A = 10^(exp);

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Gain / Güte
beta  = sqrt(A)/Q;

% Filterkoeffizienten
b0 =     A * ((A + 1) - (A - 1) * c + beta * s);
b1 = 2 * A * ((A - 1) - (A + 1) * c);
b2 =     A * ((A + 1) - (A - 1) * c - beta * s);
a0 =          (A + 1) + (A - 1) * c + beta * s;
a1 =    -2 * ((A - 1) + (A + 1) * c);
a2 =          (A + 1) + (A - 1) * c - beta * s;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H2 = tf(numerator,denominator,ts);

% Plot
subplot(2,2,3)
options.Title.String = 'Lowshelf';
bode(H1, H2,options);
legend('G = +20dB', 'G = -20dB');
grid on

%% 8) Highshelf pos. Gain

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;
dBGain = 20;

% Gain umrechnen
exp = (dBGain) / 40.0;
A = 10^(exp);

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Gain / Güte
beta  = sqrt(A)/Q;

% Filterkoeffizienten
b0 =      A * ((A + 1) + (A - 1) * c + beta * s);
b1 = -2 * A * ((A - 1) + (A + 1) * c);
b2 =      A * ((A + 1) + (A - 1) * c - beta * s);
a0 =           (A + 1) - (A - 1) * c + beta * s;
a1 =      2 * ((A - 1) - (A + 1) * c);
a2 =           (A + 1) - (A - 1) * c - beta * s;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H1 = tf(numerator,denominator,ts);


%% 8) Highshelf neg. Gain

% Parameter
Q = 0.707;
cutoff = 100;
samplerate = 24000;
dBGain = -20;

% Gain umrechnen
exp = (dBGain) / 40.0;
A = 10^(exp);

% Einbindung Cutoff-Frequenz
w = 2 * pi * cutoff / samplerate;
s = sin(w);
c = cos(w);

% Einbindung Gain / Güte
beta  = sqrt(A)/Q;

% Filterkoeffizienten
b0 =      A * ((A + 1) + (A - 1) * c + beta * s);
b1 = -2 * A * ((A - 1) + (A + 1) * c);
b2 =      A * ((A + 1) + (A - 1) * c - beta * s);
a0 =           (A + 1) - (A - 1) * c + beta * s;
a1 =      2 * ((A - 1) - (A + 1) * c);
a2 =           (A + 1) - (A - 1) * c - beta * s;

% Übertragungsfunktion
numerator   = [b0, b1, b2];
denominator = [a0, a1, a2];
ts = 1/samplerate;
H2 = tf(numerator,denominator,ts);

% Plot
subplot(2,2,4)
options.Title.String = 'Highshelf';
bode(H1, H2 ,options);
legend('G = +20dB', 'G = -20dB');
grid on