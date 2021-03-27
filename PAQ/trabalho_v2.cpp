#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <iostream>
#include <locale.h>
#include <vector>
#include <fstream>

///Trabalho paq- segunda parte
///Aluna: Sabrina Bittencourt Sampaio

using namespace std;

struct Ocorrencia{
    int arquivo; //posição do arquivo na lista de arquivos processados.
    int qtdOcorrencias=0; //qtd de vezes em que a palavra foi encontrada
    vector <int> linhas; //linhas onde a palavra foi encontrada
}typedef ocorrencia;


//Estrutura contendo os dados da palavra
struct Palavra{
    int tamPalavra;
    string caracteres;
    int qtdOcorrencias=0; //qtd arquivos que possuem a palavra
    vector <Ocorrencia> ocorrencias;
}typedef palavra;


struct Arquivo{
    string nomeArquivo; //nome de um arquivo texto já processado
}typedef arquivo;


struct Indice{
    int qtdArquivos=0; //quantidade de arquivos de texto lidos até então
    vector<Arquivo> arquivos; //lista contendo os nomes dos arquivos texto já processados
    int qtdPalavras=0;
    vector<Palavra> palavras;//lista contendo todas as palavras já encontrada
}typedef indice;

string name;


//Função para obter as linhas de um arquivo. Teremos como retorno um vetor de strings que contém as linhas.
vector <string> getLines(indice* ind){
    char nome[30];
    string line;
    vector <string> lines;
    int cont=0;

    cout << "Informe o nome do arquivo: ";
    cin >> nome;
    name = nome;
    ifstream f (nome);
    if(ind->qtdArquivos!=0){
        for(int i=0;i<ind->arquivos.size();i++){
            if(ind->arquivos[i].nomeArquivo==nome){
                lines.push_back("-1");
                return lines;
            }else
                cont++;
        }
    }if(cont == ind->arquivos.size()){
        arquivo arq;
        arq.nomeArquivo = nome;
        ind->arquivos.push_back(arq);
        ind->qtdArquivos++;
        if (f.is_open()){
            while (! f.eof() ){
              getline (f,line);
              lines.push_back(line);
            }
            f.close();
        }
        return lines;
    }
}

//Função para inserir ordenadamente uma palavra no vetor de palavras
vector<palavra> insertVector(palavra word, vector<palavra> p, indice* ind){
    auto it = p.begin();

    if(p.size()==0){
        ind->qtdPalavras++;
        p.push_back(word);
    }
    else{
        for(int i=0;i<p.size();i++){
          if(p[i].caracteres>word.caracteres){
                if(i==0){
                  ind->qtdPalavras++;
                  p.insert(it,word);
                  break;
                }
                else{
                    ind->qtdPalavras++;
                    p.insert(it+i,word);
                    break;
                }
          }else if(p[i].caracteres==word.caracteres){
                for(int j=0;j<p[i].ocorrencias.size();j++){
                    if(p[i].ocorrencias[j].arquivo == word.ocorrencias[0].arquivo){
                        p[i].ocorrencias[j].qtdOcorrencias++;
                        p[i].ocorrencias[j].linhas.push_back(word.ocorrencias[0].linhas[0]);
                        break;
                    }else{
                         p[i].ocorrencias.push_back(word.ocorrencias[0]);
                         break;
                    }
                }
                break;

          } else if(i+1==p.size()){
                    ind->qtdPalavras++;
                    p.push_back(word);
                    break;
          }
        }

    }
    return p;
}

//Função para criar o vetor de palavras. Recebe como parâmetro o vetor contendo as linhas e retorna
//o vetor de palavras ordenado.
void getPalavras(vector<string> lines, indice* ind){
    char * pch;

    for(int i=0;i<lines.size();i++){
       pch = strtok ((char*)lines[i].c_str()," ,.-");

       while (pch != NULL)
       {
         palavra word;
         ocorrencia ocor;
         word.caracteres = pch;
         word.tamPalavra = string(pch).size();
         ocor.arquivo = ind->qtdArquivos;
         ocor.qtdOcorrencias++;
         ocor.linhas.push_back(i+1);
         word.ocorrencias.push_back(ocor);
         ind->palavras = insertVector(word,ind->palavras,ind);
         pch = strtok (NULL, " ,.-");
       }
    }
}

int main(){
    int option=0;
    setlocale(LC_ALL, "Portuguese");
    indice ind;

    do{
        cout << "\n----------Menu-----------" << endl;
        cout << "1- Processar um novo arquivo texto" << endl;
        cout << "2- Salvar o indice atual" << endl;
        cout << "3- Ler um arquivo de indice" << endl;
        cout << "4- Sair" << endl;
        cin >> option;

        switch(option){
            case 1:{
                vector<string> lines;
                lines = getLines(&ind);
                if(lines[0]=="-1"){
                    cout << "Indice para arquivo ja criado!" << endl;
                    break;
                }
                getPalavras(lines,&ind);

                cout << "Indice para o arquivo " << name << " criado com sucesso!";

                for(int i=0; i<ind.palavras.size(); i++){
                    for(int j=0; j<ind.palavras[i].ocorrencias.size();j++){

                        cout << "Arquivo:" << ind.palavras[i].ocorrencias[j].arquivo << " QtdOcor: " << ind.palavras[i].ocorrencias[j].qtdOcorrencias << "Linhas:";
                        for(int w=0;w<ind.palavras[i].ocorrencias[j].linhas.size();w++){
                            cout << " " << ind.palavras[i].ocorrencias[j].linhas[w];
                        }
                    }
                    cout << ind.palavras[i].caracteres << endl;
                }
                cout << "Qtd: " << ind.qtdPalavras << endl;

            }break;

            case 2:{
                //Abrimos um arquivo binário para gerar os índices
                FILE *f = fopen("indice.dat","wb");
                if(f == NULL)
                    cout << "Erro ao abrir o arquivo.";
                else{
                    int s = ind.palavras.size();
                    int s_w=0;
                    fwrite(&s,sizeof(int),1,f);

                    for(int i=0; i<ind.palavras.size(); i++){

                        fwrite(&ind.palavras[i].tamPalavra, sizeof(int), 1, f);
                        fwrite(&(ind.palavras[i].caracteres.c_str()[0]), sizeof(char), ind.palavras[i].tamPalavra, f);

                        int tam = ind.palavras[i].ocorrencias[i].linhas.size();

                        fwrite(&tam, sizeof(int), 1, f);
                        fwrite(&(ind.palavras[i].ocorrencias[i].linhas[0]), sizeof(int), ind.palavras[i].ocorrencias[i].linhas.size(), f);

                    }
                    cout << "Arquivo de índices criado com sucesso!" << endl;
                }
                fclose(f);

               cout << "...";
            }break;
        }
    }while(option!=4);

    return 0;
}
