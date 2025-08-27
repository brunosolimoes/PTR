% Abrir o arquivo para leitura
fid = fopen('tempo_e_jitter.txt', 'r');

% Ignorar o cabeçalho
fgetl(fid);  % Lê e ignora a primeira linha (cabeçalho)

% Ler o arquivo usando textscan, com separadores por vírgula
dados = textscan(fid, '%s %d %f %f', 'Delimiter', ',');

% Fechar o arquivo
fclose(fid);

% Extrair as colunas de tempo (T(k)) e jitter (Jitter(k))
tempos = dados{3};    % Coluna 3: T(k)
jitters = dados{4};   % Coluna 4: Jitter(k)

% Remover a primeira simulação (índice 1)
tempos = tempos(2:end);
jitters = jitters(2:end);

% Calcular as estatísticas para os tempos de computação (T(k))
media_tempos = mean(tempos);
variancia_tempos = var(tempos);
desvio_padrao_tempos = std(tempos);
maximo_tempos = max(tempos);
minimo_tempos = min(tempos);

% Calcular as estatísticas para os jitters (Jitter(k))
media_jitters = mean(jitters);
variancia_jitters = var(jitters);
desvio_padrao_jitters = std(jitters);
maximo_jitters = max(jitters);
minimo_jitters = min(jitters);

% Criar a tabela comparativa
resultados = [
    media_tempos, media_jitters;
    variancia_tempos, variancia_jitters;
    desvio_padrao_tempos, desvio_padrao_jitters;
    maximo_tempos, maximo_jitters;
    minimo_tempos, minimo_jitters
];

% Abrir o arquivo de saída para escrever os resultados
arquivo = fopen('resultados_tabela.txt', 'w');

% Escrever o cabeçalho da tabela no arquivo
fprintf(arquivo, 'Tabela Comparativa: Média, Variância, Desvio Padrão, Máximo, Mínimo\n');
fprintf(arquivo, '-------------------------------------------------------------\n');
fprintf(arquivo, 'Métrica                | T(k)           | Jitter(k)\n');
fprintf(arquivo, '-------------------------------------------------------------\n');

% Escrever os resultados das estatísticas
fprintf(arquivo, 'Média                 | %.6f        | %.6f\n', media_tempos, media_jitters);
fprintf(arquivo, 'Variância             | %.6f        | %.6f\n', variancia_tempos, variancia_jitters);
fprintf(arquivo, 'Desvio Padrão         | %.6f        | %.6f\n', desvio_padrao_tempos, desvio_padrao_jitters);
fprintf(arquivo, 'Máximo                | %.6f        | %.6f\n', maximo_tempos, maximo_jitters);
fprintf(arquivo, 'Mínimo                | %.6f        | %.6f\n', minimo_tempos, minimo_jitters);

% Fechar o arquivo
fclose(arquivo);

disp('Resultados foram salvos em "resultados_tabela.txt".');

