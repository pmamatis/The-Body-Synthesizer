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

GainIteration = [0 20 -20];

%% For several Gains
for i = 1:3

    %% 7) Lowshelf

    % Parameter
    Q = 0.707;
    cutoff = 200;
    samplerate = 24000;
    dBGain = GainIteration(i);

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

    %% 6) Peaking EQ I

    % Parameter
    Q = 0.707;
    cutoff = 400;
    samplerate = 24000;
    dBGain = GainIteration(i);

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

    %% 6) Peaking EQ II

    % Parameter
    Q = 0.707;
    cutoff = 800;
    samplerate = 24000;
    dBGain = GainIteration(i);

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
    H3 = tf(numerator,denominator,ts);

    %% 6) Peaking EQ III

    % Parameter
    Q = 0.707;
    cutoff = 1600;
    samplerate = 24000;
    dBGain = GainIteration(i);

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
    H4 = tf(numerator,denominator,ts);

    %% 8) Highshelf

    % Parameter
    Q = 0.707;
    cutoff = 3200;
    samplerate = 24000;
    dBGain = GainIteration(i);

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
    H5 = tf(numerator,denominator,ts);



%% Plot

% Plot
figure(i);
%f1.Position = [10 10 1500 750];
options.Title.String = strcat('Equalizer: G = ', {' '}, num2str(GainIteration(i)), 'dB', {' '}, 'für alle 5 Bänder');

if(i == 1) 
    options.YLim = [-5 5];
    bode(H1, options);
    legend('LS + PEQ I + PEQ II + PEQ III + HS');
elseif(i == 2)
    options.YLim = [-5 30];
    bode(H1, H2, H3, H4, H5, options);
    legend('LS', 'PEQ I', 'PEQ II', 'PEQ III', 'HS');
elseif(i == 3)
    options.YLim = [-25 10];
    bode(H1, H2, H3, H4, H5, options);
    legend('LS', 'PEQ I', 'PEQ II', 'PEQ III', 'HS');
end

grid on

end
