#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 1000000000

int a[tam];

void printvet(int vetor[]) {
  int i;
  for(i=0; i<tam; i++) {
    printf("%d ", vetor[i]);
  }
  printf("\n");
}

void troca(int vet[], int a, int b) {
  int aux = vet[a];
  vet[a] = vet[b];
  vet[b] = aux;
};

void quickSort(int vet[], int ini, int fim) {
  int pivo, ult, i;
  if(ini <= fim) {
    pivo = ini;
    ult = ini;
    for(i=ini+1; i<=fim; i++) {
      if(vet[i] <= vet[pivo]) {
        ult++;
        troca(vet, ult, i);
      }
    }
    troca(vet, pivo, ult);
    quickSort(vet, ini,ult-1);
    quickSort(vet, ult+1,fim);
  }
}

void selectSort(int vet[], int t){
     int i,j,menor,aux;
     for(i=0;i<(tam-1);i++){
        menor=i;
          for(j=(i+1);j<tam;j++){
              if(vet[j]<vet[menor])
                 menor=j;
        }
      if (vet[i] != vet[menor]){
       aux = vet[i];
       vet[i] = vet[menor];
       vet[menor] = aux;
    }
  }
}

void merge(int vet[], int a[], int ini, int meio, int fim){
    int idA=ini, idB=meio+1, fimA=meio, fimB=fim;
    int pos=ini,i;

    while(idA<=fimA && idB<=fimB){
        if(vet[idA]<vet[idB]){
            a[pos]=vet[idA];
            idA++;
            pos++;
        }
        else {
            a[pos]=vet[idB];
            idB++;
            pos++;
        }
    }
    if(idA>fimA){
        while(idB<=fimB){
            a[pos]=vet[idB];
            idB++;
            pos++;
        }
    }
    else{
        while(idA<=fimA){
            a[pos]=vet[idA];
            idA++;
            pos++;
        }
    }
    for(i=ini;i<=fim;i++){
        vet[i]=a[i];
    }
}

void mergeSort(int vet[],int ini,int fim){
     int meio;

     if(ini<fim){
        meio= (ini+fim)/2;
        mergeSort(vet,ini,meio);
        mergeSort(vet,meio+1,fim);
        merge(vet,a,ini,meio,fim);
    }
}





int main(void) {

   FILE *f, *r;
    int i,n;
    int *vetor=(int*)calloc(tam,(sizeof(int)));
    int *vetaux1=(int*)calloc(tam,(sizeof(int)));
    int *vetaux2=(int*)calloc(tam,(sizeof(int)));

    f=fopen("vetor1.txt","w");
    srand(time(NULL));
        for(i=0;i<tam;i++){
            fprintf(f,"%d ",rand()%1000);
        }
    fclose(f);

    r=fopen("vetor1.txt","r");
    for(i=0; i<tam;i++) {
        fscanf(r,"%d ", &n);
        vetor[i] = n;
        vetaux1[i] = n;
        vetaux2[i] = n;
  }
  fclose(r);
  //printvet(vetor);
  //printf("fim \n");
    clock_t Ticks[2];
    Ticks[0] = clock();

    mergeSort(vetor,0,tam);

    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    //printvet(vetor);
    printf("Tempo gasto merge sort: %g ms.\n", Tempo);

    clock_t Tick[2];
    Tick[0] = clock();

    quickSort(vetaux1,0,tam);

    Tick[1] = clock();
    double Temp = (Tick[1] - Tick[0]) * 1000.0 / CLOCKS_PER_SEC;
    //printvet(vetor);
    printf("Tempo gasto quick sort: %g ms.\n", Temp);

    clock_t Tic[2];
    Tic[0] = clock();

    selectSort(vetaux2,tam);

    Tic[1] = clock();
    double T = (Tic[1] - Tic[0]) * 1000.0 / CLOCKS_PER_SEC;
    //printvet(vetor);
    printf("Tempo gasto select sort: %g ms.\n", T);


  free(vetaux1);
  free(vetaux2);
  free(vetor);

  return 0;
}






















































































