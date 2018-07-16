#include <iostream>
#include <string>
#include <fstream>
#include <math.h>


using namespace std;

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



class noh {
friend class tabelaHash;
private:
  int indexBin;
  int chaveBloco;
public:
  noh(int indexBin, int chaveBloco);
};

noh::noh(int index, int chave) {
  int indexBin; //'Andar' da Hash em binário
  int chaveBloco; // Posição do Bloco
}



class tabelaHash {
friend int main();
friend class bloco;
private:
  //vetor de ponteiros de nós
  noh** elementos;
  int capacidade = 16;
public:
  //construtor padrão
  tabelaHash(int cap = 16);
  //destrutor
  ~tabelaHash();
  //insere um valor chave v com chave c
  void insereHash(deusesGregos d);
  //recupera um valor associado a uma dada chave
  string recuperaHash(deusesGregos d);
  //retira um valor associado a uma chave
  void removeHash(int id);
  //busca um struct no bloco usando a tabela
  deusesGregos buscaHash(int id);
  //percorre a tabela para debug
  //void percorre();
  
};

//construtor padrão
tabelaHash::tabelaHash(int cap) {

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

void leBloco(bloco* aux, int posBytes);


void menu_principal(){
  cout << endl;
  cout << "[#####################[MENU]#########################]" << endl;
  cout << "[ Entre com a opção desejada :                       ]" << endl;
  cout << "[ (1) -  para inserir um novo deus no arquivo :      ]" << endl;
  cout << "[ (2) -  para remover um deus do arquivo :           ]" << endl;
  cout << "[ (3) -  para consultar um deus no arquivo :         ]" << endl;
  cout << "[ (4) -  para imprimir todos registros :             ]" << endl;
  cout << "[ (5) -  para imprimir de modo ordenado :            ]" << endl;
  cout << "[ (0) -  para sair :                                 ]" << endl;
  cout << "[####################################################]" << endl << endl;
}


int main() {

  tabelaHash* tabela = new tabelaHash(16);
  
  int escolha = -1;
  deusesGregos dg;

  while(escolha != 0) {
    menu_principal();
    cin >> escolha;

    switch (escolha) {
      //Função Inserir
      case 1:
        {
             
          cout << "Digite o id do deus: " << endl;

				  cin >> dg.id;

				  cin.ignore();

				  cout << "Digite o nome do deus: " << endl;

				  cin.getline(dg.nome, 50);

				  cout << "Digite o domínio do deus: " << endl;

				  cin.getline(dg.dominio, 10);

				  cout << "Digite a biografia do deus: " << endl;

				  cin.getline(dg.biografia, 200);
          
          //tabela->insereHash(dg);
          
          break;
        }
      case 2:
        {
          cout << "Deus a ser remover: " << endl;

          break;
        }
      case 3:
        {
          cout << "Deus a ser consultado: " << endl;
          break;
        }
      case 4:
        {
          
          break;
        }
      case 5:
        {
          break;
        }
      default:
        {
          cout << "Favor inserir número válido" << endl;
          break;
        }
    }
  }

  return 0;
}
