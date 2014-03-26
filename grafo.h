#ifndef GRAFO_H_
#define GRAFO_H_

#include <cstdlib>
#include <string>
#include "vertice.h"
#include <vector>
#include <iostream>

using namespace std;

class Grafo
{
	private:
		Vertice **listaVertice;
		//Uma lista de ponteiros de ponteiros de vertice
		int nvertice;
		//Inteiro guardando o numero de vertices;
		
		int nvertice_atual;
		//inteiro que guarda o numero de vertices atuais;
		
		int direcionado;
		//Flag se o grafo é direcionado ou nao;
		
		int buscaProfundidade(int atual, int alvo);
		//Faz uma busca em profundidade do atual ao alvo recusivamente;
		
		int despintarGrafo();
		//Despinta todo o grafo;
		
		int * recursivaOrdemTopologica(int * resultado);
		//Metodo auxiliar a ordemTopologica
		
		int zeraCaminhoGrafo();
		//Chama funcao zeraCaminho a todos do grafo;
		
	public:
	
		Grafo(int nvertice);
		//Construtor do Grafo com informação do numero de vertices
	
		int novoVertice(int id, string nome);
		//Adiciona um vertice com o ID e o nome
	
		int novaAresta(int id1, int id2, int peso);
		//Adiciona uma aresta entre ID1 e ID2 com o respectivo peso
	
		string  get(int id);
		//Retorna se existir com o nome;
	
		int deleteid(int id);
		//Remove o vertice ID retornando string informando se foi sucedido ou nao
	
		int * vizinhos(int id);
		//Retorna a lista de vizinhos de vertice ID (aquele que ID aponta)
	
		int conexao(int id1, int id2);
		//informa se há conexão entre id1 e id2
	
		int * ordemTopologica();
		//Retorna lista de vertice em ordem topologica
		//Somente para direcionados e conectados
		//Tamanho do vertice em pos [0]
	
		int * arvoreminima(int * custototal);
		//Retorna lista de arestas que compoe a arvore minima
		//Somente para não-direcionados e conectados
	
		int * menorcaminho(int id1, int id2, int * custo);
		//Retorna uma lista de vertices que compoe o menos caminho entre id1 e id2
		
		int getNvertice();
		//Retorna o numero de vertices
		
		int setDirecionado(int n);
		//Coloca se o grafo é direcionado ou nao;
		
};
#endif
