#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <iostream>
#include <locale.h>
#include <fstream>
#include <vector>

///Exercício Estruturação de Binários
///Aluna: Sabrina Bittencourt Sampaio

using namespace std;

struct Meeting{
    int id;
    int day, mounth, year;
    int hour, minute;
    int qtdPeople;
}typedef meeting;

int pos = 0;
int end_file;

//Função para obter as linhas com as modificações do arquivo txt
string getFlines(FILE* alt){
    char line_aux [50];
    string line;

    alt = fopen("correcoes.txt","r");

    fseek(alt,0,SEEK_END);
    end_file = ftell(alt);
    fseek(alt,0,SEEK_SET);

    //realizamos a leitura do arquivo apenas se a posição for diferente do final do arquivo
    if(pos != end_file){
        fseek(alt,pos,SEEK_SET);
        line = fgets(line_aux,100,alt);
        pos = ftell(alt);
        fclose(alt);
        return line;
    }else
        return "fim";


}

//Função para retornar um vetor de strings com cada elemento da linha lida do arquivo
vector<string> getModifications(FILE* alt){
    vector <string> mod;
    char * pch;
    string line = getFlines(alt);

    pch = strtok ((char*)line.c_str()," ");

       while (pch != NULL)
       {
         mod.push_back(pch);
         pch = strtok (NULL, " ");
       }

    return mod;
}

//Função para obtermos um registro novo a partir do arquivo txt com modificador "I"
meeting create(meeting compare, vector<string> mods){
     meeting new_meeting;
     new_meeting.id = stoi(mods[0]);
     new_meeting.day = stoi(mods[2]);
     new_meeting.mounth = stoi(mods[3]);
     new_meeting.year = stoi(mods[4]);
     new_meeting.hour = stoi(mods[5]);
     new_meeting.minute = stoi(mods[6]);
     new_meeting.qtdPeople = stoi(mods[7]);

     return new_meeting;
}

//Função para obtermos um registro modificado a partir do arquivo txt com modificador "M"
meeting modify(meeting compare, vector<string> mods){
    if(mods[2]=="DIA")
        compare.day = stoi(mods[3]);

     else if(mods[2]=="MES")
        compare.mounth = stoi(mods[3]);


    else if(mods[2]=="ANO")
        compare.year = stoi(mods[3]);


    else if(mods[2]=="HORA")
        compare.hour = stoi(mods[3]);


    else if(mods[2]=="MINUTO")
        compare.minute = stoi(mods[3]);


    else if(mods[2]=="PESSOAS")
        compare.qtdPeople = stoi(mods[3]);


    return compare;
}


int main(){
    setlocale(LC_ALL, "Portuguese");
    int end_file;

    FILE *o = fopen("original.bin","rb");
    FILE *c = fopen("corigido.bin","wb");
    FILE *alt;
    vector<string> mods;
    bool insere = true;

    if(o == NULL)
        cout << "Erro ao abrir o arquivo.";
    else{
        fseek(o,0,SEEK_END);
        end_file = ftell(o)/sizeof(meeting);
        fseek(o,0,SEEK_SET);
        meeting compare;


        for(int i=0; i<=end_file; i=i){
            if(i==0){
                fread(&compare,sizeof(meeting),1,o);
                mods = getModifications(alt);
                i++;
            }
            //Quando o arquivo txt chega ao fim, apenas copiamos os registros do arquivo mestre para o arquivo corrigido
            if(mods[0]=="fim"){
                  for(int j=i; j<=end_file; j++){
                      fwrite(&compare,sizeof(meeting),1,c);
                      fread(&compare,sizeof(meeting),1,o);
                  }
                 break;
            }

            //Inserimos o registro original do arquivo mestre
            if(compare.id < stoi(mods[0])){
                 if(insere){
                    fwrite(&compare,sizeof(meeting),1,c);
                    fread(&compare,sizeof(meeting),1,o);
                    i++;
                 }else{
                     insere = true;
                     fread(&compare,sizeof(meeting),1,o);
                     i++;

                 }
            }
            //Inserimos o registro novo do arquivo txt de modificações
            else if(compare.id > stoi(mods[0])){
                if(mods[1]=="I"){
                     meeting new_meeting;
                     new_meeting = create(compare, mods);
                     fwrite(&new_meeting,sizeof(meeting),1,c);
                }else if(mods[1]=="M")
                        cout << "Não foi possivel modificar o registro com id: " << mods[0] << ". O registro não exite no arquivo mestre." << endl;
                 else{
                        cout << "Não foi possivel excluir o registro com id: " << mods[0] << ". O registro não exite no arquivo mestre." << endl;
                 }
                mods.clear();
                mods = getModifications(alt);

            }
            //Realizamos as modificações quando os ids são iguais
            else if(compare.id == stoi(mods[0])){
                if(mods[1]=="I")
                    cout << "Não foi possivel inserir o registro com id: " << mods[0] << ". O registro já exite no arquivo mestre." << endl;
                else if(mods[1]=="M"){
                    compare = modify(compare,mods);
                }
                else{
                    insere=false;
                }

                mods.clear();
                mods = getModifications(alt);
            }
        }

        //Caso o arquivo original tenha acabado, e o de modificações ainda não, inserimos os registros
        //adicionais do arquivo de modificações
        while(mods[0]!="fim"){
            if(mods[1]=="I"){
                 meeting new_meeting;
                 new_meeting = create(compare, mods);
                 fwrite(&new_meeting,sizeof(meeting),1,c);

            }else if(mods[1]=="M")
                    cout << "Não foi possivel modificar o registro com id: " << mods[0] << ". O registro não exite no arquivo mestre." << endl;
             else{
                    cout << "Não foi possivel excluir o registro com id: " << mods[0] << ". O registro não exite no arquivo mestre." << endl;
             }

            mods.clear();
            mods = getModifications(alt);
        }



        fclose(c);

        //Abrimos o arquivo corrigido para verificar se as modificações foram aplicadas corretamente
        FILE *c1 = fopen("corigido.bin","rb");

        int end_file1;
        fseek(c1,0,SEEK_END);
        end_file1 = ftell(c1)/sizeof(meeting);
        fseek(c1,0,SEEK_SET);

        for(int j=0;j<end_file1;j++){
            meeting show;
            fread(&show,sizeof(meeting),1,c1);
            cout << show.id << " "<< show.day << " " << show.mounth << " " << show.year << " " << show.hour << " " << show.minute << " " << show.qtdPeople << endl;

        }

    }
    fclose(o);
    return 0;
}
