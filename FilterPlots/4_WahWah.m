%% Plot options
options = bodeoptions;
options.PhaseVisible = 'off';
options.FreqUnits = 'Hz';
options.Title.FontSize = 24;
options.XLabel.FontSize = 20;
options.YLabel.FontSize = 20;
options.TickLabel.FontSize = 20;
options.XLim = [1, 5000];
options.YLim = [-40 5];

QIteration = [0.707 1.414 3 6 12 20];

%% For several Qs
for i = 1:length(QIteration)

%% 3) BandpassCPG

% Parameter
Q = QIteration(i);
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
H1(i) = tf(numerator,denominator,ts);

end

%% Plot

% Plot
figure(1);
%f1.Position = [10 10 1500 750];
options.Title.String = strcat('WahWah CPG Bandpass-Filter, Güte Q variiert');

bode(H1(1), H1(2), H1(3), H1(4), H1(5), H1(6), options);
legend('Q = 0.707', 'Q = 1.414', 'Q = 3', 'Q = 6', 'Q = 12', 'Q = 20');

grid on

%% 
CutoffIteration = [20 50 100 200 500];

%% For several Qs
for i = 1:length(CutoffIteration)

%% 3) BandpassCPG

% Parameter
Q = 3;
cutoff = CutoffIteration(i);
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
H1(i) = tf(numerator,denominator,ts);

end

%% Plot

% Plot
figure(2);
%f1.Position = [10 10 1500 750];
options.Title.String = strcat('WahWah CPG Bandpass-Filter, Q = 3, Mittenfrequenz variiert');

bode(H1(1), H1(2), H1(3), H1(4), H1(5), options);
legend('f = 20 Hz', 'f = 50 Hz','f = 100 Hz','f = 200 Hz','f = 500 Hz');

grid on

