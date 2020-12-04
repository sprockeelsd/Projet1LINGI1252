#!/usr/bin/env python3

#python3 graphs.py
#sudo apt-get install python3-pip
#pip3 install matplotlib
#pip3 install scipy
#pip3 install pandas

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as sc

data = pd.read_csv("datas.csv", sep=None, engine='python')

x=[]
for i in data:
	x.append(i)

datanb = data[x[0]].values
philos = np.array(data[x[2]])
produc = np.array(data[x[3]])
reader = np.array(data[x[4]])

c = 0 #Nrun 5
for i in datanb:
    if i==datanb[0]:
        c+=1

freq = len(datanb)//c # nombre de threads utilisés...Nthreads = 1,2,3,4,5,6,7,8

"""
Matrix range les mesures présentes dans datas.csv de la maniere suivante:
-chaque ligne represente la perforance d'une expérience différente
-chaque colonne represente le nombre de threads utilisés pour l'expérience
-chaque entrée represente toutes les mesures faites pour la même expérience et les mêmes paramètres
"""
matrix = np.empty((3,freq,c))
for i in range(c):
	for j in range(1,freq+1):
		index = i*freq+j-1
		matrix[0][j-1][i] = philos[index]
		matrix[1][j-1][i] = produc[index]
		matrix[2][j-1][i] = reader[index]

"""
MatrixStat range les mesures présentes dans datas.csv de la maniere suivante:
-chaque ligne represente la perforance d'une expérience différente
-chaque colonne represente le nombre de threads utilisés pour l'expérience
-chaque entrée represente la moyenne et l'écart type de toutes les mesures faites pour la même expérience et les mêmes paramètres
"""
matrixStat = np.empty((3,freq,2))
for i in range(len(matrix)):
	for j in range(len(matrix[i])):
		stat = sc.describe(matrix[i][j])
		matrixStat[i][j][0] = stat.mean
		matrixStat[i][j][1] = np.sqrt(stat.variance)

"""
Y range les mesures présentes dans datas.csv de la maniere suivante:
les dimensions 2 et 3 ont été échangées pour pouvoir faire le graphe
"""
y = np.empty((3,2,freq))
for i in range(len(matrixStat)):
	y[i][0] = matrixStat[i][:,0]
	y[i][1] = matrixStat[i][:,1]

#print(matrix)
#print(matrixStat)
#print(y)

z = np.linspace(1,freq,freq)
if(x[0]=='Vmin'): z = np.linspace(1, 951, 20)

plt.figure(figsize=(50,50))
plt.subplot(221)
plt.title(x[2])
plt.xlabel(x[0])
plt.ylabel("time [s]")
plt.plot(z,y[0][0])
plt.plot(z,y[0][1])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.legend(["Mean","Std. Dev"])
plt.subplot(222)
plt.title(x[3])
plt.xlabel(x[0])
plt.ylabel("time [s]")
plt.plot(z,y[1][0])
plt.plot(z,y[1][1])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.legend(["Mean","Std. Dev"])
plt.subplot(223)
plt.title(x[4])
plt.xlabel(x[0])
plt.ylabel("time [s]")
plt.plot(z,y[2][0])
plt.plot(z,y[2][1])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.legend(["Mean","Std. Dev"])
plt.subplot(224)
plt.title("Comparaison")
plt.xlabel(x[0])
plt.ylabel("time [s]")
plt.plot(z,y[0][0])
plt.plot(z,y[1][0])
plt.plot(z,y[2][0])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.legend(x[2:])
plt.show()
