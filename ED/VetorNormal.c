#include <stdio.h>
#include <stdlib.h>
#define N 1000


int busca(int vet[],int valor){
    int i=1;
    while(i<=vet[0]){
        if(vet[i]==valor)
            return i;
        i++;
    }
    return -1;
}

void inserir(int vet[],int valor){
    int ident=-1;
    ident=busca(vet,valor);
    if(ident==-1){
        vet[0]++;
        vet[vet[0]]=valor;
    }
}

void remover(int vet[],int valor){

    int ident=-1;
    int i;
    ident=busca(vet,valor);
    if(ident!=-1){
        for(i=ident;i<=vet[0];i++){
            vet[i]=vet[i+1];
        }
        vet[0]--;
    }
}

void main(){
    int vet[N+5],num,i,k;
    FILE *f;
    f=fopen("numeros.txt","r");
    vet[0]=0;
    for(i=1;i<=(N/2);i++){
        fscanf(f,"%d\n",&num);
        inserir(vet,num);
    }
    int opcao,cont=(N/2)+1;
    while(cont<=N){
        fscanf(f,"%d ",&opcao);
        switch(opcao){
    case 0:
        fscanf(f,"%d\n",&num);
        inserir(vet,num);
        break;
    case 1:
        fscanf(f,"%d\n",&num);
        remover(vet,num);
        break;
        }
        cont++;
    }
    /*for(k=1;k<=vet[0];k++)
        printf("%d ",vet[k]);*/
}
