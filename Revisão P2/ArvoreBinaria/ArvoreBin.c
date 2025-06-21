#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int elemento;
    struct no *dir;
    struct no *esq;
}no;

// Pilha --------

typedef struct noP{
    no *noArv;
    struct noP *prox;
}noP;

typedef struct Pilha{
    noP *inicio;
}Pilha;

void inicializarP(Pilha *teste){
    teste->inicio = NULL;
}

int vaziaP(Pilha *teste){
    if(teste->inicio == NULL){
        return 1;
    }
    return 0;
}

void inserirP(Pilha *teste, no *noArvore){
    noP *colocador = malloc(sizeof(noP));
    colocador->noArv = noArvore;
    colocador->prox = teste->inicio;
    teste->inicio = colocador;
}

no* retirarP(Pilha *teste){
    if(teste->inicio == NULL){
        return NULL;
    }
    noP *retirador = teste->inicio;
    teste->inicio = retirador->prox;

    no *retornador = retirador->noArv;
    free(retirador);

    return retornador;
}

void reiniciarP(Pilha *teste){
    while(teste->inicio != NULL){
        retirarP(teste);
    }
}

// Fim da Pilha ------

void inicializar(no **raiz){
    *raiz = NULL;
}

void criarRaiz(no **raiz, int ele){
    *raiz = malloc(sizeof(no));
    if(raiz == NULL){
        printf("Heap cheio\n");
        return;
    }
    (*raiz)->dir = NULL;
    (*raiz)->esq = NULL;
    (*raiz)->elemento = ele;
}

int vazia(no *raiz){
    if(raiz == NULL){
        return 1;
    }
    return 0;
}

void criarFilhoEsq(no *base, int elemento){
    if(vazia(base->esq)){
        base->esq = malloc(sizeof(no));
        if(base->esq == NULL){
            printf("Heap cheio\n");
            return;
        }
        base->esq->elemento = elemento;
        base->esq->esq = NULL;
        base->esq->dir = NULL;
    }
}

void criarFilhoDir(no *base, int elemento){
    if(vazia(base->dir)){
        base->dir = malloc(sizeof(no));
        if(base->dir == NULL){
            printf("Heap cheio\n");
            return;
        }
        base->dir->elemento = elemento;
        base->dir->esq = NULL;
        base->dir->dir = NULL;
    }
}

int descobreNivel(no *raiz, int nivel, int elemento){
    if(vazia(raiz)){
        printf("RaizVazia");
        return -1;
    }
    if(raiz->elemento == elemento){
        return nivel;
    }

    int nivelesq = descobreNivel(raiz->esq, nivel+1, elemento);

    if(nivelesq != -1){
        return nivelesq;
    }

    int niveldir = descobreNivel(raiz->dir, nivel+1, elemento);
    if(niveldir != -1){
        return niveldir;
    }


    return -1;
}

no* retornaPai(no *raiz, int elemento){
    no *retornador = NULL;
    if(raiz == NULL){
        return NULL;
    }

    if(raiz->esq != NULL){
        if(raiz->esq->elemento == elemento){
            return raiz;
        }
        retornador = retornaPai(raiz->esq, elemento);
        if(retornador != NULL){
            return retornador;
        }
    }


    if(raiz->dir != NULL){
        if(raiz->dir->elemento == elemento){
            return raiz;
        }
        retornador = retornaPai(raiz->dir, elemento);
        if(retornador != NULL){
            return retornador;
        }
    }

    return NULL;
}

void leituraPreOrdem(no *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->elemento);
        leituraPreOrdem(raiz->esq);
        leituraPreOrdem(raiz->dir);
    }
}

void leituraEmOrdem(no *raiz){
    if(raiz!= NULL){
        leituraEmOrdem(raiz->esq);
        printf("%d ", raiz->elemento);
        leituraEmOrdem(raiz->dir);
    }
}

void leituraPosOrdem(no *raiz){
    if(raiz != NULL){
        leituraPosOrdem(raiz->esq);
        leituraPosOrdem(raiz->dir);
        printf("%d ", raiz->elemento);
    }
}

void leituraParenteses(no *raiz){
    if(raiz != NULL){
        printf("(%d ",raiz->elemento);
        leituraParenteses(raiz->esq);
        leituraParenteses(raiz->dir);
        printf(")");
    }
}

void leituraPreOrdemPilha(no *raiz){
    Pilha *toDo;
    inicializarP(toDo);

    no *leitor = raiz;

    while(leitor != NULL){
        printf("%d ", leitor->elemento);
        inserirP(toDo, leitor->dir);
        leitor = leitor->esq;
        if(leitor == NULL){
            leitor = retirarP(toDo);
        }
    }
}

int descobrirAltura(no *raiz, int altura){
    if(raiz == NULL){
        return altura;
    }
    int h1 = altura, h2 = altura;
    if(raiz->dir != NULL){
        h1 = descobrirAltura(raiz->dir, altura+1);
    }
    if(raiz->esq != NULL){
        h2 = descobrirAltura(raiz->esq, altura+1);
    }

    if(h1 >= h2){
        return h1;
    }else{
        return h2;
    }
}

int nivelNo(no *raiz, int elemento, int nivel){
    int nivelE = nivel, nivelD = nivel;
    if(raiz == NULL){
        return -1;
    }
    if(raiz->elemento == elemento){
        return nivel;
    }
    nivelE = nivelNo(raiz->esq, elemento, nivel+1);

    nivelD = nivelNo(raiz->dir, elemento, nivel+1);


    if(nivelE > nivelD){
        return nivelE;
    }else{
        return nivelD;
    }
}

void resetarArvore(no **raiz){
    if(*raiz != NULL){
        no *remD = (*raiz)->dir;
        no *remE = (*raiz)->esq;

        resetarArvore(&remD);
        resetarArvore(&remE);
        free(*raiz);
        *raiz = NULL;
    }
}

int ehBalanceada(no *arvore){
    int altDir, altEsq;
    if(vazia(arvore)){
        return 1;
    }
    altDir = descobrirAltura(arvore->dir, 0);
    altEsq = descobrirAltura(arvore->esq, 0);

    if(!((altDir - altEsq)>=-1 && (altDir - altEsq)<=1)){
        return 0;
    }
    return (ehBalanceada(arvore->dir) && ehBalanceada(arvore->esq));
}

int main(){
    Pilha *pile = NULL;
    no *arvore = NULL;
    no *leitor;
    int recebedor;

    inicializarP(&pile);
    inicializar(&arvore);

    criarRaiz(&arvore, 1);
    criarFilhoEsq(arvore, 2);
    criarFilhoDir(arvore, 3);
    criarFilhoEsq(arvore->esq, 4);
    criarFilhoDir(arvore->esq, 5);
    //criarFilhoEsq(arvore->dir, 6);
    //criarFilhoDir(arvore->dir, 7);
    criarFilhoEsq(arvore->esq->esq, 8);

    leitor = retornaPai(arvore, 4);
    printf("\nNo do elemento '4' esta no nivel : %d\n", descobreNivel(&arvore, 0 ,4));
    printf("O no pai do no com elemento '4' e: %d", leitor->elemento);

    printf("\nLeitura preOrdem: \n");
    leituraPreOrdem(arvore);
    printf("\nLeitura em Ordem: \n");
    leituraEmOrdem(arvore);
    printf("\nLeitura posordem\n");
    leituraPosOrdem(arvore);

    printf("\nLeitura preordem parent: \n");
    leituraParenteses(arvore);

    /*printf("\nLeitura preordem pilha: \n");
    leituraPreOrdemPilha(arvore);*/

    recebedor = descobrirAltura(arvore, 0);
    printf("\nAltura da arvore: %d\n", recebedor);

    recebedor = nivelNo(arvore, 3, 0);
    printf("\nNivel do no 3: %d\n", recebedor);

    recebedor = ehBalanceada(arvore);
    if(recebedor){
        printf("\nA arvore esta balancieada\n");
    }else{
        printf("\nA arvore nao esta balanceada\n");
    }

    resetarArvore(&arvore);
    reiniciarP(&pile);
    return 0;
}
