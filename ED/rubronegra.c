#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0
#define tam 100

struct NO{
    int info;
    struct NO* esq;
    struct NO* dir;
    int cor;
};

typedef struct NO* ArvRB;

int cor(struct NO* H){
    if(H==NULL){
        return BLACK;
    }else{
        return H->cor;
    }
}

void TrocaCor(struct NO* H){
    H->cor = !(H->cor);
    if(H->esq != NULL)
        H->esq->cor = !(H->esq->cor);
    if(H->dir != NULL)
        H->dir->cor = !(H->dir->cor);
}

struct NO * rotEsq(struct NO* A){
    struct NO* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO * rotDir(struct NO* A){
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO* move2EsqRED(struct NO* H){
    TrocaCor(H);
    if (cor(H->dir->esq)== RED){
        H->dir = rotDir(H->dir);
        H = rotEsq(H);
        TrocaCor(H);
    }
    return H;
}

struct NO* move2DirRED(struct NO* H){
    TrocaCor(H);
    if(cor(H->esq->esq)==RED){
        H=rotDir(H);
        TrocaCor(H);
    }
    return H;
}

struct NO* balancear(struct NO* H){
    //nó Vermelho é sempre filho à esquerda
    if(cor(H->dir) == RED)
        H = rotEsq(H);

    //Filho da esquerda e neto da esquerda são vermelhos

    if(H->esq != NULL && cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotDir(H);

    //2 filhos Vermelhos: troca cor!
    if(cor(H->esq) == RED && cor(H->dir) == RED)
        TrocaCor(H);

    return H;
}


///FUNÇOES INSERIR
struct NO* insereNO(struct NO* H, int valor, int *resp){
    if(H==NULL){
        struct NO* novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL){
            *resp = -1;
            return NULL;
        }
        novo->info = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }

    if(valor == H->info)
        *resp = 0; //VALOR DUPLICADO
    else{
        if(valor < H->info)
            H->esq = insereNO(H->esq, valor, resp);
        else
            H->dir = insereNO(H->dir, valor, resp);
    }

    if(cor(H->dir)==RED && cor(H->esq)== BLACK)
        H = rotEsq(H);

    if(cor(H->esq)==RED && cor(H->esq->esq)==RED)
        H = rotDir(H);

    if(cor(H->esq)==RED && cor(H->dir)==RED)
        TrocaCor(H);

    return H;
}

int insere(ArvRB* raiz, int valor){
    int resp;
    ///Busca e insere:
    *raiz = insereNO(*raiz, valor, &resp);
    if((*raiz)!= NULL){
        (*raiz)->cor = BLACK;
    }
    return resp;
}

///FUNÇÕES REMOVER
struct NO* removerMenor(struct NO* H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }
    if(cor(H->esq)==BLACK && cor(H->esq->esq)==BLACK)
        H = move2EsqRED(H);

    H->esq =removerMenor(H->esq);
    return balancear(H);
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO* no2 = atual->esq;
    while(no2!=NULL){
        no1 = no2;
        no2=no2->esq;
    }
    return no1;
}

struct NO* removeNO(struct NO* H, int valor){
    if(valor < (H->info)){
        if(cor(H->esq)==BLACK && cor(H->esq->esq)==BLACK)
            H= move2EsqRED(H);

        H->esq = removeNO(H->esq, valor);
    }else{
        if(cor(H->esq)==RED)
            H = rotDir(H);

        if(valor == H->info && (H->dir == NULL)){
            free(H);
            return NULL;
        }

        if(cor(H->dir)==BLACK && cor(H->dir->esq)==BLACK){
            H= move2DirRED(H);
        }

        if(valor == H->info){
            struct NO* x = procuraMenor(H->dir);
            H->info = x->info;
            H->dir = removerMenor(H->dir);
        }else{
            H->dir = removeNO(H->dir, valor);
        }
    }
    return balancear(H);
}

int consulta(ArvRB raiz, int valor){
    if(raiz == NULL)
        return 0;
    if(raiz->info == valor)
        return 1;

    if(valor < (raiz->info))
        return consulta(raiz->esq, valor);
    else
        return consulta(raiz->dir, valor);
}

int removeRB(ArvRB *raiz, int valor){
    if(consulta(*raiz, valor)){
        struct NO* h = *raiz;
        ///Busca:
        *raiz = removeNO(h, valor);
        if(*raiz != NULL)
            (*raiz)->cor = BLACK;
        return 1;
    }else{
        return 0;
    }
}

///OUTRAS
void mostrar(ArvRB raiz, int c){
    if(raiz != NULL){
        printf("Altura: %d\n", c);
        printf("cor: %d\n", raiz->cor);
        printf("valor: %d\n\n\n", raiz->info);

        mostrar(raiz->esq, c+1);
        mostrar(raiz->dir, c+1);
    }
}

void freeGERAL(ArvRB raiz){
    if(raiz != NULL){
        freeGERAL(raiz->esq);
        freeGERAL(raiz->dir);
        free(raiz);
    }
}

int main (){
    ArvRB *raiz;
    ArvRB p = NULL;
    raiz = &p;
    FILE *f;
    f=fopen("numeros.txt","r");

    int i,num,op;

    for(i=0;i<tam/2;i++){
        fscanf(f,"%d\n",&num);
        insere(raiz, num);
    }

     for(i=(tam/2);i<tam;i++){
        fscanf(f,"%d\n",&op);
        switch(op){
               case 0:
                fscanf(f,"%d\n",&num);
                insere(raiz, num);
                break;
               case 1:
                fscanf(f,"%d\n",&num);
                removeRB(raiz,num);
                break;
        }

    }


    //mostrar(*raiz,0);

    freeGERAL(*raiz);
    return 0;
}
