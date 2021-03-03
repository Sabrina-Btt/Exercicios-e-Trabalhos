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


int main(){
    int option=0;
    setlocale(LC_ALL, "Portuguese");

    do{
        cout << "\n----------Menu-----------" << endl;
        cout << "1- Registrar uma nova reunião" << endl;
        cout << "2- Mostrar reuniões agendadas" << endl;
        cout << "3- Sair" << endl;
        cin >> option;

        switch(option){
            case 1:{
                ///Registramos uma nova reunião---------------------------------------
                meeting new_meeting;
                cout << "\nInforme a data (dd/mm/aaaa): ";
                cin >> new_meeting.day;
                cout << "Informe a hora (h:min): ";
                cin >> new_meeting.hour;
                cout << "Informe o assunto da reunião (até 20 caracteres): ";
                cin.ignore();
                getline(cin,new_meeting.note);
                if((new_meeting.note).size()>20){
                    cout << "\nA descrição da reunião deve conter até 20 caracteres\n";
                    cout << "Tente novamente!\n";
                    break;
                }

                FILE *f = fopen("agenda.bin","ab");
                if(f == NULL)
                    cout << "Erro ao abrir o arquivo.";
                else{
                    fwrite(&new_meeting,sizeof(meeting),1,f);
                    cout << "Reunião agendada com sucesso!" << endl;
                }

                fclose(f);
            }break;

            case 2:{
                ///Mostramos uma reunião segundo uma data fornecida pelo usuário------
                string date;
                cout << "\nInforme a data: ";
                cin >> date;
                int end_file;
                int c=0;

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
                            cout << "\n----Reunião----\n";
                            cout << "Hora: " + show.hour + "\n"<<"Assunto: " + show.note <<endl;
                        }else
                            //Incrementamos um contador c  que deve ser igual ao final do arquivo
                            //para saber se não existe a reunião na data fornecida
                            c++;
                    }
                    //Caso a data fornecida não esteja no arquivo, uma mensagem é mostrada ao usuário
                    if(c==end_file)
                        cout<< "\nNão existem reuniões marcadas para este dia\n";
                }
                fclose(f1);
            }break;
        }
    }while(option!=3);


    return 0;
}
