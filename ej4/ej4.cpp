#include <bits/stdc++.h>

#include "../Classes/Grafo.cpp"

using namespace std;

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
