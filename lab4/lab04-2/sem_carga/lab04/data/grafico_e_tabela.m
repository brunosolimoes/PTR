% Limpeza inicial
clear; clc;

% Leitura dos arquivos
data_yk = dlmread('pos_or_log.txt', ',');         % Arquivo com saída do sistema
data_ref = dlmread('registro_ref.txt', ',');     % Arquivo com referências
data_ymx = dlmread('registro_ymx.txt', ',');     % Arquivo com ymx
data_ymy = dlmread('registro_ymy.txt', ',');     % Arquivo com ymy

% Dados do arquivo pos_or_log.txt
tempo_yk = data_yk(:, 1);         % Tempo da saída
posicao_x = data_yk(:, 2);        % Posição X
posicao_y = data_yk(:, 3);        % Posição Y

% Dados do arquivo registro_ref.txt
tempo_ref = data_ref(:, 1);       % Tempo da referência
xref = data_ref(:, 2);            % Referência X
yref = data_ref(:, 3);            % Referência Y

% Dados dos arquivos ymx e ymy
tempo_ymx = data_ymx(:, 1);       % Tempo para ymx
ymx = data_ymx(:, 2);             % Valores de ymx
tempo_ymy = data_ymy(:, 1);       % Tempo para ymy
ymy = data_ymy(:, 2);             % Valores de ymy

% Ajuste de intervalo: considera o horizonte comum de simulação
tempo_comum = intersect(intersect(tempo_yk, tempo_ref), intersect(tempo_ymx, tempo_ymy));

% Interpolação dos dados para alinhar os tempos
xref_interp = interp1(tempo_ref, xref, tempo_comum, 'linear');
yref_interp = interp1(tempo_ref, yref, tempo_comum, 'linear');
ymx_interp = interp1(tempo_ymx, ymx, tempo_comum, 'linear');
ymy_interp = interp1(tempo_ymy, ymy, tempo_comum, 'linear');
posicao_x_interp = interp1(tempo_yk, posicao_x, tempo_comum, 'linear');
posicao_y_interp = interp1(tempo_yk, posicao_y, tempo_comum, 'linear');

% **Parte para gerar os gráficos de xref e yref para um horizonte de 20s**

% Definir o horizonte de simulação (20 segundos)
horizonte_simulacao = 20; % Tempo máximo de 20 segundos
passo_tempo = 0.12;      % Intervalo de amostragem de 0.12s, conforme dados do arquivo
tempo_simulacao = 0:passo_tempo:horizonte_simulacao;

% Interpolar xref e yref para o horizonte de simulação de 20s
xref_simulacao = interp1(tempo_ref, xref, tempo_simulacao, 'linear');
yref_simulacao = interp1(tempo_ref, yref, tempo_simulacao, 'linear');

% Plotar xref ao longo do tempo (20s)
figure;
plot(tempo_simulacao, xref_simulacao, '-o', 'LineWidth', 1.5);
xlabel('Tempo (s)');
ylabel('xref');
title('Gráfico de xref para Horizonte de 20s');
grid on;

% Plotar yref ao longo do tempo (20s)
figure;
plot(tempo_simulacao, yref_simulacao, '-o', 'LineWidth', 1.5);
xlabel('Tempo (s)');
ylabel('yref');
title('Gráfico de yref para Horizonte de 20s');
grid on;

% **Fim da parte de gráficos para xref e yref**

% Novos gráficos: xref vs ymx e yref vs ymy
figure;

% xref vs ymx
subplot(2, 1, 1);
plot(tempo_comum, xref_interp, 'b--', 'LineWidth', 2, 'DisplayName', 'xref');
hold on;
plot(tempo_comum, ymx_interp, 'r-', 'LineWidth', 2, 'DisplayName', 'ymx');
title('Comparação: Referência X (xref) vs Modelo ymx');
xlabel('Tempo (s)');
ylabel('Posição X');
legend show;
grid on;
set(gca, 'LineWidth', 1.5, 'FontSize', 12);

% yref vs ymy
subplot(2, 1, 2);
plot(tempo_comum, yref_interp, 'k--', 'LineWidth', 2, 'DisplayName', 'yref');
hold on;
plot(tempo_comum, ymy_interp, 'g-', 'LineWidth', 2, 'DisplayName', 'ymy');
title('Comparação: Referência Y (yref) vs Modelo ymy');
xlabel('Tempo (s)');
ylabel('Posição Y');
legend show;
grid on;
set(gca, 'LineWidth', 1.5, 'FontSize', 12);

% Ajuste dos limites do eixo Y para garantir que ambos os gráficos sejam visíveis
ylim([min(min(yref_interp), min(ymy_interp)), max(max(yref_interp), max(ymy_interp))]);

% Estatísticas de Posição X e Y
stats_x = [mean(posicao_x_interp), var(posicao_x_interp), std(posicao_x_interp), max(posicao_x_interp), min(posicao_x_interp)];
stats_y = [mean(posicao_y_interp), var(posicao_y_interp), std(posicao_y_interp), max(posicao_y_interp), min(posicao_y_interp)];

% Exibição das estatísticas
fprintf('Estatísticas para Posição X:\n');
fprintf('Média: %.4f, Variância: %.4f, Desvio Padrão: %.4f, Máximo: %.4f, Mínimo: %.4f\n', stats_x);
fprintf('\nEstatísticas para Posição Y:\n');
fprintf('Média: %.4f, Variância: %.4f, Desvio Padrão: %.4f, Máximo: %.4f, Mínimo: %.4f\n', stats_y);
