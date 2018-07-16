#include <iostream>
#include <stdlib.h>
using namespace std;

string transformarBinario (int numero) {
    int cont = 0;
    int num = numero;
    while (num > 0) {
        num /= 2;
        cont++;
    }
    if (cont == 0) {
        char* bin = new char[2];
        bin[0] = 48;
        bin[1] = '\0';
        return bin;
    }
    char* bin = new char[cont+1];
    int resto;
    int i = cont-1;
    while (numero > 0) {
        resto = numero%2;
        bin[i] = resto + 48;
        numero /= 2;
        i--;
    }
    bin[cont] = '\0';
    return bin;
}

class Trie {
    public:
        Trie ();
        ~Trie ();
        void insere (string bin, int dec);
        void insereAux (string bin, int dec);
        void redimensionar (int dec);
        inline int esquerdo (int i);
        inline int direito (int i);
        void imprime ();
        string atualizarBin (int dec);
    protected:
        int* vetTrie;
        int compChave;
        int capacidade;
};

Trie::Trie () {
    capacidade = 3;
    compChave = 1;
    vetTrie = new int[capacidade];
    for (int i = 0; i < capacidade; i++) {
        if (i == 0)
            vetTrie[i] = 0;
        else
            vetTrie[i] = -1;
    }
}

Trie::~Trie () {
    delete[] vetTrie;
}

void Trie::insere (string bin, int dec) {
    bin = atualizarBin(dec);
    int atual = 0;
    for (int i = 0; i < compChave; i++) {
        if (bin[i] == '0') {
            atual = esquerdo(atual);
        }
        else {
            atual = direito(atual);
        }
    }
    if (vetTrie[atual] == -1 || vetTrie[atual] == dec) {
        vetTrie[atual] = dec;
    }
    else {
        redimensionar(vetTrie[atual]);
        insereAux(atualizarBin(dec), dec);
    }
}

void Trie::insereAux(string bin, int dec) {
    int atual = 0;
    for (int i = 0; i < compChave; i++) {
        if (bin[i] == '0') {
            atual = esquerdo(atual);
        }
        else {
            atual = direito(atual);
        }
    }
    vetTrie[atual] = dec;
}

void Trie::redimensionar (int dec) {
    int novaCapacidade = (capacidade*2) + 1;
    int* novoVetor = new int[novaCapacidade];
    for (int i = 1; i < novaCapacidade; i++) {
        if (i%2 == 0)
            novoVetor[i] = 1;
        else
            novoVetor[i] = 0;
    }
    for (int i = capacidade/2; i < capacidade; i++) {
        novoVetor[esquerdo(i)] = vetTrie[i];
        novoVetor[direito(i)] = vetTrie[i];
    }
    delete[] vetTrie;

    capacidade = novaCapacidade;
    vetTrie = new int[capacidade];
    vetTrie = novoVetor;

    novoVetor = NULL;
    delete[] novoVetor;

    compChave++;
    insere(atualizarBin(dec), dec);
}

inline int Trie::esquerdo (int i) {
    return 2*i+1;
}

inline int Trie::direito (int i) {
    return 2*i+2;
}

void Trie::imprime () {
    for (int i = 0; i < capacidade; i++) {
        cout << vetTrie[i] << " ";
    }
}

string Trie::atualizarBin (int dec) {
    string bin = transformarBinario(dec);
    int tamBin = bin.size();
    if (tamBin < compChave) {
        char* binAux = new char[compChave+1];
        for (int i = 0; i < compChave; i++) {
            binAux[i] = '0';
        }
        int j = compChave-1;
        for (int i = tamBin-1; i >= 0; i--) {
            binAux[j] = bin[i];
            j--;
        }
        binAux[compChave] = '\0';
        return binAux;
    }
    return bin;
}

///////////////////////////////
int transformarDecimal (string bin) {
    int contador = 0;
    while (transformarBinario(contador) != bin)
        contador++;
    return contador;
}

string atualizarBinTeste(int id) {
  int compChave = 2;
  string bin = transformarBinario(id);
  int tamBin = bin.size();
  char* binAux;
  if (tamBin <= compChave) {
    binAux = new char[tamBin+1];
    for (int i = 0; i < tamBin; i++) {
        binAux[i] = bin[i];
    }
    binAux[tamBin] = '\0';
  }
  else {
    binAux = new char[compChave+1];
    for (int i = 0; i < compChave; i++) {
        binAux[i] = bin[i];
    }
    binAux[compChave] = '\0';
  }
  cout << binAux << endl;
  return binAux;
}

int main () {
    /*int dec;
    Trie trieBin;
    cin >> dec;
    while (dec != -1) {
        trieBin.insere(transformarBinario(dec), dec);
        trieBin.imprime();
        cout << endl;
        cin >> dec;
    }*/
    int id;
    cin >> id;
    while (id != -1) {
        cout << transformarDecimal(atualizarBinTeste(id)) << endl;
        cin >> id;
    }
    return 0;
}
