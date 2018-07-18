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

string transformarBinario (int numero);
int transformarDecimal (string bin);

class noh {
  friend class tabelaHash;
  private:
    string indiceBin;
    int posBloco;
    bool indiceReal;
  public:
    noh (string indiceBin) {
      this->indiceBin = indiceBin;
      posBloco = -1;
      indiceReal = true;
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
    void insereNaHash (deusesGregos d, bool insercaoNormal, int compChave);
    void reinsereBloco (bloco& bloc, int posBloco);
    deusesGregos buscaHash (int id);
    void removeHash (int id);
    void redimensionarHash ();
    string atualizarBin (int id);
    void ler ();
    void escrever ();
};

#endif