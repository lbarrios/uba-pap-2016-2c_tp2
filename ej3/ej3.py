#
#
############################################## CLASSES
#
#

class Arista:
	def __init__(self, pos1, pos2):
		assert(pos1 != pos2)
		assert(pos1 >= 0)
		assert(pos2 >= 0)
		self.source = pos1
		self.target = pos2
		self.bridge = False
	def other(self, pos):
		if pos == self.source:
			return self.target
		if pos == self.target:
			return self.source
		assert(False)
	def __eq__(self,other):
		same_order = self.source == other.source and self.target == other.target
		diff_order = self.source == other.target and self.target == other.source
		return same_order or diff_order
	def __repr__(self):
	 	return "[" + str(self.source + 1) + "]->[" + str(self.target + 1) + "]"	 	
	def __str__(self):
	 	return "[" + str(self.source + 1) + "]->[" + str(self.target + 1) + "]"	 	

class Vertice:
	def __init__(self):
		self.idAristas = []
		self.depth = -1
		self.low = 0
		self.componente = -1
	def __repr__(self):
	 	return "[]{" + str(self.idAristas) + "}"	 	
	def __str__(self):
		return "[]{" + str(self.idAristas) + "}"



#
#
############################################## INPUT PARSE
#
#

def conseguirInput():
	global N,M
	global caminos,esquinas
	N,M =  map(lambda x: int(x) ,raw_input().split(" "))
	esquinas = []
	for x in range(0,N):
		esquinas.append(Vertice())
	caminos = []
	for x in range(0,M):
		C1,C2 = map(lambda x: int(x) - 1, raw_input().split(" "))
		caminos.append(Arista(C1,C2))
		esquinas[C1].idAristas.append(x)
		esquinas[C2].idAristas.append(x)


def procesarInput():
	Q = int(raw_input())

	for x in range(0,Q):
		inp =raw_input().split(" ")
		question = inp[0]
		if question == "A":
			e1 = int(inp[1]) - 1
			e2 = int(inp[2]) - 1
			print preguntaA(e1,e2)
		if question == "B":
			c1 = int(inp[1]) - 1
			print preguntaB(c1)
		if question == "C":
			e1 = int(inp[1]) - 1
			print preguntaC(e1)



#
#
############################################## FUNCIONES
#
#

def descubrirPuentes():
	raiz = 0
	dfsBridgeDiscoverer(raiz,0,raiz)


def dfsBridgeDiscoverer(v,d,padre):
	global esquinas, caminos

	e1 = esquinas[v]
	e1.depth = d
	e1.low = d

	for x in [x for x in e1.idAristas if caminos[x].other(v) != padre]:
		
		c1 = caminos[x]
		w = c1.other(v)
		e2 = esquinas[w]

		if e2.depth == -1:
			e1.low = min(e1.low,dfsBridgeDiscoverer(w,d+1,v))
			if e2.low >= e2.depth:
				c1.bridge = True
		else:
			e1.low = min(e1.low,e2.depth)

	return e1.low



def descubrirComponentes():
	global esquinas,caminos,componentesSizes
	
	pilaComponenteActual = []
	pilaComponentesFuturos = []
	verticesVistos = []
	componentesSizes = []

	for x in esquinas:
		verticesVistos.append(False)

	currentComponente = -1
	pilaComponentesFuturos.append(0)	
	verticesVistos[0] = True

	while pilaComponenteActual != [] or pilaComponentesFuturos != []:
		if pilaComponenteActual == []:
			
			tope = pilaComponentesFuturos.pop()

			pilaComponenteActual.append(tope)

			currentComponente += 1
			esquinas[tope].componente = currentComponente
			componentesSizes.append(1)

		else:
			tope = pilaComponenteActual.pop()

			for x in esquinas[tope].idAristas:
				y = caminos[x].other(tope)
				if not verticesVistos[y]:
					verticesVistos[y] = True
					if caminos[x].bridge:
						pilaComponentesFuturos.append(y)
					else:
						pilaComponenteActual.append(y)
						esquinas[y].componente = currentComponente
						componentesSizes[currentComponente] += 1


def calcularBridgeDistance(e1,e2):
	vistos = []
	for x in esquinas:
		vistos.append(False)

	t, d = dfsBridgeDistanceCalculator(e1,0,e2,vistos)
	return d

def dfsBridgeDistanceCalculator(v,d,t,vistos):
	global esquinas, caminos

	if v == t:
		return True, d

	e1 = esquinas[v]
	vistos[v] = True
	for x in [x for x in e1.idAristas if not vistos[caminos[x].other(v)]]:
		w = caminos[x].other(v)
		d2 = d+1 if caminos[x].bridge else d 
		found, d2 = dfsBridgeDistanceCalculator(w,d2,t,vistos)

		if found:
			return True, d2

	return False, 0

#
#
############################################## QUESTIONS
#
#

def preguntaA(e1, e2):
	return calcularBridgeDistance(e1,e2)

def preguntaB(c1):
	global caminos
	return int(caminos[c1].bridge)

def preguntaC(e1):
	global esquinas, componentesSizes
	return componentesSizes[esquinas[e1].componente] - 1


#
#
############################################## MAIN
#
#

conseguirInput()
descubrirPuentes()
descubrirComponentes()
procesarInput()
