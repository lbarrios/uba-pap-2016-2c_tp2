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

class GraphWithDFS(UndirectedGraph):
	"""A class representing a graph with DFS"""
	def __init__(self, N, M, E):
		super(GraphWithDFS,self).__init__(N,M,E)
		self.visited = [False for i in range(N)]

	def dfs(self,v):
		self.visited[v] = True
		debug("\nentering ",v)
		debug("adjacency: ",self.adjacency[v])
		for w in self.adjacency[v]:
			debug("checking",w)
			if not self.visited[w]:
				debug("node",w,"is not visited")
				self.dfs(w)
			else:
				debug("node",w,"is visited")
		debug("RETURNING",v)
		return

N, M = map(int,input().split())
E = [ list(map(int,input().split())) for i in range(M) ]
G = GraphWithDFS(N,M,E)
print(G.N)
print(G.M)
print(G.adjacency)

G.dfs(1)

Q = int(input())
queries = [ input().split() for i in range(Q) ]
