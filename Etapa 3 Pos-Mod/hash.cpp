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

void tabelaHash::insereNaHash(deusesGregos d, bool insercaoNormal, int compChave) {
  int h = transformarDecimal(atualizarBin(d.id));
  if (elementos[h]->posBloco == -1 || (!elementos[h]->indiceReal && !insercaoNormal)) {
      elementos[h]->posBloco = tam;
      elementos[h]->indiceReal = true;
      bloco bloc;
      bloc.insereNoBloco(d, compChave);
      bloc.escreverBloco(bloc, -1);
      tam++;
      bloc.escreverBloco(bloc, elementos[h]->posBloco);
  } else {
    bloco bloc;
    int posBytes = elementos[h]->posBloco*sizeof(bloco);
    bloc.lerBloco(bloc, posBytes);
    if (bloc.insereNoBloco(d, compChave)) {
      bloc.escreverBloco(bloc, elementos[h]->posBloco);
    } else {
      if (bloc.testarCompChave(this->compChave)) {
        redimensionarHash();
        cout << "\nRedimensionou!" << endl;
        reinsereBloco(bloc, elementos[h]->posBloco);
        insereNaHash(d, 0, bloc.pegarCompChave());
      } else {
        reinsereBloco(bloc, elementos[h]->posBloco);
        insereNaHash(d, 0, bloc.pegarCompChave());
        cout << "\nDivisao de Bloco!" << endl;
      }
    }
  }
  cout << "\nInserido com sucesso!" << endl; //PRECISA DE CORRECAO
}

void tabelaHash::reinsereBloco (bloco& umBloco, int posBloco) {
  deusesGregos vetorAux[4];
  for (int i = 0; i < 4; i++) {
    vetorAux[i] = umBloco.pegarDados(i);
  }
  umBloco.resetarBloco();
  umBloco.escreverBloco(umBloco, posBloco);
  for (int i = 0; i < 4; i++) {
    insereNaHash(vetorAux[i], 0, compChave);
  }
}

string tabelaHash::atualizarBin(int id) {
  string bin = transformarBinario(id);
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

deusesGregos tabelaHash::buscaHash(int id) {
  int h = transformarDecimal(atualizarBin(id));
  deusesGregos d;
  if (elementos[h]->posBloco != -1) {
    int posBytes = elementos[h]->posBloco*sizeof(bloco);
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
    novoVetor[i]->posBloco = elementos[i]->posBloco;
    novoVetor[capacidade+i]->posBloco = elementos[i]->posBloco;
    novoVetor[capacidade+i]->indiceReal = false;
  }

  delete[] elementos;

  capacidade = novaCapacidade;
  elementos = new noh*[capacidade];
  for(int i = 0; i < capacidade; i++) {
    elementos[i] = new noh(transformarBinario(i));
  }
  for (int i = 0; i < capacidade; i++) {
    elementos[i]->posBloco = novoVetor[i]->posBloco;
    elementos[i]->indiceReal = novoVetor[i]->indiceReal;
  }

  delete[] novoVetor;

  compChave++;
}

void tabelaHash::removeHash(int id) {
  int h = transformarDecimal(atualizarBin(id));
  if (elementos[h]->posBloco != -1) {
    int posBytes = elementos[h]->posBloco*sizeof(bloco);
    bloco bloc;
    bloc.lerBloco(bloc, posBytes);
    bool ativo = bloc.removeDoBloco(id);
    bloc.escreverBloco(bloc, elementos[h]->posBloco);
    if (!ativo) {
      elementos[h]->posBloco = -1;
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
    delete[] elementos;
    elementos = new noh*[capacidade];
    for(int i = 0; i < capacidade; i++) {
      elementos[i] = new noh(transformarBinario(i));
    }
    while (input >> elementos[i]->indiceBin >> elementos[i]->posBloco) {
      i++;
    }
  }
  input.close();
}

void tabelaHash::escrever() {
  for (int i = 0; i < capacidade; i++) {
    cout << elementos[i]->indiceBin << "\t" << elementos[i]->posBloco << endl;
  }
  ofstream output("tabHash.txt");
  output << tam << endl << capacidade << endl << compChave;
  for (int i = 0; i < capacidade; i++)
    output << endl << elementos[i]->indiceBin << "\t" << elementos[i]->posBloco;
  output.close();
}