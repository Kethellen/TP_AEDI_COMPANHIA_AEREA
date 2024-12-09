// voo.h
#ifndef VOO_H
#define VOO_H

#include <iostream>
#include <string>
#include <vector>
#include "tripulacao.h"
#include "passageiro.h"

using namespace std;

/**
 * Classe Voo
 */
class Voo {
private:
    string codigo;
    string data;
    string hora;
    string origem;
    string destino;
    string codigoAviao;
    vector<Tripulacao> tripulacao;
    vector<Passageiro> passageiros;

public:
    Voo();

    string criaStringDeDados();

    void setCodigo();
    string getCodigo();

    void setData(string data);
    string getData();

    void setHora(string hora);
    string getHora();

    void setOrigem(string origem);
    string getOrigem();

    void setDestino(string destino);
    string getDestino();

    void setCodigoAviao(string codigoAviao);
    string getCodigoAviao();

    void adicionarTripulacao(Tripulacao tripulante);
    void adicionarPassageiro(Passageiro passageiro);

    void mostrarVoo();
    void adicionarVoo();
    void buscarVoo(string codigo);
    void atualizarVoo(string codigo, Voo &v);
    void excluirVoo(string codigo, Voo &v);

    int armazenaDadosEmArquivo(string arquivo, string dados);
};

#endif