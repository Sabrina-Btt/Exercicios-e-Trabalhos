#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <iostream>
#include <locale.h>
#include <vector>
#include <fstream>

///Trabalho paq- terceira parte
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
            break;
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

//Função para realizar uma busca simples dada uma palavra
void buscaSimples(string s, indice* ind){
    int in=0, c=ind->letras[tolower(s.c_str()[0]-97)];
    int aux = ind->letras[tolower(s.c_str()[0]-97)];

    if(aux == -1){
        cout << "Palavra não encontrada!" << endl;
        return;
    }

    for(int i=aux; i<ind->palavras.size(); i++){
        if(strcmp((char*)s.c_str(),(char*)ind->palavras[i].caracteres.c_str())==0){
            for(int j=0;j<ind->palavras[i].ocorrencias.size();j++){
                cout << "\nA palavra aparece no arquivo ";
                in = ind->palavras[i].ocorrencias[j].arquivo;
                cout << ind->arquivos[in-1].nomeArquivo;
                cout << " na(s) linha(s): ";
                for(int k=0;k<ind->palavras[i].ocorrencias[j].linhas.size();k++){
                    cout << ind->palavras[i].ocorrencias[j].linhas[k] << " ";
                }
            }cout << endl;
            return;
        }
        else{
            c++;
        }
    }if(c==ind->palavras.size()){
        cout << "Palavra não encontrada!\n";
    }
}

//Função para realizar a busca composta E
void buscaCompostaE(vector<string> p_busca, indice* ind){
    int in=0, found=0, c=0, not_found=0;
    vector<int> arqs;

    for(int i=0; i<p_busca.size(); i++){
        int c=ind->letras[tolower(p_busca[i].c_str()[0]-97)];
        int aux = ind->letras[tolower(p_busca[i].c_str()[0]-97)];

        if(aux == -1){
            cout << "A busca composta não obteve nenhum resultado." << endl;
            return;
        }

        for(int j=aux; j<ind->palavras.size(); j++){
            if(strcmp((char*)p_busca[i].c_str(),(char*)ind->palavras[j].caracteres.c_str())==0){
                   if(found ==1){
                        for(int k=0;k<ind->palavras[j].ocorrencias.size();k++){
                            for(a : arqs){
                                if(ind->palavras[j].ocorrencias[k].arquivo == a){
                                    in = ind->palavras[j].ocorrencias[k].arquivo;
                                    cout << "As palavras foram encontradas no arquivo " << ind->arquivos[in-1].nomeArquivo << endl;
                                    break;
                                }
                                else
                                    not_found++;
                            }
                        }
                        if(not_found == (ind->palavras[j].ocorrencias.size()*arqs.size())){
                            cout << "A busca composta não obteve nenhum resultado." << endl;
                        }
                        return;

                   }
                   for(int l=0;l<ind->palavras[j].ocorrencias.size();l++){
                       arqs.push_back(ind->palavras[j].ocorrencias[l].arquivo);
                   }
                   found++;
            }else{
                c++;
            }
        }if(c==ind->palavras.size()){
            cout << "A busca composta não obteve nenhum resultado." << endl;
            return;
        }
    }
}

//Função de busca auxiliar que retorna os valores dos arquivos que uma palavra ocorre
vector<int> buscaAux(string s, indice* ind){
    int in=0, c=ind->letras[tolower(s.c_str()[0]-97)];
    int aux = ind->letras[tolower(s.c_str()[0]-97)];
    vector<int> ind_arquivos;

    if(aux == -1){
        return ind_arquivos;
    }

    for(int i=aux; i<ind->palavras.size(); i++){
        if(strcmp((char*)s.c_str(),(char*)ind->palavras[i].caracteres.c_str())==0){
            for(int j=0;j<ind->palavras[i].ocorrencias.size();j++){
                ind_arquivos.push_back(ind->palavras[i].ocorrencias[j].arquivo);
            }
            return ind_arquivos;
        }
        else{
            c++;
        }
    }if(c==ind->palavras.size()){
        return ind_arquivos;
    }
}

//Função para realizar a busca composta OU a partir de duas listas com os valores dos arquivos em que as palavras ocorrem
void buscaCompostaOU(vector<string> p_busca, indice* ind){
    vector<int> lista1;
    vector<int> lista2;
    vector<int> resultado;
    int tam=0;

    lista1 = buscaAux(p_busca[0], ind);
    lista2 = buscaAux(p_busca[1], ind);

    tam = lista1.size() + lista2.size();

    if(tam == 0){
        cout << "A busca composta não obteve nenhum resultado." << endl;
    }else{
        int ind1 = 0, ind2 = 0;
        for(int i=0; i<tam; i++){
            if(ind1 == lista1.size() && ind2 == lista2.size())
                break;
            if(ind1 == lista1.size()){
                resultado.push_back(lista2[ind2]);
                ind2++;
            }
            else if(ind2 == lista2.size()){
                resultado.push_back(lista1[ind1]);
                ind1++;
            }
            else{
                if(lista1[ind1] == lista2[ind2]){
                    resultado.push_back(lista1[ind1]);
                    ind1++;
                    ind2++;
                }
                else if(lista1[ind1]<lista2[ind2]){
                    resultado.push_back(lista1[ind1]);
                    ind1++;
                }
                else{
                    resultado.push_back(lista2[ind2]);
                    ind2++;
                }
            }
        }
        cout << "Foram encontradas ocorrencias de ao menos uma das palavras no(s) arquivo(s):";
        for(r:resultado){
            cout <<  " " << ind->arquivos[r-1].nomeArquivo;
        }
        cout << endl;
        lista1.clear();
        lista2.clear();
        resultado.clear();

    }
}


int main(){
    int option=0, op=0;
    setlocale(LC_ALL, "Portuguese");
    indice ind;
    indice indl;
    bool salvo = false;
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
        cout << "Escolha: ";
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

                cout << "Indice para o arquivo " << name << " criado com sucesso!" << endl;

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
                        ind.arquivos[i].nomeArquivo = ind.arquivos[i].nomeArquivo + '\0';
                        fwrite(&(ind.arquivos[i].nomeArquivo.c_str()[0]), sizeof(char),tamNomeArq, f);
                    }

                    fwrite(&ind.qtdPalavras,sizeof(int),1,f);

                    for(int j=0; j<ind.qtdPalavras; j++){
                        fwrite(&ind.palavras[j].tamPalavra, sizeof(int), 1, f);
                        ind.palavras[j].caracteres = ind.palavras[j].caracteres + '\0';
                        fwrite(&(ind.palavras[j].caracteres.c_str()[0]), sizeof(char), ind.palavras[j].tamPalavra, f);
                        ind.palavras[j].qtdOcorrencias = ind.palavras[j].ocorrencias.size();
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

                salvo = true;

            }break;

            case 3:{
               for(int l=0;l<26;l++){
                    ind.letras[l] = -1;
                }

                //Abrimos para leitura o arquivo binário de índices
               FILE *f = fopen("indice.dat","rb");
               if(f == NULL)
                    cout << "Erro ao abrir o arquivo.";
               else{
                    fread(&ind.qtdArquivos,sizeof(int),1,f);

                    for(int i=0; i<ind.qtdArquivos; i++){
                        int tamNomeArq;
                        fread(&tamNomeArq, sizeof(int), 1, f);

                        char* arq = (char*) malloc(sizeof(char) * tamNomeArq);
                        fread(arq, sizeof(char), tamNomeArq, f);

                        arquivo new_arq;
                        new_arq.nomeArquivo = string(arq,tamNomeArq);
                        ind.arquivos.push_back(new_arq);

                        free(arq);
                    }

                    fread(&ind.qtdPalavras,sizeof(int),1,f);

                    char aux;
                    for(int j=0; j<ind.qtdPalavras; j++){
                         palavra new_palavra;

                        int tamPalavra;
                        fread(&tamPalavra, sizeof(int), 1, f);

                        char* s = (char*) malloc(sizeof(char) * tamPalavra);
                        fread(s, sizeof(char), tamPalavra, f);

                        new_palavra.tamPalavra = tamPalavra;
                        new_palavra.caracteres = string(s, tamPalavra);
                        if(j==0){
                            aux = new_palavra.caracteres.c_str()[0];
                            ind.letras[tolower(new_palavra.caracteres.c_str()[0]) -97] = j;

                        }else if(aux != new_palavra.caracteres.c_str()[0]){
                            aux = new_palavra.caracteres[0];
                            ind.letras[tolower(new_palavra.caracteres.c_str()[0]) -97] = j;
                        }else{
                             aux = new_palavra.caracteres.c_str()[0];
                        }

                        free(s);

                        fread(&new_palavra.qtdOcorrencias, sizeof(int), 1, f);


                        for(int k=0; k<new_palavra.qtdOcorrencias; k++){
                            ocorrencia new_ocor;
                            fread(&new_ocor.arquivo, sizeof(int), 1, f);
                            fread(&new_ocor.qtdOcorrencias, sizeof(int), 1, f);

                            int* linhas = (int*) malloc(sizeof(int) * (new_ocor.qtdOcorrencias));
                            fread(linhas, sizeof(int), new_ocor.qtdOcorrencias , f);

                            for(int i = 0; i < new_ocor.qtdOcorrencias ; i++){
                                new_ocor.linhas.push_back(linhas[i]);
                            }
                            new_palavra.ocorrencias.push_back(new_ocor);

                            free(linhas);
                        }
                        ind.palavras.push_back(new_palavra);

                    }

                    salvo = false;
                    cout << "Arquivo lido com sucesso!" << endl;
               }


               fclose(f);

            }break;

        case 4:{
             string p_in;
             do{
                cout << "\n-------Menu de Buscas--------" << endl;
                cout << "1- Busca Simples" << endl;
                cout << "2- Busca Composta (E)" << endl;
                cout << "3- Busca Composta (OU)" << endl;
                cout << "4- Voltar ao menu inicial" << endl;
                cout << "Escolha: ";
                cin >> op;

                switch(op){
                    case 1:{
                        if(salvo){
                            cout << "O arquivo já foi salvo, para realizar buscas realize uma leitura antes" << endl;
                            break;
                        }
                        cout << "Digite a palavra que deseja buscar: " << endl;
                        cin >> p_in;
                        p_in = strlwr((char*)p_in.c_str());
                        buscaSimples(p_in,&ind);

                    }break;
                    case 2:{
                        if(salvo){
                            cout << "O arquivo já foi salvo, para realizar buscas realize uma leitura antes" << endl;
                            break;
                        }

                        cout << "Digite as palavras que deseja buscar: " << endl;
                        cin.ignore();
                        getline( cin, p_in);

                        vector<string> p_busca;
                        char * pch;
                        pch = strtok ((char*)p_in.c_str()," ,-");
                        while (pch != NULL){
                            strlwr(pch);
                            p_busca.push_back(pch);
                            pch = strtok (NULL, " ,-");
                        }

                        if(p_busca.size()>2 || p_busca.size()<2){
                            cout << "A busca composta E aceita apenas 2 palavras como entrada, tente novamente." << endl;
                            break;
                        }

                        buscaCompostaE(p_busca,&ind);

                    }break;

                    case 3:{
                        if(salvo){
                            cout << "O arquivo já foi salvo, para realizar buscas realize uma leitura antes" << endl;
                            break;
                        }

                        cout << "Digite as palavras que deseja buscar: " << endl;
                        cin.ignore();
                        getline( cin, p_in);

                        vector<string> p_busca;
                        char * pch;
                        pch = strtok ((char*)p_in.c_str()," ,-");
                        while (pch != NULL){
                            strlwr(pch);
                            p_busca.push_back(pch);
                            pch = strtok (NULL, " ,-");
                        }

                        if(p_busca.size()>2 || p_busca.size()<2){
                            cout << "A busca composta OU aceita apenas 2 palavras como entrada, tente novamente." << endl;
                            break;
                        }

                        buscaCompostaOU(p_busca,&ind);

                    }break;
                }
             }while(op!=4);

        } break;
    }
}while(option!=5);

    return 0;
}

