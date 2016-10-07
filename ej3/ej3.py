#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from debugging import debug
from sys import setrecursionlimit
setrecursionlimit(100000)

class UndirectedGraph:
	"""A class representing a graph"""
	def __init__(self, N, M, E):
		self.N, self.M = N, M
		self.adjacency = [list() for i in range(N)]
		for e in E:
			self.adjacency[e[0]].append(e[1])
			self.adjacency[e[1]].append(e[0])

	def addEdge(self,v, w):
		self.adjacency[v].append(w)

class UndirectedGraphWithDFS(UndirectedGraph):
	"""A class representing a graph with DFS"""
	def __init__(self, N, M, E):
		super(UndirectedGraphWithDFS,self).__init__(N,M,E)
		self.visited = [False for i in range(N)]

	def dfs(self,v):
		self.visited[v] = True
		for w in self.adjacency[v]:
			if not self.visited[w]:
				self.dfs(w)

class UndirectedGraphWithArticulationPoints(UndirectedGraphWithDFS):
	"""A class representing a graph with Articulation Points"""
	def __init__(self, N, M, E):
		super(UndirectedGraphWithArticulationPoints,self).__init__(N,M,E)
		self.discovery_time = [0 for i in range(N)]
		self.low_value = [0 for i in range(N)]
		self.cycle_component = [i for i in range(N)]
		self.parent = [None for i in range(N)]
		self.ap = [False for i in range(N)]
		self.time = 0

	def dfs_A(self, v_current, w_end):
		self.visited = [False for i in range(N)]
		total_bridges = 0
		def _dfs_A(v_current, w_end, bridges):
			nonlocal total_bridges
			debug("visiting",v_current+1,"/",w_end+1,"with bridges",bridges)
			if v_current == w_end:
				total_bridges = bridges
			self.visited[v_current] = True
			for w in self.adjacency[v_current]:
				if not self.visited[w]:
					if self.cycle_component[v_current] != self.cycle_component[w]:
						debug(v_current+1,"and",w+1,"are in different cycles, adding one bridge",bridges+1)
						_dfs_A(w, w_end, bridges+1)
					else:
						_dfs_A(w, w_end, bridges)
		_dfs_A(v_current,w_end, 0)
		print(total_bridges)


	def dfs_ap(self,v):
		self.visited[v] = True
		self.low_value[v] = self.discovery_time[v] = self.time = self.time+1
		children = 0
		for w in self.adjacency[v]:
			if not self.visited[w]: # tree edge
				children += 1
				self.parent[w] = v
				self.dfs_ap(w)
				# check if v is AP
				if self.parent[v] == None:
					# v is root, check if has two or more children
					if children > 1:
						self.ap[v] = True
						debug(v,"es punto de articulacion")
				else:
					# v is not root, check if low value of one of its child
					# is more than discovery value of v
					if self.low_value[w] >= self.discovery_time[v]:
						self.ap[v] = True
						debug(v,"es punto de articulacion")
				# check if the subtree rooted with w
				# has connection to one of the ancestors of v
				self.low_value[v] = min(self.low_value[v], self.low_value[w])
				self.cycle_component[v] = min(self.cycle_component[v], self.cycle_component[w])
			# if node is visited, update low value of v...
			elif self.parent[v] != w:
				debug("Actualizando low_value para",v)
				self.low_value[v] = min(self.low_value[v], self.discovery_time[w])
				self.cycle_component[v] = min(self.cycle_component[v], self.cycle_component[w])

# input parsing
# O(N+M)
N, M = map(int,input().split())
E = [ list(map(lambda x: x-1,map(int,input().split()))) for i in range(M) ]
G = UndirectedGraphWithArticulationPoints(N,M,E)

# run dfs+ap on G
# O(N+M)
G.dfs_ap(0)
# second run to find cycles components
# O(N+M)
G.visited = [False for i in range(N)]
G.dfs_ap(0)

debug("discovery_time =", G.discovery_time)
debug("low_value =", G.low_value)
debug("cycle_component =", G.cycle_component)
debug("parent =", G.parent)
debug("ap =", G.ap)

B = [0 for i in range(M)] # O(M)
Caux = [0 for i in range(N)] # O(M)
C = [0 for i in range(N)] # O(M)

# pre-calculation of B, O(M)
for k,e in enumerate(E):
	if G.cycle_component[e[0]] != G.cycle_component[e[1]]:
		# if i remove e, then there is no way to go from e[0] to e[1]
		B[k] = 1

# pre-calculation of..
# Caux, O(N)
for v in G.cycle_component:
	Caux[v] += 1
# C, O(N), for every node, assign on C the size of the cycle_component minus one
#
for v in range(N):
	C[v] = Caux[G.cycle_component[v]] - 1

Q = int(input())
queries = [ input().split() for i in range(Q) ]

for query in queries:
	if query[0] == "A": # O(Qa)
		v1 = int(query[1])-1
		w1 = int(query[2])-1
		G.dfs_A(v1,w1)
		#for e in E: # O(M)
	elif query[0] == "B": # O(Qb)
		print(B[int(query[1])-1]) # O(1)
	elif query[0] == "C": # O(Qc)
		print(C[int(query[1])-1]) # O(1)
