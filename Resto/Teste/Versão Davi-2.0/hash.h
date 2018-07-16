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

class deusesGregos;
class bloco;

using namespace std;

int funcaoHash (int indice);
int transformarBinario (int numero);

class noh {
friend class tabelaHash;
private:
  int indexBin;
  int chaveBloco;
public:
  noh();
};

class tabelaHash {
friend class deusesGregos;
friend int main();
friend class bloco;
private:
  //vetor de ponteiros de nós
  noh** elementos;
  int capacidade = 16;
public:
  //construtor padrão
  tabelaHash();
  //destrutor
  ~tabelaHash();
  //insere um valor chave v com chave c
  void insereHash(deusesGregos d);
  //recupera um valor associado a uma dada chave
  string recuperaHash(deusesGregos d);
  //retira um valor associado a uma chave
  void removeHash(int id);
  //busca um struct no bloco usando a tabela
  deusesGregos buscaHash(int id);
  //percorre a tabela para debug
  //void percorre();
  
};

#endif
