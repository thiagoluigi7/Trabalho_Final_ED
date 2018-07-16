/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Deuses Gregos struct
*/

#ifndef _DEUSESGREGOS_H
#define _DEUSESGREGOS_H

#include "hash.h"

class noh;
class tabelaHash;

//criação da classe deuses gregos;
class deusesGregos {
friend class noh;
friend class tabelaHash;
friend class bloco;
friend int main();
private:
  int id;
  char nome[50];
  char dominio[50]; // ex: deus da chuva
  char biografia[200];
  //Outros campos
public:
  bool ativoRegistro;
};

class bloco {
friend class noh;
friend class tabelaHash;
private:
  int chaveHash;
  bool ativoBloco = false;
  int tam = 0;
  deusesGregos vetorDeuses[]; // 1+3 colisões
public:
  bloco(int indexBin);
  ~bloco();
  void insereBloco(deusesGregos d);
  deusesGregos procuraBloco(int id);
  void removeBloco(int id);
  void escreveArquivo(deusesGregos d);
};

//Função Global
void leBloco(bloco* aux, int posBytes);

#endif