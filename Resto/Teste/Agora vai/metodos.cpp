/* 
  --Trabalho de Estrutura de Dados.
  --Sistema de Cadastro em Hashing Extensível
  --Copyright 2018 by Davi Horner
                      Gabriel Amorim
                      Thiago Luigi  
  --Arquivo contém a implementação das classes e dos módulos;
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include "metodos.hpp"

// Constantes
#define capBloco 4
#define capTabela 16

using namespace std;

// ############################ [Início da implementação do bloco] ###########################

// Construtor da classe Bloco
Bloco::Bloco () {
	for (int i = 0; i < capBloco; i++) {
		bloco[i].id = -1;
		bloco[i].nome[50] = ' ';
		bloco[i].dominio[50] = ' ';
		bloco[i].biografia[200] = ' ';
	}
	tamBloco = 0;
	ativo = false;
}

// Destrutor da classe Bloco
Bloco::~Bloco () {
	for (int i = 0; i < capBloco; i++) {
		bloco[i].id = -1;
		bloco[i].nome[50] = ' ';
		bloco[i].dominio[50] = ' ';
		bloco[i].biografia[200] = ' ';
	}
	tamBloco = 0;
	cabecalho = -1;
}

// Método para inserir no bloco
void Bloco::insereBloco (Dado deus) {
	if (!emUso()) {
		bloco[tamBloco] = deus;
		tamBloco++;
		ativo = true;
		cabecalho = funcaoHash(deus.id);
	} else if (blocoCheio()) {
		cout << "|***************[ERRO]***************|" << endl;
		cout << "| O bloco está cheio.                |" << endl;
		cout << "| Não é possível inserir mais dados. |" << endl;
		cout << "|************************************|" << endl;
		exit(EXIT_FAILURE);
	} else {
		bloco[tamBloco] = deus;
		tamBloco++;
	}
}

// Método para encontrar a posição em bytes do bloco do arquivo
int Bloco::posicaoArquivo (Bloco* novoBloco) {
	ifstream Leitura;
	int pos = -1;
  	Leitura.open("Olimpo.bin", ios::binary);
  	if (Leitura) {
		Leitura.seekg(0, Leitura.end);
		int tamArq = Leitura.tellg();
		Leitura.seekg(0, Leitura.beg);
		int qntBloc = tamArq / sizeof(Bloco);
		Bloco* aux = new Bloco;
		for (int i = 0; i < qntBloc; i++) {
  			Leitura.read((char*)(aux), sizeof(Bloco));
  			if (aux->cabecalho == novoBloco->cabecalho) {
				pos = i*sizeof(Bloco);
			}
  		}
  	} else if (!Leitura) {
  		cout << endl << "Esse deus não está cadastrado" << endl;
  		pos = -1;
  	}
  	Leitura.close();
  	return pos;	
}

// Método para verificar se o bloco está em uso
bool Bloco::emUso () {
	return ativo;
}

// Método para verificar se o bloco está cheio
bool Bloco::blocoCheio () {
	return (tamBloco == 4);
}

// Método para a impressão do bloco
void Bloco::imprimeBloco () {
	if (ativo) {
		cout << ">>>>>>>>>>>>>>>>>>>>>>[BLOCO]<<<<<<<<<<<<<<<<<<<<<<" << endl;
		cout << "Tamanho: " << tamBloco << endl;
		cout << "Cabeçalho: " << cabecalho << endl;
		cout << "Uso: " << ativo << endl;
		Dado* deus = new Dado[tamBloco];
		deus = bloco;
		insertionSort(deus, tamBloco);
		for (int i = 0; i < tamBloco; i++) {
			cout << "=====================(Deus" << " " << i << ")======================" << endl;
			cout << "ID: " << deus[i].id << endl;
			cout << "Nome:" << deus[i].nome << endl;
			cout << "Dominio: " << deus[i].dominio << endl;
			cout << "Biografia: " << deus[i].biografia << endl;
			cout << "===================================================" << endl;
		}
		//Isto é necessário pois como deus é um ponteiro se não fosse apontado para NULL antes de deletado
		//estará apagando o endereço dos blocos.
		deus = NULL;
		delete[] deus;
	}
	cout << endl << endl;
}

// Método para impressão apenas do deus consultado
void Bloco::impressaoConsulta (int id) {
	bool existe = false;
	for (int i = 0; i < tamBloco; i++) {
		if (bloco[i].id == id) {
			cout << "======================(Deus)======================" << endl;
			cout << "ID: " << bloco[i].id << endl;
			cout << "Nome:" << bloco[i].nome << endl;
			cout << "Dominio: " << bloco[i].dominio << endl;
			cout << "Biografia: " << bloco[i].biografia << endl;
			cout << "===================================================" << endl;
			existe = true;
		}
	}
	if (!existe)
		cout << "Esse id não está na cadastrado " << endl;
}

// Método para encontrar a posição no vetor do bloco
int Bloco::posDeus (int id) {
	int posD = -1;
	for (int i = 0; i < tamBloco; i++) {
		if (bloco[i].id == id) {
			posD = i;
		}
	}
	
	return posD;
}

// Método para remover um deus na posição do vetor e também atualizar posições
void Bloco::removeDeus (int posId) {
	bloco[posId].id = -1;
	if (posId < tamBloco -1) {
		for (int i = posId; i < tamBloco-1; i++) {
			bloco[i] = bloco[i+1];  
		}
	} else if (tamBloco == 1) { 
		ativo = false;
	}
	tamBloco--; 
}

// Método para verificar um ID repetido
bool Bloco::procuraIdRepetido (int id) {
	bool existe = false;
	for (int i = 0; i < tamBloco; i++) {
		if (bloco[i].id == id) {
			existe = true;
		}
	}
	return existe;
}

// Método para retornar o tamanho do bloco
int Bloco::tamanhoBloco () {
	return tamBloco;
}

// Método para a impressão de ids
void Bloco::imprimeDeusID () {
	if (ativo) {
		cout << "|BLOCO" << " " << cabecalho << "|" << endl;
		Dado* deus = new Dado[tamBloco];
		deus = bloco;
		insertionSort(deus, tamBloco);
		for (int i = 0; i < tamBloco; i++) {
			cout << "ID: " << deus[i].id << " "; 
			cout << "Nome:" << deus[i].nome;
			cout << endl;
		}
		cout << endl;
		// Isto é necessário pois como deus é um ponteiro se não fosse apontado para NULL antes de deletado
		// estará apagando o endereço dos blocos.
		deus = NULL;
		delete[] deus;
	}
}

// ############################## [Fim da implementação do bloco] ##############################

// ############################ [Início da implementação da tabela] ############################

// Construtor da tabela
tabelaHash::tabelaHash (int cap)  {
	capacidade = cap;
	elementos = new int[capacidade];
	for (int i = 0; i < capacidade; i++) {
		elementos[i] = -1;
	}
}

// Destrutor da tabela
tabelaHash::~tabelaHash () {
	ofstream saida("hashFile.txt");
	for (int i = 0; i < capacidade; i++) {
		saida << converteBinario(i) << "\t" << elementos[i] << endl;
	}
	saida.close();

	delete[] elementos;
}

// Método para inserir na tabela
void tabelaHash::insereTabela (Dado deus) {
	int pos = converteDecimal(funcaoHash(deus.id));
	if (posicaoOcupada(pos)) { // Bloco existe
		Bloco* auxBloco = new Bloco;
		carregaBloco(auxBloco, elementos[pos]);
		auxBloco->insereBloco(deus);
		escreveArquivoVelho(auxBloco, elementos[pos]);
		delete auxBloco;
	} else { // Bloco não existe
		// Cria um novo bloco
		Bloco* novoBloco = new Bloco;
		novoBloco->insereBloco(deus);
		escreveArquivoNovo(novoBloco);
		int bytes = novoBloco->posicaoArquivo(novoBloco);
		elementos[pos] = bytes;
		delete novoBloco;
	}
}

// Método para ler uma tabela do arquivo
void tabelaHash::leTabelaArquivo () {
	ifstream leituraTabelaHash("hashFile.txt");
  	int posicaoTabelaHash, byte;
  	if (leituraTabelaHash.is_open()) {
  		for (int i = 0; i < capTabela; i++) {
  			leituraTabelaHash >> posicaoTabelaHash;
  			leituraTabelaHash >> byte;
  			elementos[converteDecimal(posicaoTabelaHash)] = byte;
  		}
  		leituraTabelaHash.close();
  		cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  		imprimeTabela();
  	}
}

// Método para atualizar a tabela
void tabelaHash::atualizaTabela (int h) {
	elementos[h] = -1;
}

// Método para atualiazar a tabela
void tabelaHash::imprimeTabela () {
	for (int i = 0; i < capacidade; i++) {
		cout << converteBinario(i) << "\t" << elementos[i] << endl;
	}
}

// Método para verificar a posição ocupada
bool tabelaHash::posicaoOcupada (int pos) {
	if (elementos[pos] == -1) {
		return false;
	} else {
		return true;
	}
}

// Método para retornar a posição em bytes
int tabelaHash::posicaoBytes (int h) {
	return elementos[h];
}

// ############################ [Fim da implementação da tabela] ############################

// ####################### [Início da implementação dos módulos globais] ####################

// Subprograma da função hash
int funcaoHash (int i) {
	int h = i % capTabela;
	return converteBinario(h);
}

// Subprograma para converter um decimal para binário
int converteBinario (int decimal) {
    int aux[4];
    int resto, binario;

    aux[3] = decimal % 2;
    resto = decimal / 2;
    aux[2] = resto % 2;
    resto = resto / 2;
    aux[1] = resto % 2;
    resto = resto / 2;
    aux[0] = resto % 2;

    binario = aux[0]*1000 + aux[1]*100 + aux[2]*10 + aux[3]*1;

    return binario;
}

// Subprograma para converter um decimal para binário
int converteDecimal (int binario) {
    int aux[4];
    int decimal;

    aux[0] = binario / 1000;
    binario = binario % 1000;
    aux[1] = binario / 100;
    binario = binario % 100;
    aux[2] = binario / 10;
    aux[3] = binario % 10;

    decimal = (int)(aux[0] * pow(2, 3) + aux[1] * pow(2, 2) + aux[2] * pow(2, 1) + aux[3] * pow(2, 0));
    return decimal;
}

// Subprograma para inserir os dados
void insereDados (tabelaHash* tabelaCadastro) {
	Dado deus;
	// Leitura de Dados:

	bool fail;
	do {
		cout << "Entre com o id do deus:" << endl;
		cin >> deus.id;
		fail = cin.fail(); 
		cin.clear();
		cin.ignore(200, '\n');
		if (fail == true) {
			cerr << "Colocou caráter ao invés de número! Tente novamente !" << endl;
		}
	} while (fail == true);
	
	cout << "Entre com o nome do deus:" << endl;
	cin.getline(deus.nome, 50);
	cout << "Entre com o domínio do deus:" << endl;
	cin.getline(deus.dominio, 50);
	cout << "Entre com a biografia do deus:" << endl;
	cin.getline(deus.biografia, 200);

	int posVal = tabelaCadastro->posicaoBytes(converteDecimal(funcaoHash(deus.id)));
	if (posVal != -1) {
		Bloco* blocIns = new Bloco;
		carregaBloco(blocIns, posVal);
		bool existeRep = blocIns->procuraIdRepetido(deus.id);
		if (existeRep) {
			cout << "Id repetido !" << endl;
			char opcao;
			cout << "Deseja tentar outro id [s/n] " << endl;
			cin >> opcao;
			if (opcao == 's') {
				system("clear");
				return insereDados(tabelaCadastro);
			} else {
				system("clear");
				menu();
				return;
			}
		} else {
			tabelaCadastro->insereTabela(deus);
			cout << endl <<"Deus Cadastrado com sucesso" << endl;
		}
	} else {
		tabelaCadastro->insereTabela(deus);
		cout << endl << "Deus Cadastrado com sucesso" << endl;
	}
	
}

// Subprograma para escrever escrever em um arquivo novo
void escreveArquivoNovo (Bloco* auxBloco) {
	ofstream salva("Olimpo.bin", ios::binary|ios::app);
	if (salva.is_open()) {
		salva.write(reinterpret_cast<const char*> (auxBloco), sizeof(Bloco));
	}	
	salva.close();
}

// Subprograma para escrever em um arquivo já usado
void escreveArquivoVelho (Bloco* auxBloco, int posBytes) {
	fstream salva("Olimpo.bin", ios::binary| ios::out| ios::in);
	if (salva.is_open()) {
		salva.seekp(posBytes, ios::cur);
		salva.write(reinterpret_cast<const char*> (auxBloco), sizeof(Bloco));
	}	
	salva.close();
}

// Subprograma para carregar um bloco
void carregaBloco (Bloco* auxBloco, int posBytes) {
	ifstream Carregar;
	Carregar.open("Olimpo.bin", ios::binary);
	if (Carregar.is_open()) {
		Carregar.seekg(posBytes, ios::cur);
		Carregar.read((char*)(auxBloco), sizeof(Bloco));
	} else {
		cout << endl << "Erro na leitura do arquivo ou arquivo inesistente!" << endl << endl;
	}
	Carregar.close();
}

// Subprograma para remover dados
void removeDados (tabelaHash* tabelaCadastro) {
	imprimeID();
	int id, numH;
	bool fail;
	do {
		cout << "Insira um ID: " << endl;
		cin >> id;
		fail = cin.fail(); 
		cin.clear();
		cin.ignore(200, '\n');
		if (fail == true) {
			cerr << "Colocou caráter ao invés de número! Tente novamente !" << endl;
		}
	} while (fail == true);

	numH = converteDecimal(funcaoHash(id));
	if (tabelaCadastro->posicaoOcupada(numH)) {
		Bloco* blocRem = new Bloco;
		int posBytes = tabelaCadastro->posicaoBytes(numH);
		carregaBloco(blocRem, posBytes);
		int posId = blocRem->posDeus(id);
 		if (posId == -1) {
			cout << "Não exite deus com esse id não está na cadastrado " << endl;
			char opcao;
			cout << "Deseja sair da Remoção [s/n] " << endl;
			cin >> opcao;
			if (opcao == 'n') {
				system("clear");
				return removeDados(tabelaCadastro);
			} else {
				system("clear");
				menu();
				return;
			}
		} else {
			blocRem->removeDeus(posId);
			escreveArquivoVelho(blocRem, posBytes);
			if (blocRem->tamanhoBloco() == 0) {
				tabelaCadastro->atualizaTabela(numH);
			}
			cout << "Deus removido com sucesso" << endl;
		}
		delete blocRem;
	} else  {
		cout << "Não exite deus com esse id não está na cadastrado " << endl;
		char opcao;
		cout << "Deseja sair da Remoção [s/n] " << endl;
		cin >> opcao;
		if (opcao == 'n') {
			system("clear");
			return removeDados(tabelaCadastro);
		} else {
			system("clear");
			menu();
			return;
		}
	}
}

// Subprograma para consultar os dados
void consultaDados (tabelaHash* tabelaCadastro) {
	int id, numH;
	bool fail;
	do {
		cout << "Insira um ID: " << endl;
		cin >> id;
		fail = cin.fail(); 
		cin.clear();
		cin.ignore(200, '\n');
		if (fail == true) {
			cerr << "Colocou caráter ao invés de número! Tente novamente !" << endl;
		}
	} while (fail == true);

	numH = converteDecimal(funcaoHash(id));
	if (tabelaCadastro->posicaoOcupada(numH)) {
		Bloco* blocCons = new Bloco;
		carregaBloco(blocCons, tabelaCadastro->posicaoBytes(numH));
		blocCons->impressaoConsulta(id);
		delete blocCons;
	}
	
}

// Subprograma para imprimri o arquivo em ordem
void imprimeArquivoOrdem () {
	ifstream leitura;
	leitura.open("Olimpo.bin", ios::binary);
	if (leitura.is_open()) {
		Bloco* impTodo = new Bloco;
		leitura.seekg(0, ios::end);
		int tamArq = leitura.tellg();
		leitura.seekg(0, ios::beg);
		int var = sizeof(Bloco);
		int qntBloco = tamArq/var;
		for (int i = 0; i < qntBloco; i++) {		
			leitura.read(reinterpret_cast<char*> (impTodo), sizeof(Bloco));
			impTodo->imprimeBloco();
		}
	}
	
  	leitura.close();
}

// Subprograma para imprimir o bloco em ordem
void imprimeBlocoOrdem (tabelaHash* tabelaCadastro) {
	int numBin;
	tabelaCadastro->imprimeTabela();
	bool fail;
	do {
		cout << endl << "Insira uma posição em número binário correspondente à tabela: " << endl;
		cin >> numBin;
		fail = cin.fail(); 
		cin.clear();
		cin.ignore(200, '\n');
		if (fail == true) {
			cerr << "Colocou caráter ao invés de número! Tente novamente !" << endl;
		}
	} while (fail == true);
	
	if (tabelaCadastro->posicaoBytes(converteDecimal(numBin)) == -1) {
		cout << "Posição Desocupada ! " << endl << endl;
		char opcao;
		cout << "Deseja sair da posição [s/n] " << endl;
		cin >> opcao;
		if (opcao == 'n') {
			system("clear");
			return imprimeBlocoOrdem(tabelaCadastro);
		} else if (opcao != 'n') {
			system("clear");
			menu();
			return;
		}
	} else {
		Bloco* blocOrd = new Bloco;
		carregaBloco(blocOrd, tabelaCadastro->posicaoBytes(converteDecimal(numBin)));
		blocOrd->imprimeBloco();
	}
}

// Subprograma para ordenar os registros durante a inserção
void insertionSort(Dado* deus, int tam){
	int i, j, aux;
	char charAux1[50], charAux2[50], charAux3[200]; 
	for (i = 1; i < tam; i++){
		aux = deus[i].id;
		strcpy(charAux1, deus[i].nome);
		strcpy(charAux2, deus[i].dominio);
		strcpy(charAux3, deus[i].biografia);
		j = i - 1;
		while ((j >= 0) and (aux < signed(deus[j].id))) {
			deus[j+1].id = deus[j].id;
			strcpy(deus[j+1].nome, deus[j].nome);
			strcpy(deus[j+1].dominio, deus[j].dominio);
			strcpy(deus[j+1].biografia, deus[j].biografia);
			j--;
		}
	deus[j+1].id = aux;
	strcpy(deus[j+1].nome, charAux1);
	strcpy(deus[j+1].dominio, charAux2);
	strcpy(deus[j+1].biografia, charAux3);
	}
}

// Subprograma para impressão dos IDs
void imprimeID () {
	ifstream leitura;
		leitura.open("Olimpo.bin", ios::binary);
		if (leitura.is_open()) {
			Bloco* impTdId = new Bloco;
			leitura.seekg(0, ios::end);
			int tamArq = leitura.tellg();
			leitura.seekg(0, ios::beg);
			int var = sizeof(Bloco);
			int qntBloco = tamArq/var;
			for (int i = 0; i < qntBloco; i++) {		
				leitura.read(reinterpret_cast<char*> (impTdId), sizeof(Bloco));
				impTdId->imprimeDeusID();
			}
			leitura.close();
		}
}

// Subprograma para o menu do programa
void menu() {
	cout << endl;
	cout << "|#####################[Menu]#####################|    " << endl;
	cout << "S                                                S    " << endl;
	cout << "|         Entre com a opção desejada:            |    " << endl;
	cout << "S                                                S    " << endl;
	cout << "|                                                |    " << endl;
	cout << "| (1) - para inserir um novo deus no arquivo:    |    " << endl;
	cout << "|                                                |    " << endl;
	cout << "| (2) - para remover um deus do arquivo:         |    " << endl;
	cout << "|                                                |    " << endl;
	cout << "| (3) - para consultar um deus no arquivo:       |    " << endl;
	cout << "|                                                |    " << endl;
	cout << "| (4) - para imprimir todos registros:           |    " << endl;
	cout << "|                                                |    " << endl;
	cout << "| (5) - para imprimir Bloco:                     |    " << endl;
	cout << "|                                                |    " << endl;
	cout << "| (0) - para sair:                               |    " << endl;
	cout << "S                                                S    " << endl;
	cout << "|                                                |    " << endl;
	cout << "S                                                S    " << endl;
	cout << "|################################################|    " << endl;
	cout << endl;
}

// ######################### [Fim da implementação dos módulos globais] ############################