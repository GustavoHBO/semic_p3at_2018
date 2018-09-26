#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAMANHOMAXIMOVETOR 100
#define TAMANHOMINIMOVETOR 30
#define TAMANHOMAXIMOMOVIMENTACAO 300
#define TAMANHOMAXIMOGIRO 180

#define TAMANHOMAXIMOMUTACAOMOVIMENTO 10
#define TAMANHOMAXIMOMUTACAOGIRO 2

#define TAMANHOPOPULACAOINICIAL 100
#define TAMANHOPOPULACAO 100

#define TAXAMUTACOES 50
#define TAXAMUTACAOINDIVIDUO 40
#define TAXAMUTACAOMOVIMENTO 1

int gerarInt(int valorMinimo, int valorMaximo){
    return (rand()%(valorMaximo-valorMinimo)) + valorMinimo;
}

int **gerarPopulacaoInicial(){
    int **populacaoInicial = (int**)malloc(TAMANHOPOPULACAOINICIAL*sizeof(int*));
    for(int i = 0; i < TAMANHOPOPULACAOINICIAL; i++)
        populacaoInicial[i] = (int*)malloc(TAMANHOMAXIMOVETOR*sizeof(int));
    for(int i = 0; i < TAMANHOPOPULACAOINICIAL; i++){
        for(int j = 2; j < TAMANHOMAXIMOVETOR-1; j+=2){
            populacaoInicial[i][j] = gerarInt(-TAMANHOMAXIMOMOVIMENTACAO, TAMANHOMAXIMOMOVIMENTACAO);
            populacaoInicial[i][j+1] = gerarInt(-TAMANHOMAXIMOGIRO, TAMANHOMAXIMOGIRO);
        }
    }
    return populacaoInicial;
}

int calcularFitness(int *individuo){
    int pontuacao = 0;

}

void mutarIndividuos(int **populacao){
    for(int i = 0; i < (TAMANHOPOPULACAO*TAXAMUTACOES)/100; i++){
        int j = gerarInt(0, TAMANHOPOPULACAO-1);
        if(populacao[j][1] == 0){
            for(int k = 0; k < (TAXAMUTACAOINDIVIDUO*populacao[j][0])/100; k++){
                int gene = gerarInt(2, populacao[j][0]);
                if(gene%2 == 0){
                    populacao[j][gene] = populacao[j][gene] + gerarInt(-TAXAMUTACAOMOVIMENTO, TAXAMUTACAOMOVIMENTO);
                } else{
                    populacao[j][gene] = populacao[j][gene] + gerarInt(-TAMANHOMAXIMOMUTACAOGIRO, TAMANHOMAXIMOMUTACAOGIRO);
                }
            }
        }
    }
}

int main(int argc, char const *argv[]){
    srand(time(NULL));
    int **populacaoInicial = gerarPopulacaoInicial();
    mutarIndividuos(populacaoInicial);
    for(int i = 0; i < TAMANHOPOPULACAOINICIAL; i++){
        printf("%d", i+1);
        for(int j = 0; j < TAMANHOMAXIMOVETOR; j+=2){
            printf("[%d]", populacaoInicial[i][j]);
            printf("[%d]", populacaoInicial[i][j+1]);
        }
        printf("\n\n");
    }
    return 0;
}