import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import csv

#read data
agfRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\aveGlobalFitnessPlacement.csv', header=None, names=['agf'])
agfData = agfRaw.pop('agf')

agf = np.array(agfData)
for i in range(0, agf.size):
    print(agfData[i])

def plot_function(x, y, stringX, stringY, stringT):
    plt.plot(x, y)
    plt.title(stringT)
    plt.xscale('linear')
    plt.xlabel(stringX)
    plt.ylabel(stringY)

plot_function(range(0, agf.size), agf, "Generation", "Fitness", "Average Global Placement Fitness")
plt.show()