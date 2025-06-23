//Armazenar e recuperar uma arvore de um arquivo binario
#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int elemento;
    struct no *esq;
    struct no *dir;
}no;

void escreveArquivo(FILE *teste, no *raiz){
    no escritor = *raiz;
    int sim = 1,
        nao = 0;

    if(raiz != NULL){
        fwrite(&sim, sizeof(int), 1, teste); //Sentinela
        fwrite(&escritor, sizeof(no), 1, teste);
    }else{
        return;
    }

    if(raiz->esq != NULL){
        escreveArquivo(teste, raiz->esq);
    }else{
        fwrite(&nao, sizeof(int), 1, teste);
    }
    if(raiz->dir != NULL){
        escreveArquivo(teste, raiz->dir);
    }else{
        fwrite(&nao, sizeof(int), 1, teste);
    }
}

no* leArquivo(FILE *teste){
    no leitor;
    no *escrevendo;
    int sentinela;
    if(fread(&sentinela, sizeof(int), 1, teste) == 1){
        if(sentinela){
            escrevendo = malloc(sizeof(no));
            if(escrevendo == NULL){
                printf("Erro de alocaco no heap \n");
                return;
            }
            fread(&leitor, sizeof(no), 1, teste);
            escrevendo->elemento = leitor.elemento;
            escrevendo->esq = leArquivo(teste);
            escrevendo->dir = leArquivo(teste);

            return escrevendo;
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}

void leitura(no *raiz){
    if(raiz == NULL){
        printf("()");
        return;
    }
    printf("(");
    printf("%d ", raiz->elemento);
    leitura(raiz->esq);
    leitura(raiz->dir);
    printf(")");
}

int main(){
    no *no1 = NULL, *no2 = NULL, *no3 = NULL, *no4 = NULL, *no5 = NULL, *no6 = NULL, *no7 = NULL;

    no1 = malloc(sizeof(no));
    no2 = malloc(sizeof(no));
    no3 = malloc(sizeof(no));
    no4 = malloc(sizeof(no));
    no5 = malloc(sizeof(no));
    no6 = malloc(sizeof(no));
    no7 = malloc(sizeof(no));

    // Criando os nós
    no1->elemento = 1;
    no2->elemento = 2;
    no3->elemento = 3;
    no4->elemento = 4;
    no5->elemento = 5;
    no6->elemento = 6;
    no7->elemento = 7;

    no1->esq = NULL;
    no1->dir = NULL;
    no2->esq = NULL;
    no2->dir = NULL;
    no3->esq = NULL;
    no3->dir = NULL;
    no4->esq = NULL;
    no4->dir = NULL;
    no5->esq = NULL;
    no5->dir = NULL;
    no6->esq = NULL;
    no6->dir = NULL;
    no7->esq = NULL;
    no7->dir = NULL;
    //--------------

    // Montando arvore
    no4->esq = no2;
    no4->dir = no6;
    no2->esq = no1;
    no2->dir = no3;
    no6->esq = no5;
    no6->dir = no7;
    //-----------------

    printf("Arvore antes da escrita: ");
    leitura(no4);

    FILE *arq;

    arq = fopen("exercicio.bin", "wb");
    if(arq != NULL){
        printf("\nabriu o arquivo\n");
    }

    escreveArquivo(arq, no4);

    fclose(arq);
    printf("fechou o arquivo\n");

    printf("Arvore depois da escrita no arquivo: ");
    leitura(no4);
    printf("\n");

    //Aqui eu só embaralho os nós para ter certeza que a escrita e a recuperação estão funcionando
    free(no1);
    free(no2);
    free(no3);
    free(no4);
    free(no5);
    free(no6);
    free(no7);
    //--------------------------------------------------------------------------------------------

    arq = fopen("exercicio.bin", "rb");
    if(arq!= NULL){
        printf("Aqruivo aberto para leitura\n");
    }
    no2 = leArquivo(arq);

    fclose(arq);

    printf("Arvore apos leitura e insercao direta do arquivo: \n");
    leitura(no2);

    //free(no1);
    free(no2);
    /*free(no3);
    free(no4);
    free(no5);
    free(no6);
    free(no7);*/
    return 0;
}
