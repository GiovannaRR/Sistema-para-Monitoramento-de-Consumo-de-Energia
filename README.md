# Sistema de Gerenciamento de Consumo de Energia

Este projeto implementa um sistema em linguagem C para registrar, analisar e gerar relatórios de consumo de energia elétrica. Através deste sistema, é possível armazenar dados de consumo (data, hora, consumo em kWh e custo por kWh), calcular médias (diária, semanal e mensal), identificar picos de consumo, calcular o consumo total e custo estimado, sugerir ações para economia de energia e gerar relatórios detalhados com base nos registros coletados.

## Funcionalidades

- **Registro de Consumo:**  
  Permite a entrada de dados referentes à medição de consumo (data, hora, consumo em kWh e custo por kWh) e armazena essas informações no arquivo `Dados_Consumo.txt`.

- **Cálculo de Médias:**  
  Calcula as médias de consumo:
  - **Média Diária:** Média baseada no consumo de cada registro.
  - **Média Semanal:** Média dos consumos a cada 7 dias.
  - **Média Mensal:** Média dos consumos a cada 30 dias.

- **Identificação de Picos de Consumo:**  
  Analisa os registros para identificar e exibir os momentos em que o consumo ultrapassa 1.5 vezes a média geral, possibilitando a detecção de possíveis picos de uso.

- **Cálculo do Consumo Total e Custo Estimado:**  
  Realiza a soma total do consumo registrado e calcula o custo total estimado com base no valor do kWh informado.

- **Sugestão de Economia de Energia:**  
  Examina os registros de consumo por hora e, caso a média de consumo em determinado horário ultrapasse um limite crítico (acima de 1.5 kWh), gera sugestões de economia que são salvas no arquivo `Sugestoes_Economia.txt`.

- **Geração de Relatório Detalhado:**  
  Cria um relatório diário detalhado, dividindo o consumo em quatro períodos do dia (madrugada, manhã, tarde e noite) e salvando as informações no arquivo `Relatorio_Consumo.txt`.

## Sobre o Projeto

O sistema utiliza uma estrutura de dados (`struct DadosConsumo`) para armazenar os registros de consumo e implementa funções específicas para cada uma das funcionalidades listadas. Através de um menu interativo, o usuário pode selecionar a operação desejada, que é processada recursivamente para manter o fluxo do programa até a opção de saída.

### Exemplo de Execução

A seguir, um exemplo simplificado do fluxo de execução:

```plaintext
============Menu============
1. Registro:
2. Media:
3. Picos de consumo:
4. Consumo total:
5. Sugestao de consumo:
6. Gerar Relatorio Detalhado:
7. Sair:
============================
Selecione uma opcao: 1
