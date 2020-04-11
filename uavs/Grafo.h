/*********************************************
	Arquivo:            Grafo.h
	Nome do aluno:      Gilson Evandro Just Junior e Giovandro Goles
	Projeto:            Grafo
	Classe:             Engenharia de Redes de Comunicações

	...define a classe;
**********************************************/
#ifndef __GRAFO_H__
#define __GRAFO_H___

#define MAXNOS 100
#define INFINITO 99999

class Grafo {
protected:
    bool adj[MAXNOS][MAXNOS]; //matriz booleana adjacencia.
    bool caminho[MAXNOS][MAXNOS]; //matriz booleana fechamento transitivo.
    int peso[MAXNOS][MAXNOS]; //matriz inteira peso.
    int precede[MAXNOS]; //vetor inteiro precede.
    int num_nos; //número de nós.
public:
    Grafo(int nnos); //construtor padrão.
	void Multiplica(bool a[MAXNOS][MAXNOS], bool b[MAXNOS][MAXNOS], bool res[MAXNOS][MAXNOS], int N);
	void Copia(bool dest[MAXNOS][MAXNOS], bool origem[MAXNOS][MAXNOS], int N);
	void Oulogico(bool dest[MAXNOS][MAXNOS], bool m[MAXNOS][MAXNOS], int N);
    bool existe_caminho(int a, int b); //verifica se existe caminho entre 2 nós fornecidos.
    bool adjacente(int a, int b); //verifica se há adjacencia entre 2 nós.
    int MenorCaminho(int s, int t); //retorna peso do menor caminho.
    int ret_peso(int a, int b); //retorna o peso entre 2 nós.
    void Caminho(); //calcula a matriz fechamento transitivo.
    void une(int a, int b); //faz a união de 2 nós fornecidos.
	void remove(int a, int b);
    void une_peso(int a, int b, int peso_value); //união de 2 nós sendo fornecido o peso também.
	//void remv(int a, int b);
    void imprime_adj(); //imprime a matriz adjacencia.
	void imprime_caminho();
    void imprime_peso(); //imprime uma matriz com os pesos. 
	//void imprime_fechamento();
    void imprime_precede(); //imprime o menor caminho.  
};
#endif
