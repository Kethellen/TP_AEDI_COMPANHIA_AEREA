#ifndef RESERVA_H
#define RESERVA_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * Classe Reserva
 * Gerencia os dados e operacoes de uma reserva
 */
class Reserva {
private:
    string codigo;
    string codigoVoo;
    int numeroAssento;
    string codigoPassageiro;

    /**
     * Verifica se uma reserva ja existe no arquivo
     * @param identificador - Codigo da reserva
     * @return true se a reserva existir, false caso contrario
     */
    bool reservaExiste(string identificador);

    /**
     * Cria uma string formatada com os dados da reserva
     * @return String formatada com os dados da reserva
     */
    string criaStringDeDados();

    /**
     * Armazena os dados da reserva no arquivo
     * @param dados - Informacoes da reserva
     * @return 1 em caso de erro, 0 em caso de sucesso
     */
    int armazenaDadosEmArquivo(string dados);

public:
    /**
     * Construtor da classe Reserva
     * @param codigoVoo - Codigo do voo
     * @param numeroAssento - Numero do assento
     * @param codigoPassageiro - Codigo do passageiro
     */
    Reserva(string codigoVoo, int numeroAssento, string codigoPassageiro);

    Reserva();
    /**
     * Pesquisa uma reserva pelo codigo
     * @param identificador - Codigo da reserva
     * @return String contendo os dados da reserva ou uma mensagem de erro
     */
    void pesquisarReserva(string identificador);

    /**
     * Atualiza uma reserva
     * @param identificador - Codigo da reserva
     * @param novoCodigoVoo - Novo codigo do voo
     * @param novoNumeroAssento - Novo numero do assento
     * @param novoCodigoPassageiro - Novo codigo do passageiro
     * @return true se a reserva foi atualizada, false caso contrario
     */
    void atualizarReserva(string identificador);

    /**
     * Remove uma reserva do arquivo
     * @param identificador - Codigo da reserva
     * @return true se a reserva foi removida, false caso contrario
     */
    void removerReserva(string identificador);

    string gerarCodigo();
};

#endif
