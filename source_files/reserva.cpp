#include "Reserva.h"

#define FILE_RESERVA "../data_files/reserva.txt"

/**
 * Construtor padrão da classe Reserva
 */
Reserva::Reserva() {
    codigo = "\0";
    codigoVoo = "\0";
    numeroAssento = 0;
    codigoPassageiro = "\0";
}

/**
 * Método que cria a string de dados para armazenamento no arquivo
 */
string Reserva::criaStringDeDados() {
    return this->codigo + "," +
           this->codigoVoo + "," +
           to_string(this->numeroAssento) + "," +
           this->codigoPassageiro + ";\n";
}

/**
 * Método para definir e acessar o atributo código da classe Reserva
 */
void Reserva::setCodigo() {
    int maiorCodigoAtual = 0;
    string linha;

    // Abre o arquivo para leitura
    ifstream arq_entrada(FILE_RESERVA);

    if (!arq_entrada.is_open()) {
        cout << "Erro ao abrir o arquivo de reservas para leitura." << endl;
        return;
    }

    // Percorre todas as linhas do arquivo
    while (getline(arq_entrada, linha)) {
        // Extrai o código (considerando que o código está antes da primeira vírgula)
        size_t pos = linha.find(",");
        if (pos != string::npos) {
            string codigoExtraido = linha.substr(0, pos);
            // Remove o prefixo "R" e converte para número
            if (codigoExtraido[0] == 'R') {
                int codigoNumerico = stoi(codigoExtraido.substr(1));
                if (codigoNumerico > maiorCodigoAtual) {
                    maiorCodigoAtual = codigoNumerico;
                }
            }
        }
    }

    arq_entrada.close();

    // Define o novo código incrementando o maior código encontrado
    this->codigo = "R" + to_string(maiorCodigoAtual + 1);
}

/**
 * Método auxiliar para definir o código manualmente (se necessário)
 */
void Reserva::setCodigo(string codigo) {
    this->codigo = codigo;
}

/**
 * Método para acessar o atributo código da classe Reserva
 */
string Reserva::getCodigo() {
    return this->codigo;
}

/**
 * Métodos set e get para codigoVoo
 */
void Reserva::setCodigoVoo(string codigoVoo) {
    this->codigoVoo = codigoVoo;
}

string Reserva::getCodigoVoo() {
    return this->codigoVoo;
}

/**
 * Métodos set e get para numeroAssento
 */
void Reserva::setNumeroAssento(int numeroAssento) {
    this->numeroAssento = numeroAssento;
}

int Reserva::getNumeroAssento() {
    return this->numeroAssento;
}

/**
 * Métodos set e get para codigoPassageiro
 */
void Reserva::setCodigoPassageiro(string codigoPassageiro) {
    this->codigoPassageiro = codigoPassageiro;
}

string Reserva::getCodigoPassageiro() {
    return this->codigoPassageiro;
}

/**
 * Método para exibir os atributos da classe Reserva
 */
void Reserva::mostrarReserva() {
    cout << "Código da Reserva: " << getCodigo() << endl;
    cout << "Código do Voo: " << getCodigoVoo() << endl;
    cout << "Número do Assento: " << getNumeroAssento() << endl;
    cout << "Código do Passageiro: " << getCodigoPassageiro() << endl;
}

/**
 * Método para adicionar nova reserva
 */
void Reserva::adicionaReserva(Reserva &r) {
    cout << "Digite o código do voo: ";
    cin >> codigoVoo;
    r.setCodigoVoo(codigoVoo);

    cout << "Digite o número do assento: ";
    cin >> numeroAssento;
    r.setNumeroAssento(numeroAssento);

    cout << "Digite o código do passageiro: ";
    cin >> codigoPassageiro;
    r.setCodigoPassageiro(codigoPassageiro);

    r.setCodigo(); // Gera o código automaticamente

    cout << "Cadastro de reserva adicionado com sucesso!" << endl;

    if (r.armazenaDadosEmArquivo(r.criaStringDeDados()) == -1) {
        cout << "\nErro ao salvar em arquivo!\n";
    } else {
        cout << "\nInformações salvas em arquivo!\n";
    }
}

/**
 * Método que verifica se uma reserva já existe no arquivo
 * @param identificador - Código da reserva
 * @return true se a reserva existir, false caso contrário
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
 * Método que armazena os dados da reserva no arquivo
 * @param dados - Informações da reserva
 * @return -1 em caso de erro, 0 em caso de sucesso
 */
int Reserva::armazenaDadosEmArquivo(string dados) {
    ofstream arquivoReserva(FILE_RESERVA, ios::app);

    if (!arquivoReserva.is_open()) {
        cerr << "Erro ao abrir o arquivo de reservas.\n";
        return -1;
    }

    arquivoReserva << dados;
    arquivoReserva.close();
    return 0;
}

/**
 * Método para buscar reserva pelo código
 */
void Reserva::buscaReserva(string codigo) {
    bool encontrado = false;
    string linha;

    ifstream arq_entrada(FILE_RESERVA);

    if (!arq_entrada.is_open()) {
        cout << "Erro ao abrir o arquivo de reservas para leitura" << endl;
        return;
    }

    while (getline(arq_entrada, linha)) {
        // Verifica se a linha contém o código da reserva
        if (linha.find(codigo + ",") == 0) {
            encontrado = true;

            // Divide a linha em partes para preencher os atributos
            stringstream ss(linha);
            string parte;
            vector<string> partes;

            while (getline(ss, parte, ',')) {
                partes.push_back(parte);
            }

            // Preenche os atributos do objeto atual
            if (partes.size() >= 4) { // Certifica que há ao menos 4 partes
                setCodigo(codigo);
                setCodigoVoo(partes[1]);          // Código do Voo
                setNumeroAssento(stoi(partes[2])); // Número do Assento
                setCodigoPassageiro(partes[3]);   // Código do Passageiro

                cout << "Reserva encontrada com as seguintes informações:\n";
                mostrarReserva(); // Exibe as informações
            }
            break;
        }
    }

    arq_entrada.close();

    if (!encontrado) {
        cout << "Reserva com código " << codigo << " não encontrada." << endl;
    }
}

/**
 * Método para atualizar uma reserva
 */
void Reserva::atualizaReserva(string codigo, Reserva &r) {
    // Primeiro busca a reserva pelo código
    r.buscaReserva(codigo);

    // Pergunta se deseja atualizar os dados
    char escolha;
    cout << "Deseja atualizar as informações desta reserva? (s/n): ";
    cin >> escolha;

    if (tolower(escolha) != 's') {
        cout << "Atualização cancelada." << endl;
        return;
    }

    // Solicita novas informações
    string novoCodigoVoo, novoCodigoPassageiro;
    int novoNumeroAssento;

    cout << "Digite o novo código do voo (ou pressione Enter para manter o atual): ";
    cin.ignore();
    getline(cin, novoCodigoVoo);

    cout << "Digite o novo número do assento (ou 0 para manter o atual): ";
    cin >> novoNumeroAssento;

    cout << "Digite o novo código do passageiro (ou pressione Enter para manter o atual): ";
    cin.ignore();
    getline(cin, novoCodigoPassageiro);

    // Atualiza apenas se o usuário informou novos dados
    if (!novoCodigoVoo.empty()) {
        r.setCodigoVoo(novoCodigoVoo);
    }
    if (novoNumeroAssento != 0) {
        r.setNumeroAssento(novoNumeroAssento);
    }
    if (!novoCodigoPassageiro.empty()) {
        r.setCodigoPassageiro(novoCodigoPassageiro);
    }

    // Atualiza o arquivo
    ifstream arq_entrada(FILE_RESERVA);
    ofstream arq_temp("temp.txt");

    if (!arq_entrada.is_open() || !arq_temp.is_open()) {
        cout << "Erro ao abrir os arquivos para atualização." << endl;
        return;
    }

    string linha;
    while (getline(arq_entrada, linha)) {
        // Substitui a linha da reserva pelo conteúdo atualizado
        if (linha.find(codigo + ",") == 0) {
            arq_temp << r.criaStringDeDados(); // Insere os dados atualizados
        } else {
            arq_temp << linha << endl; // Mantém os outros registros
        }
    }

    arq_entrada.close();
    arq_temp.close();

    // Substitui o arquivo original pelo atualizado
    remove(FILE_RESERVA);
    rename("temp.txt", FILE_RESERVA);

    cout << "Reserva atualizada com sucesso!" << endl;
}

/**
 * Método para excluir uma reserva
 */
void Reserva::excluirReserva(string codigo, Reserva &r) {
    // Primeiro busca a reserva pelo código
    r.buscaReserva(codigo);
    // Pergunta se deseja excluir a reserva
    char escolha;
    cout << "Deseja excluir esta reserva? (s/n): ";
    cin >> escolha;

    if (tolower(escolha) != 's') {
        cout << "Exclusão cancelada." << endl;
        return;
    }

    // Atualiza o arquivo
    ifstream arq_entrada(FILE_RESERVA);
    ofstream arq_temp("temp.txt");

    if (!arq_entrada.is_open() || !arq_temp.is_open()) {
        cout << "Erro ao abrir os arquivos para exclusão." << endl;
        return;
    }

    string linha;
    bool encontrado = false;

    while (getline(arq_entrada, linha)) {
        // Se encontrar a reserva pelo código, não escreve essa linha no arquivo temporário
        if (linha.find(codigo + ",") == 0) {
            encontrado = true;
            cout << "Reserva excluída com sucesso!" << endl;
        } else {
            arq_temp << linha << endl; // Mantém os outros registros
        }
    }

    if (!encontrado) {
        cout << "Reserva não encontrada!" << endl;
    }

    arq_entrada.close();
    arq_temp.close();

    // Substitui o arquivo original pelo atualizado
    remove(FILE_RESERVA);
    rename("temp.txt", FILE_RESERVA);
}