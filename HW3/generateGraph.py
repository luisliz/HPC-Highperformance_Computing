import matplotlib.pyplot as plt
import networkx as nx
import random
import math 
import numpy as np

n = 20

G = nx.fast_gnp_random_graph(n*n,0.1)

for i in G.edges(data=True): 
    i[2]['weight'] = round(random.random()*100)
    #print(i)

matrix = nx.to_dict_of_dicts(G)

res = []
f = open("graph.txt", "w")
for i in range(n): 
    f.write("\n")
    print("\n")
    for j in range(n): 
        if i in matrix and j in matrix[i]: 
            f.write(str(matrix[i][j]['weight'])+', ')
            #res[i].append(matrix[i][j]['weight'])
            print(matrix[i][j]['weight'], end="\t")
        else: 
            f.write('99999, ')
            print("INF", end="\t") 
f.close()

