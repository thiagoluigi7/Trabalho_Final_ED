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


using namespace std;


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
  deusesGregos Teste;
  return Teste;

}

void bloco::removeBloco(int id) {
  ofstream output("panteao.bin", ios::binary | ios::app);
  cout<<"Por favor funcione"<<endl;
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



//Nomear as funções

