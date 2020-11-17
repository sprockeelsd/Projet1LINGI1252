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
datanb = data["nb_coeur"].values
philos = np.array(data["temps_P"])
produc = np.array(data["temps_PC"])
reader = np.array(data["temps_RW"])

c = 0 #Nrun 5
for i in datanb:
    if i==datanb[0]:
        c+=1

freq = len(datanb)//c #Nthreads 1...8

matrix = np.empty((3,freq,c))
for i in range(c):
	for j in range(1,freq+1):
		index = i*freq+j-1
		matrix[0][j-1][i] = philos[index]
		matrix[1][j-1][i] = produc[index]
		matrix[2][j-1][i] = reader[index]

matrixStat = np.empty((3,freq,2))
for i in range(len(matrix)):
	for j in range(len(matrix[i])):
		stat = sc.describe(matrix[i][j])
		matrixStat[i][j][0] = stat.mean
		matrixStat[i][j][1] = np.sqrt(stat.variance)

y = np.empty((3,2,freq))
for i in range(len(matrixStat)):
	y[i][0] = matrixStat[i][:,0]
	y[i][1] = matrixStat[i][:,1]

#print(matrix)
#print(matrixStat)
#print(y)

plt.figure(figsize=(18, 6))

x = np.linspace(1,freq,freq)

plt.subplot(231)
plt.title("Philosophers")
plt.xlabel("N° of threads")
plt.ylabel("time [s]")
plt.plot(x,y[0][0])
plt.plot(x,y[0][1])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.legend(["Mean","Std. Dev"])
plt.subplot(232)
plt.title("Producer/Consumer")
plt.xlabel("N° of threads")
plt.ylabel("time [s]")
plt.plot(x,y[1][0])
plt.plot(x,y[1][1])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.legend(["Mean","Std. Dev"])
plt.subplot(233)
plt.title("Reader/Writer")
plt.xlabel("N° of threads")
plt.ylabel("time [s]")
plt.plot(x,y[2][0])
plt.plot(x,y[2][1])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.legend(["Mean","Std. Dev"])
plt.subplot(234)
plt.title("Philosophers")
plt.xlabel("N° of threads")
plt.ylabel("time [s]")
plt.boxplot(matrix[0])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.subplot(235)
plt.title("Producer/Consumer")
plt.xlabel("N° of threads")
plt.ylabel("time [s]")
plt.boxplot(matrix[1])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.subplot(236)
plt.title("Reader/Writer")
plt.xlabel("N° of threads")
plt.ylabel("time [s]")
plt.boxplot(matrix[2])
plt.ylim(ymin=0)
plt.xlim(xmin=0)
plt.show()
