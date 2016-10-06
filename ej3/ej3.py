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
			self.adjacency[e[0]-1].append(e[1]-1)

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
		self.discovery_time = [N+1 for i in range(N)]
		self.low_value = [N+1 for i in range(N)]


N, M = map(int,input().split())
E = [ list(map(int,input().split())) for i in range(M) ]
G = UndirectedGraphWithArticulationPoints(N,M,E)
print(G.N)
print(G.M)
print(G.adjacency)

G.dfs(1)

Q = int(input())
queries = [ input().split() for i in range(Q) ]
