#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#define SIZECHAR 30

using namespace std;

//Registro :
struct banda_rock {
  char nome[SIZECHAR];
  int numero_integrantes;
  char estilo[SIZECHAR];
  int ano_criacao;
  char musica_famosa[SIZECHAR];
  bool ativo;
};

//Nomear todas as funcoes aqui :
void menu_principal();
void inserir_cadastro(int &quant, banda_rock* ptrcatalogo);
void editar_novo (banda_rock &RockBand);
void busca(string name_band,banda_rock *ptrcatalogo,int num_reg_busc, bool achou);
void listar(banda_rock *ptrcatalogo,int numero_registros_listar);
void ordenacao_registro(banda_rock* ord_reg, int tam);

//Menu
void menu_principal(){
  cout<<"1 - Inserir cadastro " << endl;
  cout<<"2 - Editar cadastro  " << endl;
  cout<<"3 - Buscar cadastro  " << endl;
  cout<<"4 - Listar cadastro  " << endl;
  cout <<endl;//7 - Modo [DEV] listagem completa.
  cout<<"0 - Sair " << endl;
}

void inserir_cadastro(int &quant, banda_rock* ptrcatalogo){
  cout << endl << "Inserir Dados" << endl;

  for (int i = 0; i < quant; i++) {
    cout << endl << "Banda " << i+1 << endl;
	  cout << endl << "Digite o nome da banda : ";
    cin.getline(ptrcatalogo[i].nome,SIZECHAR);

    cout << endl;
    cout << "Digite o numero de integrantes : ";

    cin >> ptrcatalogo[i].numero_integrantes;

    cout << endl;
    cout << "Qual o genero do Rock : ";

    cin.ignore();
    cin.getline(ptrcatalogo[i].estilo,SIZECHAR);

    cout << endl;
    cout << "Ano de criacao : ";

    cin >> ptrcatalogo[i].ano_criacao;
    cin.ignore();

    cout << endl;
    cout << "Melhor Hit : ";

    cin.getline(ptrcatalogo[i].musica_famosa,SIZECHAR);

    cout << endl;

    ptrcatalogo[i].ativo = true;
  }
 return;
}

void editar_novo(banda_rock &RockBand){
	cout << "Digite o novo nome da banda : ";
	cin.getline(RockBand.nome,SIZECHAR);
	cout << endl;
	cout << "Digite o numero integrantes : ";
	cin >> RockBand.numero_integrantes;
	cout << endl;
	cout << "Digite o novo estilo : ";
	cin.ignore();
	cin.getline(RockBand.estilo,SIZECHAR);
	cout << endl;
	cout << "Digite o novo ano criacao : ";
	cin >> RockBand.ano_criacao;
	cout << endl;
	cout << "Digite o nova musica : ";
	cin.ignore();
	cin.getline(RockBand.musica_famosa,SIZECHAR);
	cout << endl;
	RockBand.ativo = true;
	return;
}

void busca(string name_band,banda_rock *ptrcatalogo,int num_reg_busc, bool achou) {
	cout << "Digite o nome da banda que deseja buscar : ";
	cin.ignore();
	getline(cin,name_band);
	for(int i = 0; i < num_reg_busc; i++){
		if(name_band == ptrcatalogo[i].nome){

			if(ptrcatalogo[i].ativo == true){
				cout << endl;
				cout <<  "   Nome da Banda: " << ptrcatalogo[i].nome << endl;
				cout <<  "   Numero de integrantes: " << ptrcatalogo[i].numero_integrantes << endl;
				cout <<  "   Estilo: " << ptrcatalogo[i].estilo << endl;
				cout <<  "   Ano de criacao: " << ptrcatalogo[i].ano_criacao << endl;
				cout <<  "   Melhor hit: " << ptrcatalogo[i].musica_famosa << endl;
				achou = true;
			}
		}
	}
	if(!achou){
		cout << endl << "Essa banda nao esta cadastrada" << endl;
	}
	return;
}

void listar (banda_rock *ptrcatalogo,int numero_registros_listar){
	if (numero_registros_listar>1){
		ordenacao_registro (ptrcatalogo, numero_registros_listar);
	}
	cout << endl;
	cout << "Bandas em ordem alfabetica ordenadas pelo nome da banda : " << endl << endl;
	for ( int i = 0; i < numero_registros_listar; ++i ) {
		if(ptrcatalogo[i].ativo == true) {
			cout <<  "   Nome da Banda: " << ptrcatalogo[i].nome << endl;
			cout <<  "   Numero de integrantes: " << ptrcatalogo[i].numero_integrantes << endl;
			cout <<  "   Estilo: " << ptrcatalogo[i].estilo << endl;
			cout <<  "   Ano de criacao: " << ptrcatalogo[i].ano_criacao << endl;
			cout <<  "   Melhor hit: " << ptrcatalogo[i].musica_famosa << endl;
			cout << endl;
		}
	}
	return;
}

void ordenacao_registro (banda_rock* ord_reg, int tam) {
  int i = 0;
  bool troca = true;
  banda_rock aux;
  while ((troca)&&(i < tam)){
    troca = false;
    for(int j=0; j < (tam-1) - i; j++){
      if((strcmp(ord_reg[j].nome, ord_reg[j+1].nome)) > 0){

        strcpy(aux.nome, ord_reg[j].nome);
        aux.numero_integrantes = ord_reg[j].numero_integrantes;
        strcpy(aux.estilo,ord_reg[j].estilo);
        aux.ano_criacao = ord_reg[j].ano_criacao;
        strcpy(aux.musica_famosa,ord_reg[j].musica_famosa);
        aux.ativo = ord_reg[j].ativo;

        strcpy(ord_reg[j].nome, ord_reg[j+1].nome);
        ord_reg[j].numero_integrantes = ord_reg[j+1].numero_integrantes;
        strcpy(ord_reg[j].estilo, ord_reg[j+1].estilo);
        ord_reg[j].ano_criacao = ord_reg[j+1].ano_criacao;
        strcpy(ord_reg[j].musica_famosa, ord_reg[j+1].musica_famosa);
        ord_reg[j].ativo = ord_reg[j+1].ativo;

        strcpy(ord_reg[j+1].nome, aux.nome);
        ord_reg[j+1].numero_integrantes = aux.numero_integrantes;
        strcpy(ord_reg[j+1].estilo, aux.estilo);
        ord_reg[j+1].ano_criacao = aux.ano_criacao;
        strcpy(ord_reg[j+1].musica_famosa, aux.musica_famosa);
        ord_reg[j+1].ativo = aux.ativo;

        troca = true;
      }
    }
    i++;
  }
}

//Função apenas para modo debug para verifição de registro :
void lerRegistros(char* file_name, ifstream &entrada){

	entrada.open(file_name, ios::binary);

	if( entrada ){
		entrada.seekg(0, entrada.end);
		int tam = entrada.tellg();
		entrada.seekg(0, entrada.beg);

		int numero_registros = tam / sizeof(banda_rock);
		banda_rock* bandas = new banda_rock[numero_registros];

		cout << endl << "numero de registros no  total : " << numero_registros << endl<<endl;

    for(int i = 0; i < numero_registros; i++){
      entrada.read((char*)(&bandas[i]), sizeof(banda_rock));
		}

		for( int i = 0; i < numero_registros; ++i ){

			cout << "Nome da banda: " << bandas[i].nome << endl;
			cout << "Numero de integrantes: " << bandas[i].numero_integrantes << endl;
			cout << "Estilo: " << bandas[i].estilo << endl;
			cout << "Ano de criacao: " << bandas[i].ano_criacao << endl;
			cout << "Melhor hit: " << bandas[i].musica_famosa << endl;
		  cout << "Ativo : " << bandas[i].ativo << endl;
		  cout << endl;

		}

		delete[] bandas;
	}
	else
	{
	 	cout << "Erro na leitura do arquivo ou arquivo inesistente !!";
	}
	return;
}

//Funcao Principal :
int main(){
  int quant = 0;
  char* file_name = NULL;
  char back;
  int opcao = -1;

  banda_rock* ptrcatalogo = NULL;

  do {
  	menu_principal();

  	cout << endl << "Escolha uma opcao digitando o numero : ";

  	cin>>opcao;

  	switch(opcao) {
	  	case 1:
	  	{
	  	  cout << endl << "Digite a quantidade de bandas : ";
		    cin >> quant;

		    file_name = new char[100];

			  cout << endl << "Digite o nome do arquivo a ser armazenado as bandas (com o extensao) : ";
			  cin >> file_name;
			  cin.ignore();

		    //Alocacao de registro :
			  ptrcatalogo = new banda_rock[quant];

			  //Operacao para salvar :
		    fstream salvar_bandas;
		    salvar_bandas.open(file_name, ios::binary|ios::app|ios::out);

		    inserir_cadastro(quant, ptrcatalogo);

		    for(int i = 0; i < quant; i++){
		      salvar_bandas.write(reinterpret_cast<const char*> (&ptrcatalogo[i]), sizeof(banda_rock));
		    }

		    delete[] ptrcatalogo;

		    salvar_bandas.close();

		    delete file_name;

		    cout << endl << "Deseja volta ao menu principal ? [Y/N]" << endl;
		    cin >> back;

		    if( back == 'N' || back == 'n' ){
		      opcao = 0;
			  }
			  else{
				system("clear");
			  }

		    break;
		  }
  		case 2:
  		{
  			cout << "Editar Dados" <<endl;

  			file_name = new char[100];
  			string name_band;
  			bool achou = false;
  			banda_rock RockBand;
  			cout << endl <<"Digite o nome do arquivo a ser armazenado as bandas (com o extensao) : ";
  			cin >> file_name;

  			ifstream read_editar;
  			read_editar.open(file_name, ios::binary);

  			if ( read_editar ) {
  				cout << endl <<"Digite o nome da banda que deseja editar : ";
  				cin.ignore();
  				getline(cin,name_band);
  				read_editar.seekg(0, read_editar.end);
  				int tam_editar = read_editar.tellg();
  				read_editar.seekg(0, read_editar.beg);

  				int num_reg_edit = tam_editar / sizeof(banda_rock);
  				banda_rock* ptrcatalogo = new banda_rock;
  				int pos = 0;
  				ofstream save (file_name, ios::binary|ios::out|ios::in);
  				for (int i = 0; i < num_reg_edit; i++) {
  					read_editar.read((char*)(ptrcatalogo), sizeof(banda_rock));
  					if (name_band == ptrcatalogo->nome) {
  						if(ptrcatalogo->ativo == true) {
  							ptrcatalogo->ativo = false;
  							pos = i*sizeof(banda_rock);
  							cout << endl << "posição em bytes : " << pos  << endl <<endl;
  							save.seekp(pos, ios::cur);
  							save.write((const char *)(&ptrcatalogo),sizeof(banda_rock));
  	  					achou = true;
  	  				}
  					}
  				}
  				save.close();

  				if (!achou){
  					cout << endl << "Essa banda nao esta cadastrada" << endl;
  				}else{
  					save.open(file_name, ios::binary|ios::app|ios::out);
  					editar_novo(RockBand);
  					save.write((const char *)(&RockBand),sizeof(banda_rock));
  					delete ptrcatalogo;
  					read_editar.close();
  					save.close();
  				}
  			} else {
   				cout << endl <<"Erro na leitura do arquivo ou arquivo inesistente !" << endl << endl;
  			}
  			read_editar.close();

  			delete file_name;

  		  cout << endl <<" Deseja volta ao menu principal ? [Y/N]" << endl;
  		  cin >> back;

  		  if( back == 'N' || back == 'n' ){
  		    opcao = 0;
  			}	else {
  				system("clear");
  			}
  		  break;
  		}
  		case 3:
  		{
  			cout << endl << "Buscar Dados" << endl;

  			file_name = new char[100];
  			string name_band;
  			bool achou = false;
  			cout << endl <<"Digite o nome do arquivo a ser armazenado as bandas (com o extensao) : ";
  			cin >> file_name;

  			ifstream read_busca;
  			read_busca.open(file_name, ios::binary);

  			if( read_busca ){
  				read_busca.seekg(0, read_busca.end);
  				int tam_buscar = read_busca.tellg();
  				read_busca.seekg(0, read_busca.beg);

  				int num_reg_busc = tam_buscar / sizeof(banda_rock);
  				banda_rock* ptrcatalogo = new banda_rock[num_reg_busc];

  				cout << endl << "Este arquivo contem " << num_reg_busc << " bandas (ativas/inativas)  " <<endl;
  				cout << endl;
  				for(int i = 0; i < num_reg_busc; i++){
       			read_busca.read((char*)(&ptrcatalogo[i]), sizeof(banda_rock));
  				}
  				busca(name_band, ptrcatalogo, num_reg_busc, achou);

  				delete[] ptrcatalogo;

  			}else{
   				cout << endl <<"Erro na leitura do arquivo ou arquivo inesistente !" << endl << endl;
  			}
  			read_busca.close();

  			delete file_name;

  		  cout << endl <<"Deseja volta ao menu principal ? [Y/N]" << endl;
  		  cin >> back;

  		  if( back == 'N' || back == 'n' ){
  		    opcao = 0;
  			}	else {
  				system("clear");
  			}
        break;
  		}
  		case 4:
  		{
  			cout<<endl<<"Listar Dados : "<<endl;
  			file_name = new char[100];
  			cout << endl <<"Digite o nome do arquivo a ser armazenado as bandas (com o extensao) : ";
  			cin >> file_name;

  			ifstream read_listar;
  			read_listar.open(file_name, ios::binary);

  			if( read_listar ){
  				read_listar.seekg(0, read_listar.end);
  				int size_struct = read_listar.tellg();
  				read_listar.seekg(0, read_listar.beg);

  				int numero_registros_listar = size_struct / sizeof(banda_rock);
  				banda_rock* ptrcatalogo = new banda_rock[numero_registros_listar];

       		for (int i = 0; i < numero_registros_listar; i++) {
       			read_listar.read((char*)(&ptrcatalogo[i]), sizeof(banda_rock));
  				}
  				read_listar.close();

  				listar(ptrcatalogo, numero_registros_listar);

  				delete[] ptrcatalogo;
  			}else{
   				cout << endl <<"Erro na leitura do arquivo ou arquivo inesistente !" << endl << endl;
  			}
  			delete file_name;
  		  cout << "Deseja volta ao menu principal ? [Y/N]" << endl;
  		  cin >> back;

  		  if ( back == 'N' || back == 'n' ) {
  		    opcao = 0;
  			} else {
  				system("clear");
  			}
  		  break;
  		}
  		case 7:
  		{
  			cout << "leitura completa para Debug : " << endl;
  			file_name = new char[100];
  			cout << endl <<"Digite o nome do arquivo a ser armazenado as bandas (com o extensao) : ";
  			cin >> file_name;
  			ifstream entrada;
  			lerRegistros(file_name, entrada);
  			entrada.close();
  			delete file_name;
  			cout << endl << "Deseja volta ao menu principal ? [Y/N]" << endl;
  		  cin >> back;

  		  if ( back == 'N' || back == 'n' )  {
  		    opcao = 0;
  			}	else {
  				system("clear");
  			}

  			break;
  		}
  		case 0:
  		{
  			break;
  		}
  	}
  }while (opcao != 0);

  return 0;
}
