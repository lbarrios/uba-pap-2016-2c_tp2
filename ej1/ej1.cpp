#include <bits/stdc++.h>

using namespace std;

struct Arista {
	int nodo;
	int capacidad;
	int flujo;
};

struct Nodo {
	char tipo; // 'E': est; 'A': escuela; 'X': ninguna de las dos
	vector<Arista> adyacentes;
};

int BFS(int startNode, int endNode, vector<Nodo>* grafo) {
	queue<int> q;
	q.push(startNode);

}

int main() {
	int N, M;
	cin >> N >> M;

	vector<Nodo> grafoInput(N+2);
	Nodo* fuente = &grafoInput[0];
	Nodo* sumidero = &grafoInput[N+1];



	fuente -> tipo = 'X';
	sumidero -> tipo = 'X';

	for(int i = 1; i < N+1; i++) {
		cin >> grafoInput[i].tipo;
		
		if(grafoInput[i].tipo == 'A'){
			
			Arista a;
			a.capacidad = 1;
			a.flujo = 0;
			a.nodo = i;
			fuente -> adyacentes.push_back(a);	
		}

		if(grafoInput[i].tipo == 'E'){
			
			Arista a;
			a.capacidad = 1;
			a.flujo = 0;
			a.nodo = N+1;
			grafoInput[i].adyacentes.push_back(a);
		}

	}

	for(int i = 0; i < M; i++) {
		int A, B;
		cin >> A >> B;
		Arista a;
		a.nodo = B;
		a.capacidad = 1;
		a.flujo = 0;

		grafoInput[A].adyacentes.push_back(a);
		a.nodo = A;
		grafoInput[B].adyacentes.push_back(a);
	}

	vector<Nodo> caminoAumento = grafoInput;

	for(int i=0; i< N+2; i++){
		

	} 


	/*for(int i = 0; i < N+2; i++) { //para imprimir grafoInput
		cout << "nodo: " << i << endl;
		for(int j = 0; j < grafoInput[i].adyacentes.size(); j++) {
			cout << "*: " << grafoInput[i].adyacentes[j].nodo << ", ";
		}
		cout << endl;
	}*/




	return 0;
}