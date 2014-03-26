#ifndef VERTICE_H_
#define VERTICE_H_

#include <cstdlib>
#include <string>
#include <vector>

#include <iostream>

using namespace std;

class Vertice
{
	private:
		string nome;
		//Nome do vertice
		vector<int> aresta;
		//vetor com os numero impares sendo o destino e o proximo par sendo o peso; pos 0 é o numero de arestas;
		int pintado;
		//Flag que indica se é pintado ou não;
		int grau_entrada;
		//inteiro que marca o grau de entrada do vertice
		vector<int> caminho;
		//Grava o caminho até este vertice
		//Usado para menor caminho
		
	public:

		Vertice(string nome);
		//Construtor de novo vertice junto com o nome;

		string getNome();
		//Retorna o nome do vertice
		int * getVizinho();
		//Retorna lista de quem é origem


		int novaAresta(int id, int peso);
		//Insere uma aresta sendo este como origem
		int removeAresta(int id);
		//Remove que arestas que aponta a id
		int * getAresta();
		//Retorna o vetor das arestas;

		int colorir(int cor);
		//Colore o vertice
		int pintar();
		//Pinta o vertice
		int despintar();
		//Despinta o vertice
		int getPintado();
		//Retorna se foi pintado

		int getGrauEntrada();
		//Retorna o grau de entrada
		int incrementaGrauEntrada();
		//Incrementa o grau de entrada deste vertice
		int decrementaGrauEntrada();
		//Decrementa o grau de entrada deste vertice

		int getPeso(int id);
		//Retorna o peso da aresta que aponta para id

		int * getCaminho();
		//retorna o caminho deste vertice
		int addCaminho(int * novocaminho);
		//adiciona o caminho a esse vertice
		int addCaminho(int novocaminho);
		//Para fazer Overload de funçao
		int zeraCaminho();
		//Zera o caminho do vertice
};
#endif
