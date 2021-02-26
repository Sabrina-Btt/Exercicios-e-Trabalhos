#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <iostream>
#include <locale.h>

///Exercício Arquivos Binários
///Aluna: Sabrina Bittencourt Sampaio

using namespace std;

struct Meeeting{
    string day;
    string hour;
    string note;
}typedef meeting;


void add_meeting(FILE **f){
    meeting new_meeting;
    cout << "Informe a data (dd/mm/aaaa): ";
    cin >> new_meeting.day;
    cout << "Informe a hora (h:min): ";
    cin >> new_meeting.hour;
    cout << "Informe o assunto da reunião (até 20 caracteres): ";
    cin.ignore();
    getline( cin,new_meeting.note);

    if(*f == NULL)
        cout << "Erro ao abrir o arquivo.";
    else{
        fwrite(&new_meeting,sizeof(meeting),1,*f);
        cout << "Reunião agendada com sucesso!" << endl;
    }
}

void show_meeting(FILE **f1){
    string date;
    cout << "Informe a data: ";
    cin >> date;
    meeting show;
    int i=1;

    if(*f1 == NULL)
        cout << "Erro ao abrir o arquivo.";
    else{
        do{
            i=fread(&show,sizeof(meeting),1,*f1);
             cout << "Hora: " + show.hour + "\n"<<"Assunto: " + show.note + "\n"<<endl;
            if(date==show.day){
                cout << "----Reunião----\n";
                cout << "Hora: " + show.hour + "\n"<<"Assunto: " + show.note + "\n"<<endl;
            }
        }while(i>0);
    }
}

int main(){
    int option=0;
    setlocale(LC_ALL, "Portuguese");

    do{
        cout << "----------Menu-----------" << endl;
        cout << "1- Agendar reunião" << endl;
        cout << "2- Ver reuniões agendadas" << endl;
        cout << "3- Sair" << endl;
        cin >> option;

        switch(option){
            case 1:{
                meeting new_meeting;
                cout << "Informe a data (dd/mm/aaaa): ";
                cin >> new_meeting.day;
                cout << "Informe a hora (h:min): ";
                cin >> new_meeting.hour;
                cout << "Informe o assunto da reunião (até 20 caracteres): ";
                cin.ignore();
                getline( cin,new_meeting.note);

                FILE *f = fopen("agenda.bin","ab");
                if(f == NULL)
                    cout << "Erro ao abrir o arquivo.";
                else{
                    fwrite(&new_meeting,sizeof(meeting),1,f);
                    cout << "Reunião agendada com sucesso!" << endl;
                }

                //FILE *f = fopen("agenda.bin","ab");
                //add_meeting(&f);
                fclose(f);
            }break;

            case 2:{
                string date;
                cout << "Informe a data: ";
                cin >> date;
                int end_file;

                FILE *f1 = fopen("agenda.bin","rb");

                if(f1 == NULL)
                    cout << "Erro ao abrir o arquivo.";
                else{
                    fseek(f1,0,SEEK_END);
                    end_file = ftell(f1)/sizeof(meeting);
                    fseek(f1,0,SEEK_SET);
                    meeting show;

                    for(int i=0; i<end_file; i++){
                        fread(&show,sizeof(meeting),1,f1);
                        if(date==show.day){
                            cout << "----Reunião----\n";
                            cout << "Hora: " + show.hour + "\n"<<"Assunto: " + show.note + "\n"<<endl;
                        }
                    }
                }
                //FILE *f1 = fopen("agenda.bin","rb");
                //show_meeting(&f1);
                fclose(f1);
            }break;
        }
    }while(option!=3);


    return 0;
}


