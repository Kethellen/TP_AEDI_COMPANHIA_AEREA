#include "voo.h"
#include <fstream>
#include <sstream>

#define FILE_VOO "../data_files/voo.txt"

/**
 * Construtor padrão da classe Voo
 */
Voo::Voo() {
    codigo = "\0";
    data = "\0";
    hora = "\0";
    origem = "\0";
    destino = "\0";
    codigoAviao = "\0";
}

/**
 * Cria string de dados para armazenamento
 */
string Voo::criaStringDeDados() {
    string tripulacaoDados, passageirosDados;

    // Concatena os dados da tripulação
    for (auto itTrip = tripulacao.begin(); itTrip != tripulacao.end(); ++itTrip) {
        tripulacaoDados += itTrip->getCodigo() + "|";
    }

    // Concatena os dados dos passageiros
    for (auto itPass = passageiros.begin(); itPass != passageiros.end(); ++itPass) {
        passageirosDados += itPass->getCodigo() + "|";
    }

    // Remove o último caractere '|' (se necessário)
    if (!tripulacaoDados.empty()) {
        tripulacaoDados.pop_back();
    }
    if (!passageirosDados.empty()) {
        passageirosDados.pop_back();
    }

    return codigo + "," + data + "," + hora + "," + origem + "," + destino + "," + codigoAviao + "," +
            tripulacaoDados + "," + passageirosDados + ";\n";
}


string Voo::getCodigo() { return codigo; }

void Voo::setData(string data) { this->data = data; }
string Voo::getData() { return data; }

void Voo::setHora(string hora) { this->hora = hora; }
string Voo::getHora() { return hora; }

void Voo::setOrigem(string origem) { this->origem = origem; }
string Voo::getOrigem() { return origem; }

void Voo::setDestino(string destino) { this->destino = destino; }
string Voo::getDestino() { return destino; }

void Voo::setCodigoAviao(string codigoAviao) { this->codigoAviao = codigoAviao; }
string Voo::getCodigoAviao() { return codigoAviao; }

void Voo::adicionarTripulacao(Tripulacao tripulante) {
    tripulacao.push_back(tripulante);
}

void Voo::adicionarPassageiro(Passageiro passageiro) {
    passageiros.push_back(passageiro);
}

/**
 * Mostrar informações do Voo
 */
void Voo::mostrarVoo() {
    cout << "Codigo: " << getCodigo() << endl;
    cout << "Data: " << getData() << endl;
    cout << "Hora: " << getHora() << endl;
    cout << "Origem: " << getOrigem() << endl;
    cout << "Destino: " << getDestino() << endl;
    cout << "Codigo Aviao: " << getCodigoAviao() << endl;

//implementar passando pela tripulacao e pelos passageiros
    cout << "Tripulacao: ";

        //cout << t.getCodigo() << " ";
    //cout << endl;

    cout << "Passageiros: ";

        //cout << p.getCodigo() << " ";
    //cout << endl;
}

void Voo::adicionarVoo() {
    cout << "Digite a data do voo: ";
    cin >> data;
    setData(data);

    cout << "Digite a hora do voo: ";
    cin >> hora;
    setHora(hora);

    cout << "Digite a origem: ";
    cin >> origem;
    setOrigem(origem);

    cout << "Digite o destino: ";
    cin >> destino;
    setDestino(destino);

    cout << "Digite o codigo do aviao: ";
    cin >> codigoAviao;
    setCodigoAviao(codigoAviao);

    setCodigo();

    
    if (armazenaDadosEmArquivo(FILE_VOO, criaStringDeDados()) == -1) {
        cout << "Erro ao salvar em arquivo!" << endl;
    } else {
        cout << "Voo salvo com sucesso!" << endl;
    }
    
}

/**
 * Metodo para definir acessar e definir o atributo codigo da classe pessoa
 */
void Voo::setCodigo() {
    int maiorCodigoAtual = 0;
    string linha;

    // Abre o arquivo para leitura
    ifstream arq_entrada(FILE_VOO);

    if (!arq_entrada.is_open()) {
        cout << "Erro ao abrir o arquivo de passageiros para leitura." << endl;
        return;
    }

    // Percorre todas as linhas do arquivo
    while (getline(arq_entrada, linha)) {
        // Extrai o codigo (considerando que o codigo esta antes da primeira virgula)
        size_t pos = linha.find(",");
        if (pos != string::npos) {
            string codigoExtraido = linha.substr(0, pos);
            // Remove o prefixo "P" e converte para numero
            if (codigoExtraido[0] == 'V') {
                int codigoNumerico = stoi(codigoExtraido.substr(1));
                if (codigoNumerico > maiorCodigoAtual) {
                    maiorCodigoAtual = codigoNumerico;
                }
            }
        }
    }

    arq_entrada.close();

    // Define o novo codigo incrementando o maior codigo encontrado
    this->codigo = "V" + to_string(maiorCodigoAtual + 1);
}

void Voo::buscarVoo(string codigo) {
    ifstream arq_entrada(FILE_VOO);
    string linha;
    bool encontrado = false;

    if (!arq_entrada.is_open()) {
        cout << "Erro ao abrir o arquivo de voos." << endl;
        return;
    }

    while (getline(arq_entrada, linha)) {
        if (linha.find(codigo + ",") == 0) {
            encontrado = true;
            cout << "Voo encontrado: " << linha << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Voo nao encontrado." << endl;
    }

    arq_entrada.close();
}

void Voo::atualizarVoo(string codigo, Voo &v) {
    // Primeiro busca o voo pelo codigo
    v.buscarVoo(codigo);
    // Pergunta se deseja atualizar os dados
    char escolha;
    cout << "Deseja atualizar as informacoes deste voo? (s/n): ";
    cin >> escolha;
    if (tolower(escolha) != 's') {
        cout << "Atualizacao cancelada." << endl;
        return;
    }
    // Solicita novas informacoes
    string novaData, novaHora, novaOrigem, novoDestino, novoCodigoAviao;
    cout << "Digite a nova data (ou pressione Enter para manter o atual): ";
    cin.ignore();
    getline(cin, novaData);
    cout << "Digite a nova hora (ou pressione Enter para manter o atual): ";
    getline(cin, novaHora);
    cout << "Digite a nova origem (ou pressione Enter para manter o atual): ";
    getline(cin, novaOrigem);
    cout << "Digite o novo destino (ou pressione Enter para manter o atual): ";
    getline(cin, novoDestino);
    cout << "Digite o novo codigo do aviao (ou pressione Enter para manter o atual): ";
    getline(cin, novoCodigoAviao);
    // Atualiza apenas se o usuario informou novos dados
    if (!novaData.empty()) {
        v.setData(novaData);
    }
    if (!novaHora.empty()) {
        v.setHora(novaHora);
    }
    if (!novaOrigem.empty()) {
        v.setOrigem(novaOrigem);
    }
    if (!novoDestino.empty()) {
        v.setDestino(novoDestino);
    }
    if (!novoCodigoAviao.empty()) {
        v.setCodigoAviao(novoCodigoAviao);
    }
    // Atualiza o arquivo
    ifstream arq_entrada("voos.txt");
    ofstream arq_temp("temp.txt");
    if (!arq_entrada.is_open() || !arq_temp.is_open()) {
        cout << "Erro ao abrir os arquivos para atualizacao." << endl;
        return;
    }
    string linha;
    while (getline(arq_entrada, linha)) {
        // Substitui a linha do voo pelo conteudo atualizado
        if (linha.find(codigo + ",") == 0) {
            arq_temp << v.criaStringDeDados() << endl; // Insere os dados atualizados
        } else {
            arq_temp << linha << endl; // Mantem os outros registros
        }
    }
    arq_entrada.close();
    arq_temp.close();
    // Substitui o arquivo original pelo atualizado
    remove("voos.txt");
    rename("temp.txt", "voos.txt");
    cout << "Voo atualizado com sucesso!" << endl;
}

void Voo::excluirVoo(string codigo, Voo &v) {
}

int Voo::armazenaDadosEmArquivo(string arquivo, string dados) {
    ofstream arquivoEscrita(arquivo, ios::app);
    if (!arquivoEscrita.is_open()) {
        cerr << "Erro ao abrir o arquivo " << arquivo << " para escrita.\n";
        return -1;
    }

    arquivoEscrita << dados;
    arquivoEscrita.close();
    return 0;
}