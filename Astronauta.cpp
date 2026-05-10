#include "Astronauta.h"
#include <iostream>
using namespace std;

//construtor: inicializar os atributos do astronauta
Astronauta::Astronauta(string cpf, int idade, string nome) {
    this->cpf = cpf;
    this->nome = nome;
    this->idade = idade;
    this->vivo = true;        //todo astronauta tem q começar vivo
    this->disponivel = true;  //todo astronauta tem q começar disponível
}

//exibir os dados básicos do astronauta
void Astronauta::exibir() {
    cout << "CPF: " << cpf << " | Nome: " << nome << " | Idade: " << idade;
    cout << " | Vivo: " << (vivo ? "sim" : "nao");
    cout << " | Disponivel: " << (disponivel ? "sim" : "nao") << endl;
}