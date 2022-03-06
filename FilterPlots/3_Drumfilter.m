%% Plot options
options = bodeoptions;
options.PhaseVisible = 'off';
options.FreqUnits = 'Hz';
options.Title.FontSize = 24;
options.XLabel.FontSize = 20;
options.YLabel.FontSize = 20;
options.TickLabel.FontSize = 20;
options.XLim = [10, 11000];
options.YLim = [-30 30];

QIteration = [0.707 1.414 3 6 12 20];

%% For several Gains
for i = 1:length(QIteration)

    %% 7) Lowshelf

    % Parameter
    Q = QIteration(i);
    cutoff = 200;
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
    H1(i) = tf(numerator,denominator,ts);

end

%% Plot

% Plot
figure(1);
%f1.Position = [10 10 1500 750];
options.Title.String = strcat('Drumfilter: G = -20 dB, Güte Q variiert');

options.YLim = [-50 30];
bode(H1(1), H1(2), H1(3), H1(4), H1(5), H1(6), options);
legend('Q = 0.707', 'Q = 1.414', 'Q = 3', 'Q = 6', 'Q = 12', 'Q = 20');

grid on

