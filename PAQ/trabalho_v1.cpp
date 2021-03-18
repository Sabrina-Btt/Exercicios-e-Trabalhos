#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <iostream>
#include <locale.h>
#include <vector>
#include <fstream>

///Trabalho paq- primeira parte
///Aluna: Sabrina Bittencourt Sampaio

using namespace std;

//Estrutura contendo os dados da palavra
struct Palavra{
    int tamPalavra;
    string caracteres;
    vector <int> linhas;
}typedef palavra;


//Função para obter as linhas de um arquivo. Teremos como retorno um vetor de strings que contém as linhas.
vector <string> getLines(){
    char nome[30];
    string line;
    vector <string> lines;

    cout << "Informe o nome do arquivo: ";
    cin >> nome;
    ifstream f (nome);
    if (f.is_open()){
        while (! f.eof() ){
          getline (f,line);
          lines.push_back(line);
        }
        f.close();
    }
    return lines;
}

//Função para inserir ordenadamente uma palavra no vetor de palavras
vector<palavra> insertVector(palavra word, vector<palavra> p){
    auto it = p.begin();

    if(p.size()==0){
        p.push_back(word);
    }
    else{
        for(int i=0;i<p.size();i++){
          if(p[i].caracteres>word.caracteres){
                if(i==0){
                  p.insert(it,word);
                  break;
                }
                else{
                    p.insert(it+i,word);
                    break;
                }
          }else if(p[i].caracteres==word.caracteres){
                p[i].linhas.push_back(word.linhas[0]);
                break;
          } else if(i+1==p.size()){
                    p.push_back(word);
                    break;}
        }

    }
    return p;
}

//Função para criar o vetor de palavras. Recebe como parâmetro o vetor contendo as linhas e retorna
//o vetor de palavras ordenado.
vector<palavra> getPalavras(vector<string> lines){
    vector <palavra> words;
    char * pch;

    for(int i=0;i<lines.size();i++){
       pch = strtok ((char*)lines[i].c_str()," ,.-");

       while (pch != NULL)
       {
         palavra word;
         word.caracteres = pch;
         word.tamPalavra = string(pch).size();
         word.linhas.push_back(i+1);
         words = insertVector(word,words);
         pch = strtok (NULL, " ,.-");
       }
    }
    return words;
}

//Função utilizada para procurar uma palavra no vetor de palavras que foram lidos do arquivo binário.
//Informa ao usuário a palavra, quantidade de ocorrências e em quais linhas ocorre.
void search_palavras(vector <palavra> words){
    string palavra;
    cout << "Digite a palavra que deseja procurar: ";
    cin >> palavra;
    int cont =0;
    for(int i=0;i<words.size();i++){
        if(palavra == words[i].caracteres){
            cout << "Palavra: " << words[i].caracteres << endl;
            cout << "Ocorre " << words[i].linhas.size() << " vezes" << endl;
            cout << "Linhas de ocorrência: " << endl;
            for(int j=0;j<words[i].linhas.size();j++)
                cout << words[i].linhas[j] << endl;


        }else
        cont++;
    }
    if(cont==words.size())
        cout << "Palavra não existe no arquivo!" << endl;
}

int main(){
    int option=0;
    setlocale(LC_ALL, "Portuguese");

    do{
        cout << "\n----------Menu-----------" << endl;
        cout << "1- Criar um índice para arquivo texto" << endl;
        cout << "2- Utilizar um índice existente para realizar buscas por palavras" << endl;
        cout << "3- Sair" << endl;
        cin >> option;

        switch(option){
            case 1:{
                vector<string> lines;
                lines = getLines();

                vector <palavra> words;
                words = getPalavras(lines);

                //Abrimos um arquivo binário para gerar os índices
                FILE *f = fopen("indice.dat","wb");
                if(f == NULL)
                    cout << "Erro ao abrir o arquivo.";
                else{
                    int s = words.size();
                    int s_w=0;
                    fwrite(&s,sizeof(int),1,f);

                    for(int i=0; i<words.size(); i++){

                        fwrite(&words[i].tamPalavra, sizeof(int), 1, f);
                        fwrite(&(words[i].caracteres.c_str()[0]), sizeof(char), words[i].tamPalavra, f);

                        int tam = words[i].linhas.size();

                        fwrite(&tam, sizeof(int), 1, f);
                        fwrite(&(words[i].linhas[0]), sizeof(int), words[i].linhas.size(), f);

                    }
                    cout << "Arquivo de índices criado com sucesso!" << endl;
                }
                fclose(f);

            }break;

            case 2:{
               int tam;
               vector<palavra> p;

               //Abrimos para leitura o arquivo binário de índices
               FILE *f1 = fopen("indice.dat","rb");
               if(f1 == NULL)
                    cout << "Erro ao abrir o arquivo.";
                else{
                   fread(&tam,sizeof(int),1,f1);

                   for(int i=0;i<tam;i++){
                        palavra p_aux;

                        int tamPalavra;
                        fread(&tamPalavra, sizeof(int), 1, f1);

                        char* s = (char*) malloc(sizeof(char) * tamPalavra);
                        fread(s, sizeof(char), tamPalavra, f1);

                        int tamLinhas;
                        fread(&tamLinhas, sizeof(int), 1, f1);

                        int* linhas = (int*) malloc(sizeof(int) * tamLinhas);
                        fread(linhas, sizeof(int), tamLinhas, f1);

                        p_aux.tamPalavra = tamPalavra;
                        p_aux.caracteres = string(s);

                        for(int i = 0; i < tamLinhas; i++){
                            p_aux.linhas.push_back(linhas[i]);
                        }

                       //Preenchemos o vetor que será utilizado para a busca de palavras
                       p.push_back(p_aux);
                       free(s);
                       free(linhas);
                   }

                   search_palavras(p);
                }

               fclose(f1);
            }break;
        }
    }while(option!=3);

    return 0;
}


