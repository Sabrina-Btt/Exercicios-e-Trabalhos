#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define tam 100

typedef struct val{
    int valor;
    struct val *prox;
} Valor;

typedef struct s_hash{
    int table_size;
    int qnt;
    Valor **valores;
} Hash;

Hash* criaHash(int table_size){
    Hash *h = (Hash*)malloc(sizeof(Hash));
    h->qnt = 0;
    h->table_size = table_size;
    h->valores = (Valor**)malloc(sizeof(Valor*) * table_size);
    for(int i = 0; i < table_size; i++){
        h->valores[i] = NULL;
    }
    return h;
}

int PegaPosicao(int chave, int table_size){
    float mult = (sqrt(5) - 1)/2;
  	float val = chave * mult;
  	val = val - (int)val;
    return (int)(table_size * val);
}

bool TemNaPosicao(int chave, Hash *h){
    int pos = PegaPosicao(chave, h->table_size);

    Valor *aux = h->valores[pos];
    while(aux != NULL){
        if(aux->valor == chave){
            return true;
        }
        aux = aux->prox;
    }
    return false;
}

Valor* insereLista(Valor *val, int valor){
    if(val == NULL){
        val = (Valor*)malloc(sizeof(Valor));
        val->valor = valor;
        val->prox = NULL;
        return val;
    }else{
        Valor *aux = val;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = (Valor*)malloc(sizeof(Valor));
        aux->prox->valor = valor;
        aux->prox->prox = NULL;
        return val;
    }
}

void inserir(int valor, Hash *h){
    if(h == NULL || h->qnt == h->table_size)
        return;

    if(TemNaPosicao(valor, h))
        return;

    int pos = PegaPosicao(valor, h->table_size);
  	h->valores[pos] = insereLista(h->valores[pos], valor);
  	h->qnt++;
}

void remover (int valor, Hash *h){
    if(h == NULL)
      return;
  	int pos = PegaPosicao(valor, h->table_size);
  	if(h->valores[pos] == NULL)
      return;
  	free(h->valores[pos]);
  	h->valores[pos] = NULL;
}

void printa(Hash *h){
  for(int i = 0; i < h->table_size; i++){
    if(h->valores[i] != NULL){
      printf("%d\n", h->valores[i]->valor);
    }
  }
}

int main(){

    Hash *h = criaHash(1427);
    char s[80];
    //sprintf(s, "%d.txt", N);
    FILE *f=fopen("numeros.txt","r");

    for(int i = 0; i < tam/2; i++){
        int a;
        fscanf(f, "%d", &a);
        inserir(a, h);
    }
    for(int i = 0; i < tam/2; i++){

        int a, b;
        fscanf(f, "%d %d", &a, &b);

        switch(b){
            case 0: inserir(a, h); break;
            case 1: remover(a, h); break;
        }
    }
    printa(h);
}
