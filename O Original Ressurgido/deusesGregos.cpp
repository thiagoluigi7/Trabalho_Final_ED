/*
  Trabalho de Estrutura de Dado
  Monte Olimpo
  Copyright 2018 by Davi Horner
                    Gabriel Amorim
                    Thiago Luigi
  Arquivo Deuses Gregos método
*/
#include <iostream>
#include <fstream>
#include "deusesGregos.h"
#include "hash.h"

using namespace std;

bloco::bloco() {
  chaveHash = -1;
  ativoBloco = false;
  tam = 0;
  for (int i = 0; i < 4; i++) {
    vetorDeuses[i].id = -1;
    vetorDeuses[i].nome[50] = ' ';
    vetorDeuses[i].dominio[50] = ' ';
    vetorDeuses[i].biografia[200] = ' ';
  }
}

void bloco::insereNoBloco(deusesGregos d) { //NAO PODE INSERIR REPETIDO
  if(ativoBloco == true) {
    if(tam < 4) {
      chaveHash = transformarBinario(funcaoHash(d.id));
      //if (insereOrdenado(vetorDeuses, d)) {
        vetorDeuses[tam] = d;
        tam++;
      //}
    } else {
      cout << "BLOCO CHEIO" << endl;
    }
  } else {
    chaveHash = transformarBinario(funcaoHash(d.id));
    ativoBloco = true;
    vetorDeuses[tam] = d;
    tam++;
  }
}

void bloco::insereOrdenado (deusesGregos vetorDeuses[], deusesGregos d) {
  
}

deusesGregos bloco::procuraNoBloco(int id) { //ARRUMAR PARA O CASO DE SER MESMA HASH E NAO ENCONTRAR ID
  deusesGregos d;
  if (ativoBloco != false) {
    for (int i = 0; i < 4; i++) {
      if (vetorDeuses[i].id == id) {
          cout << vetorDeuses[i].id << endl << vetorDeuses[i].nome << endl << vetorDeuses[i].dominio << endl << vetorDeuses[i].biografia << endl;
      }
    }
  }
  return d;
}

void bloco::escreverBloco(bloco& umBloco, int posBloco) {
  if (posBloco == -1) {  
    ofstream output("panteao.bin", ios::binary | ios::app);
    output.write(reinterpret_cast<const char*>(&umBloco), sizeof(bloco));
    output.close();
  }
  else {
    fstream output("panteao.bin", ios::binary | ios::ate | ios:: out | ios::in);
    output.seekp(posBloco*sizeof(bloco));
    output.write(reinterpret_cast<const char*>(&umBloco), sizeof(bloco));
    output.close();
  }
}

void bloco::lerBloco(bloco& umBloco, int posBytes) {
  ifstream input("panteao.bin", ios::binary);
  if (input) {
    input.seekg(posBytes);
    input.read((char*)(&umBloco), sizeof(bloco));
  } 
  else {
    cout << endl << "Erro na leitura do arquivo ou arquivo inexistente!" << endl;
  }
  input.close();
}

void imprimirBloco (bloco bloc) { //COLOCAR COMO METODO
  if (bloc.ativoBloco) {
    for (int i = 0; i < bloc.tam; i++) {
      cout << bloc.vetorDeuses[i].id << endl << bloc.vetorDeuses[i].nome << endl << bloc.vetorDeuses[i].dominio << endl << bloc.vetorDeuses[i].biografia << endl;
    }
  }
}

void imprimeBlocos () {
  ifstream input("panteao.bin", ios::binary);
  if (input) {
  bloco bloc;
    input.seekg(0, ios::end);
    int tam = input.tellg();
    tam = tam/sizeof(bloco);
    if (tam == 0) {
      cout << "Nenhum deus registrado" << endl;
      input.close();
      return;
    }
    input.seekg(0, ios::beg);
    for (int i = 0; i < tam; i++) {
      input.read((char*)(&bloc), sizeof(bloco));
      imprimirBloco(bloc);
    }
    input.close();
  }
  else {
    cout << endl << "Erro na leitura do arquivo ou arquivo inexistente!" << endl;
  }
}

/*void bloco::removeDoBloco(int id) {
  if (ativoBloco != false) {
    for (int i = 0; i < 4; i++) {
      if (vetorDeuses[i].id == id)
        cout << "Removeu" << endl;
    }
    //escreveArquivo(posBloco);
  }
}*/