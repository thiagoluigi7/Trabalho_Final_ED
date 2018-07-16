/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Declaração dos Metodos da Hash
*/

#include <iostream>
#include "deusesGregos.h"
#include "hash.h"

using namespace std;

int funcaoHash (int id, int capacidade) {
  //int h = 0;
  //h = id % capacidade;
  return id;
}

string transformarBinario (int numero) {
    int cont = 0;
    int num = numero;
    while (num > 0) {
        num /= 2;
        cont++;
    }
    if (cont == 0) {
        char* bin = new char[2];
        bin[0] = 48;
        bin[1] = '\0';
        return bin;
    }
    char* bin = new char[cont+1];
    int resto;
    int i = cont-1;
    while (numero > 0) {
        resto = numero%2;
        bin[i] = resto + 48;
        numero /= 2;
        i--;
    }
    bin[cont] = '\0';
    return bin;
}

int transformarDecimal (string bin) {
    int decimal = 0;
    while (transformarBinario(decimal) != bin)
        decimal++;
    return decimal;
}

tabelaHash::tabelaHash() {
  capacidade = 2;
  tam = 0;
  compChave = 1;
  elementos = new noh*[capacidade];
  for(int i = 0; i < capacidade; i++) {
    elementos[i] = new noh(transformarBinario(i));
  }
}

tabelaHash::~tabelaHash() {
  delete[] elementos;
}

void tabelaHash::insereHash(deusesGregos d) {
  int h = transformarDecimal(atualizarBin(d.id));
  if (elementos[h]->indiceAtivo == false) {
    elementos[h]->chaveBloco = tam;
    elementos[h]->indiceAtivo = true;
    bloco bloc;
    bloc.insereNoBloco(d, compChave);
    bloc.escreverBloco(bloc, -1);
    tam++;
    cout << "PASSOU AQUI" << d.id << endl;
  } else {
    cout << "COLIDIU: " << d.id << endl;
    bloco bloc;
    int posBytes = elementos[h]->chaveBloco*sizeof(bloco);
    bloc.lerBloco(bloc, posBytes);
    if (bloc.insereNoBloco(d, compChave)) {
      cout << "Inserção bem sucedida" << endl;
    } else {
      if (bloc.testarCompChave(compChave)) {
        redimensionarHash();
        cout << "\nRedimensionou!" << endl;
        insereHash(d);
        for (int i = 0; i < 4; i++) {
          insereHash(bloc.pegarDados(i));
        }
      } else {
        /*for (int i = 0; i < 4; i++) {
          insereHash(bloc.pegarDados(i));
        }*/
      }
    }
    bloc.escreverBloco(bloc, elementos[h]->chaveBloco);
  }
}

/////////////////////////////////////////
string tabelaHash::atualizarBin(int id) {
  string bin = transformarBinario(funcaoHash(id, capacidade));
  int tamBin = bin.size();
  char* binAux;
  if (tamBin <= compChave) {
    binAux = new char[tamBin+1];
    for (int i = 0; i < tamBin; i++) {
        binAux[i] = bin[i];
    }
    binAux[tamBin] = '\0';
  }
  else {
    binAux = new char[compChave+1];
    for (int i = 0; i < compChave; i++) {
        binAux[i] = bin[i];
    }
    binAux[compChave] = '\0';
  }
  return binAux;
}

//recupera um valor associado a uma dada chave
/*int tabelaHash::recuperaHash(int id) {
  int h = transformarDecimal(atualizarBin(id));
  if (elementos[h]->chaveBloco != -1) {
    return h;
  }
  return -1;
}*/

deusesGregos tabelaHash::buscaHash(int id) {
  int h = transformarDecimal(atualizarBin(id));
  deusesGregos d;
  if (elementos[h]->chaveBloco != -1) {
    int posBytes = elementos[h]->chaveBloco*sizeof(bloco);
    bloco bloc;
    bloc.lerBloco(bloc, posBytes);
    bloc.procuraNoBloco(id);
  } else {
    cout << "REGISTRO NAO EXISTE" << endl;
  }
  return d;
}

void tabelaHash::redimensionarHash () {
  int novaCapacidade = capacidade*2;
  noh** novoVetor = new noh*[novaCapacidade];
  for(int i = 0; i < novaCapacidade; i++) {
    novoVetor[i] = new noh(transformarBinario(i));
  }
  for (int i = 0; i < capacidade; i++) {
    novoVetor[i]->chaveBloco = elementos[i]->chaveBloco;
    novoVetor[capacidade+i]->chaveBloco = elementos[i]->chaveBloco;
  }
  for (int i = 0; i < capacidade; i++) {
    delete elementos[i];
  }
  delete[] elementos;

  capacidade = novaCapacidade;
  elementos = new noh*[capacidade];
  for(int i = 0; i < capacidade; i++) {
    elementos[i] = new noh(transformarBinario(i));
  }
  for (int i = 0; i < capacidade; i++) {
    elementos[i]->chaveBloco = novoVetor[i]->chaveBloco;
  }

  for (int i = 0; i < capacidade; i++) {
    novoVetor[i] = NULL;
    delete novoVetor[i];
  }
  delete[] novoVetor;

  compChave++;
}

void tabelaHash::removeHash(int id) {
  int h = transformarDecimal(atualizarBin(id));
  if (elementos[h]->chaveBloco != -1) {
    int posBytes = elementos[h]->chaveBloco*sizeof(bloco);
    bloco bloc;
    bloc.lerBloco(bloc, posBytes);
    bool ativo = bloc.removeDoBloco(id);
    bloc.escreverBloco(bloc, elementos[h]->chaveBloco);
    if (!ativo) {
      elementos[h]->chaveBloco = -1;
      tam--;
    }
  } else {
    cout << "REGISTRO NAO EXISTE" << endl;
  }
}

void tabelaHash::ler() {
  ifstream input("tabHash.txt");
  if (input) {
    int i = 0;
    input >> tam >> capacidade >> compChave;
    while (input >> elementos[i]->indiceBin >> elementos[i]->chaveBloco)
      i++;
  }
  input.close();
}

void tabelaHash::escrever() {
  for (int i = 0; i < capacidade; i++) {
    cout << elementos[i]->indiceAtivo << " ";
    cout << elementos[i]->indiceBin << "\t" << elementos[i]->chaveBloco << endl;
  }
  ofstream output("tabHash.txt");
  output << tam << endl << capacidade << endl << compChave << endl;
  for (int i = 0; i < capacidade; i++)
    output << elementos[i]->indiceBin << "\t" << elementos[i]->chaveBloco << endl;
  output.close();
}

//percorre a tabela hash (Debug) Não terminado
// void tabelaHash::percorre(){
//   noh* atual;
//   for(int i=0;i<capacidade;i++){
//     cout<<i<<":";
//     atual=elementos[i];
//     while(atual!=NULL){
//       cout<<atual->chave<<atual->dg.id;
//       atual = atual->proximo;
//     }
//     cout<<"NULL";
//   }
// }