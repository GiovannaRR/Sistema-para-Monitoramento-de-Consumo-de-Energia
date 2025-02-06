#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 255

    struct DadosConsumo{
        char data[11];
        char hora[6];
        float consumo_kWh;
        float custo_kWh;    
    }RegistroConsumo;

    void Registro(struct DadosConsumo RegistroConsumo[], int *n){

        printf("\n============Dados de Registro da Medicao============\n");
        
        FILE *arquivo = fopen("Dados_Consumo.txt", "a");
        if(arquivo == NULL){
            printf("Erro ao abrir o arquivo para escrita.\n");
            return;
        }

        printf("Digite a data (dd/mm/aaaa):\n");
            getchar();
            fgets(RegistroConsumo[*n].data, sizeof(RegistroConsumo[*n].data), stdin);
            RegistroConsumo[*n].data[strlen(RegistroConsumo[*n].data) ] = '\0';
        printf("Digite a hora (hh:mm):\n");
            getchar();
            fgets(RegistroConsumo[*n].hora, sizeof(RegistroConsumo[*n].hora), stdin); //quando a gente terminar o codigo, colocar um verificador pra hora não ser tipo "42:69"
            RegistroConsumo[*n].hora[strlen(RegistroConsumo[*n].hora) ] = '\0';  // antes da "]" tinha um "-1", não é necessário se o vetor tiver o tamanho exato 
        printf("Digite o consumo em kWh:\n");
            scanf("%f", &RegistroConsumo[*n].consumo_kWh);
        printf("Digite o custo em kWh:\n");
            scanf("%f", &RegistroConsumo[*n].custo_kWh);

        fprintf(arquivo, "%s %s %.2f %.2f\n",
                RegistroConsumo[*n].data,
                RegistroConsumo[*n].hora,
                RegistroConsumo[*n].consumo_kWh,
                RegistroConsumo[*n].custo_kWh);
        (*n)++;

        fclose(arquivo);
        printf("Dados gravados com sucesso no arquivo!...");
    }
    

    void CalculaMedia(struct DadosConsumo RegistroConsumo[], int n){
        float media_diaria = 0, media_semanal = 0, media_mensal = 0;
        float SomaD = 0, SomaS = 0, SomaM = 0;
        int dias = 0, semanas = 0, meses = 0;

        //calcula os dias existentes no vetor
        for(int i = 0; i < n; i++){
            media_diaria += RegistroConsumo[i].consumo_kWh;
            dias++;
        //faz a media caso haja 7 dias
            if(dias % 7 == 0){
                media_semanal += media_diaria;
                semanas++;
                media_diaria = 0;
            }
        //faz a media caso haja 30 dias
            if(dias % 30 == 0){
                media_mensal += media_semanal + media_diaria;
                meses++;
                media_semanal = 0;
            }
        } 

        if(dias > 0){
            SomaD = media_diaria / dias;
        }
        else{
            media_diaria = 0;
        }

        if(semanas > 0){
            SomaS = media_semanal / semanas;
        }
        else{
            media_semanal = 0;
        }

        if(meses > 0){
            SomaM = media_mensal / meses;
        }
        else{
            media_mensal = 0;
        }

        printf("Media diaria: %.2f kWh\n", SomaD);
        printf("Media semanal: %.2f kWh\n", SomaS);
        printf("Media mensal: %.2f kWh\n", SomaM);
    }
    void PicosConsumo(struct DadosConsumo RegistroConsumo[], int n){
        float soma = 0;

        for(int i = 0; i < n; i++){
            soma += RegistroConsumo[i].consumo_kWh;
        }

        float media = (n > 0 ? soma / n : 0);

        printf("\nPicos de Consumo (acima de %.2f kWh):\n", media * 1.5);
        for (int i = 0; i < n; i++) {
            if (RegistroConsumo[i].consumo_kWh > media * 1.5) {
                printf("Data: %s, Hora: %s, Consumo: %.2f kWh\n",
                    RegistroConsumo[i].data, RegistroConsumo[i].hora, RegistroConsumo[i].consumo_kWh);
            }
        }
    }
    void ConsumoTotal(struct DadosConsumo RegistroConsumo[], int n){
        float consumo_total = 0, custo_total = 0;
        //acumula todos os registros e faz a soma, depois multiplica pelo custo
        for(int i = 0; i < n; i++){
            consumo_total += RegistroConsumo[i].consumo_kWh;
            custo_total += RegistroConsumo[i].consumo_kWh * RegistroConsumo[i].custo_kWh;

        }
        printf("Consumo Total: %.2f kWh\n", consumo_total);
        printf("Custo Total Estimado: %.2f R$\n", custo_total);
    }

    void SugerirEconomia(struct DadosConsumo RegistroConsumo[], int n) {
    float soma[24] = {0};
    int contagem[24] = {0};
    
    for (int i = 0; i < n; i++) {
        int hora;
        sscanf(RegistroConsumo[i].hora, "%d", &hora); //ignora entrada do teclado, vai logo na string
        soma[hora] += RegistroConsumo[i].consumo_kWh;
        contagem[hora]++;
    }

    FILE *arquivo = fopen("Sugestoes_Economia.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de sugestões.\n");
        return;
    }
    //gravando no artigo com as horas correspondentes ao alto consumo
    fprintf(arquivo, "Sugestões de economia de energia:\n");
    for (int i = 0; i < 24; i++) {
        if (contagem[i] > 0) {
            float media = soma[i] / contagem[i];
            if (media > 1.5) {
                fprintf(arquivo, "Horário %02d:00 - Alto consumo detectado. Evite ligar aparelhos pesados.\n", i);
            }
        }
    }
    fclose(arquivo);
    printf("Sugestoes salvas em 'Sugestoes_Economia.txt'.\n");
}
 
   void GerarRelatorioDetalhado(struct DadosConsumo RegistroConsumo[], int n) {
    if (n == 0) {
        printf("Nenhum registro para gerar relatorio.\n");
        return;
    }

    FILE *arquivo = fopen("Relatorio_Consumo.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita do relatorio.\n");
        return;
    }

    fprintf(arquivo, "RELATORIO DETALHADO DE CONSUMO\n");
    fprintf(arquivo, "==============================\n\n");

    // variaveis para acumular o consumo de cada periodo
    float consumo_madrugada = 0; // 00:00 - 05:59
    float consumo_manha     = 0; // 06:00 - 11:59
    float consumo_tarde     = 0; // 12:00 - 17:59
    float consumo_noite     = 0; // 18:00 - 23:59

    // armazena a data atual sendo processada
    char dataAtual[11];
    strcpy(dataAtual, RegistroConsumo[0].data);

    for (int i = 0; i < n; i++) {
        // se a data do registro for diferente da dataAtual,
        // escreve o relatorio do dia anterior e reinicia os acumuladores.
        if (strcmp(RegistroConsumo[i].data, dataAtual) != 0) {
            float totalDia = consumo_madrugada + consumo_manha + consumo_tarde + consumo_noite;
            fprintf(arquivo, "Data: %s\n", dataAtual);
            fprintf(arquivo, "  Madrugada (00:00 - 05:59): %.2f kWh\n", consumo_madrugada);
            fprintf(arquivo, "  Manha     (06:00 - 11:59): %.2f kWh\n", consumo_manha);
            fprintf(arquivo, "  Tarde     (12:00 - 17:59): %.2f kWh\n", consumo_tarde);
            fprintf(arquivo, "  Noite     (18:00 - 23:59): %.2f kWh\n", consumo_noite);
            fprintf(arquivo, "  Consumo Total do Dia:   %.2f kWh\n", totalDia);
            fprintf(arquivo, "----------------------------------------\n");

            // reinicia os acumuladores e atualiza a dataatual
            strcpy(dataAtual, RegistroConsumo[i].data);
            consumo_madrugada = consumo_manha = consumo_tarde = consumo_noite = 0;
        }

        // extrai a hora do registro
        int hora = 0;
        sscanf(RegistroConsumo[i].hora, "%d", &hora);

        // acumula o consumo no periodo correspondente
        if (hora >= 0 && hora < 6) {
            consumo_madrugada += RegistroConsumo[i].consumo_kWh;
        }
        else if (hora >= 6 && hora < 12) {
            consumo_manha += RegistroConsumo[i].consumo_kWh;
        }
        else if (hora >= 12 && hora < 18) {
            consumo_tarde += RegistroConsumo[i].consumo_kWh;
        }
        else if (hora >= 18 && hora < 24) {
            consumo_noite += RegistroConsumo[i].consumo_kWh;
        }
    }

    // relatorio para ultimo dia calculado
    float totalDia = consumo_madrugada + consumo_manha + consumo_tarde + consumo_noite;
    fprintf(arquivo, "Data: %s\n", dataAtual);
    fprintf(arquivo, "  Madrugada (00:00 - 05:59): %.2f kWh\n", consumo_madrugada);
    fprintf(arquivo, "  Manha     (06:00 - 11:59): %.2f kWh\n", consumo_manha);
    fprintf(arquivo, "  Tarde     (12:00 - 17:59): %.2f kWh\n", consumo_tarde);
    fprintf(arquivo, "  Noite     (18:00 - 23:59): %.2f kWh\n", consumo_noite);
    fprintf(arquivo, "  Consumo Total do Dia:   %.2f kWh\n", totalDia);
    fprintf(arquivo, "----------------------------------------\n");

    fclose(arquivo);
    printf("Relatorio detalhado salvo em 'Relatorio_Consumo.txt'.\n");
    }


    void menu(struct DadosConsumo RegistroConsumo[], int *total){
        int opcoes;
        printf("\n============Menu============\n");
        printf("1.Registro:\n");
        printf("2.Media:\n");
        printf("3.Picos de consumo:\n");
        printf("4.Consumo total:\n");
        printf("5.Sugestao de consumo:\n");
        printf("6.Gerar Relatorio Detalhado:\n");
        printf("7.Sair:\n");
        printf("============================\n");
        printf("Selecione uma opcao: ");
        scanf("%d", &opcoes);

         switch(opcoes){

            case 1 :
                Registro(RegistroConsumo, total) ;
                break;
            
            case 2:
                CalculaMedia(RegistroConsumo, *total);
                break;

            case 3:
                PicosConsumo(RegistroConsumo, *total);
                break;

            case 4:
                ConsumoTotal(RegistroConsumo, *total);
                break;

            case 5:
                SugerirEconomia(RegistroConsumo, *total);
                break;

            case 6:
                GerarRelatorioDetalhado(RegistroConsumo, *total);
                break;

            case 7: 
                printf("Obrigada por usar o programa!...");
                return;

            default:
                printf("Opcao invalida, tente novamente!");
        }
        menu(RegistroConsumo, total);
    }

int main(){

    int capacidade = 10; // capacidade inicial
    int total = 0;
    struct DadosConsumo *RegistroConsumo = malloc(capacidade * sizeof(struct DadosConsumo));
    if (RegistroConsumo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
        //menu utilizando recursao
        menu(RegistroConsumo, &total);

    return 0;
}