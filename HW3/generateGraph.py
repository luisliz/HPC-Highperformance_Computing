# Author: Aric Hagberg (hagberg@lanl.gov)
import matplotlib.pyplot as plt
import networkx as nx
import random
import math 

n = 100
randW = []
for i in range(n): 
    randW.append(random.random())

G = nx.fast_gnp_random_graph(n,0.1)

nx.draw(G)

for i in G.edges(data=True): 
    i[2]['weight'] = random.random()
    print(i)
