/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Deuses Gregos struct
*/

#ifndef _CLASSE
#define _CLASSE

#include <fstream>

class deusesGregos {
  friend class tabelaHash;
  friend class bloco;
  public:
    int id;
    char nome[50];
    char dominio[50];
    char biografia[200];
};

class bloco {
  friend void imprimirBloco (bloco bloc);
  friend class tabelaHash;
  private:
    bool ativoBloco;
    int tam;
    int compChaveBloco;
    deusesGregos vetorDeuses[4];
  public:
    bloco();
    bool insereNoBloco (deusesGregos d, int compChave);
    deusesGregos procuraNoBloco (int id);
    void insereOrdenado (deusesGregos d);
    bool removeDoBloco (int id);
    bool testarCompChave (int compChave);
    deusesGregos pegarDados (int pos);
    void resetarBloco ();
    int pegarCompChave ();
    void imprimirBloco (const bloco& umBloco);
    void escreverBloco (bloco& umBloco, int posBloco);
    void lerBloco (bloco& umBloco, int posBytes);
};

void imprimeBlocos ();
void imprimirBloco (bloco bloc);

#endif