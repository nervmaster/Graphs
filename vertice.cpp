#include "vertice.h"

// PUBLICO

Vertice::Vertice(string nome)
{
	this->pintado = 0;
	this->nome = nome;
	this->grau_entrada = 0;
	aresta.push_back(1); //Contador de arestas na pos 0;
	caminho.push_back(1); //Contador de caminho na pos 0;
}

int Vertice::novaAresta(int id, int peso)
{
	//Nova aresta aumenta o contador
	aresta[0]++;
	aresta.push_back(id); //Posição ímpar>0: 1, 3, 5, 7... contém destino.
	aresta.push_back(peso); //Posição Par>0: 2,4,6,8... contem peso;
	//Tuplas impar;par>0 é uma aresta (1,2)(3,4)(5,6)

	//cout << "VERTICE ARESTA[0]: " << aresta[0] << " ID:" << id << " Peso:" << peso << endl;
	
}

string Vertice::getNome()
{
	return this->nome;
}

int Vertice::removeAresta(int id)
{//remove as arestas que apontam para id
	int i;
	int counter=0;
	
	for(i=1;i<aresta[0]*2-1;i+=2) //Pegar so os impares >0
	{
		if(aresta[i] == id) //Se encontrar move o vetor a esquerda.
		{
			counter++; //Encontrou
			if(i < (aresta[0]*2)-2) //Se não está ao final do vetor (evitar acesso inadequado a mem)
			{	
				aresta[i] = aresta[i+2];
				aresta[i+1] = aresta[i+3];
			}
		}
	}
	for(i=0;i<counter;i++)
	{
		aresta[0]--; //Uma aresta a menos
		aresta.pop_back();
		aresta.pop_back();
	}
	return 1;
}

int * Vertice::getVizinho()
{//retorna lista de vizinhos
	int *lista;
	int counter=0;
	int i;
	
	lista = new int[aresta[0]+1];
	
	
	
	lista[0] = aresta[0];
	
	for(i=1;i<aresta[0]*2;i+=2) //*2 pois são tuplas e a pos 0 marca o numero de tuplas
	{
		counter++;
		lista[counter] = aresta[i];
	}
	
	return lista;
}

int Vertice::pintar()
{
	this->pintado=1;
}

int Vertice::despintar()
{
	this->pintado=0;
}

int Vertice::getPintado()
{
	return this->pintado;
}

int Vertice::getGrauEntrada()
{
	return grau_entrada;
}

int Vertice::incrementaGrauEntrada()
{
	grau_entrada++;
}

int Vertice::decrementaGrauEntrada()
{
	grau_entrada--;
}

int Vertice::getPeso(int id)
{
	int i=1;
	int achado=0; //Flag para indicar a existencia de uma aresta a id
	
	
	while(!achado)
	{
		if(aresta[i]==id)
			achado = 1;
		i+=2; //Para pegar somente os impares; Que é o id da tupla;
	}
	if(achado)
		return aresta[i-1]; //Devido ao +2 retorna uma unidade que é o peso da aresta
	return 0;
}

int Vertice::addCaminho(int * novocaminho)
{
	int i;
	
	for(i=1;i<novocaminho[0];i++)
	{
		caminho.push_back(novocaminho[i]);
		caminho[0]++;
	}
	return 1;
}

int Vertice::addCaminho(int novocaminho)
{
	int i;
	
	caminho.push_back(novocaminho);
	caminho[0]++;
	
	return 1;
}



int * Vertice::getCaminho()
{
	int i;
	int * result;
	
	result = new int[caminho[0]];
	
	for(i=0;i<caminho[0];i++)
	{
		result[i] = caminho[i];
	}
	return result;
}

int Vertice::zeraCaminho()
{
	caminho.clear();
	caminho.push_back(1);
}

int * Vertice::getAresta()
{
	int * lista;
	int i;
	lista = new int[aresta[0]*2-1]; //Não pega o tamanho da lista;
	for(i=0;i<aresta[0]*2-1;i++)
	{
		lista[i] = aresta[i];
	}
	return lista;
}

int Vertice::colorir(int cor)
{
	this->pintado = cor;
	return 1;
}
