#include <bits/stdc++.h>

#include "../Classes/Grafo.cpp"

using namespace std;

int main() {
	int N, M;
	cin >> N >> M;

	vector<Nodo> grafoInput = CreateGrafoFlujoWithShadowNodes(N);


    int iFuente = fuente(grafoInput);
    int iSumidero = sumidero(grafoInput);

	for(int i = 1; i <= N; i++) {
        int iShadow = shadowNode(grafoInput,i);
        char type;

		cin >> type;
        grafoInput[i].tipo = type;
        grafoInput[iShadow].tipo = type;

        grafoInput[i].addBinaryAdyacente(iShadow);

		if(grafoInput[i].tipo == 'A'){
            grafoInput[iFuente].addBinaryAdyacente(i);
		}
		if(grafoInput[i].tipo == 'E'){
			grafoInput[iShadow].addBinaryAdyacente(iSumidero);
		}
	}

    for(int i = 1; i <= M; i++) {
        int from; int to;
        cin >> from >> to;
        int toShadow = shadowNode(grafoInput, to);
        int fromShadow = shadowNode(grafoInput, from);

        grafoInput[fromShadow].addBinaryAdyacente(to);
        grafoInput[toShadow].addBinaryAdyacente(from);

    }

	cout << EdmondKarps(grafoInput) << endl;


	return 0;
}
