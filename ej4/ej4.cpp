#include <bits/stdc++.h>

#include "../Classes/Grafo.cpp"

using namespace std;

vector<int>  KosarajuSharir(vector<Nodo> grafo){
    vector<int> grupoFuertementeConexo;
    vector<bool> visitado;
    vector<bool> expanded;
    for(int x = 0; x < grafo.size();x++){
            visitado.push_back(false);
            expanded.push_back(false);
            grupoFuertementeConexo.push_back(-1);
    }
    vector<int> forwardPila;
    vector<int> backwardPila;

    for(int x = 0; x < grafo.size(); x++){
        if(!visitado[x]){
            visitado[x] = true;
            forwardPila.push_back(x);
            while(forwardPila.size() > 0){
                int innerX = forwardPila[forwardPila.size()-1];
                bool deadEnd = true;
                if(!expanded[innerX]){
                    for(int y=0; y < grafo[innerX].aristas.size();y++){
                        int vecino = grafo[innerX].aristas[y].nodoId;
                        if(!visitado[vecino]){
                            deadEnd = false;
                            visitado[vecino] = true;
                            expanded[innerX] = true;
                            forwardPila.push_back(vecino);
                        }
                    }
                }
                vector<int> a;
                if(deadEnd){
                   // cout<< "*POP*" << endl;
                    backwardPila.push_back(innerX);
                    forwardPila.pop_back();
                    a = backwardPila;
                   // cout<< "BACKWARD :";
                   // for(int i = 0; i < a.size(); i++){cout << "|" << a[i] ;}; cout << endl;
                }
                    a = forwardPila;
                   // cout<< "FORWARD :";
                   // for(int i = 0; i < a.size(); i++){cout << "|" << a[i] ;}; cout << endl;
            }
        }
    }
    vector<Nodo> grafoTrans = GrafoTranspuesto(grafo);
    while(backwardPila.size() > 0){
        int currentNodo = backwardPila[backwardPila.size() - 1];
        backwardPila.pop_back();
        if(grupoFuertementeConexo[currentNodo] == -1){
            //cout << "CNODO:" << currentNodo << endl;
            vector<int> vecinosPila;
            vecinosPila.push_back(currentNodo);
            grupoFuertementeConexo[currentNodo] = currentNodo;
            while(vecinosPila.size() > 0){
                int currentVecino = vecinosPila[vecinosPila.size() - 1];
              //  cout <<currentVecino << "_";
                //grupoFuertementeConexo[currentVecino] = currentNodo;
                vecinosPila.pop_back();
                for(int x = 0; x < grafoTrans[currentVecino].aristas.size(); x++){
                    int vecino = grafoTrans[currentVecino].aristas[x].nodoId;
                  //  cout << "vecino:" << vecino<< endl;
                    if( grupoFuertementeConexo[vecino] == -1){
                        grupoFuertementeConexo[vecino] = currentNodo;
                        vecinosPila.push_back(vecino);
                    }
                }
              //  cout << endl;
            }
          //  cout << endl;
        }
    }
    return grupoFuertementeConexo;
}


int main() {
	int A, P, Q;
    int from, to;

	cin >> A >> P;
    vector<Nodo> grafoInput = CreateGrafo(A);

    for(int i = 0; i < P; i++) {
        cin >> from >> to;
        from--; to--;
        grafoInput[from].addAdyacente(to);
    }

    //Grupo Fuermente Conexo
    vector<int> GFC = KosarajuSharir(grafoInput);

    cin >> Q;

    for(int i = 0; i < Q; i++){
        cin >> from >> to;
        from--; to--;
        cout << (GFC[from] == GFC[to] ? 'S' : 'N') << endl;
    }


	return 0;
}
