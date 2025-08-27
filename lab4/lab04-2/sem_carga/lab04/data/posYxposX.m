% Leia os dados do arquivo, ignorando o cabeçalho
data = dlmread('pos_or_log.txt', ',', 1, 0); % Ignora a primeira linha (cabeçalho)

% Separar as colunas
tempo = data(:, 1);      % Coluna 1: Tempo
posX = data(:, 2);       % Coluna 2: Posição X
posY = data(:, 3);       % Coluna 3: Posição Y
orientacao = data(:, 4); % Coluna 4: Orientação

% Filtrar os dados a partir de tempo >= 0.03000
filtro = tempo >= 0.03000;
tempo = tempo(filtro);
posX = posX(filtro);
posY = posY(filtro);
orientacao = orientacao(filtro);

% Plotar PosX (eixo X) versus PosY (eixo Y) em uma figura separada
figure;
plot(posX, posY, '-o', 'LineWidth', 1.5);
xlabel('Posição X');
ylabel('Posição Y');
title('Trajetória');
grid on;

% Plotar a Orientação ao longo do Tempo em uma figura separada
figure;
plot(tempo, orientacao, '-o', 'LineWidth', 1.5);
xlabel('Tempo (s)');
ylabel('Orientação (rad)');
title('Orientação ao longo do Tempo');
grid on;

% Exibir os primeiros 10 valores filtrados para conferência
disp('Primeiros 10 valores dos dados filtrados:');
disp(table(tempo(1:2000), posX(1:2000), posY(1:2000), orientacao(1:2000), ...
    'VariableNames', {'Tempo', 'Posicao_X', 'Posicao_Y', 'Orientacao'}));

