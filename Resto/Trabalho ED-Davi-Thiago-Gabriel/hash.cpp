/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Declaração dos Metodos da Hash
*/

#include <iostream>
#include <string>
#include "deusesGregos.h"
#include "hash.h"
#include <cstring>
#include <math.h>
#include <cstdlib>

using namespace std;

deusesGregos procuraBloco(int id);
void removeBloco(int id);

int funcaoHash(int id) {//indice => chave => id; 
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

//construtor padrão
tabelaHash::tabelaHash() {

  elementos = new noh*[capacidade];
  for(int i=0; i < capacidade; i++) {
    elementos[i]->indexBin = transformarBinario(i);
    elementos[i]->chaveBloco = -1;

  }
  
}

//destrutor
tabelaHash::~tabelaHash() {
  delete[] elementos;
}

//insere um valor v com chave c
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

//recupera um valor associado a uma dada chave
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

//retira um valor associado a uma chave
void tabelaHash::removeHash(int id) {
  int h=funcaoHash(id);
  int b=transformarBinario(id);
  
  deusesGregos d;
  deusesGregos *pd = &d;
  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indexBin == b)) {
    *pd = procuraBloco(id); //Ficar de olho
    if ((pd != NULL) && (pd->id == id)) {
      removeBloco(id);
    } else {
      cout << "ERRO NA REMOÇÃO" << endl;
    }
  }
}

deusesGregos tabelaHash::buscaHash(int id) { //Ficar de olho

  int h = funcaoHash(id);
  int b = transformarBinario(id);
  deusesGregos d;
  deusesGregos *pd = &d;

  if ((elementos[h]->chaveBloco != -1) && (elementos[h]->indexBin == b)) {

    *pd = procuraBloco(id);

    if ((pd != NULL) && (pd->id == id)) {

      cout << d.id << d.nome << d.dominio << d.biografia << endl;

    } else {

      cout << "ERRO NA BUSCA" << endl;

    }

  }

}

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