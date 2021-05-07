import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import csv

#read data
pZeroRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player0Average.csv', header=None, names=['agf'])
pZeroData = pZeroRaw.pop('agf')

pZero = np.array(pZeroData)
# for i in range(0, pZero.size):
#     print(pZeroData[i])

pOneRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player1Average.csv', header=None, names=['agf'])
pOneData = pOneRaw.pop('agf')

pOne = np.array(pOneData)
for i in range(0, pOne.size):
    print(pOne[i])

pTwoRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player2Average.csv', header=None, names=['agf'])
pTwoData = pTwoRaw.pop('agf')

pTwo = np.array(pTwoData)
# for i in range(0, pTwo.size):
#     print(pTwoData[i])

def plot_function(y, p0, p1, p2, stringX, stringY, stringT):
    plt.plot(y, p0, label="Trained Genetic Algorithm")
    plt.plot(y, p1, label="Random Player 1")
    plt.plot(y, p2, label="Random Player 2")
    plt.title(stringT)
    plt.legend()
    plt.xscale('linear')
    plt.xlabel(stringX)
    plt.ylabel(stringY)

plot_function(range(0, pZero.size), pZero, pOne, pTwo, "Round", "Owned Regions", "Owned Regions Per Player")
plt.show()