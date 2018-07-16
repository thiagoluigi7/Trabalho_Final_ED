/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Declaração da Hash
*/

#ifndef _HASH_H
#define _HASH_H

#include "deusesGregos.h"

using namespace std;

int funcaoHash (int indice);
int transformarBinario (int numero);

class noh {
  friend class tabelaHash;
  private:
    int indiceBin;
    int chaveBloco;
  public:
    noh(int indiceBin) {
      this->indiceBin = indiceBin; //'Andar' da Hash em binário
      chaveBloco = -1; // Posição do Bloco
  }
};

class tabelaHash {
  private:
    noh** elementos;
    int capacidade;
    int tam;
  public:
    tabelaHash();
    ~tabelaHash();
    void insereHash(deusesGregos d);
    void removeHash(int id);
    string recuperaHash(int id);
    deusesGregos buscaHash(int id);
    void ler();
    void escrever();
};

#endif
