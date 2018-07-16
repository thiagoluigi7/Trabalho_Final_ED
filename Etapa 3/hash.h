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

int funcaoHash (int id, int capacidade);
string transformarBinario (int numero);
int transformarDecimal (string bin);

class noh {
  friend class tabelaHash;
  private:
    string indiceBin;
    int chaveBloco;
    bool indiceAtivo;
  public:
    noh (string indiceBin) {
      this->indiceBin = indiceBin; //'Andar' da Hash em binário
      chaveBloco = -1; // Posição do Bloco
      indiceAtivo = false;
  }
};

class tabelaHash {
  private:
    noh** elementos;
    int capacidade;
    int tam;
    int compChave;
  public:
    tabelaHash ();
    ~tabelaHash ();
    void insereHash (deusesGregos d);
    //int recuperaHash (int id);
    deusesGregos buscaHash (int id);
    void removeHash (int id);
    void redimensionarHash ();
    string atualizarBin (int id);
    void ler ();
    void escrever ();
};

#endif