// Bibliotecas
#include <iostream>
#include <string>
#include <fstream>   
#include <locale.h>
#include <stdlib.h>

using namespace std;

// Registro para o game
struct game {
	int id;
	char nome[100];
	int anoLancamento;
	char plataforma[100];
	char descricao[700];
};

// Subprogramas secundários
// Subprograma para ler o arquivo de dados
game* lerArquivo(int* tamanho) {
	//Declarações e abertura do arquivo
	ifstream entrada;
	entrada.open("saida.dat", ios::binary);
	game* bloco;
  	if (entrada) {
  		
		//Pega o tamanho do arquivo
		entrada.seekg (0, entrada.end);
		int tam = entrada.tellg();
		entrada.seekg (0, entrada.beg);
		
		//Descobre a quantidade de jogos e lê jogo por jogo, colocando na variável bloco
		bloco = new game [tam/sizeof(game)];		
		int qtd = tam/sizeof(game);
		for (int i = 0; i < qtd; i++) {
			entrada.read (reinterpret_cast<char *> (&bloco[i]), sizeof(game)); 
		}   
		entrada.close();
		
		//salva a quantidade de jogos que o arquivo possui por parametro por referência
		*tamanho = qtd;
	} else {
		*tamanho = 0;
	}
	
	return bloco;
}

// Subprograma para a impressão à tela de um vetor de game 
void print (game dadosGame[], int tam) {
	cout << "_______________________________________________" << endl;
	for (int i = 0; i < tam; i++) {
		cout << "ID: " << dadosGame[i].id << endl;
		cout << "Nome: " << dadosGame[i].nome << endl;
		cout << "Ano de Lançamento: " << dadosGame[i].anoLancamento << endl;
		cout << "Plataforma: " << dadosGame[i].plataforma << endl;
		cout << "Descricao: " << dadosGame[i].descricao << endl;
		cout << "_______________________________________________" << endl;
	}
}
// Subprograma para inserir os dados de um jogo (somente 1 por chamada)
void insercaoDados (int tam) {
	
	//Requisição dos dados do novo jogo
	game* jogo = new game [1];
	cout << "Nome do jogo: ";
	cin.ignore();
	cin.getline(jogo[0].nome, 100);
	cout << "Ano de Lançamento: ";
	cin >> jogo[0].anoLancamento;
	cin.ignore();
	cout << "Plataforma: ";
	cin.getline(jogo[0].plataforma, 100);
	cout << "Descrição: ";
	cin.getline(jogo[0].descricao, 700);
	jogo[0].id = tam+1;

	//Append no arquivo para salvar o novo jogo
	ofstream saida("saida.dat", ios::binary|ios::app);
	saida.write ((const char *) (&jogo[0]), sizeof(game));
	saida.close();
	
	//mensagem de resultado
	cout << "Jogo com id " << jogo[0].id  << " inserido com sucesso!" << endl;
}
// Subprograma para a atualização dos dados cadastrados
void atualizacaoDados (game* jogos, int tam) {
	int id;
	cout << "Qual ID você deseja atualizar? ";
	cin >> id;

	//Pega o indice do elemento a ser editado
	int indice;
	for (int i = 0; i < tam; i++) {
		if (jogos[i].id == id) {
			indice = i;
		}
	}

	//Lê os novos dados
	game novoJogo;
	cout << "Novo nome de " << jogos[indice].nome << ": ";
	cin.ignore();
	cin.getline(novoJogo.nome, 100);
	cout << "Novo ano de lançamento de " << jogos[indice].nome << ": ";
	cin >> novoJogo.anoLancamento;
	cin.ignore();
	cout << "Nova plataforma de " << jogos[indice].nome << ": ";
	cin.getline(novoJogo.plataforma, 100);
	cout << "Nova descricao de " << jogos[indice].nome << ": ";
	cin.getline(novoJogo.descricao, 700);
	novoJogo.id = id;
	system("clear");

	//Controle para confirmação da alteração
	cout << "Você tem certeza que deseja atualizar os seguintes dados: " << endl;
	cout << jogos[indice].nome << " >> "<< novoJogo.nome << endl;
	cout << jogos[indice].descricao << " >> " << novoJogo.descricao << endl;
	cout << jogos[indice].anoLancamento << " >> " << novoJogo.anoLancamento << endl;
	cout << jogos[indice].plataforma << " >> " << novoJogo.plataforma << endl;
	cout << "--Legenda--" << endl;
	cout << "0 - Não" << endl;
	cout << "1 - Sim" << endl;
	int resposta;
	cin >> resposta;
	if (resposta != 1) {
		cout << "Nada foi alterado" << endl;
		return;
	}

	//Salva no arquivo a alteração 
	ofstream saida("saida.dat", ios::binary);
	for (int i = 0; i < tam; i++) {
		if (jogos[i].id == id) {
			saida.write ((const char *) (&novoJogo), sizeof(game));
		} else {
			saida.write ((const char *) (&jogos[i]), sizeof(game));
		}
	}
	saida.close();
	cout << "Tudo alterado com sucesso!" << endl;
}

// Subprograma para uma busca de um ou mais jogos dado um certo ano requisitado pelo usuário
void buscaDados (game dadosGame[], int limite) {
	//Inicializa todas as variáveis necessárias para a busca e requisita o ano à ser buscado
	int anoBuscado, j = 0;
	game aux[limite];
	bool achou = false;
	cout << "Digite o ano que deseja buscar: ";
	cin >> anoBuscado;
	
	//Salva os jogos que possuem o ano requisitado
	for (int i = 0; i < limite; i++) {
		if (dadosGame[i].anoLancamento == anoBuscado) {
			aux[j++] = dadosGame[i];
			achou = true;
		}
	}
	
	//Exibe os resultados
	if (achou) {
		print(aux, j);
	} else {
		cout << "Nenhum dado encontrado." << endl;
	}
}
	
// Subprograma para a ordenação dos dados cadastrados pelo metodo bubble
void ordenacaoDadosCadastrados (game dadosGame[], int limite) {
	game aux;
	for (int i = 0; i < limite - 1; i++) {
		for (int j = 0; j < limite - 1; j++) {
			if (dadosGame[j].anoLancamento > dadosGame[j+1].anoLancamento) {
				aux = dadosGame[j];
				dadosGame[j] = dadosGame[j+1];
				dadosGame[j+1] = aux;
			}
		}
	}
}

// Subprograma principal
int main () {
	//Metodo da classe 
	setlocale(LC_ALL, "Portuguese");
	
	//inicialização sem a escolha de opção
	int opcao = -1;
	
	//inicialização das variáveis que receberá os dados dos arquivos
	game *dadosGame;
	int tam;

	//Main loop
	while (opcao!=0) {
		system("clear");
		
		//menu
		cout << "Entre com a operação desejada" << endl
			 << "1 para inserção de dados" << endl
			 << "2 para atualização de dados" << endl
			 << "3 para busca de dados" << endl
			 << "4 para listagem dos dados cadastrados em ordem crescente" << endl
			 << "0 para sair" << endl;
		cin >> opcao;

		dadosGame = lerArquivo(&tam);

		//Aciona a requisição do do usuário, verificando com switch case a opção selecionada
		switch (opcao) {
			case 1:
				insercaoDados(tam);
				break;
			case 2:
				atualizacaoDados(dadosGame, tam);
				break;
			case 3:
				buscaDados(dadosGame, tam);
				break;
			case 4:
				ordenacaoDadosCadastrados(dadosGame, tam);
				print(dadosGame, tam);
				break;
			case 5:
				print(dadosGame, tam);
				break;
			case 0:
				return 0;
			default:
				cout << "Opção não cadastrada" << endl;
		}
		
		//Pausa para ver qualquer tipo de resultado.
		cout << "Pressione enter para continuar..."; 
		cin.ignore();
		cin.get();
	}
}
