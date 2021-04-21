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
    int tamPalavra=0;
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
    int letras[26];
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
    int c=0;

    word.caracteres = strlwr((char*)word.caracteres.c_str());

    if(p.size()==0){
        ind->qtdPalavras++;
        p.push_back(word);
        ind->letras[tolower(word.caracteres.c_str()[0]) -97] = 0;

    }
    else{
        for(int i=0;i<p.size();i++){
          if(p[i].caracteres>word.caracteres){
            ind->qtdPalavras++;
            p.insert(it+i,word);
            ind->letras[tolower(word.caracteres.c_str()[0]) -97] = i;
            for(int l=(tolower(word.caracteres.c_str()[0]) -97)+1; l<26; l++){
                if(ind->letras[l]!=-1){
                    ind->letras[l]+=1;
                }
            }
            break;
          }
          else if(p[i].caracteres==word.caracteres){
                for(int j=0;j<p[i].ocorrencias.size();j++){
                    if(p[i].ocorrencias[j].arquivo == word.ocorrencias[0].arquivo){
                        p[i].ocorrencias[j].qtdOcorrencias++;
                        p[i].ocorrencias[j].linhas.push_back(word.ocorrencias[0].linhas[0]);
                        break;
                    }else{
                         c++;
                    }
                }
                if(c == p[i].ocorrencias.size()){
                     p[i].ocorrencias.push_back(word.ocorrencias[0]);
                     break;
                }

          }else if(i+1==p.size()){
                    ind->qtdPalavras++;
                    p.push_back(word);
                    ind->letras[tolower(word.caracteres.c_str()[0]) -97] = i+1;
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
    indice indl;
    for(int l=0;l<26;l++){
        ind.letras[l] = -1;
    }

    do{
        cout << "\n----------Menu-----------" << endl;
        cout << "1- Processar um novo arquivo texto" << endl;
        cout << "2- Salvar o indice atual" << endl;
        cout << "3- Ler um arquivo de indice" << endl;
        cout << "4- Realizar buscas" << endl;
        cout << "5- Sair" << endl;
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

                /*for(int l=0;l<26;l++){
                    cout << ind.letras[l] << endl;
                }

                for(int l=0;l<ind.palavras.size();l++){
                    cout << ind.palavras[l].caracteres << endl;
                }*/

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

                    for(int j=0; j<ind.qtdPalavras; j++){
                        fwrite(&ind.palavras[j].tamPalavra, sizeof(int), 1, f);
                        fwrite(&(ind.palavras[j].caracteres.c_str()[0]), sizeof(char), ind.palavras[j].tamPalavra, f);
                        ind.palavras[j].qtdOcorrencias = ind.palavras[j].ocorrencias.size();
                        fwrite(&ind.palavras[j].qtdOcorrencias, sizeof(int), 1, f);
                        cout << "qtd arquivos: " << ind.palavras[j].qtdOcorrencias << endl;


                        for(int k=0; k<ind.palavras[j].ocorrencias.size(); k++){
                            fwrite(&ind.palavras[j].ocorrencias[k].arquivo, sizeof(int), 1, f);
                            fwrite(&ind.palavras[j].ocorrencias[k].qtdOcorrencias, sizeof(int), 1, f);
                            cout << "qtd ocor: " << ind.palavras[j].ocorrencias[k].qtdOcorrencias << endl;
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
                //Abrimos para leitura o arquivo binário de índices
               FILE *f = fopen("indice.dat","rb");
               if(f == NULL)
                    cout << "Erro ao abrir o arquivo.";
               else{
                    fread(&indl.qtdArquivos,sizeof(int),1,f);


                    for(int i=0; i<indl.qtdArquivos; i++){
                        int tamNomeArq;
                        fread(&tamNomeArq, sizeof(int), 1, f);

                        char* arq = (char*) malloc(sizeof(char) * tamNomeArq);
                        fread(arq, sizeof(char), tamNomeArq, f);

                        arquivo new_arq;
                        new_arq.nomeArquivo = string(arq);
                        indl.arquivos.push_back(new_arq);

                        free(arq);
                    }

                    fread(&indl.qtdPalavras,sizeof(int),1,f);

                    ocorrencia new_ocor;
                    for(int j=0; j<indl.qtdPalavras; j++){
                        palavra new_palavra;
                        fread(&new_palavra.tamPalavra, sizeof(int), 1, f);
                        cout << "tamanho: " << new_palavra.tamPalavra << endl;

                        char* p = (char*) malloc(sizeof(char) * (new_palavra.tamPalavra));
                        fread(p, sizeof(char), new_palavra.tamPalavra, f);
                        new_palavra.caracteres = string(p);

                        fread(&new_palavra.qtdOcorrencias, sizeof(int), 1, f);
                        //cout << indl.palavras[j].qtdOcorrencias << endl;


                        for(int k=0; k<new_palavra.qtdOcorrencias; k++){
                            fread(&new_ocor.arquivo, sizeof(int), 1, f);
                            fread(&new_ocor.qtdOcorrencias, sizeof(int), 1, f);
                            //cout << indl.palavras[j].ocorrencias[k].qtdOcorrencias << endl;

                            int* linhas = (int*) malloc(sizeof(int) * (new_ocor.qtdOcorrencias));
                            fread(linhas, sizeof(int), new_ocor.qtdOcorrencias , f);

                            for(int i = 0; i <= new_ocor.qtdOcorrencias ; i++){
                                //cout << "oi";
                                new_ocor.linhas.push_back(linhas[i]);
                            }
                            new_palavra.ocorrencias.push_back(new_ocor);
                            free(linhas);
                        }
                        indl.palavras.push_back(new_palavra);
                      free(p);
                    }


                    for(int j=0; j<indl.qtdPalavras; j++){
                        cout << indl.palavras[j].caracteres << "foi lido"<< endl;
                    }

               }

               fclose(f);

            }break;
        }
    }while(option!=5);

    return 0;
}
