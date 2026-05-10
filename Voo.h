#ifndef VOO_H
#define VOO_H

#include <string>
#include <vector>
using namespace std;


class Voo {
public:
    int codigo;
    int estado; // 0=planejado, 1=em curso, 2=sucesso, 3=explosao
    vector<string> cpfsPassageiros; // CPF dos astronautas no voo

    //todo voo começa planejado e s/ astronautas
    Voo(int codigo);

    string estadoTexto();

    //ver se o cpf ja ta no voo
    bool temAstronauta(string cpf);

    //adicionar cpf no voo
    void adicionarAstronauta(string cpf);

    //remover cpf
    bool removerAstronauta(string cpf);
};

#endif