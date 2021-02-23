#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <locale.h>

using namespace std;

//Map para armazenar as ocorrências de um determinado char. A key é o próprio char e o value, a quantidade
//de ocorrências
typedef std::map<char, int> Mymap;


//Struct para armazenar posteriormente cada key e value do map para ordenação
struct Data{
    unsigned char c;
    int qtd;
}typedef data;


//Função que define o critério de ordenação (no caso, decrescente)
bool sortData(const data& d1, const data& d2)
{
   return d1.qtd > d2.qtd;
}


int main(){
    char name[30];
    std::map<char, int>::iterator it;
    std::map<char, int>::iterator aux;
    vector <data>::iterator ptr;
    vector<data> character;
    Mymap m;
    setlocale(LC_ALL, "Portuguese");


    cout << "Entre com o nome do arquivo: ";
    cin >> name;

    FILE *f = fopen(name, "r");

    if(f == NULL){
        cout << "Erro ao abrir o arquivo.";
    }else{
        while(!feof(f)){
            unsigned char c;
            c = fgetc(f);

            //Caso o char tenha código ASCII maior que 32, verificaremos se este já se encontra em nossa map.
            //Se estiver, incrementamos o valor de ocorrências, se não, adicionamos uma nova entrada de c em map
            //com value 1
            if(int(c)>= 32 && int(c)<255){
                aux = m.find(c);
                if (aux != m.end()){
                    aux->second++;
                }else{
                    m.insert(Mymap::value_type(c, 1));
                }
            }
        }

        fclose(f);

        //Como queremos ordenar nosso map por value, vamos transferí-lo para um vetor de structs
        for (it = m.begin(); it != m.end(); ++it) {
            data d = {(*it).first, (*it).second};
            character.push_back(d);
        }

        //Efetuaremos a ordenação com base na função descrita anteriormente
        sort (character.begin(), character.end(), sortData);


        //Por fim, temos o resultado
        for (const auto& caux: character){
             cout << "char:" << caux.c << "\t qtd:" << caux.qtd << '\n';
        }

    }

    return (0);
}

