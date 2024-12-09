#include "Assento.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define FILE_ASSENTOS "data-files/assentos.txt"

using namespace std;

/**
 * Construtor da classe Assento
 * Inicializa um novo assento, associando-o ao passageiro informado.
 * Define o status inicial como desocupado.
 */
Assento::Assento(int passageiro)
{
    this->numero = gerarCodigo();
    this->passageiro = passageiro;
    this->status = "desocupado";

    cout << "Criando numero de assento " << this->numero << "...\n";
    if (!assentoExiste(to_string(this->numero)))
    {
        string assentoStr = criaStringDeDados();
        if (armazenaDadosEmArquivo(assentoStr) == 0)
        {
            cout << "Assento cadastrado com sucesso!\n";
        }
        else
        {
            cerr << "Erro ao armazenar os dados do assento.\n";
        }
    }
    else
    {
        cout << "Assento ja existente.\n";
    }
}

/**
 * Metodo que cria uma string formatada com os dados do assento para armazenamento no arquivo.
 * Retorna uma string contendo as informacoes do assento.
 */
string Assento::criaStringDeDados()
{
    return to_string(this->numero) + "," + to_string(this->passageiro) + "," + this->status + ";\n";
}

/**
 * Metodo que verifica se um assento ja existe no arquivo.
 * Recebe o numero do assento como identificador.
 * Retorna true se o assento ja existir, ou false caso contrario.
 */
bool Assento::assentoExiste(string identificador)
{
    ifstream arquivoAssento(FILE_ASSENTOS);

    if (!arquivoAssento.is_open())
    {
        cerr << "Erro ao abrir o arquivo de assentos.\n";
        return false;
    }

    string linha;
    while (getline(arquivoAssento, linha))
    {
        string codigo;
        stringstream ss(linha);
        getline(ss, codigo, ',');
        if (codigo == identificador)
        {
            arquivoAssento.close();
            return true;
        }
    }

    arquivoAssento.close();
    return false;
}

/**
 * Metodo que armazena os dados do assento no arquivo.
 * Recebe os dados do assento como string.
 * Retorna 1 em caso de erro ao abrir o arquivo, ou 0 em caso de sucesso.
 */
int Assento::armazenaDadosEmArquivo(string dados)
{
    ofstream arquivoAssento(FILE_ASSENTOS, ios::app);

    if (!arquivoAssento.is_open())
    {
        cerr << "Erro ao abrir o arquivo de assentos.\n";
        return 1;
    }

    arquivoAssento << dados;
    arquivoAssento.close();

    return 0;
}

/**
 * Metodo que gera um novo codigo para o assento.
 * Retorna o proximo codigo disponivel.
 */
int Assento::gerarCodigo()
{
    int maiorCodigoAtual = 0;
    ifstream arquivoAssento(FILE_ASSENTOS);

    if (arquivoAssento.is_open())
    {
        string linha;
        while (getline(arquivoAssento, linha))
        {
            if (linha.empty())
                continue;

            size_t pos = linha.find(",");
            if (pos != string::npos)
            {
                try
                {
                    int codigoAtual = stoi(linha.substr(0, pos));
                    if (codigoAtual > maiorCodigoAtual)
                    {
                        maiorCodigoAtual = codigoAtual;
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    continue;
                }
                catch (const std::out_of_range &e)
                {
                    continue;
                }
            }
        }
        arquivoAssento.close();
    }

    return maiorCodigoAtual + 1;
}

/**
 * Metodo para pesquisar os detalhes de um assento pelo numero.
 * Recebe o numero do assento.
 * Exibe os dados do assento no terminal, ou uma mensagem de erro caso nao seja encontrado.
 */
void Assento::pesquisarAssento(int numeroAssento)
{
    ifstream arquivoAssento(FILE_ASSENTOS);

    if (!arquivoAssento.is_open())
    {
        cerr << "Erro ao abrir o arquivo de assentos.\n";
        return;
    }

    string linha;
    while (getline(arquivoAssento, linha))
    {
        if (linha.find(to_string(numeroAssento) + ",") == 0)
        {
            cout << "Assento encontrado: " << linha << endl;
            arquivoAssento.close();
            return;
        }
    }

    cout << "Assento nao encontrado.\n";
    arquivoAssento.close();
}

/**
 * Metodo para atualizar o status de um assento no arquivo.
 * Recebe o numero do assento e o novo status.
 * Exibe uma mensagem de sucesso ou erro.
 */
void Assento::atualizarAssento(int numeroAssento, string novoStatus)
{
    ifstream arquivoAssento(FILE_ASSENTOS);
    if (!arquivoAssento.is_open())
    {
        cerr << "Erro ao abrir o arquivo de assentos.\n";
        return;
    }

    ofstream arquivoTemp("data-files/temp.txt");
    string linha;
    bool encontrado = false;

    while (getline(arquivoAssento, linha))
    {
        if (linha.find(to_string(numeroAssento) + ",") == 0)
        {
            encontrado = true;
            stringstream ss(linha);
            string numero, passageiro, status;

            getline(ss, numero, ',');
            getline(ss, passageiro, ',');
            getline(ss, status, ',');

            string novoRegistro = numero + "," + passageiro + "," + novoStatus + ";\n";
            arquivoTemp << novoRegistro;
        }
        else
        {
            arquivoTemp << linha << endl;
        }
    }

    arquivoAssento.close();
    arquivoTemp.close();

    remove(FILE_ASSENTOS);
    rename("data-files/temp.txt", FILE_ASSENTOS);

    if (encontrado)
    {
        cout << "Assento atualizado com sucesso.\n";
    }
    else
    {
        cout << "Assento nao encontrado.\n";
    }
}

/**
 * Metodo para remover um assento do arquivo.
 * Recebe o numero do assento.
 * Exibe uma mensagem de sucesso ou erro.
 */
void Assento::removerAssento(int numeroAssento)
{
    ifstream arquivoAssento(FILE_ASSENTOS);
    if (!arquivoAssento.is_open())
    {
        cerr << "Erro ao abrir o arquivo de assentos.\n";
        return;
    }

    ofstream arquivoTemp("data-files/temp.txt");
    string linha;
    bool encontrado = false;

    while (getline(arquivoAssento, linha))
    {
        if (linha.find(to_string(numeroAssento) + ",") == 0)
        {
            encontrado = true;
        }
        else
        {
            arquivoTemp << linha << endl;
        }
    }

    arquivoAssento.close();
    arquivoTemp.close();

    remove(FILE_ASSENTOS);
    rename("data-files/temp.txt", FILE_ASSENTOS);

    if (encontrado)
    {
        cout << "Assento removido com sucesso.\n";
    }
    else
    {
        cout << "Assento nao encontrado.\n";
    }
}
