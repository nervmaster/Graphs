#include "grafo.h"

// PUBLICOS

Grafo::Grafo(int nvertice)
{
	this->nvertice = nvertice;
	this->nvertice_atual = nvertice;
	
	listaVertice = new Vertice*[nvertice];
	//Cria um array com os todos os objetos vertice
	
}//Construtor

int Grafo::novoVertice(int id, string nome)
{
	//Cria um novo vertice com seu nome
	if(listaVertice[id] = new Vertice(nome))
		return 1;
	return 0;
}

int Grafo::novaAresta(int id1, int id2, int peso)
{
	if(listaVertice[id1]->novaAresta(id2, peso))
	{
		listaVertice[id2]->incrementaGrauEntrada();
		//Incrementa o grau de entrada do alvo
		return 1;
	}
	return 0;
}

string Grafo::get(int id)
{
	if(listaVertice[id])
		return listaVertice[id]->getNome();
	return NULL;
}

int Grafo::deleteid(int id)
{
	int i;
	int *vizinho;
	
	if(listaVertice[id]!=NULL)
	{
		
		vizinho = listaVertice[id]->getVizinho();
		//Pega uma lista de vertices que ele é origem
		//vizinhos
		//Decrementa o grau de entrada de seus vizinhos;
		for(i=1;i<vizinho[0];i++)
		{
			listaVertice[vizinho[i]]->decrementaGrauEntrada();
		}
		
		delete vizinho;
		
		for(i=0;i<nvertice;i++) //Deletar todas as referencias ao vertice deletado
		{						//Percorre N deletando
			if(listaVertice[i]) //se existe o vertice
			{
				listaVertice[i]->removeAresta(id); //Deleta todos as arestas de id
			}
		}
		
		delete listaVertice[id];
		nvertice_atual--;
		listaVertice[id] = NULL;
		return 1;
	}
	return 0;
}

int * Grafo::vizinhos(int id)
{
	int * lista;
	
	if(listaVertice[id]) //Verificar se o vertice existe
	{
		
		lista = listaVertice[id]->getVizinho();
		//Pega a lista de vertice que ele é origem
		return lista;
	}
	lista = new int;
	*lista = 0;
	return lista;
}

int Grafo::conexao(int id1, int id2)
{
	//Despintar todos os vertices
	this->despintarGrafo();
		
	if(listaVertice[id1] && listaVertice[id2]) //Se a origem e alvo são validos fazer a busca
	{
		return this->buscaProfundidade(id1,id2);
	}
	return -1;
}



int Grafo::buscaProfundidade(int atual, int alvo)
{
	int resultado = 0;
	int counter = 1;
	int *vizinho;
	
	vizinho = listaVertice[atual]->getVizinho(); //Pega lista de vizinhos
	
	if(!listaVertice[atual]->getPintado()) //Se não esta pintado
		listaVertice[atual]->pintar(); //pinta
	else
		return 0; //Se ja foi cancela recursao
			
	if(atual == alvo) //Se encontrado
	{
		return 1;
	}
	
	while(counter < vizinho[0]) //Como o indicador é do tamanho do vetor então vizinho[0] tem tamanho minimo 1
	{
		resultado = buscaProfundidade(vizinho[counter], alvo);
		counter++;
		if(resultado)
			return resultado;
	}
	return resultado; //Para o termino de toda a recursao
}

int Grafo::despintarGrafo()
{
	int i;
	
	for(i=0;i<nvertice;i++)
	{
		if(listaVertice[i]) //Para só acessar válidos
			listaVertice[i]->despintar();
	}
	return 1;
}

int * Grafo::recursivaOrdemTopologica(int * resultado)
{
	int posinicio = resultado[0];//marca a posição inicial desta recursão no vetor resultado
	int posfinal;//marca a posição final desta recursão no vetor resultado
	int *vizinho;
	int i;
	int j;
	
	if(resultado[0] < nvertice_atual)
	{
		for(i=0;i<nvertice;i++)
		{
			if(listaVertice[i] && !listaVertice[i]->getPintado() && !listaVertice[i]->getGrauEntrada())//Se existe o vertice e nao tiver pintado
			{
				vizinho = listaVertice[i]->getVizinho();
				listaVertice[i]->pintar(); //pinta o vertice				
				resultado[resultado[0]] = i; //Vai imprimindo no vetor contador
				resultado[0]++;
				if(vizinho[0]-1)
				{//Pegando os com grau entrada 0
					for(i=1;i<vizinho[0];i++)
					{//removendo as arestas
						listaVertice[vizinho[i]]->decrementaGrauEntrada();
					}
					delete[] vizinho;
				}
			}
		}
		posfinal = resultado[0];
		
		recursivaOrdemTopologica(resultado);
	
		//Agora retornar nos vertices
		for(i=posinicio;i<posfinal;i++)
		{
			vizinho = listaVertice[resultado[i]]->getVizinho();
			for(j=1;i<vizinho[0];i++)
			{
				listaVertice[vizinho[j]]->incrementaGrauEntrada();
			}
		}
	}
	return resultado;
}

int * Grafo::ordemTopologica()
{
	int i;
	int *resultado;
	
	this->despintarGrafo();
	//Todos os grafos despintados
	
	if(!this->direcionado) //Somente opera em direcionados;
	{
		resultado = new int;
		*resultado = 0;
		return resultado;
	}
		
	resultado = new int[nvertice+1];
	resultado[0] = 1;
	//tamanho do vetor
	return recursivaOrdemTopologica(resultado);
	
}

int Grafo::getNvertice()
{
	return nvertice;
}

int * Grafo::menorcaminho(int id1, int id2, int * custo)
{
	int * dist;
	int * conjuntoq;
	int * vizinho;
	int i;
	int cont;
	int atual;
	int pos;
	int alt;
	int * caminho;
	
	dist = new int[nvertice];
	
	for(i=0;i<nvertice;i++)//Sei que acarreta em desperdicio de espaço se ha vertices deletados;
	{
		dist[i] = -1; //Representação simbolica para inf
	}
	
	dist[id1] = 0; //O vertice origem para todos os outros vertices
	
	conjuntoq = new int[nvertice_atual+1];
	
	cont=1;
	for(i=0;i<nvertice;i++)
	{
		if(listaVertice[i]) //Se existe o vertice
		{
			conjuntoq[cont] = i;
			cont++;
		}
	}
	conjuntoq[0] = nvertice_atual+1; //Informa quantos vertices estão presentes no conjunto
	
	while(conjuntoq[0]) 
	{
		cont = -1;
		for(i=1;i<conjuntoq[0];i++)
		{
			if((dist[conjuntoq[i]] >= 0 && cont >= dist[conjuntoq[i]]) || cont==-1)
			{
				cont = dist[conjuntoq[i]];			//Pega o vertice com menor dist
				atual = conjuntoq[i];
				pos = i;
			}	
		}
		
		for(i=pos;i<conjuntoq[0]-1;i++)
		{
			conjuntoq[i] = conjuntoq[i+1]; //Faz a deleção movendo o vetor a esquerda
		}
		conjuntoq[0]--;
		
		vizinho = listaVertice[atual]->getVizinho();
		
		for(i=1;i<vizinho[0];i++)
		{
			alt = dist[atual] + listaVertice[atual]->getPeso(vizinho[i]);
			
			if(dist[vizinho[i]] < 0 || alt < dist[vizinho[i]])
			{
				listaVertice[vizinho[i]]->zeraCaminho(); 								//Adiciona o caminho do vertice ao vertice
				listaVertice[vizinho[i]]->addCaminho(listaVertice[atual]->getCaminho());
				listaVertice[vizinho[i]]->addCaminho(atual);				
				
				dist[vizinho[i]] = alt;
			}
		}
		
		delete vizinho;
	}
	

	caminho = listaVertice[id2]->getCaminho();
	*custo = dist[id2];
	
	delete[] dist;
	delete[] conjuntoq;
	
	this->zeraCaminhoGrafo();
	
	return caminho;
}

int Grafo::zeraCaminhoGrafo()
{
	int i;
	for(i=0;i<nvertice;i++)
	{
		if(listaVertice[i])
			listaVertice[i]->zeraCaminho();
	}
	return 1;
}

int * Grafo::arvoreminima(int * custototal)
{
	//Variaveis para ter a lista ordenada de vertices
	
	vector<int> listaaresta;
	vector<int>::iterator it;
	int i;
	int j;
	
	int dummy;
	
	int * lista;
	int * listaaux;
	
	//Variaveis para fazer a arvore minima;
	
	int contador=0;
	int * arestaresultado;
	vector< vector<int> > listacores;
	vector< vector<int> >::iterator itlistacor;
	int contcor=0;
	vector<int>::iterator itcor;
	int corv1;
	int corv2;
	
	
	
	if(this->direcionado) //nao funciona em direcionados;
	{
		lista = new int;
		*lista = 0;
		*custototal = 0;
		return lista;
	}	
	
	it = listaaresta.begin();
	
	for(i=0;i<nvertice;i++)
	{
		if(listaVertice[i])
		{
			lista = listaVertice[i]->getAresta();
			j = 1;
			while(j<lista[0]*2-1)
			{
				listaaux = new int[3];
				if(i < lista[j])
				{
					listaaux[0] = i;
					listaaux[1] = lista[j];
				}
				else
				{
					listaaux[0] = lista[j];
					listaaux[1] = i;
				}
				listaaux[2] = lista[j+1];
				j+=2;
				if(listaaresta.empty())
				{
					listaaresta.push_back(listaaux[0]);
					listaaresta.push_back(listaaux[1]);
					listaaresta.push_back(listaaux[2]);
				}
				else //Se não está vazio;
				{
					it = listaaresta.begin();
					it+=2; //it = peso da aresta;
					while(*it < listaaux[2] && it < listaaresta.end())
					{
						it+=3;
					}
					if(it <= listaaresta.end())
						it-=2;	//voltando a pos das coordenadas
					else
						it = listaaresta.end();

					if(it == listaaresta.end() || !(*it == listaaux[0] && *(it+1) == listaaux[1])) //Se ja não foi adicionado;
					{
						listaaresta.insert(it,listaaux, listaaux+3);
					}
				}
				delete[] listaaux;
			}//fim while
			delete[] lista;
		}
	}//fim for
	
	//listaaresta possui a lista ordenada por peso das arestas;

	
	*custototal = 0;
	
	this->despintarGrafo();
	
	arestaresultado = new int[(nvertice_atual-1)*2+1];
	
	it = listaaresta.begin();

	while(it < listaaresta.end()) //para um grafo conectado são necessarias nvertice-1 arestas
	{
		corv1 = listaVertice[*it]->getPintado();
		corv2 = listaVertice[*(it+1)]->getPintado();
		
		if(corv1 || corv2) //Se um dos dois estiver pintado;
		{
			if(corv1 && corv2) //Ambos estão pintados
			{
				if(corv1 != corv2) //Se são de cores diferentes
				{
					*(custototal)+= *(it+2); // Incrementa o custo da aresta;
					contador++;
					
				
					arestaresultado[contador*2-1] = *it;
					arestaresultado[contador*2] = *(it+1);

					if(corv1 < corv2) //todos ficam com a cor menor;
					{
						for(itcor = listacores[corv2-1].begin()+1; itcor < listacores[corv2-1].end(); itcor++)
						{
							listacores[corv1-1].push_back(*itcor);
							listaVertice[*itcor]->colorir(corv1); //Todos serão cor do v1;
							listacores[corv1-1][0]++; //Aumenta o contador;
						}
						listacores[corv2-1].clear();
					}
					else
					{
						for(itcor = listacores[corv1-1].begin()+1; itcor < listacores[corv1-1].end(); itcor++)
						{
							listacores[corv2-1].push_back(*itcor);
							listaVertice[*itcor]->colorir(corv2); //Todos serão cor do v1;
							listacores[corv2-1][0]++; //Aumenta o contador;
						}
						listacores[corv1-1].clear();
					}
				}
			}
			else //So um esta pintado
			{
				*(custototal)+= *(it+2); // Incrementa o custo da aresta;
				contador++;
			
				arestaresultado[contador*2-1] = *it;
				arestaresultado[contador*2] = *(it+1);

				if(corv1) //Se v1 é o pintado
				{
					listacores[corv1-1].push_back(*(it+1));
					listacores[corv1-1][0]++;
					listaVertice[*(it+1)]->colorir(corv1);
				}
				else
				{
					listacores[corv2-1].push_back(*it);
					listacores[corv2-1][0]++;
					listaVertice[*(it)]->colorir(corv2);
				}
			}
		}
		else //Nenhum esta pintado
		{
			*(custototal)+= *(it+2); // Aresta Valida
			contador++;
			
			arestaresultado[contador*2-1] = *it;
			arestaresultado[contador*2] = *(it+1);
			
			listacores.push_back(vector<int>());
			listacores[contcor].push_back(2); //2 vertices no grupo;
			listacores[contcor].push_back(*it);
			listacores[contcor].push_back(*(it+1));
						
			listaVertice[*it]->colorir(contcor+1);
			listaVertice[*(it+1)]->colorir(contcor+1);
			
			contcor++;
		}
		it+=3;
	}
	arestaresultado[0] = contador*2+1;
	
	for(i=0;i<contcor;i++)
		listacores[i].clear();
	listacores.clear();
		
		
	return arestaresultado;
}

int Grafo::setDirecionado(int n)
{
	if(n>0)
		this->direcionado = 1;
	else
		this->direcionado = 0;
	return 1;
}
