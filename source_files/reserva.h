#ifndef RESERVA_H
#define RESERVA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/***
 * Classe Reserva
 * Representa uma reserva com atributos como codigo, codigo do voo,
 * numero do assento e codigo do passageiro.
 */
class Reserva {
private:
    /*** Codigo da reserva ***/
    string codigo;

    /*** Codigo do voo associado ***/
    string codigoVoo;

    /*** Numero do assento na reserva ***/
    int numeroAssento;

    /*** Codigo do passageiro associado ***/
    string codigoPassageiro;

public:
    /*** Construtores ***/
    Reserva();
    Reserva(string codigoVoo, int numeroAssento, string codigoPassageiro);

    /*** Metodos de manipulacao de atributos (getters e setters) ***/
    void setCodigo();
    void setCodigo(string codigo);
    string getCodigo();

    void setCodigoVoo(string codigoVoo);
    string getCodigoVoo();

    void setNumeroAssento(int numeroAssento);
    int getNumeroAssento();

    void setCodigoPassageiro(string codigoPassageiro);
    string getCodigoPassageiro();

    /*** Metodos de funcionalidade ***/
    string criaStringDeDados(); // Gera a representacao da reserva como uma string
    void mostrarReserva();      // Exibe os detalhes da reserva
    void adicionaReserva(Reserva &r); // Adiciona uma nova reserva ao arquivo

    /*** Metodos auxiliares ***/
    bool reservaExiste(string identificador); // Verifica se a reserva ja existe no arquivo
    int armazenaDadosEmArquivo(string dados); // Salva os dados da reserva no arquivo

    /*** Metodos para operacoes CRUD ***/
    void buscaReserva(string codigo);         // Busca uma reserva pelo codigo
    void atualizaReserva(string codigo, Reserva &r); // Atualiza uma reserva existente
    void excluirReserva(string codigo, Reserva &r);  // Exclui uma reserva do arquivo
};

#endif