#include <bits/stdc++.h>

using namespace std;

struct Arista {
	int nodoId;
	int capacidad;
	int flujo;
};



class Nodo{
public:
    bool isShadow;
    char tipo;
    vector<Arista> aristas;
    Nodo();
    Nodo(char typeChar);
    void addBinaryAdyacente(int nodoId);
};

vector<Nodo> CreateGrafo(int inputSize){
    int grafoSize = (inputSize)+2;
    vector<Nodo> GrafoInput(grafoSize);
    return GrafoInput;
}

vector<Nodo> CreateGrafoWithShadowNodes(int inputSize){
    int grafoSize = (inputSize * 2)+2;
    vector<Nodo> GrafoInput(grafoSize);
    for(int i = inputSize + 1; i < grafoSize - 1; i++){
            GrafoInput[i].isShadow = true;
    }
    return GrafoInput;
}

int fuente(vector<Nodo> grafo){
    return 0;
}

int sumidero(vector<Nodo> grafo){
    return grafo.size() - 1;
}

int shadowNode(vector<Nodo> grafo, int originalNode){
    return originalNode + (grafo.size() - 2)/2;
}


Nodo::Nodo(){
    tipo = ' ';
    isShadow = false;
};

Nodo::Nodo(char typeChar){
    tipo = typeChar;
    isShadow = false;
};

void Nodo::addBinaryAdyacente(int nodoId){
    Arista a;
	a.capacidad = 1;
	a.flujo = 0;
	a.nodoId = nodoId;
    aristas.push_back(a);
};

std::ostream &operator<<(std::ostream &os, Arista const &a) {
    return os << "["<< a.flujo << "/" << a.capacidad << "-}" << a.nodoId << "]" ;
}

std::ostream &operator<<(std::ostream &os, vector<Arista> const &a) {
    for(int x = 0; x < a.size(); x++){os << a[x];} return os;
}

std::ostream &operator<<(std::ostream &os, Nodo const &a) {
    return os << " '" << a.tipo << "'" << a.aristas;
}

int MAXVALUE = 500000000;

bool menorContraInfinito(int a, int b){
    if(a == b) return false;
    if( b == -1) return true;
    return a < b;

}

struct CaminoCrecimiento{
    vector<int> nodos;
    vector<int> posicionEnPadre;
    int flujoASacar;
};

CaminoCrecimiento buscarCaminoCrecimiento(vector<Nodo> grafo){
    int iFuente = fuente(grafo);
    int iSumidero = sumidero(grafo);

    vector<int> flujos(grafo.size());
    vector<int> padre(grafo.size());
    vector<int> lugarEnPadre(grafo.size());

    for(int x = 0; x < grafo.size(); x++){
            flujos[x] = -1;
            padre[x] = -1;
            lugarEnPadre[x] = -1;
    }

    vector<int> camino;
    camino.push_back(iFuente);
    int caminopos = 0;

    while(camino.size() > caminopos){
        int curNodo = camino[caminopos];
        vector<Arista> aristas = grafo[curNodo].aristas;
        for(int x = 0; x < aristas.size();x++){
            int xNodo = aristas[x].nodoId;
            int flujo = aristas[x].capacidad - aristas[x].flujo;
            if(flujo > 0 and flujos[xNodo] == -1){
                if(xNodo != iSumidero){
                        lugarEnPadre[xNodo] = x;
                        padre[xNodo] = curNodo;
                        flujos[xNodo] = min(flujos[curNodo], flujo);
                        if(curNodo == iFuente) flujos[xNodo] = flujo;
                        camino.push_back(xNodo);
                }else{
                    int pSumidero = padre[iSumidero];
                    int curFlujo = min(flujos[curNodo], flujo);
                    if( pSumidero == -1 or flujos[pSumidero] > curFlujo){
                        lugarEnPadre[iSumidero] = x;
                        padre[iSumidero] = curNodo;
                        flujos[iSumidero] = curFlujo;

                    }
                }
            }
        }
        caminopos += 1;
    }

    CaminoCrecimiento respuesta;
    respuesta.flujoASacar = flujos[iSumidero];

    vector<int> caminoNodos;
    vector<int> caminoNodosLugarEnPadre;

    int currentNodo = padre[iSumidero];
    caminoNodosLugarEnPadre.push_back(lugarEnPadre[iSumidero]);
    while(currentNodo > -1){
        caminoNodos.push_back(currentNodo);
        caminoNodosLugarEnPadre.push_back(lugarEnPadre[currentNodo]);
        currentNodo = padre[currentNodo];
    }
    respuesta.nodos = caminoNodos;
    respuesta.posicionEnPadre = caminoNodosLugarEnPadre;


    return respuesta;
}

std::ostream &operator<<(std::ostream &os, vector<Nodo> const &a) {
    if(a[a.size()-2].isShadow){for(int x = 0; x <= a.size()/2; x++){if(x == 0) os << x << ":"<< a[x] << endl;
    if(x == a.size()/2) os << a.size()-1 << ":"<< a[a.size()-1] << endl; if(x != 0 and x != a.size()/2) os <<
    x << ":"<< a[x] << " ---> " << shadowNode(a,x) << ":" << a[shadowNode(a,x)] << endl;}}
    else{for(int x = 0; x < a.size(); x++){os << x << ":"<< a[x] << endl;}}
    return os;
}


int EdmondKarps(vector<Nodo> grafo){
    //cout << grafo << endl;
    CaminoCrecimiento curCamino = buscarCaminoCrecimiento(grafo);
    int p = 0;
    int limits = 4;
    while(curCamino.nodos.size() > 0){
        /*if(p<limits){
           // cout << "CAMINOS:" << endl;
            for(int m = 0; m < curCamino.nodos.size();m++){
            //    cout << "[" << curCamino.nodos[m] << "]";
            }
            cout << endl;

            cout << "POSICION PADRES:" << endl;
            for(int m = 0; m < curCamino.posicionEnPadre.size();m++){
                cout << "[" << curCamino.posicionEnPadre[m] << "]";
            }
            cout << endl;
        }*/
        for(int i = 0; i < curCamino.nodos.size(); i++){
            grafo[curCamino.nodos[i]].aristas[curCamino.posicionEnPadre[i]].flujo += curCamino.flujoASacar;
        }
        curCamino = buscarCaminoCrecimiento(grafo);
        /*if(p<limits) cout << grafo << endl;

        p = p +1;*/
    }
   //  cout << grafo << endl;
    int answer = 0;
    for(int i = 0; i < grafo.size(); i ++){
        Nodo n = grafo[i];
        for(int x = 0; x< n.aristas.size();x++){
            Arista a = n.aristas[x];
            if(a.nodoId == grafo.size()-1){
               // cout << a.flujo<<endl;
                answer += a.flujo;
            }
        }

    }

    return answer;

}


