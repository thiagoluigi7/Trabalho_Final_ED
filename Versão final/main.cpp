/* 
  --Trabalho de Estrutura de Dados.
  --Sistema de Cadastro em Hashing Extensível
  --Copyright 2018 by Davi Horner
                      Gabriel Amorim
                      Thiago Luigi
  --Arquivo contém as execuções;
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

int main() {
	cout << "Sistema de cadastro: " << endl;
	int opcao;
	char questao;

	// Criação da tabela hash
	tabelaHash* tabelaCadastro =  new tabelaHash;

	// Leitura das informações de uma tabela, caso exista uma no arquivo hashFile.txt
	tabelaCadastro->leTabelaArquivo();
	
	// Loop principal do programa
	do {
		menu();
		cin >> opcao;
		// Estrutura seletiva para a escola das opções
		switch (opcao) {
			case 0:
			{
				cout << "Programa terminado." << endl;
				
				break;
			}
			case 1:
			{
				// Subprograma para inserir um novo objeto no arquivo
				insereDados(tabelaCadastro);
				
				cout << endl << "Deseja continuar no programa ? [s/n] " << endl;
				cin >> questao;
				if (questao == 'n') {
					opcao = 0; 
				}
				system("clear");

				break;
			}
			case 2:
			{
				// Subprograma para remover um objeto do arquivo.
				removeDados(tabelaCadastro);
				cout << endl << "Deseja continuar no programa ? [s/n] " << endl;
				cin >> questao;
				if (questao == 'n') {
					opcao = 0; 
				}
				system("clear");

				break;
			}
			case 3:
			{
				// Subprograma para consultar um deus no arquivo.
				consultaDados(tabelaCadastro);
				cout << endl << "Deseja continuar no programa ? [s/n] " << endl;
				cin >> questao;
				if (questao == 'n') {
					opcao = 0; 
				}
				system("clear");

				break;
			}
			case 4:
			{
				// Subprograma para imprimir todo o conteúdo do arquivo, na ordem de armazenamento.
				imprimeArquivoOrdem();
				cout << endl << "Deseja continuar no programa ? [s/n] " << endl;
				cin >> questao;
				if (questao == 'n') {
					opcao = 0; 
				}
				system("clear");
			
				break;
			}
			case 5:
			{
				// Subprograma para imprimir todo o bloco com os deuses ordenados.
				imprimeBlocoOrdem(tabelaCadastro);
				cout << endl << "Deseja continuar no programa? [s/n] " << endl;
				cin >> questao;
				if (questao == 'n') {
					opcao = 0; 
				}
				system("clear");
				
				break;
			}
			default:
			{
				system("clear");
				cout << "Opção não cadastrada! Tente novamente." << endl;
				
				break;
			}
		}
	} while (opcao != 0);
	delete tabelaCadastro;
	return 0;
}
