#include "Reserva.h"

#define FILE_RESERVA "data-files/reservas.txt"

/**
 * Construtor da classe Reserva
 * Inicializa uma nova reserva com os parametros fornecidos
 */
Reserva::Reserva(string codigoVoo, int numeroAssento, string codigoPassageiro) {
    this->codigo = gerarCodigo();
    this->codigoVoo = codigoVoo;
    this->numeroAssento = numeroAssento;
    this->codigoPassageiro = codigoPassageiro;

    cout << "Criando reserva de codigo " << this->codigo << "...\n";
    if (!reservaExiste(this->codigo)) {
        string reservaStr = criaStringDeDados();
        if (armazenaDadosEmArquivo(reservaStr) == 0) {
            cout << "Reserva cadastrada com sucesso!\n";
        } else {
            cerr << "Erro ao armazenar os dados da reserva.\n";
        }
    } else {
        cout << "Reserva ja existente.\n";
    }
}

Reserva::Reserva() {
    this->codigo = '\0';
    this->codigoVoo = '\0';
    this->numeroAssento = '\0';
    this->codigoPassageiro = '\0';
}
/**
 * Metodo que cria a string formatada para armazenar no arquivo
 * @return String com os dados da reserva
 */
string Reserva::criaStringDeDados() {
    return this->codigo + "," + this->codigoVoo + "," +
           to_string(this->numeroAssento) + "," + this->codigoPassageiro + ";\n";
}

/**
 * Metodo que verifica se uma reserva ja existe no arquivo
 * @param identificador - Codigo da reserva
 * @return true se a reserva existir, false caso contrario
 */
bool Reserva::reservaExiste(string identificador) {
    ifstream arquivoReserva(FILE_RESERVA);

    if (!arquivoReserva.is_open()) {
        cerr << "Erro ao abrir o arquivo de reservas.\n";
        return false;
    }

    string linha;
    while (getline(arquivoReserva, linha)) {
        string codigo;
        stringstream ss(linha);
        getline(ss, codigo, ',');
        if (codigo == identificador) {
            arquivoReserva.close();
            return true;
        }
    }

    arquivoReserva.close();
    return false;
}

/**
 * Metodo que armazena os dados da reserva no arquivo
 * @param dados - Informacoes da reserva
 * @return 1 em caso de erro, 0 em caso de sucesso
 */
int Reserva::armazenaDadosEmArquivo(string dados) {
    ofstream arquivoReserva(FILE_RESERVA, ios::app);

    if (!arquivoReserva.is_open()) {
        cerr << "Erro ao abrir o arquivo de reservas.\n";
        return 1;
    }

    arquivoReserva << dados;
    arquivoReserva.close();
    return 0;
}

/**
 * Metodo que gera um novo codigo para a reserva
 * @return Novo codigo gerado
 */
string Reserva::gerarCodigo() {
    int maiorCodigoAtual = 0;
    ifstream arquivoReserva(FILE_RESERVA);

    if (arquivoReserva.is_open()) {
        string linha;

        while (getline(arquivoReserva, linha)) {
            if (linha.empty()) continue;

            size_t pos = linha.find(",");
            if (pos != string::npos) {
                try {
                    int codigoAtual = stoi(linha.substr(0, pos));
                    if (codigoAtual > maiorCodigoAtual) {
                        maiorCodigoAtual = codigoAtual;
                    }
                } catch (const std::invalid_argument &e) {
                    continue;
                } catch (const std::out_of_range &e) {
                    continue;
                }
            }
        }

        arquivoReserva.close();
    }

    return to_string(maiorCodigoAtual + 1);
}

/**
 * Metodo para pesquisar uma reserva pelo codigo
 * @param identificador - Codigo da reserva
 */
void Reserva::pesquisarReserva(string identificador) {
    ifstream arquivoReserva(FILE_RESERVA);

    if (!arquivoReserva.is_open()) {
        cerr << "Erro ao abrir o arquivo de reservas.\n";
    }

    string linha;
    while (getline(arquivoReserva, linha)) {
        if (linha.find(identificador + ",") == 0) {
            cout << "Reserva encontrada: " << linha << endl;
            arquivoReserva.close();
        }
    }

    cout << "Reserva nao encontrada.\n";
    arquivoReserva.close();
}

/**
 * Metodo para atualizar uma reserva
 * @param identificador - Codigo da reserva
 */
void Reserva::atualizarReserva(string identificador) {
    ifstream arquivoReserva(FILE_RESERVA);
    if (!arquivoReserva.is_open()) {
        cerr << "Erro ao abrir o arquivo de reservas para atualizacao.\n";
        // return;
    }

    ofstream arquivoTemporario("data-files/temp.txt");
    string linha;
    bool encontrado = false;

    while (getline(arquivoReserva, linha)) {
        if (linha.find(identificador + ",") == 0) {
            encontrado = true;

            string novoCodigoVoo, novoCodigoPassageiro;
            int novoNumeroAssento;

            cout << "Digite o novo codigo do voo: ";
            cin.ignore();
            getline(cin, novoCodigoVoo);
            cout << "Digite o novo numero do assento: ";
            cin >> novoNumeroAssento;
            cin.ignore();
            cout << "Digite o novo codigo do passageiro: ";
            getline(cin, novoCodigoPassageiro);

            string novoRegistro = identificador + "," + novoCodigoVoo + "," +
                                  to_string(novoNumeroAssento) + "," + novoCodigoPassageiro + ";\n";
            arquivoTemporario << novoRegistro;
        } else {
            arquivoTemporario << linha << endl;
        }
    }

    arquivoReserva.close();
    arquivoTemporario.close();

    remove(FILE_RESERVA);
    rename("data-files/temp.txt", FILE_RESERVA);

    if (encontrado) {
        cout << "Reserva atualizada com sucesso.\n";
    } else {
        cout << "Reserva nao encontrada.\n";
    }
}

/**
 * Metodo para remover uma reserva do arquivo
 * @param identificador - Codigo da reserva
 */
void Reserva::removerReserva(string identificador) {
    ifstream arquivoReserva(FILE_RESERVA);
    if (!arquivoReserva.is_open()) {
        cerr << "Erro ao abrir o arquivo de reservas para exclusao.\n";
        return;
    }

    ofstream arquivoTemporario("data-files/temp.txt");
    string linha;
    bool encontrado = false;

    while (getline(arquivoReserva, linha)) {
        if (linha.find(identificador + ",") == 0) {
            encontrado = true;
        } else {
            arquivoTemporario << linha << endl;
        }
    }

    arquivoReserva.close();
    arquivoTemporario.close();

    remove(FILE_RESERVA);
    rename("data-files/temp.txt", FILE_RESERVA);

    if (encontrado) {
        cout << "Reserva removida com sucesso.\n";
    } else {
        cout << "Reserva nao encontrada.\n";
    }
}
