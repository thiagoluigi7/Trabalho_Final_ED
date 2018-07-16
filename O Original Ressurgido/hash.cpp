/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Declaração dos Metodos da Hash
*/

#include <iostream>
#include <cstring>
#include <math.h>
#include "deusesGregos.h"
#include "hash.h"

using namespace std;

int funcaoHash(int id) { //indice => chave => id; 
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
  tam = 0;
  elementos = new noh*[capacidade];
  for(int i=0; i < capacidade; i++) {
    elementos[i] = new noh(transformarBinario(i));
  }
}

tabelaHash::~tabelaHash() {
  delete[] elementos;
}

void tabelaHash::insereHash(deusesGregos d) {
  int h = funcaoHash(d.id);
  if (recuperaHash(d.id) == "NÃO ENCONTRADO!") {
    elementos[h]->chaveBloco = tam;
    bloco bloc;
    bloc.insereNoBloco(d);
    bloc.escreverBloco(bloc, -1);
    tam++;
  } else {
    cout << "COLIDIU: " << d.id << endl;
    bloco bloc;
    int posBytes = elementos[h]->chaveBloco*sizeof(bloco);
    bloc.lerBloco(bloc, posBytes);
    bloc.insereNoBloco(d);
    bloc.escreverBloco(bloc, elementos[h]->chaveBloco);
  }
}

//recupera um valor associado a uma dada chave
string tabelaHash::recuperaHash(int id) {
  int h = funcaoHash(id);
  int b = transformarBinario(id);
  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indiceBin == b)) {
    return "ENCONTRADO NA HASH!"; //Melhorar a saída        
  } else {
    return "NÃO ENCONTRADO!";
  }
}

deusesGregos tabelaHash::buscaHash(int id) {
  int h = funcaoHash(id);
  int b = transformarBinario(id);
  deusesGregos d;
  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indiceBin == b)) {
    int posBytes = elementos[h]->chaveBloco*sizeof(bloco);
    bloco bloc;
    bloc.lerBloco(bloc, posBytes);
    bloc.procuraNoBloco(id);
  } else {
    cout << "REGISTRO NAO EXISTE" << endl;
  }
  return d;
}

void tabelaHash::ler() {
  ifstream input("tabHash.txt");
  if (input) {
    int i = 0;
    input >> tam;
    while (input >> elementos[i]->indiceBin >> elementos[i]->chaveBloco)
      i++;
  }
  input.close();
}

void tabelaHash::escrever() {
  ofstream output("tabHash.txt");
  output << tam << endl;
  for (int i = 0; i < 16; i++)
    output << elementos[i]->indiceBin << "\t" << elementos[i]->chaveBloco << endl;
  output.close();
}

//retira um valor associado a uma chave
/*void tabelaHash::removeHash(int id) {
  int h=funcaoHash(id);
  int b=transformarBinario(id);
  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indiceBin == b)) {
    bloco B1(h);
    int posBytes = elementos[h]->chaveBloco*sizeof(bloco);
    leBloco(B1, posBytes);
    B1.removeDoBloco(id); //FALTA REMOVER O INDICE NA HASH
  } else {
    cout << "ERRO NA REMOÇÃO" << endl;
  }
}*/

//percorre a tabela hash (Debug) Não terminado
// void tabelaHash::percorre(){
//   noh* atual;
//   for(int i=0;i<capacidade;i++){
//     cout<<i<<":";
//     atual=elementos[i];
//     while(atual!=NULL){
//       cout<<atual->chave<<atual->dg.id;
//       atual = atual->proximo;
//     }
//     cout<<"NULL";
//   }
// }