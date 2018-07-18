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
  ativoBloco = false;
  tam = 0;
  compChaveBloco = 1;
  for (int i = 0; i < 4; i++) {
    vetorDeuses[i].id = -1;
    vetorDeuses[i].nome[50] = ' ';
    vetorDeuses[i].dominio[50] = ' ';
    vetorDeuses[i].biografia[200] = ' ';
  }
}

bool bloco::insereNoBloco(deusesGregos d, int compChave) {
  if(ativoBloco == true) {
    if(tam < 4) {
      insereOrdenado(d);
    } else {
      return false;
    }
  } else {
    ativoBloco = true;
    vetorDeuses[tam] = d;
    tam++;
    compChaveBloco = compChave;
  }
  return true;
}

void bloco::insereOrdenado(deusesGregos d) {
  int i = 0;
  while (d.id > vetorDeuses[i].id && i < tam)
    i++;
  if (i == tam) {
    vetorDeuses[i] = d;
    tam++;
  } else if (d.id == vetorDeuses[i].id) {
    cout << "JA EXISTE" << endl;
  } else {
    for (int j = tam; j > i; j--) {
      vetorDeuses[j] = vetorDeuses[j-1];
    }
    vetorDeuses[i] = d;
    tam++;
  }
}

deusesGregos bloco::procuraNoBloco(int id) {
  deusesGregos d;
  int i = 0;
  while (id != vetorDeuses[i].id && i < tam) {
    i++;
  }
  if (id == vetorDeuses[i].id) {
    cout << vetorDeuses[i].id << endl;
    cout << vetorDeuses[i].nome << endl; 
    cout << vetorDeuses[i].dominio << endl; 
    cout << vetorDeuses[i].biografia << endl;
  }
  else {
    cout << "REGISTRO NAO EXISTE" << endl;
  }
  return d;
}

bool bloco::removeDoBloco(int id) {
  int i = 0;
  while (id != vetorDeuses[i].id && i < tam) {
    i++;
  }
  if (id == vetorDeuses[i].id) {
    for (int j = i; j < tam-1 ;j++) {
      vetorDeuses[j] = vetorDeuses[j+1];
    }
    tam--;
    if (tam != 0) 
      return true;
    else {
      ativoBloco = false;
      tam = 0;
      compChaveBloco = 1;
      for (int i = 0; i < 4; i++) {
        vetorDeuses[i].id = -1;
        vetorDeuses[i].nome[50] = ' ';
        vetorDeuses[i].dominio[50] = ' ';
        vetorDeuses[i].biografia[200] = ' ';
      }
      return false;
    }
  }
  else {
    cout << "REGISTRO NAO EXISTE" << endl;
    return true;
  }
}

deusesGregos bloco::pegarDados (int pos) {
  return vetorDeuses[pos];
}

int bloco::pegarCompChave () {
  return compChaveBloco;
}

bool bloco::testarCompChave (int compChave) {
  if (compChave == compChaveBloco) {
    return true;
  }
  return false;
}

void bloco::resetarBloco () {
  ativoBloco = false;
  tam = 0;
  compChaveBloco = 1;
  for (int i = 0; i < 4; i++) {
    vetorDeuses[i].id = -1;
    vetorDeuses[i].nome[50] = ' ';
    vetorDeuses[i].dominio[50] = ' ';
    vetorDeuses[i].biografia[200] = ' ';
  }
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

void bloco::imprimirBloco(const bloco& bloc) {
  if (ativoBloco) {
    for (int i = 0; i < bloc.tam; i++) {
      cout << vetorDeuses[i].id << endl; 
      cout << vetorDeuses[i].nome << endl; 
      cout << vetorDeuses[i].dominio << endl; 
      cout << vetorDeuses[i].biografia << endl;
      cout << endl;
    }
  }
}

void imprimeBlocos() { //CORRIGIR O CASO DE APÓS REMOCAO TOTAL NAO APARECER TEXTO INFORMATIVO
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
      cout << "############ BLOCO: " << i << " ############" << endl; //NAO PODDE APARECER COM BLOCO VAZIO
      bloc.imprimirBloco(bloc);
    }
    input.close();
  }
  else {
    cout << endl << "Erro na leitura do arquivo ou arquivo inexistente!" << endl;
  }
}