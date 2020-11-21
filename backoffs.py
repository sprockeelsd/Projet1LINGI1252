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

vmin = data[x[0]].values
X1 = np.array(data[x[1]])
X2 = np.array(data[x[2]])
X3 = np.array(data[x[3]])
X4 = np.array(data[x[4]])
X5 = np.array(data[x[5]])
X6 = np.array(data[x[6]])
X7 = np.array(data[x[7]])

plt.figure(figsize=(200, 120))#figsize=(20, 12)

plt.title("Backoff")
plt.xlabel(x[0])
plt.ylabel("time [s]")
plt.plot(vmin,X1)
plt.plot(vmin,X2)
plt.plot(vmin,X3)
plt.plot(vmin,X4)
plt.plot(vmin,X5)
plt.plot(vmin,X6)
plt.plot(vmin,X7)
plt.legend(["X1","X2","X3","X4","X5","X6","X7"])
plt.show()
