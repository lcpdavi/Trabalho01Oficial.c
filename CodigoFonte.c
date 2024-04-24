#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOTA_DE_CORTE 7.0

typedef struct{
    char nome[30];
    char telefone[20];
    char curso[30];
    float nota1; 
    float nota2;
    char *consideracaoFinal;
}Aluno;

void processarAluno(char* line, FILE* saida) {
    Aluno aluno;

    // sscanf para analisar a linha
    sscanf(line, "%[^,],%[^,],%[^,],%f,%f", aluno.nome, aluno.telefone, aluno.curso, &aluno.nota1, &aluno.nota2);

    // Calcula a média
    double media = (double)(aluno.nota1 + aluno.nota2) / 2.0;

    // Verifica se o aluno foi aprovado ou reprovado
    aluno.consideracaoFinal = (media >= NOTA_DE_CORTE) ? "APROVADO" : "REPROVADO";

    // string formatada
    char string_formatada[100000];
    sprintf(string_formatada, "%s,%.2lf,%s", aluno.nome, (double)media, aluno.consideracaoFinal);

    // Envio para o output
    printf("%s\n", string_formatada);
    fprintf(saida, "%s\n", string_formatada);
}

void lerCSV(const char *filename){
    FILE *entrada = fopen(filename,"r");
    FILE *saida = fopen("C:/Users/ds598/OneDrive/Documentos/Estrutura de dados/Trabalho01/SituacaoFinal.csv", "w");

    if(entrada == NULL || saida == NULL){
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char line[200];

    // Lê a primeira linha que contém os cabeçalhos (nome, telefone, curso, nota1, nota2)
    fgets(line, sizeof(line), entrada);

    printf("Nome,Media,Aprovado\n");

    // Lê cada linha subsequente
    while (fgets(line, sizeof(line), entrada)){
        processarAluno(line, saida);
    }

    fclose(saida);
    fclose(entrada);
}

int main(){
    lerCSV("C:/Users/ds598/OneDrive/Documentos/Estrutura de dados/Trabalho01/DadosEntrada.csv");

    return 0;
}