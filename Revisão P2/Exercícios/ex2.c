// Função que verifica se uma árvore é binaria de busca e se for, verifica se é uma avl e se for avl
#include<stdio.h>
#include<stdlib.h>

typedef struct no{ // Nó da arvore
    int elemento;
    struct no *esq;
    struct no *dir;
}no;

int altura(no *raiz){
    int altEsq = 0, altDir = 0;
    if(raiz == NULL){
        return 0;
    }

    if(raiz->esq != NULL){
        altEsq = 1 + altura(raiz->esq);
    }

    if(raiz->dir != NULL){
        altDir = 1 + altura(raiz->dir);
    }

    if(altEsq > altDir){
        return altEsq;
    }else{
        return altDir;
    }
}

int fatorBalanceamento(no *raiz){
    int altEsq, altDir;

    altEsq = altura(raiz->esq);
    altDir = altura(raiz->dir);

    return (altDir - altEsq);
}

int ehAVL(no *raiz){
    int retorno = 1,
        esquerda = 0,
        direita = 0,
        FB;

    if(raiz == NULL){
        return 1;
    }

    FB = fatorBalanceamento(raiz);
    if(FB >= -1 && FB<= 1){
        esquerda = ehAVL(raiz->esq);
        direita = ehAVL(raiz->dir);
    }else{
        return 0;
    }

    if(esquerda && direita){
        return 1;
    }else{
        return 0;
    }
}

int ehBST(no *raiz, int min, int max){
    int retorno = 1;

    if(raiz == NULL){
        return 1;
    }

    if(raiz->elemento < min || raiz->elemento > max){
        return 0;
    }

    retorno = ehBST(raiz->esq, min, raiz->elemento);
    if(retorno){
        retorno = ehBST(raiz->dir, raiz->elemento, max);
    }

    return retorno;
}

void analizarArvore(no *raiz){
    int BST = 0;
    int AVL = 0;

    if(raiz != NULL){
        BST = ehBST(raiz, -20000, 20000);
        AVL = ehAVL(raiz);
    }

    if(BST){
        printf("A arvore e binaria de busca\n");
        if(AVL){
            printf("A arvore e AVL\n");
        }
    }else{
        printf("A arvore n eh binaria de busca\n");
    }
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
    no7->esq = no6;
    no6->esq = no5;
    no5->esq = no4;
    no4->esq = no3;
    no3->esq = no2;
    no2->esq = no1;
    //-----------------

    analizarArvore(no7);

    free(no1);
    free(no2);
    free(no3);
    free(no4);
    free(no5);
    free(no6);
    free(no7);

    return 0;
}
