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

//criação da classe deuses gregos;
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
  friend void imprimeBlocos ();
  friend void imprimirBloco (bloco bloc);
  friend class tabelaHash;
  private:
    bool ativoBloco;
    int tam;
    //int chaveHash; //NAO SEI SE PRECISA
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
    void escreverBloco (bloco& umBloco, int posBloco);
    void lerBloco (bloco& umBloco, int posBytes);
};

void imprimeBlocos ();
void imprimirBloco (bloco bloc);

#endif