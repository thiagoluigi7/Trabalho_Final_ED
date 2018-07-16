/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Declaração dos Métodos
*/


#ifndef MÉTODOS_H
#define MÉTODOS_H
#include <iostream>

using namespace std;

class deusesGregos { 
    friend class noh;
    friend class bloco;
    friend class tabelaHash;
    friend int main();
    private:
        int id;
        char nome[50];
        char dominio[50];
        char biografia[200];
    public:
        bool ativoRegistro;
};

class bloco {
    friend class deusesGregos;
    friend class tabelaHash;
    friend int main();
    private:
        int chaveHash;
        bool ativoBloco;
        int tam;
        deusesGregos vetorDeuses[];
    public:
        bloco(int indexBin);
        ~bloco();
        void insereBloco(deusesGregos d);
        deusesGregos procuraBloco(int id);
        void removeBloco(int id);
        void escreveArquivo(deusesGregos d);
};

class noh {
friend class tabelaHash;
private:
  int indexBin;
  int chaveBloco;
public:
  noh();
  noh(int indexBin, int chaveBloco);
};

class tabelaHash {
    friend class bloco;
    friend class deusesGregos;
    friend int main();
    private:
        noh** elementos;
        int capacidade;
    public:
        tabelaHash ();
        tabelaHash(int cap);
        ~tabelaHash ();
        void insereHash(deusesGregos d);
        string recuperaHash(deusesGregos d);
        void removeHash(int id);
        deusesGregos buscaHash(int id);
};

#endif