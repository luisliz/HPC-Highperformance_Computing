import matplotlib.pyplot as plt
import networkx as nx
import random
import sys 

def generateFile(n): 
    G = nx.fast_gnp_random_graph(n,0.1)

    for i in G.edges(data=True): 
        i[2]['weight'] = round(random.random()*100)

    matrix = nx.to_dict_of_dicts(G)
    
    res = []
    f = open("graph.txt", "w")
    for i in range(n): 
        f.write("\n")
        for j in range(n): 
            if i in matrix and j in matrix[i]: 
                f.write(str(matrix[i][j]['weight'])+', ')
            else: 
                f.write('99999, ')
    print("File written")
    f.close()

if __name__ == "__main__": 
    generateFile(int(sys.argv[1]))
