/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Main
*/

#include <iostream>
#include <fstream>
#include "hash.h"
#include "deusesGregos.h"



using namespace std;

//Nomear funçoes
void menu_principal();


void menu_principal(){
  cout << endl;
  cout << "[#####################[MENU]#########################]" << endl;
  cout << "[ Entre com a opção desejada :                       ]" << endl;
  cout << "[ (1) -  para inserir um novo deus no arquivo :      ]" << endl;
  cout << "[ (2) -  para remover um deus do arquivo :           ]" << endl;
  cout << "[ (3) -  para consultar um deus no arquivo :         ]" << endl;
  cout << "[ (4) -  para imprimir todos registros :             ]" << endl;
  cout << "[ (5) -  para imprimir de modo ordenado :            ]" << endl;
  cout << "[ (0) -  para sair :                                 ]" << endl;
  cout << "[####################################################]" << endl << endl;
}


int main() {

  tabelaHash* tabela = new tabelaHash();
  //ofstream output("indice.bin", ios::app | ios::binary);
  //ofstream output("panteao.bin", ios::binary); //
  int escolha = -1;
  deusesGregos dg;

  while(escolha != 0) {
    menu_principal();
    cin >> escolha;

    switch (escolha) {
      //Função Inserir
      case 1:
        {
             
          cout << "Digite o id do deus: " << endl;

				  cin >> dg.id;

				  cin.ignore();

				  cout << "Digite o nome do deus: " << endl;

				  cin.getline(dg.nome, 50);

				  cout << "Digite o domínio do deus: " << endl;

				  cin.getline(dg.dominio, 10);

				  cout << "Digite a biografia do deus: " << endl;

				  cin.getline(dg.biografia, 200);
          
          tabela->insereHash(dg);
          
          break;
        }
      case 2:
        {
          cout << "Deus a ser remover: " << endl;

          break;
        }
      case 3:
        {
          cout << "Deus a ser consultado: " << endl;
          break;
        }
      case 4:
        {
          
          break;
        }
      case 5:
        {
          break;
        }
      default:
        {
          cout << "Favor inserir número válido" << endl;
          break;
        }
    }
  }

  return 0;
}
