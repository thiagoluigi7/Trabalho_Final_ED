/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Implementação dos Métodos
*/

#include "Métodos.h"
#include <fstream>
#include <math.h>

using namespace std;

//bloco
bloco::bloco(int indexBin) {

  int chaveHash = indexBin;
  bool ativoBloco = true;
  int tam = tam + 1;
  deusesGregos vetorDeuses[4] = {};

}

bloco::~bloco() {

  int chaveHash = -1;
  bool ativoBloco = false;
  int tam = 0;
  deusesGregos vetorDeuses[4] = {};

}

void bloco::insereBloco(deusesGregos d) {

  if(ativoBloco == true) {

    if(tam < 4) {

      vetorDeuses[tam] = d;
      tam++;
      escreveArquivo(d);
      

    } else {

      cout << "[~~~~~~~~ERRO~~~~~~~~]" << endl;
      cout << "[  Bloco está cheio  ]" << endl;
      cout << "[~~~~~~~~~~~~~~~~~~~~]" << endl;

    }

  } else {

    vetorDeuses[tam] = d;
    tam++;
    ativoBloco = true;
    escreveArquivo(d);    

  }
  
}

deusesGregos bloco::procuraBloco(int id) {
  ifstream input("panteao.bin", ios::binary | ios::app);
  
}

void bloco::removeBloco(int id) {
  ofstream output("panteao.bin", ios::binary | ios::app);

}

void bloco::escreveArquivo(deusesGregos d) {

  ofstream output("panteao.bin", ios::binary | ios::ate);
  output.write((char*)(chaveHash), sizeof(int));
  output.write((char*)(ativoBloco), sizeof(bool));
  output.write((char*)(tam), sizeof(int));
  output.write((char*)(d.id), sizeof(int));
  output.write((char*)(d.nome), sizeof(char));
  output.write((char*)(d.dominio), sizeof(char));
  output.write((char*)(d.biografia), sizeof(char));
  output.close();

}

void leBloco(bloco* aux, int posBytes) { //Terminar

  ifstream leitura;
  leitura.open("panteao.bin", ios::binary);
  
  if (leitura) {

    leitura.seekg(posBytes, ios::cur);
    leitura.read((char*) (&aux), sizeof(bloco));

  } else {

    cout << endl << "Erro na leitura do arquivo ou arquivo inexistente!" << endl;

  }

  leitura.close();

}

//Noh
noh::noh() {
  int indexBin = -1; 
  int chaveBloco = -1; 
}

noh::noh(int index, int chave) {
  int indexBin = index; 
  int chaveBloco = chave;
}

//tabelaHash
int funcaoHash(int id) {
  long h = 0;
  h = id % 16;
  return h;
}

int transformarBinario(int numero) {
    int bin = 0;
    int cont = 0;
    int resto;
    numero = funcaoHash(numero);
    while(numero > 0){
        resto = numero % 2;
        numero = numero / 2;
        bin = bin + (resto * pow(10,(cont)));
        cont++;
    }
    return bin;
}

tabelaHash::tabelaHash() {

  capacidade = 16;
  elementos = new noh*[capacidade];
  for(int i=0; i < capacidade; i++) {
    elementos[i]->indexBin = transformarBinario(i);
    elementos[i]->chaveBloco = -1;
  }
  
}

tabelaHash::tabelaHash(int cap) {

  capacidade = cap;
  elementos = new noh*[capacidade];
  for(int i=0; i < capacidade; i++) {
    elementos[i]->indexBin = transformarBinario(i);
    elementos[i]->chaveBloco = -1;

  }
  
}

tabelaHash::~tabelaHash() {
  delete[] elementos;
}

void tabelaHash::insereHash(deusesGregos d) {

  int h;
  h = funcaoHash(d.id);

  if (recuperaHash(d) == "NÃO ENCONTRADO!") {

    bloco* B1 = new bloco(h);
    B1->insereBloco(d);

  } else {

    cout << "Colidiu: " << d.id << endl;
    bloco* B1 = new bloco(h);
    int posBytes = elementos[h]->chaveBloco*sizeof(bloco);
    leBloco(B1, posBytes);
    B1->insereBloco(d);

  }

}

string tabelaHash::recuperaHash(deusesGregos d) {
  int h;
  h = funcaoHash(d.id);
  int b;
  b = transformarBinario(d.id);
  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indexBin == b )) {
    return "ENCONTRADO NA HASH!"; //Melhorar a saída        
  } else {
    return "NÃO ENCONTRADO!";
  }
}

void tabelaHash::removeHash(int id) {
  int h=funcaoHash(id);
  int b=transformarBinario(id);
  
  bloco b1(elementos[h]->indexBin);
  deusesGregos d;
  deusesGregos *pd = &d;
  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indexBin == b)) {
    *pd = b1.procuraBloco(id); //Ficar de olho
    if ((pd != NULL) && (pd->id == id)) {
      b1.removeBloco(id);
    } else {
      cout << "ERRO NA REMOÇÃO" << endl;
    }
  }
}

deusesGregos tabelaHash::buscaHash(int id) { //Ficar de olho

  int h = funcaoHash(id);
  int b = transformarBinario(id);

    bloco b1(elementos[h]->indexBin);

  deusesGregos d;
  deusesGregos *pd = &d;

  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indexBin == b)) {

    *pd = b1.procuraBloco(id);

    if ((pd != NULL) && (pd->id == id)) {

      cout << d.id << d.nome << d.dominio << d.biografia << endl;

    } else {

      cout << "ERRO NA BUSCA" << endl;

    }

  }

}

