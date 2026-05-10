#include "Voo.h"
#include <iostream>
using namespace std;

Voo::Voo(int codigo) {
    this->codigo = codigo;
    this->estado = 0;
}

string Voo::estadoTexto() {
    if (estado == 0) return "planejado";
    if (estado == 1) return "em curso";
    if (estado == 2) return "finalizado com sucesso";
    return "finalizado com explosao";
}

bool Voo::temAstronauta(string cpf) {
    for (int i = 0; i < cpfsPassageiros.size(); i++) {
        if (cpfsPassageiros[i] == cpf) {
            return true;
        }
    }
    return false;
}

void Voo::adicionarAstronauta(string cpf) {
    cpfsPassageiros.push_back(cpf);
}

bool Voo::removerAstronauta(string cpf) {
    for (int i = 0; i < cpfsPassageiros.size(); i++) {
        if (cpfsPassageiros[i] == cpf) {
            //remover o cpf da lista
            cpfsPassageiros.erase(cpfsPassageiros.begin() + i);
            return true;
        }
    }
    return false; //não encontrou o cpf
}