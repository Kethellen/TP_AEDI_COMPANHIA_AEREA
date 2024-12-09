#include "passageiro.h"

#define FILE_PASSAGEIRO "../data_files/passageiro.txt"

/**
 * Construtor padrao da classe Passageiro
 */
Passageiro::Passageiro():Pessoa(){
    endereco = "\0";
    pontosDeFidelidade = 0;
}

/**
 * Metodo que cria a string de dados para armazenamento no arquivo
 */
string Passageiro::criaStringDeDados() {
    return this->codigo + "," + 
    this->nome + "," + 
    this->telefone + "," +
    this->endereco + "," + 
    to_string(this->pontosDeFidelidade) + 
    ";\n";
}

/**
 * Metodo para definir acessar e definir o atributo endereco da classe pessoa
 */
void Passageiro::setEndereco(string endereco){
    this->endereco = endereco;
}

/**
 * Metodo para definir acessar o atributo endereco da classe pessoa
 */
string Passageiro::getEndereco(){
    return endereco;
}

/**
 * Metodo para definir acessar e definir o atributo codigo da classe pessoa
 */
void Passageiro::setCodigo() {
    int maiorCodigoAtual = 0;
    string linha;

    // Abre o arquivo para leitura
    ifstream arq_entrada(FILE_PASSAGEIRO);

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
            if (codigoExtraido[0] == 'P') {
                int codigoNumerico = stoi(codigoExtraido.substr(1));
                if (codigoNumerico > maiorCodigoAtual) {
                    maiorCodigoAtual = codigoNumerico;
                }
            }
        }
    }

    arq_entrada.close();

    // Define o novo codigo incrementando o maior codigo encontrado
    this->codigo = "P" + to_string(maiorCodigoAtual + 1);
}

/**
 * Metodo auxiliar para setar codigo na busca
 */
void Passageiro::setCodigo(string codigo) {
    this->codigo = codigo;
}

/**
 * Metodo para definir acessar o atributo codigo da classe pessoa
 */
string Passageiro::getCodigo(){
    return codigo;
}

/**
 * Metodo para exibir os atributos da classe pessoa
 */
void Passageiro::mostrarPessoa(){
    cout << "Nome da pessoa: " << getPessoa() << endl;
    cout << "Telefone: " << getTelefone() << endl;
    cout << "Endereco: " << getEndereco() << endl;
    cout << "Codigo: " << getCodigo() << endl;
}

/**
 * Metodo para adicionar novos passageiros
 */
void Passageiro::adicionaPassageiro(Passageiro &p){
    
    cout << "Digite o nome do passageiro: ";
    cin.ignore(); //Limpa o buffer de entrada do primeiro getline
    getline(cin, nome);
    p.setPessoa(nome);

    cout << "Digite o telefone do passageiro: ";
    getline(cin, telefone);
    p.setTelefone(telefone);

    cout << "Digite o endereco do passageiro: ";
    getline(cin, endereco);
    p.setEndereco(endereco);
    p.setCodigo();

    cout << "Cadastro adicionado com sucesso!" << endl;
    
    if(p.armazenaDadosEmArquivo(FILE_PASSAGEIRO, p.criaStringDeDados()) == -1){
        cout << "\nErro ao salvar em arquivo!\n";
    }
    else{
        cout << "\nInformacoes salvas em arquivo!\n";
    }
}

/**
 * Metodo para buscar novos passageiros
 */
void Passageiro::buscaPassageiro(string codigo) {
    bool encontrado = false;
    string linha;

    ifstream arq_entrada(FILE_PASSAGEIRO);

    if (!arq_entrada.is_open()) {
        cout << "Erro ao abrir o arquivo de passageiros para leitura" << endl;
        return;
    }

    while (getline(arq_entrada, linha)) {
        // Verifica se a linha contem o codigo do passageiro
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
            if (partes.size() >= 4) { // Certifica que ha ao menos 4 partes
                setCodigo(codigo);
                setPessoa(partes[1]);    // Nome
                setTelefone(partes[2]);  // Telefone
                setEndereco(partes[3]);  // Endereco

                cout << "Passageiro encontrado com as seguintes informacoes:\n";
                mostrarPessoa();// Exibe as informacoes
            }
            break;
        }
    }

    arq_entrada.close();

    if (!encontrado) {
        cout << "Passageiro com codigo " << codigo << " nao encontrado." << endl;
    }
}

/**
 * Metodo para atualizar novos passageiros
 */
void Passageiro::atulizaPassageiro(string codigo, Passageiro &p) {
    // Primeiro busca o passageiro pelo codigo
    p.buscaPassageiro(codigo);

    // Pergunta se deseja atualizar os dados
    char escolha;
    cout << "Deseja atualizar as informacoes deste passageiro? (s/n): ";
    cin >> escolha;

    if (tolower(escolha) != 's') {
        cout << "Atualizacao cancelada." << endl;
        return;
    }

    // Solicita novas informacoes
    string novoNome, novoTelefone, novoEndereco;

    cout << "Digite o novo nome (ou pressione Enter para manter o atual): ";
    cin.ignore();
    getline(cin, novoNome);

    cout << "Digite o novo telefone (ou pressione Enter para manter o atual): ";
    getline(cin, novoTelefone);

    cout << "Digite o novo endereco (ou pressione Enter para manter o atual): ";
    getline(cin, novoEndereco);

    // Atualiza apenas se o usuario informou novos dados
    if (!novoNome.empty()) {
        p.setPessoa(novoNome);
    }
    if (!novoTelefone.empty()) {
        p.setTelefone(novoTelefone);
    }
    if (!novoEndereco.empty()) {
        p.setEndereco(novoEndereco);
    }

    // Atualiza o arquivo
    ifstream arq_entrada(FILE_PASSAGEIRO);
    ofstream arq_temp("temp.txt");

    if (!arq_entrada.is_open() || !arq_temp.is_open()) {
        cout << "Erro ao abrir os arquivos para atualizacao." << endl;
        return;
    }

    string linha;
    while (getline(arq_entrada, linha)) {
        // Substitui a linha do passageiro pelo conteudo atualizado
        if (linha.find(codigo + ",") == 0) {
            arq_temp << p.criaStringDeDados(); // Insere os dados atualizados
        } else {
            arq_temp << linha << endl; // Mantem os outros registros
        }
    }

    arq_entrada.close();
    arq_temp.close();

    // Substitui o arquivo original pelo atualizado
    remove(FILE_PASSAGEIRO);
    rename("temp.txt", FILE_PASSAGEIRO);

    cout << "Passageiro atualizado com sucesso!" << endl;
}

/**
 * Metodo para excluir passageiros
 */
void Passageiro::excluirPassageiro(string codigo, Passageiro &p) {
    // Primeiro busca o passageiro pelo codigo
    p.buscaPassageiro(codigo);
    // Pergunta se deseja excluir o passageiro
    char escolha;
    cout << "Deseja excluir este passageiro? (s/n): ";
    cin >> escolha;

    if (tolower(escolha) != 's') {
        cout << "Exclusao cancelada." << endl;
        return;
    }

    // Atualiza o arquivo
    ifstream arq_entrada(FILE_PASSAGEIRO);
    ofstream arq_temp("temp.txt");

    if (!arq_entrada.is_open() || !arq_temp.is_open()) {
        cout << "Erro ao abrir os arquivos para exclusao." << endl;
        return;
    }

    string linha;
    bool encontrado = false;

    while (getline(arq_entrada, linha)) {
        // Se encontrar o passageiro pelo codigo, nao escreve essa linha no arquivo temporario
        if (linha.find(codigo + ",") == 0) {
            encontrado = true;
            cout << "Passageiro excluido com sucesso!" << endl;
        } else {
            arq_temp << linha << endl; // Mantem os outros registros
        }
    }

    if (!encontrado) {
        cout << "Passageiro nao encontrado!" << endl;
    }

    arq_entrada.close();
    arq_temp.close();

    // Substitui o arquivo original pelo atualizado
    remove(FILE_PASSAGEIRO);
    rename("temp.txt", FILE_PASSAGEIRO);
}
