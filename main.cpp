#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "grafo.h"
using namespace std;

int main()
{
	/*
	Grafo *grafo;
	int * lista;
	int i;
	int peso;
	int aux;
	
	grafo = new Grafo(5);
	
	grafo->novoVertice(0,"Fulano de tal");
	grafo->novoVertice(1,"Beltrano");
	grafo->novoVertice(2,"Silva Silva");
	grafo->novoVertice(3,"Silva");
	grafo->novoVertice(4,"Sil");

	grafo->novaAresta(0,1,10);
	grafo->novaAresta(1,2,10);
	grafo->novaAresta(2,0,10);
	
	grafo->novaAresta(3,0,10);
	grafo->novaAresta(4,3,10);

	cout << "{\"ordemtop\":[";
	lista = grafo->ordemTopologica();
	for(i=1;i<lista[0];i++)
	{
		cout << lista[i];
		if(i<lista[0]-1)
			cout << ",";
	}
	cout << "]}" << endl;
	*/
	
	
	Grafo *grafo;
	string linha;
	string nome;
	stringstream ss;
	int nvertice;
	int id;
	int id2;
	int peso;
	int i;
	int aux;
	int * lista;
	
	cin >> linha >> nvertice;
	
	grafo = new Grafo(nvertice);
	
	for(i=0;i<nvertice;i++)
	{
		cin >> id; 
		getline(cin, nome);
		nome.erase(0,1); //Elimina o caractere espaço do inicio
		grafo->novoVertice(id, nome);
	}
	cin >> linha;
	if(linha == "*Arcs")
	{	
		cin >> linha;
		grafo->setDirecionado(1);
		while(linha!="*Queries")
		{
			ss << linha << " ";
			ss >> id;
			ss.str().clear();
			cin >> id2 >> peso;
	
			grafo->novaAresta(id, id2, peso);
			grafo->novaAresta(id2, id, peso);
			
			cin >> linha;
		}
	}
	else
	{
		cin >> linha;
		grafo->setDirecionado(0);
		while(linha!="*Queries")
		{
			ss << linha << " ";
			ss >> id;
			
			cin >> id2 >> peso;
			
			ss.str().clear();
			
			grafo->novaAresta(id, id2, peso);
			
			cin >> linha;
		}
	}
	
	
	while(cin >> linha)
	{
		if(linha == "get")
		{
			cin >> id;
			nome = grafo->get(id);
			cout << "{\"vertice\":{\"ID\":" << id <<",\"dado\":";
			if(nome[0])
				cout << nome << ",\"resposta\":\"sucesso\"}}" << endl;
			else
				cout << "\"\",\"resposta\":\"falha\"}}" << endl;
			nome.clear();
		}
		else if(linha == "delete")
		{
			cin >> id;
			cout << "{\"delete\":{\"ID\"" << id << "\",resposta\":\"";
			aux = grafo->deleteid(id);
			if(aux)
				cout << "sucesso\"}}" << endl;
			else
				cout << "falha\"}}" << endl;
		}
		else if(linha == "vizinhos")
		{
			cin >> id;
			cout << "{\"vizinhos\":{\"ID\":" << id << ",\"resposta\":\"";
			lista = grafo->vizinhos(id);
			if(lista[0]>1)
			{
				cout << "sucesso\",\"vizinhos\":[";
				for(i=1;i<lista[0];i++)
				{
					cout << lista[i];
					if(i < lista[0]-1)
						cout << ",";
				}
				cout << "]}}" << endl;
			}
			else
				cout << "falha\",\"vizinhos\":[]}}" << endl;
			delete[] lista;
		}
		else if(linha == "conexao")
		{
			cin >> id >> id2;
			cout << "{\"conexao\":{\"ID1\":" << id << ",\"ID2\":" << id2 << ",\"resposta\":\"";
			aux = grafo->conexao(id, id2);
			if(aux < 0)
				cout << "falha\",\"conexao\":\"\"}}" << endl;
			else
			{
				cout << "sucesso\",\"conexao\":\"";
				if(aux)
					cout << "sim\"}}" << endl;
				else
					cout << "nao\"}}" << endl;
			}
		}	
		else if(linha == "ordemtopologica")
		{
			cout << "{\"ordemtop\":[";
			lista = grafo->ordemTopologica();
			for(i=1;i<lista[0];i++)
			{
				cout << lista[i];
				if(i<lista[0]-1)
					cout << ",";
			}
			cout << "]}" << endl;
			delete[] lista;
		}
		else if(linha == "arvoreminima")
		{
			cout << "{\"arvoreminima\":{\"arestas\":[";
			lista = grafo->arvoreminima(&aux);
			peso = 0;
			for(i=1;i<lista[0];i++)
			{
				switch(peso)
				{
					case 0:
					{
						cout << "(";
						peso++;
						break;
					}
					case 1:
					{
						cout << ",";
						peso++;
						break;
					}
					case 2:
					{
						cout << ")";
						if(i<lista[0]-1)
							cout << ",(";
						peso = 1;
					}
				}
				cout << lista[i];
				if(i == lista[0]-1)
					cout << ")";
			}
			cout << "],\"custo\":" << aux << "}}" << endl;
			delete[] lista;
		}
		else if(linha == "menorcaminho")
		{
			cin >> id >> id2;
			
			cout << "{\"menorcaminho\":{\"ID1\":" << id << ",\"ID2\":" << id2 << ",\"caminho\":[";
			aux = 0;
			lista = grafo->menorcaminho(id, id2, &aux);
			for(i=1;i<lista[0];i++)
			{
				cout << lista[i];
				if (i < lista[0]-1)
					cout << ",";
				if( i == (lista[0]-1))
					cout << "," << id2;
			}
			cout << "],\"custo\":" << aux << "}}" << endl;
			delete[] lista;
		}
	}
	return 0;
}


