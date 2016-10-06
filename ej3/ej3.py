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
			self.adjacency[e[1]-1].append(e[0]-1)

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
		self.parent = [None for i in range(N)]
		self.ap = [False for i in range(N)]
		self.time = 0

	def dfs_ap(self,v):
		self.visited[v] = True
		self.low_value[v] = self.discovery_time[v] = self.time = self.time+1
		children = 0
		for w in self.adjacency[v]:
			if not self.visited[w]: # forward edge
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
			# if node is visited, update low value of v...
			elif self.parent[v] != w: # forward edge
				debug("Actualizando low_value para",v)
				self.low_value[v] = min(self.low_value[v], self.discovery_time[w])

N, M = map(int,input().split())
E = [ list(map(int,input().split())) for i in range(M) ]
G = UndirectedGraphWithArticulationPoints(N,M,E)
debug(G.N)
debug(G.M)
debug(G.adjacency)

G.dfs_ap(0)
print("discovery_time =", G.discovery_time)
print("low_value =", G.low_value)
print("parent =", G.parent)
print("ap =", G.ap)

Q = int(input())
queries = [ input().split() for i in range(Q) ]
