#include <iostream>
#include <string>
#include <vector>
#include "Astronauta.h"
#include "Voo.h"
using namespace std;

//çistas globais p guardar todos astronautas e voos cadastrados
vector<Astronauta> astronautas;
vector<Voo> voos;

//Funções aux. para encontrar astronauta ou voo pelo id
//retornar -1 se não encontrar nada


int buscarAstronauta(string cpf) {
    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].cpf == cpf) {
            return i;
        }
    }
    return -1; //não encontrou
}

int buscarVoo(int codigo) {
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].codigo == codigo) {
            return i;
        }
    }
    return -1; //não encontrou
}

//Funções p cada comando

void cadastrarAstronauta(string cpf, int idade, string nome) {
    //Verificar se já existe astronauta com esse CPF
    if (buscarAstronauta(cpf) != -1) {
        cout << "Erro: ja existe astronauta com CPF " << cpf << "." << endl;
        return;
    }

    //criar e adiciona o astronauta na lista
    Astronauta a(cpf, idade, nome);
    astronautas.push_back(a);
    cout << "Astronauta " << nome << " cadastrado com sucesso." << endl;
}

void cadastrarVoo(int codigo) {
    //verificar se já existe voo com esse código
    if (buscarVoo(codigo) != -1) {
        cout << "Erro: ja existe voo com codigo " << codigo << "." << endl;
        return;
    }

    //criar e adiciona o voo na lista
    Voo v(codigo);
    voos.push_back(v);
    cout << "Voo " << codigo << " cadastrado com sucesso." << endl;
}

void adicionarAstronauta(string cpf, int codigo) {
    //verificar se o astronauta existe
    int idxA = buscarAstronauta(cpf);
    if (idxA == -1) {
        cout << "Erro: astronauta com CPF " << cpf << " nao encontrado." << endl;
        return;
    }

    //verificar se o voo existe
    int idxV = buscarVoo(codigo);
    if (idxV == -1) {
        cout << "Erro: voo " << codigo << " nao encontrado." << endl;
        return;
    }

    //voo precisa estar planejado para aceitar novos astronautas
    if (voos[idxV].estado != 0) {
        cout << "Erro: voo " << codigo << " nao esta planejado." << endl;
        return;
    }

    //se astronauta morrer nao pode ser adicionado
    if (!astronautas[idxA].vivo) {
        cout << "Erro: astronauta " << astronautas[idxA].nome << " esta morto." << endl;
        return;
    }

    //ver se o astronauta já está no voo
    if (voos[idxV].temAstronauta(cpf)) {
        cout << "Erro: astronauta ja esta nesse voo." << endl;
        return;
    }

    //se tudo certo, adicionar
    voos[idxV].adicionarAstronauta(cpf);
    cout << "Astronauta " << astronautas[idxA].nome << " adicionado ao voo " << codigo << "." << endl;
}

void removerAstronauta(string cpf, int codigo) {
    int idxA = buscarAstronauta(cpf);
    if (idxA == -1) {
        cout << "Erro: astronauta com CPF " << cpf << " nao encontrado." << endl;
        return;
    }

    int idxV = buscarVoo(codigo);
    if (idxV == -1) {
        cout << "Erro: voo " << codigo << " nao encontrado." << endl;
        return;
    }

    if (voos[idxV].estado != 0) {
        cout << "Erro: voo " << codigo << " nao esta planejado." << endl;
        return;
    }

    //tentar remover e astronauta nao ta no voo, da erro
    bool removeu = voos[idxV].removerAstronauta(cpf);
    if (!removeu) {
        cout << "Erro: astronauta nao esta nesse voo." << endl;
    } else {
        cout << "Astronauta " << astronautas[idxA].nome << " removido do voo " << codigo << "." << endl;
    }
}

void lancarVoo(int codigo) {
    int idxV = buscarVoo(codigo);
    if (idxV == -1) {
        cout << "Erro: voo " << codigo << " nao encontrado." << endl;
        return;
    }

    if (voos[idxV].estado != 0) {
        cout << "Erro: voo " << codigo << " nao esta planejado." << endl;
        return;
    }

    //voo so pode sair com pelo menos um astronauta
    if (voos[idxV].cpfsPassageiros.size() == 0) {
        cout << "Erro: voo " << codigo << " nao tem astronautas." << endl;
        return;
    }

    //ver se todos os astronautas estao vivos e disponiveis
    for (int i = 0; i < voos[idxV].cpfsPassageiros.size(); i++) {
        string cpf = voos[idxV].cpfsPassageiros[i];
        int idxA = buscarAstronauta(cpf);

        if (!astronautas[idxA].vivo) {
            cout << "Erro: astronauta " << astronautas[idxA].nome << " esta morto." << endl;
            return;
        }
        if (!astronautas[idxA].disponivel) {
            cout << "Erro: astronauta " << astronautas[idxA].nome << " esta indisponivel." << endl;
            return;
        }
    }

    //lançar voo, tem que mudar o voo(vai ta em cursto) e deixar os astroinautas indisponiveis
    voos[idxV].estado = 1; // em curso

    for (int i = 0; i < voos[idxV].cpfsPassageiros.size(); i++) {
        string cpf = voos[idxV].cpfsPassageiros[i];
        int idxA = buscarAstronauta(cpf);
        astronautas[idxA].disponivel = false;
        astronautas[idxA].voosParticipados.push_back(codigo); //registrar participação
    }

    cout << "Voo " << codigo << " lancado com sucesso." << endl;
}

void explodirVoo(int codigo) {
    int idxV = buscarVoo(codigo);
    if (idxV == -1) {
        cout << "Erro: voo " << codigo << " nao encontrado." << endl;
        return;
    }

    //se um voo nao aconteceu, nao tem como explodir
    if (voos[idxV].estado != 1) {
        cout << "Erro: voo " << codigo << " nao esta em curso." << endl;
        return;
    }

    //voo explodiu
    voos[idxV].estado = 3;

    //se explodiu, todos astronautas morrem
    for (int i = 0; i < voos[idxV].cpfsPassageiros.size(); i++) {
        string cpf = voos[idxV].cpfsPassageiros[i];
        int idxA = buscarAstronauta(cpf);
        astronautas[idxA].vivo = false;
        astronautas[idxA].disponivel = false;
    }

    cout << "Voo " << codigo << " explodiu. Todos os astronautas morreram." << endl;
}

void finalizarVoo(int codigo) {
    int idxV = buscarVoo(codigo);
    if (idxV == -1) {
        cout << "Erro: voo " << codigo << " nao encontrado." << endl;
        return;
    }

    //se um voo nao ta em curso nao pode ser finalizado(pq n voou)
    if (voos[idxV].estado != 1) {
        cout << "Erro: voo " << codigo << " nao esta em curso." << endl;
        return;
    }

    //finalizado c sucesso
    voos[idxV].estado = 2;

    //deixar astronautas disponiveis de novo
    for (int i = 0; i < voos[idxV].cpfsPassageiros.size(); i++) {
        string cpf = voos[idxV].cpfsPassageiros[i];
        int idxA = buscarAstronauta(cpf);
        astronautas[idxA].disponivel = true;
    }

    cout << "Voo " << codigo << " finalizado com sucesso." << endl;
}

void listarVoos() {
    //listaros voos agrupados (0 a 3)
    for (int estado = 0; estado <= 3; estado++) {
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].estado != estado) continue;

            cout << "Voo " << voos[i].codigo << " - " << voos[i].estadoTexto() << endl;

            //mostrar os astronautas do voo
            for (int j = 0; j < voos[i].cpfsPassageiros.size(); j++) {
                string cpf = voos[i].cpfsPassageiros[j];
                int idxA = buscarAstronauta(cpf);
                cout << "  " << cpf << " - " << astronautas[idxA].nome << endl;
            }
        }
    }
}

void listarMortos() {
    bool temMorto = false;

    for (int i = 0; i < astronautas.size(); i++) {
        if (!astronautas[i].vivo) {
            temMorto = true;
            cout << astronautas[i].cpf << " - " << astronautas[i].nome << endl;

            //mostra os voos que ja participou 
            cout << "  Voos: ";
            for (int j = 0; j < astronautas[i].voosParticipados.size(); j++) {
                if (j > 0) cout << ", ";
                cout << astronautas[i].voosParticipados[j];
            }
            cout << endl;
        }
    }

    if (!temMorto) {
        cout << "Nenhum astronauta morto." << endl;
    }
}



int main() {
    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        }

        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome); 
            cadastrarAstronauta(cpf, idade, nome);

        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            cadastrarVoo(codigo);

        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            adicionarAstronauta(cpf, codigo);

        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            removerAstronauta(cpf, codigo);

        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            lancarVoo(codigo);

        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            explodirVoo(codigo);

        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            finalizarVoo(codigo);

        } else if (comando == "LISTAR_VOOS") {
            listarVoos();

        } else if (comando == "LISTAR_MORTOS") {
            listarMortos();
        }
    }

    return 0;
}