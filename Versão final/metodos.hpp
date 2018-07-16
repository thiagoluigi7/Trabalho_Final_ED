/* 
  --Trabalho de Estrutura de Dados.
  --Sistema de Cadastro em Hashing Extensível
  --Copyright 2018 by Davi Horner
                      Gabriel Amorim
                      Thiago Luigi
  --Arquivo contém as classes e as declarações dos módulos globais;
*/

#ifndef METODOS
#define METODOS

// Constantes
#define capBloco 4
#define capTabela 16

using namespace std;

// Struct Deus
struct deusesGregos {
	int id;
	char nome[50];
	char dominio[50];
	char biografia[200];
};

// Declaração do tipo Dado
typedef deusesGregos Dado;

// Classe bloco
class Bloco {
	friend class tabelaHash;
	friend void insertionSort (Dado* deus, int tam);
	public:
		Bloco ();
		~Bloco ();
		void insereBloco (Dado deus);
		inline bool emUso ();
		bool blocoCheio ();
		void imprimeBloco ();
		void impressaoConsulta (int id);
		int posDeus (int id);
		void removeDeus (int posId);
		bool procuraIdRepetido (int id);
		inline int tamanhoBloco ();
		void imprimeDeusID ();
	protected:
		bool ativo;
		Dado bloco[capBloco];
		int tamBloco;
		int cabecalho;
		int posicaoArquivo (Bloco* novoBloco);
};

// Classe tabela
class tabelaHash {
	public:
		tabelaHash (int cap = capTabela);
		~tabelaHash ();
		void insereTabela (Dado deus);
		void remove (int id);
		bool posicaoOcupada (int pos);
		void leTabelaArquivo ();
		void imprimeTabela ();
		inline int posicaoBytes (int h);
		void atualizaTabela (int h);
	protected :
		int* elementos;
		int capacidade;
};

// Módulos globais
int funcaoHash (int i);
int converteBinario (int decimal);
void insereDados (tabelaHash* tabelaCadastro);
void menu ();
int converteDecimal (int binario);
void escreveArquivoNovo (Bloco* novoBloco);
void escreveArquivoVelho (Bloco* auxBloco, int posBytes);
void carregaBloco (Bloco* auxBloco, int posBytes);
void removeDados (tabelaHash* tabelaCadastro);
void consultaDados (tabelaHash* tabelaCadastro);
void imprimeArquivoOrdem ();
void imprimeBlocoOrdem (tabelaHash* tabelaCadastro);
void insertionSort (Dado* deus, int tam);
void imprimeID ();

#endif // METODOS