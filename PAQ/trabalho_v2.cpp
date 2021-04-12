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

//Estrutura contendo os dados das ocorrencias de cada palavra
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
    vector <Ocorrencia> ocorrencias; //lista com as ocorrencias da palavra
}typedef palavra;


//Estrutura contendo os nome de cada arquivo lido
struct Arquivo{
    string nomeArquivo; //nome de um arquivo texto já processado
}typedef arquivo;


//Estrutura contendo os dados dos arquivos e palavras lidas
struct Indice{
    int qtdArquivos=0; //quantidade de arquivos de texto lidos até então
    vector<Arquivo> arquivos; //lista contendo os nomes dos arquivos texto já processados
    int qtdPalavras=0;
    vector<Palavra> palavras;//lista contendo todas as palavras já encontradas
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

          }else if(i+1==p.size()){
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
                //Caso um arquivo já tenha sido processado, um aviso é retornado ao usuário
                if(lines[0]=="-1"){
                    cout << "Indice para arquivo ja criado!" << endl;
                    break;
                }
                //Senão apenas criamos nosso índice normalmente
                getPalavras(lines,&ind);

                cout << "Indice para o arquivo " << name << " criado com sucesso!";

            }break;

            case 2:{
                //Abrimos um arquivo binário para gerar os índices
                FILE *f = fopen("indice.dat","wb");
                if(f == NULL)
                    cout << "Erro ao abrir o arquivo.";
                else{
                    fwrite(&ind.qtdArquivos,sizeof(int),1,f);

                    for(int i=0; i<ind.arquivos.size(); i++){
                        int tamNomeArq = ind.arquivos[i].nomeArquivo.size();
                        fwrite(&tamNomeArq, sizeof(int), 1, f);
                        fwrite(&(ind.arquivos[i].nomeArquivo.c_str()[0]), sizeof(char),tamNomeArq, f);
                    }

                    fwrite(&ind.qtdPalavras,sizeof(int),1,f);

                    for(int j=0; j<ind.palavras.size(); j++){
                        fwrite(&ind.palavras[j].tamPalavra, sizeof(int), 1, f);
                        fwrite(&(ind.palavras[j].caracteres.c_str()[0]), sizeof(char), ind.palavras[j].tamPalavra, f);
                        fwrite(&ind.palavras[j].qtdOcorrencias, sizeof(int), 1, f);

                        for(int k=0; k<ind.palavras[j].ocorrencias.size(); k++){
                            fwrite(&ind.palavras[j].ocorrencias[k].arquivo, sizeof(int), 1, f);
                            fwrite(&ind.palavras[j].ocorrencias[k].qtdOcorrencias, sizeof(int), 1, f);
                            fwrite(&(ind.palavras[j].ocorrencias[k].linhas[0]), sizeof(int), ind.palavras[j].ocorrencias[k].linhas.size(), f);
                        }
                    }
                    cout << "Arquivo de índices criado com sucesso!" << endl;
                }
                fclose(f);

                //Zeramos a estrutura do índice caso o usuário queira criar e salvar outro
                ind.qtdArquivos = 0;
                ind.arquivos.clear();
                ind.qtdPalavras = 0;
                ind.palavras.clear();

            }break;

            case 3:{
                cout << "Em breve!" << endl;
            }break;
        }
    }while(option!=4);

    return 0;
}

