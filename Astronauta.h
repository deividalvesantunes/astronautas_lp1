#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H
 
#include <string>
#include <vector>
using namespace std;
 
//definir classe que representa um astronauta cadastrado no sistema
class Astronauta {
public:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;
    vector<int> voosParticipados; 
 
    //construtor, todo astronauta começa vivo e disponível
    Astronauta(string cpf, int idade, string nome);
 
    //mostrar os dados do astronauta na tela
    void exibir();
};
 
#endif
 