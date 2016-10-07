#ifndef GRAFO_CLASS_PAP_2016_TP2
#define GRAFO_CLASS_PAP_2016_TP2

#include <bits/stdc++.h>
#include <limits>

using namespace std;

// Si bien no lo usamos, la escritura correcta del algoritmo de Dilworh require usar infinio.
int IntegerInfinityPlaceholder = numeric_limits<int>::max();

//////////
////////// CLASES Y ESTRUCTURAS
//////////

struct Arista {
	int nodoId;
	int capacidad;
	int flujo;
	//Arista* aristaInvertida;
};

class Nodo{
public:
    bool isShadow;
    char tipo;
    vector<Arista> aristas;
    Nodo();
    Nodo(char typeChar);
    void addAdyacente(int nodoId);
    void addBinaryAdyacente(int nodoId);
    void addInfiniteAdyacente(int nodoId);
};

struct CaminoCrecimiento{
    vector<int> nodos;
    vector<int> direccion;
    int flujoASacar;
};

std::ostream &operator<<(std::ostream &os, Arista const &a);

std::ostream &operator<<(std::ostream &os, vector<Arista> const &a);

std::ostream &operator<<(std::ostream &os, Nodo const &a);

std::ostream &operator<<(std::ostream &os, vector<Nodo> const &a);

//////////
////////// FUNCIONES CREACION DE GRAFOS
//////////

vector<Nodo> CreateGrafo(int inputSize){
    int grafoSize = (inputSize);
    vector<Nodo> GrafoInput(grafoSize);
    return GrafoInput;
}

vector<Nodo> CreateGrafoFlujo(int inputSize){
    int grafoSize = (inputSize)+2;
    vector<Nodo> GrafoInput(grafoSize);
    return GrafoInput;
}

vector<Nodo> CreateGrafoFlujoWithShadowNodes(int inputSize){
    // Los shadow nodes son una forma facil de generar la copia de los nodos que piden muchos algoritmos.
    int grafoSize = (inputSize * 2)+2;
    vector<Nodo> GrafoInput(grafoSize);
    for(int i = inputSize + 1; i < grafoSize - 1; i++){
            GrafoInput[i].isShadow = true;
    }
    return GrafoInput;
}

//////////
////////// FUNCIONES UTILIARIAS DE GRAFOS
//////////

int fuente(vector<Nodo> grafo){
    return 0;
}

int sumidero(vector<Nodo> grafo){
    return grafo.size() - 1;
}

int shadowNode(vector<Nodo> grafo, int originalNode){
    return originalNode + (grafo.size() - 2)/2;
}

//////////
////////// FUNCIONES DE NODOS
//////////

Nodo::Nodo(){
    tipo = ' ';
    isShadow = false;
};

Nodo::Nodo(char typeChar){
    tipo = typeChar;
    isShadow = false;
};

void Nodo::addAdyacente(int nodoId){
    Arista a;
    a.capacidad = 0;
	a.flujo = 0;
	a.nodoId = nodoId;
    aristas.push_back(a);
};

void Nodo::addBinaryAdyacente(int nodoId){
    Arista a;
	a.capacidad = 1;
	a.flujo = 0;
	a.nodoId = nodoId;
    aristas.push_back(a);
};

void Nodo::addInfiniteAdyacente(int nodoId){
    Arista a;
	a.capacidad = IntegerInfinityPlaceholder;
	a.flujo = 0;
	a.nodoId = nodoId;
    aristas.push_back(a);
};


//////
////// FUNCIONES AUXILIARES
//////

int** MatrizDePosicionesDePadres(vector<Nodo> grafo){
        int cant = grafo.size();
        int** matriz = new int*[cant];
        for(int x=0; x< cant; x++){
            matriz[x] = new int[cant];
            for(int x2=0; x2< cant; x2++) matriz[x][x2] = -1;
        }

        for(int x = 0; x < grafo.size(); x++){
            for(int y = 0; y < grafo[x].aristas.size(); y++)matriz[x][grafo[x].aristas[y].nodoId] = y;
        }

        return matriz;
}

vector<Nodo> GrafoTranspuesto(vector<Nodo> grafo){
    vector<Nodo> transpuesto;
    vector<Arista> emptyArista;
    for(int x = 0; x < grafo.size();x++){
        transpuesto.push_back(grafo[x]);
        transpuesto[x].aristas = emptyArista;
    }

    for(int x = 0; x < grafo.size();x++){
        vector<Arista> aristas = grafo[x].aristas;
        for(int y = 0; y < aristas.size();y++){
         int id = aristas[y].nodoId;
         int last = transpuesto[id].aristas.size();
         transpuesto[id].addAdyacente(x);
         transpuesto[id].aristas[last].flujo = grafo[x].aristas[y].flujo;
         transpuesto[id].aristas[last].capacidad = grafo[x].aristas[y].capacidad;
        }
    }

    return transpuesto;
}

CaminoCrecimiento buscarCaminoCrecimiento(vector<Nodo> grafo){
    int iFuente = fuente(grafo);
    int iSumidero = sumidero(grafo);

    vector<int> flujos(grafo.size());
    vector<int> padre(grafo.size());
    vector<int> direccion(grafo.size());

    for(int x = 0; x < grafo.size(); x++){
            flujos[x] = -1;
            padre[x] = -1;
            direccion[x] = 0;
    }
    direccion[0] = 1;

    vector<Nodo> residual = GrafoTranspuesto(grafo);

    vector<int> camino;
    camino.push_back(iFuente);
    int caminopos = 0;
    bool found = false;
    while(camino.size() > caminopos and !found){
        int curNodo = camino[caminopos];
        vector<Arista> aristas = grafo[curNodo].aristas;
        vector<Arista> aristasInvertidas = residual[curNodo].aristas;

        for(int x = 0; !found and x < aristas.size();x++){
                int xNodo = aristas[x].nodoId;
                int flujo = aristas[x].capacidad - aristas[x].flujo;
                if(flujo > 0 and flujos[xNodo] == -1){
                    if(xNodo != iSumidero){
                            direccion[xNodo] = 1;
                            padre[xNodo] = curNodo;
                            flujos[xNodo] = min(flujos[curNodo], flujo);
                            if(curNodo == iFuente) flujos[xNodo] = flujo;
                            camino.push_back(xNodo);
                    }else{
                        //int pSumidero = padre[iSumidero];
                        int curFlujo = min(flujos[curNodo], flujo);
                        direccion[iSumidero] = 1;
                        padre[iSumidero] = curNodo;
                        flujos[iSumidero] = curFlujo;
                        found = true;
                    }
                }
        }

        for(int x = 0; !found and x < aristasInvertidas.size();x++){
            int xNodo = aristasInvertidas[x].nodoId;
            int flujo = aristasInvertidas[x].flujo;
            if(flujo > 0 and flujos[xNodo] == -1){
                if(xNodo != iFuente){
                      /*  lugarEnPadre[xNodo] = x;*/
                        direccion[xNodo] = -1;
                        //cout << "CURRENTNODE[" << xNodo << "]" << endl;
                        padre[xNodo] = curNodo;
                        flujos[xNodo] = min(flujos[curNodo], flujo);
                        camino.push_back(xNodo);
                        /*-*/
                    }
                }
            }

        caminopos += 1;
    }

    CaminoCrecimiento respuesta;
    respuesta.flujoASacar = flujos[iSumidero];

    vector<int> caminoNodos;
    vector<int> caminoTargetNode;
    vector<int> caminoDireccion;

    int currentNodo = padre[iSumidero];

    caminoNodos.push_back(iSumidero);
    caminoDireccion.push_back(direccion[iSumidero]);
    while(currentNodo > -1){
        caminoNodos.push_back(currentNodo);
        caminoDireccion.push_back(direccion[currentNodo]);
        currentNodo = padre[currentNodo];
    }
    respuesta.nodos = caminoNodos;
    //respuesta.targetNodos = caminoTargetNode;
    respuesta.direccion = caminoDireccion;


    return respuesta;
}

//////////
////////// EdmondKarps
//////////

int EdmondKarps(vector<Nodo> grafo){
   // cout << grafo << endl;
    CaminoCrecimiento curCamino = buscarCaminoCrecimiento(grafo);
    int** posPadre = MatrizDePosicionesDePadres(grafo);
    while(curCamino.nodos.size() > 1){
       // cout<< "nodos" << endl;for(int i2 = 0; i2 < curCamino.nodos.size(); i2++){cout<< curCamino.nodos[i2] << "|";}cout<<endl;
       // cout<< "..." << endl;for(int i2 = 0; i2 < curCamino.nodos.size()-1; i2++){cout<< curCamino.direccion[i2] << "|";}cout<<endl;
        for(int i = 1; i < curCamino.nodos.size(); i++){
            int posicionArista;

            if( curCamino.direccion[i-1] > 0){
                posicionArista = posPadre[curCamino.nodos[i]][curCamino.nodos[i-1]];
                grafo[curCamino.nodos[i]].aristas[posicionArista].flujo += curCamino.flujoASacar;
            }

            else if( curCamino.direccion[i-1] < 0){
                posicionArista = posPadre[curCamino.nodos[i-1]][curCamino.nodos[i]];
                grafo[curCamino.nodos[i-1]].aristas[posicionArista].flujo -= curCamino.flujoASacar;
            }
        }

        //cout << grafo << endl;
        curCamino = buscarCaminoCrecimiento(grafo);
    }
    int answer = 0;
    for(int i = 0; i < grafo.size(); i ++){
        Nodo n = grafo[i];
        for(int x = 0; x< n.aristas.size();x++){
            Arista a = n.aristas[x];
            if(a.nodoId == grafo.size()-1){
                answer += a.flujo;
            }
        }
    }
    return answer;

}

//////////
////////// PRINTS (se ven bonitos n__n )
//////////

std::ostream &operator<<(std::ostream &os, Arista const &a) {
    return os << "["<< a.flujo << "/" << a.capacidad << "-}" << a.nodoId << "]" ;
}

std::ostream &operator<<(std::ostream &os, vector<Arista> const &a) {
    for(int x = 0; x < a.size(); x++){os << a[x];} return os;
}

std::ostream &operator<<(std::ostream &os, Nodo const &a) {
    return os << " '" << a.tipo << "'" << a.aristas;
}

std::ostream &operator<<(std::ostream &os, vector<Nodo> const &a) {
    if(a[a.size()-2].isShadow){for(int x = 0; x <= a.size()/2; x++){if(x == 0) os << x << ":"<< a[x] << endl;
    if(x == a.size()/2) os << a.size()-1 << ":"<< a[a.size()-1] << endl; if(x != 0 and x != a.size()/2) os <<
    x << ":"<< a[x] << " ---> " << shadowNode(a,x) << ":" << a[shadowNode(a,x)] << endl;}}
    else{for(int x = 0; x < a.size(); x++){os << x << ":"<< a[x] << endl;}}
    return os;
}

#endif
