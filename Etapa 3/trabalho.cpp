/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Main
*/

#include <iostream>
#include "hash.h"
#include "deusesGregos.h"

using namespace std;

void menu_principal(){
  cout << endl;
  cout << "[#####################[MENU]#########################]" << endl;
  cout << "[ Entre com a opção desejada :                       ]" << endl;
  cout << "[ (1) -  para inserir um novo deus :                 ]" << endl;
  cout << "[ (2) -  para remover um deus :                      ]" << endl;
  cout << "[ (3) -  para consultar um deus :                    ]" << endl;
  cout << "[ (4) -  para imprimir todos registros :             ]" << endl;
  cout << "[ (5) -  para imprimir um bloco especifico :         ]" << endl;
  cout << "[ (0) -  para sair :                                 ]" << endl;
  cout << "[####################################################]" << endl << endl;
}

int main() {
  tabelaHash tabela;
  tabela.ler();
  int escolha = -1;
  while(escolha != 0) {
    menu_principal();
    cin >> escolha;
    switch (escolha) {
      case 1: {
        deusesGregos d;
        cout << "Digite o id do deus: " << endl;
        cin >> d.id;
        cin.ignore();
        cout << "Digite o nome do deus: " << endl;
        cin.getline(d.nome, 50);
        cout << "Digite o domínio do deus: " << endl;
        cin.getline(d.dominio, 50);
        cout << "Digite a biografia do deus: " << endl;
        cin.getline(d.biografia, 200);
        tabela.insereHash(d);
        break;
      }
      case 2: {
        cout << "Deus a ser removido: " << endl;
        int id;
        cin >> id;
        tabela.removeHash(id);
        break;
      }
      case 3: {
        cout << "Digite o ID do deus: " << endl;
        int id;
        cin >> id;
        tabela.buscaHash(id);
        break;
      }
      case 4: {
        imprimeBlocos();
        break;
      }
      case 5: {
        
        break;
      }
      default: {
        
        break;
      }
    }
  }
  tabela.escrever();
  return 0;
}
