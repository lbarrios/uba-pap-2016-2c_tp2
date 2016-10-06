#include <bits/stdc++.h>

#include "../Classes/Grafo.cpp"

using namespace std;

int main() {
	int A, D;
	cin >> A >> D;

	//vector< vector<int> > lineas;

	int** lineas = new int*[A];
    bool** mayor = new bool*[A];
	bool** menor = new bool*[A];

    for(int x=0; x< A; x++){
        lineas[x] = new int[D];
        mayor[x] = new bool[D];
        menor[x] = new bool[D];
        for(int y=0; y < D ; y++){
            int val;
            cin >> val;
            lineas[x][y] = (val);
            mayor[x][y] = false;
            menor[x][y] = false;
        }
    }

    for(int x1=0; x1< A-1; x1++){
        for(int x2=x1+1; x2 < A; x2++){
            for(int y=0; y < D ; y++){
                    if( lineas[x1][y] <= lineas[x2][y]){
                        mayor[x2][x1] = true; menor[x1][x2] = true;
                    }
                    if( lineas[x1][y] >= lineas[x2][y]){
                        mayor[x1][x2] = true; menor[x2][x1] = true;
                    }
            }
        }
    }

	vector<Nodo> grafoInput = CreateGrafoFlujoWithShadowNodes(A);

    int iFuente = fuente(grafoInput);
    int iSumidero = sumidero(grafoInput);

	for(int i = 1; i <= A; i++) {
        int iShadow = shadowNode(grafoInput,i);
        grafoInput[iFuente].addBinaryAdyacente(i);
        grafoInput[iShadow].addBinaryAdyacente(iSumidero);
	}

    for(int x1=0; x1< A-1; x1++){
        int nodo1 = x1+1;
        for(int x2=x1+1; x2 < A; x2++){
            int nodo2 = x2+1;
            if(mayor[x1][x2] xor menor[x1][x2]){
                if(mayor[x1][x2]){
                    int nodo2Shadow = shadowNode(grafoInput, nodo2);
                    grafoInput[nodo1].addInfiniteAdyacente(nodo2Shadow);
                }
                if(menor[x1][x2]){
                    int nodo1Shadow = shadowNode(grafoInput, nodo1);
                    grafoInput[nodo2].addInfiniteAdyacente(nodo1Shadow);
                }
            }
        }
    }

    cout << A - EdmondKarps(grafoInput) << endl;
	return 0;
}
