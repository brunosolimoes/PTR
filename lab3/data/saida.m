% Carregar o arquivo CSV
data = csvread('saida.txt', 1, 0); % Ignorar a primeira linha (cabeçalho)

% Separar os vetores seno, cosseno e ângulo
seno = data(:, 1);      % Primeira coluna
cosseno = data(:, 2);   % Segunda coluna
angulo = data(:, 3);    % Terceira coluna

% Gerar gráficos
figure;

% Gráfico de cosseno e seno
subplot(2, 1, 1);
plot(seno, 'r', 'DisplayName', 'X'); hold on;
plot(cosseno, 'b', 'DisplayName', 'Y');
title('Gráfico de Yf');
xlabel('Índice');
ylabel('Valor');
legend show;
grid on;


disp('Gráficos gerados com sucesso.');

