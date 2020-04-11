/*********************************************
	Arquivo:            Grafo.cpp
	Nome do aluno:      Gilson Evandro Just Junior e Giovandro Goles       
	Projeto:            Projeto Grafo
	Classe: Engenharia de Redes de Comunicações

	... métodos da classe Grafo;
**********************************************/
#include "Grafo.h"
#include <stdlib.h>
#include <iostream>
#define INFINITO 99999

using namespace std;

//Grafo::Grafo(int nnos)//contrutor padrão.
//{
//	int i, j;
//	num_nos = nnos;
//	for (i = 0; i < num_nos; i++)
//	{
//		for (j = 0; j < num_nos; j++)
//		{
//			adj[i][j] = false; //criando a matriz com todos os valores iguais a falsos.
//		}
//	}
//}
//
//bool Grafo::existe_caminho(int a, int b)//analise se existe caminho.
//{
//	return caminho[a][b]; //se existe retorna verdade, senão, falso.
//}
//
//bool Grafo::adjacente(int a, int b)
//{
//	if ((a < MAXNOS) && (b < MAXNOS))//se 'a' e 'b' existirem, e estiver unidos retorna verdadeiro, senão falso.
//		return adj[a][b];
//}
//
//int Grafo::MenorCaminho(int s, int t)
//{
//	//variáveis auxiliares.
//	int N = num_nos;
//
//	int distancia[MAXNOS];
//	bool calculado[MAXNOS];
//	int corrente;
//	int menordist, novadist, i, k;
//	int dc;
//
//	for (i = 0; i < num_nos; i++) { //para i menor que num_nos,
//		distancia[i] = INFINITO;
//		calculado[i] = false;
//	}
//
//	distancia[s] = 0;
//	calculado[s] = true;
//	corrente = s;
//
//	while (corrente != t) { //enquanto corrente for diferente de t.
//		menordist = INFINITO;
//		dc = distancia[corrente];
//		
//		for (i = 0; i < N; i++) 
//		{
//			if (!calculado[i]) 
//			{
//				novadist = dc + ret_peso(corrente, i);
//				
//				if (novadist < distancia[i]) { //se, nova distancia for menor que distancia na posição 'i',
//					distancia[i] = novadist; //distancia recebe nova distancia.
//					precede[i] = corrente;
//				}
//				if (distancia[i] < menordist) {
//					menordist = distancia[i];
//					k = i;
//				}
//			}
//		}
//
//		corrente = k;
//		calculado[corrente] = true; //calculado é verdadeiro, ou seja, já foi calculado.
//	}
//
//	return distancia[t]; //retorna a distância.
//}
//
//int Grafo::ret_peso(int a, int b)//Retorna peso.
//{
//	if (adjacente(a, b))//se existir adjacencia,            
//		return peso[a][b];//retorna o peso.
//	else
//		return INFINITO;//senão não existe, é indicado por INFINITO.
//}
//
//
//void Grafo::Caminho()//constrói a matriz fechamento transitivo.
//{
//	int cam, i, j, k, N; //variáveis auxiliares.
//	bool adjk[MAXNOS][MAXNOS]; //matriz auxiliar booleana.
//	bool aux[MAXNOS][MAXNOS]; //matriz auxiliar booleana.
//
//	N = num_nos; //necessário para que o for seja finalizado.
//				 //Copiando uma matriz 'destino' em uma 'origem'.
//
//	for (i = 0; i < N; i++)
//	{
//		for (j = 0; j < N; j++)
//		{
//			adjk[i][j] = adj[i][j]; //copia a matriz adj(origem) em adjk(destino).
//		}
//	}
//	
//	//Copiando uma matriz 'destino' em uma 'origem'.
//	for (i = 0; i < N; i++)
//	{
//		for (j = 0; j < N; j++)
//		{
//			caminho[i][j] = adj[i][j]; //copia a matriz adj(origem) em caminho(destino).
//		}
//	}
//
//	for (cam = 1; cam < num_nos; cam++)
//	{
//		//Multiplicando duas matrizes.
//		for (i = 0; i < N; i++)
//		{
//			for (j = 0; j < N; j++)
//			{
//				aux[i][j] = false;//inicializando a matriz aux como falsa.
//	
//				for (k = 0; k < N; k++) {
//					aux[i][j] = aux[i][j] || (adj[i][k] && adjk[k][j]);//constrói a matriz auxiliar com calculos feitos com adj e adjk.
//				}
//			}
//		}
//		
//		//Somando matrizez.
//		for (i = 0; i < N; i++)
//		{
//			for (j = 0; j < N; j++)
//			{
//				caminho[i][j] = caminho[i][j] || aux[i][j]; //utilizando somando lógica a matriz fechamento transitivo é baseada em caminho e auxiliar, já criada acima.
//			}
//		}
//		
//		//Copiando uma matriz 'destino' em uma 'origem'.
//		for (i = 0; i < N; i++)
//		{
//			for (j = 0; j < N; j++)
//			{
//				adjk[i][j] = aux[i][j]; //copia a matriz aux(origem) em adjk(destino).
//			}
//		}
//
//	}
//}
//
//void Grafo::une(int a, int b)//faz a união entre dois nós.
//{
//	if ((a < num_nos) && (b < num_nos))
//	{
//		if (adj[a][b] == false)//se adjacente for falso, 
//			adj[a][b] = true; //é mudado pra verdadeiro.
//		else
//			cout << endl << "Ja existe adjacencia entre esses nos!!"; //senão a adjacencia já existe.
//	}
//	else
//		cout << endl << "Valor fora de escopo!!!" << endl;
//}
//
//void Grafo::une_peso(int a, int b, int peso_value)//união com peso.
//{
//	une(a, b); //une 'a' e 'b'.
//	peso[a][b] = peso_value;//peso na posição 'a/b' é igual ao peso fornecido pelo usuário.
//}
//
//void Grafo::remv(int a, int b)//remove nó.
//{
//	if ((a < MAXNOS) && (b < MAXNOS))
//	{
//		if (adj[a][b] == true)//se a adjacencia for verdadeira,
//			adj[a][b] = false;//é mudada para falso.
//		else
//			cout << endl << "Nao existe adjacencia entre esses nos!!";//senão, n]ao existe adjacencia entre os nós fornecidos.
//	}
//	else
//		cout << endl << "Valor fora de escopo!!!" << endl;;
//}
//
//void Grafo::imprime_adj()//imprime a matriz adjacencia.
//{
//	for (int i = 0; i < num_nos; i++)//se 'i' for menor que num_nos (linha),
//	{
//		for (int j = 0; j < num_nos; j++)//se 'j' for menor que num_nos (coluna),
//		{
//			cout << adj[i][j] << " ";//imprime matriz adjacencia na posição 'i/j'.
//		}
//		cout << endl;
//	}
//
//	cout << endl;
//}
//
//void Grafo::imprime_peso()//imprime a matriz que contém somente os pesos. 
//{
//	for (int i = 0; i < num_nos; i++)//se 'i' for menor que num_nos (linha),
//	{
//		for (int j = 0; j < num_nos; j++)//se 'j' for menor que num_nos (coluna) 
//		{
//			cout << peso[i][j] << " ";//imprime peso na posição 'i/j'.
//		}
//		cout << endl;
//	}
//
//	cout << endl;
//}
//
//void Grafo::imprime_fechamento()//imprime a matriz fechamento transitivo.
//{
//	for (int i = 0; i < num_nos; i++)//se 'i' for menor que num_nos (linha), 
//	{
//		for (int j = 0; j < num_nos; j++)//se 'j' for menor que num_nos (coluna)
//		{
//			cout << caminho[i][j] << " ";//imprime matriz caminho na posição 'i/j'.
//		}
//		cout << endl;
//	}
//
//	cout << endl;
//}
//
//void Grafo::imprime_precede()//imprime o vetor precede, o qual dá a ordem do menor caminho.
//{
//	int i;
//	cout << endl << "Voce passou pelos nos: ";
//
//	for (i = 0; i < num_nos; i++)//se 'i' for menor que num_nos, 
//	{
//		cout << ", " << precede[i];//imprime prece na posição 'i.
//	}
//
//	cout << endl;
//}



Grafo::Grafo(int nnos)//contrutor padrão.
{
	num_nos = nnos;

	for (int i = 0; i<num_nos; i++) 
	{
		for (int j = 0; j<num_nos; j++) 
		{
			adj[i][j] = false;
		}
	}
}

void Grafo::Multiplica(bool a[MAXNOS][MAXNOS], bool b[MAXNOS][MAXNOS], bool res[MAXNOS][MAXNOS], int N) {
	
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++) 
		{
			res[i][j] = false;
			
			for (int k = 0; k<N; k++) 
			{
				res[i][j] = res[i][j] || (a[i][k] && b[k][j]);
			}
		}
	}
}

void Grafo::Copia(bool dest[MAXNOS][MAXNOS], bool origem[MAXNOS][MAXNOS], int N) 
{
	for (int i = 0; i<N; i++) 
	{
		for (int j = 0; j<N; j++) 
		{
			dest[i][j] = origem[i][j];
		}
	}
}

void Grafo::Oulogico(bool dest[MAXNOS][MAXNOS], bool m[MAXNOS][MAXNOS], int N) 
{
	for (int i = 0; i<N; i++) 
	{
		for (int j = 0; j<N; j++) 
		{
			dest[i][j] = dest[i][j] || m[i][j];
		}
	}
}


void Grafo::Caminho() 
{
	bool adjk[MAXNOS][MAXNOS];
	bool aux[MAXNOS][MAXNOS];

	Copia(adjk, adj, num_nos);
	Copia(caminho, adj, num_nos);

	for (int s = 1; s<num_nos; s++)
	{
		Multiplica(adj, adjk, aux, num_nos);
		Oulogico(caminho, aux, num_nos);
		Copia(adjk, aux, num_nos);
	}
}

void Grafo::une_peso(int a, int b, int peso_value) 
{
	une(a, b);
	peso[a][b] = peso_value;
}

void Grafo::une(int a, int b) 
{
	if ((a<num_nos) && (b<num_nos)) 
	{
		if (adj[a][b] == false)
			adj[a][b] = true;
		else
			cout << endl << "Ja existe adjacencia entre esses nos !!";
	}
	else
		cout << endl << "Valor fora de escopo !!!" << endl;
}

void Grafo::remove(int a, int b) 
{
	if ((a<MAXNOS) && (b<MAXNOS)) 
	{
		if (adj[a][b] == true)
			adj[a][b] = false;
		else
			cout << endl << "Nao existe adjacencia entre esses nos !!";
	}
	else
		cout << endl << "Valor fora de escopo !!!" << endl;;
}


bool Grafo::adjacente(int a, int b)
{
	if ((a<MAXNOS) && (b<MAXNOS))
		return adj[a][b];
}

void Grafo::imprime_adj() 
{
	cout << endl << "Matriz de Adjacencias ..." << endl;

	for (int i = 0; i<num_nos; i++) 
	{
		for (int j = 0; j<num_nos; j++) 
		{
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

}

void Grafo::imprime_caminho() 
{
	for (int i = 0; i<num_nos; i++) 
	{
		for (int j = 0; j<num_nos; j++) 
		{
			cout << caminho[i][j] << " ";
		}

		cout << endl;
	}

	cout << endl;

}

void Grafo::imprime_peso() 
{
	cout << endl << "Matriz de Distancias/Pesos ..." << endl;

	for (int i = 0; i<num_nos; i++) 
	{
		for (int j = 0; j<num_nos; j++) 
		{
			cout << peso[i][j] << " ";
		}
		
		cout << endl;
	}

	cout << endl;

}

void Grafo::imprime_precede() 
{
	cout << endl << "Voce passou pelos nos: ";

	for (int i = num_nos - 1; i >= 0; i--) 
	{
		if (caminho[i] != false) 
		{
			cout << " " << precede[i];
		}
	}

	cout << endl;

}

bool Grafo::existe_caminho(int a, int b) 
{
	return caminho[a][b];
}

int Grafo::MenorCaminho(int s, int t)
{
	int N = num_nos;

	int distancia[MAXNOS];
	bool calculado[MAXNOS];
	int corrente;
	int menordist, novadist, i, k;
	int dc;

	for (i = 0; i<num_nos; i++) 
	{
		distancia[i] = INFINITO;
		calculado[i] = false;
		precede[i] = false;
	}

	distancia[s] = 0;
	calculado[s] = true;
	corrente = s;
	
	while (corrente != t) 
	{
		menordist = INFINITO;
		dc = distancia[corrente];
	
		for (i = 0; i<N; i++) 
		{
			if (!calculado[i]) 
			{
				novadist = dc + ret_peso(corrente, i);

				if (novadist < distancia[i]) 
				{
					distancia[i] = novadist;
					precede[i] = corrente;
				}
				
				if (distancia[i] < menordist) 
				{
					menordist = distancia[i];
					k = i;
				}
			}
		}

		corrente = k;
		calculado[corrente] = true;
	}

	return distancia[t];
}

int Grafo::ret_peso(int a, int b) 
{
	if (adjacente(a, b))
		return peso[a][b];
	else
		return INFINITO;
}


//------------------------------------------------------------------
