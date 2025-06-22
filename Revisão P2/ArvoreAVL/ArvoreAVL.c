#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    struct no *dir;
    struct no *esq;
    int elemento;
}no;

void rotacaoEsq(no **raiz){
    no *novaRaiz = (*raiz)->dir;
    no *temp = novaRaiz->esq;

    novaRaiz->esq = *raiz;
    (*raiz)->dir = temp;
    *raiz = novaRaiz;
}

void rotacaoDir(no **raiz){
    no *novaRaiz = (*raiz)->esq;
    no *temp = novaRaiz->dir;

    novaRaiz->dir = *raiz;
    (*raiz)->esq = temp;
    *raiz = novaRaiz;
}

int altura(no *raiz){
    int altEsq,
        altDir;

    if(raiz == NULL){
        return -1;
    }
    altEsq = altura(raiz->esq);
    altDir = altura(raiz->dir);

    if(altEsq > altDir){
        return altEsq + 1;
    }
    return altDir + 1;
}

int fatorBalanceamento(no *raiz){
    if(raiz == NULL) return 0;

    return ((altura(raiz->dir)) - (altura(raiz->esq)));
}

void insercao(no **raiz, int entrada){
    int FB;

    if((*raiz) == NULL){
        *raiz = malloc(sizeof(no));
        if((*raiz) == NULL){
            printf("ERRO: HeapCHeio");
            return 1;
        }
        (*raiz)->elemento = entrada;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }else{
        if((*raiz)->elemento > entrada){
            insercao(&(*raiz)->esq, entrada);
        }else{
            if((*raiz)->elemento < entrada){
                insercao(&(*raiz)->dir, entrada);
            }else{
                if((*raiz)->elemento == entrada){
                    return;
                }
            }
        }

        FB = fatorBalanceamento(*raiz);
        if(FB > 1){ // Desbalanceado para a direita
            if(fatorBalanceamento((*raiz)->dir) > 0){ // Se o anterior (filho desse atual) tem o mesmo sinal -> rotação simples para o lado oposto do peso
                rotacaoEsq(raiz);
            }else{ //C.C. é necessário rotação dupla
                rotacaoDir(&(*raiz)->dir);
                rotacaoEsq(raiz);
            }
        }else{
            if(FB < -1){ // Desbalanciamento para esquerda
                if(fatorBalanceamento((*raiz)->esq) < 0){ //Mesmo sinal no filho -> rotação simples pro lado contrário
                    rotacaoDir(raiz);
                }else{ // C.C. rotação dupla
                    rotacaoEsq(&(*raiz)->esq);
                    rotacaoDir(raiz);
                }
            }
        }
    }
}

no* minimo(no *arvore){
    no *aux = arvore;
    while(aux->esq != NULL){
        aux= aux->esq;
    }
    return aux;
}

void remocao(no **raiz, int elemento){
    int FB;

    if((*raiz) == NULL){
        return;
    }

    if((*raiz)->elemento > elemento){
        remocao(&(*raiz)->esq, elemento);
    }else{
        if((*raiz)->elemento < elemento){;
            remocao(&(*raiz)->dir, elemento);
        }
    }

    FB = fatorBalanceamento(*raiz);
    if(FB > 1){ // Desbalanceado para direita
        if(fatorBalanceamento((*raiz)->dir) > 0){ // Filho tem o mesmo sinal
            rotacaoEsq(raiz);
        }else{
            rotacaoDir(&(*raiz)->dir);
            rotacaoEsq(raiz);
        }
    }else{
        if(FB < -1){ // Desbalanceamento para esquerda
            if(fatorBalanceamento((*raiz)->esq) < 0){ // mesmo sinal
                rotacaoDir(raiz);
            }else{
                rotacaoEsq(&(*raiz)->esq);
                rotacaoDir(raiz);
            }
        }
    }
    if((*raiz)->elemento == elemento){
        no *aux = NULL;
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL){ //No sem filhos
            printf("entrou no noh sem filho\n");
            aux = (*raiz);
            *raiz = NULL;

            free(aux);
        }else{
            if((*raiz)->esq == NULL || (*raiz)->dir == NULL){ // No com somente um filho
                printf("entrou no noh com 1 filho\n");
                aux = (*raiz);

                ((*raiz)->esq == NULL) ? ((*raiz) = (*raiz)->dir) : ((*raiz) = (*raiz)->esq);

                free(aux);
            }else{ // no com 2 filhos
                printf("entrou no noh com 2 filhos\n");
                aux = minimo((*raiz)->dir);
                (*raiz)->elemento = aux->elemento;

                remocao(&(*raiz)->dir, aux->elemento);

            }
        }
    }
}

void leituraPreOrdem(no *raiz){
    if(raiz != NULL){
        printf("( %d ", raiz->elemento);
        leituraPreOrdem(raiz->esq);
        leituraPreOrdem(raiz->dir);
    }else{
        printf("( ");
    }
    printf(")");
}

int main(){
    no *arvore = NULL;

    insercao(&arvore, 8);
    insercao(&arvore, 4);
    insercao(&arvore, 10);
    insercao(&arvore, 2);
    insercao(&arvore, 6);

    printf("Arvore antes de rotacao: ");
    leituraPreOrdem(arvore);
    printf("\n");

    insercao(&arvore, 5);

    printf("Arvore apos a insercao do elemento '5': ");
    leituraPreOrdem(arvore);
    printf("\n");

    remocao(&arvore, 8);
    printf("Arvore apos remocao de 8: ");
    leituraPreOrdem(arvore);
    printf("\n");

    remocao(&arvore, 4);
    printf("Arvore apos remocao de 4: ");
    leituraPreOrdem(arvore);
    printf("\n");

    remocao(&arvore, 10);
    printf("Arvore apos remocao de 10: ");
    leituraPreOrdem(arvore);
    printf("\n");

    remocao(&arvore, 2);
    printf("Arvore apos remocao de 2: ");
    leituraPreOrdem(arvore);
    printf("\n");

    remocao(&arvore, 6);
    printf("Arvore apos remocao de 6: ");
    leituraPreOrdem(arvore);
    printf("\n");

    remocao(&arvore, 5);
    printf("Arvore apos remocao de 5: ");
    leituraPreOrdem(arvore);
    printf("\n");

    return 0;
}
