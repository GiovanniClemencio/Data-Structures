#include<stdio.h>
#include<stdlib.h>

// Struct para árvore
typedef struct no{
    int elemento;
    struct no *dir;
    struct no *esq;
}no;

typedef struct{
    no *raiz;
}arvore;
//-------------------

void inicializar(arvore *teste){
    teste->raiz = NULL;
}

int vazia(arvore *teste){
    if(teste->raiz == NULL){
        return 1;
    }
    return 0;
}

void inserir(arvore *teste, int elemento){
    no *buscador = teste->raiz;
    no *aux = NULL;

    while(buscador != NULL){
        aux = buscador;
        if(buscador->elemento < elemento){
            buscador = buscador->dir;
        }else{
            if(buscador->elemento > elemento){
                buscador = buscador->esq;
            }else{
                printf("O elemento tentando ser inserido ja esta na arvore");
                return;
            }
        }
    }

    buscador = malloc(sizeof(no));

    buscador->elemento = elemento;
    buscador->dir = NULL;
    buscador->esq = NULL;

    if(aux == NULL){
        teste->raiz = buscador;
    }else{
        if(aux->elemento > buscador->elemento){
            aux->esq = buscador;
        }else{
            aux->dir = buscador;
        }
    }
}

no* buscar(arvore *teste, int elemento){
    no *buscador = teste->raiz;

    while(buscador != NULL){
        if(buscador->elemento == elemento){
            return buscador;
        }
        if(buscador->elemento > elemento){
            buscador = buscador->esq;
        }else{
            buscador = buscador->dir;
        }
    }
    return NULL;
}

int retirar(arvore *teste, int elemento){
    //printf("Iniciando retirar\n");
    int popped;
    if(vazia(teste)){
        printf("Arvore vazia\n");
        return;
    }

    no *buscador = teste->raiz;
    no *paiBuscador = NULL;
    while(buscador != NULL && buscador->elemento != elemento){
        paiBuscador = buscador;
        (buscador->elemento > elemento) ? (buscador = buscador->esq) : (buscador = buscador->dir);
    }

    if(buscador == NULL){
        printf("Elemento nao encontrado\n");
        return;
    }else{
        popped = buscador->elemento;
    }
    if(buscador->dir == NULL && buscador->esq == NULL){ // No removido com 0 filhos
        //printf("Entrou no remover com 0 filhos\n");
        if(paiBuscador == NULL){
            teste->raiz = NULL;
        }else{
            (paiBuscador->esq == buscador) ? (paiBuscador->esq = NULL) : (paiBuscador->dir = NULL);
        }
        free(buscador);
    }else{
        if(buscador->esq == NULL || buscador->dir == NULL){ // No removido com 1 filho
            //printf("Entrou no remover com 1 filhos\n");
            if(paiBuscador == NULL){
                (buscador->esq == NULL) ? (teste->raiz = buscador->dir) : (teste->raiz = buscador->esq);
            }else{
                if(paiBuscador->esq == buscador){
                    if(buscador->esq == NULL){
                        paiBuscador->esq = buscador->dir;
                    }else{
                        paiBuscador->esq = buscador->esq;
                    }
                }else{
                    if(buscador->esq == NULL){
                        paiBuscador->dir = buscador->dir;
                    }else{
                        paiBuscador->dir = buscador->esq;
                    }
                }
            }
            free(buscador);
        }else{ // No removido com 2 filhos
            //printf("Entrou no remover com 2 filhos\n");
            no *sucessor = buscador->dir;
            no *auxSucessor = buscador;
            while(sucessor->esq != NULL){
                auxSucessor = sucessor;
                sucessor = sucessor->esq;
            }
            if(auxSucessor != buscador){
                auxSucessor->esq = sucessor->dir;
            }else{
                buscador->dir = sucessor->dir;
            }
            buscador->elemento = sucessor->elemento;
            free(sucessor);
        }
    }
    return popped;
}

void reiniciar(arvore *teste){
    //printf("Entrou no reiniciar\n");
    while(teste->raiz != NULL){
        printf("Raiz atual: %d \n", teste->raiz->elemento);
        retirar(teste, teste->raiz->elemento);
    }
    //printf("fim de reiniciar\n");
}

int main(){
    arvore exemplo;
    inicializar(&exemplo);


    inserir(&exemplo, 200);
    inserir(&exemplo, 100);
    inserir(&exemplo, 50);
    inserir(&exemplo, 150);
    inserir(&exemplo, 300);
    inserir(&exemplo, 250);
    inserir(&exemplo, 350);
    inserir(&exemplo, 275);
    inserir(&exemplo, 270);
    inserir(&exemplo, 285);
    inserir(&exemplo, 340);
    inserir(&exemplo, 400);

    printf("Removido : %d \n", retirar(&exemplo, 300));
    printf("Removido : %d \n", retirar(&exemplo, 350));
    printf("Removido : %d \n", retirar(&exemplo, 275));
    printf("Removido : %d \n", retirar(&exemplo, 100));
    printf("Removido : %d \n", retirar(&exemplo, 200));

    reiniciar(&exemplo);
    return 0;
}
