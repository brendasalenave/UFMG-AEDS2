/*TRABALHO PRÁTICO 2 - ALGORITMO E ESTRUTURA DE DADOS II - UFMG 2013
JUNIO CEZAR RIBEIRO DA SILVA */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <stdlib.h>

using namespace std;

typedef set<string> aux__;
typedef map<string,aux__> MAPA;

//TRANSFORMA UMA PALAVRA DO TIPO GUARDA-CHUVA EM guardachuva
void Transformar(string&);
//SEMELHANTE AO PROCESSO DE SE BUSCAR UM TELEFONE EM UMA LISTA TELEFONICA
//ENTRAREMOS COM A CHAVE (PALVRA) E RETORNARÁ O VALOR(TEXTO QUE POSSUI O A PALAVRA)
void buscar(MAPA&, string);
//Insere as palavras dos arquivos no indice
void Nova_palavra(MAPA&, string , string );
//RECEBE O ARQUIVO ATUAL E EXECUTA A LEITURA DAS PALAVRAS, JÁ CORRIGINDO-AS E MANDANDO ELAS PRO INDICE
void ler_palavras(ifstream&, MAPA&, string&);
//IRÁ RETORNAR OS ARQUIVOS(VALORES) PARA QUAL AQUELA PALAVRA(CHAVE) PERTENCE. ISTO, CASO A PALAVRA ESTEJA CONTIDA EM ALGUM DOS ARQUIVOS
//void RESULTADO(MAPA &mapa, stringstream &string_);
void RESULTADO(MAPA& , string&);

int main(){
    string ARQUIVOS[4], entrada_;
    ifstream ENTRADA;
    MAPA buscador;
    int op;
    //NOMES DOS QUATRO ARQUIVOS DE TEXTO QUE SERÃO LIDOS.
    ARQUIVOS[0]="Harry Potter e a Pedra Drogada.txt";
    ARQUIVOS[1]="Contos Eroticos do Antigo Testamento.txt";
    ARQUIVOS[2]="Crepusculo Amanhecer.txt";
    ARQUIVOS[3]="Viagens Maravilhosas ao Mundo Desconhecido.txt";
    //ETAPA PARA LER OS QUATRO ARQUIVOS E CRIAÇÃO DO ÍNDICE INVERTIDO
    for(int i=0; i<4; i++){
        ENTRADA.open(ARQUIVOS[i].c_str());
        ler_palavras(ENTRADA,buscador,ARQUIVOS[i]);
        ENTRADA.close();
    }
    do{
        system("clear");//Limpar a tela no Linux
        system("cls");//Limpar a tela no Windows
        system("color F3");
        cout<<endl<<endl<<endl<<endl<<"              ##### Marquina de Buscas - Google Paraguaio #####"<<endl<<endl<<endl;
        cout<<"                -- Digite a palavra sem acento ou cedilha --"<<endl<<endl;
        cout<<"Digite a palavra que deseja pesquisar nos arquivos: ";

        cin >> entrada_;
        RESULTADO(buscador,entrada_);
        cout<<endl<<endl;
        cout<<endl<<"Para pesquisar novamente Insira 1 e aperte enter."<<endl<<"Para sair Insira 0 e aperte enter:"<<endl<<"Opcao:  ";
        cin>>op;
        }while(op!=0);


        return 0;
    }

void Transformar(string &entrada){
    int i=0;
    string::iterator it;
    while (i<entrada.length()){
        if (!isalnum(entrada[i])){
           it = entrada.begin()+i;
           entrada.erase(it);
        }else{
            entrada[i]=tolower(entrada[i]);
            i++;
        }
    }
}

void buscar(MAPA &mapa, string entrada){
    MAPA:: const_iterator iter;
    iter=mapa.find(entrada);
    if (iter!=mapa.end()){
        cout<<endl<<endl<<"No(s) texto(s) abaixo voce encontrara esta palavra:"<<endl<<endl;
        ostream_iterator <string> output (cout, "\n");
        copy (iter->second.begin(),iter->second.end(),output);
        cout << endl;
    }else{
        cout <<endl<<endl<< "A Palavra nao foi localizada em nenhum dos textos";
    }
}

void Nova_palavra(MAPA &mapa, string nome, string arquivo){
    MAPA:: iterator aux = mapa.find(nome);
    if (aux!=mapa.end()){
      (aux->second).insert(arquivo);
    }else{
        aux__ conjunto;
        conjunto.insert(arquivo);
        mapa.insert(MAPA::value_type(nome, conjunto));
    }
}

void ler_palavras(ifstream &arquivo, MAPA &mapa, string &nome_arquivo){
   string palavra;
   while (arquivo >> palavra){
       Transformar(palavra);
       Nova_palavra(mapa,palavra,nome_arquivo);
   }
}

void RESULTADO(MAPA &mapa, string &palavra){
    Transformar(palavra);
    buscar(mapa,palavra);
}
