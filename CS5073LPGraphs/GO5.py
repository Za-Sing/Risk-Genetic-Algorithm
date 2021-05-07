import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import csv

#read data
pZeroRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player0Ave.csv', header=None, names=['agf'])
pZeroData = pZeroRaw.pop('agf')

pZero = np.array(pZeroData)
for i in range(0, pZero.size):
    print(pZero[i])



pOneRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player1Ave.csv', header=None, names=['agf'])
pOneData = pOneRaw.pop('agf')

pOne = np.array(pOneData)
# for i in range(0, pOne.size):
#     print(pOne[i])

pTwoRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player2Ave.csv', header=None, names=['agf'])
pTwoData = pTwoRaw.pop('agf')

pTwo = np.array(pTwoData)
# for i in range(0, pTwo.size):
#     print(pTwoData[i])

pThreeRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player3Ave.csv', header=None, names=['agf'])
pThreeData = pThreeRaw.pop('agf')

pThree = np.array(pThreeData)

pFourRaw = pd.read_csv(r'C:\Users\Jgonz\OneDrive\Desktop\Player4Ave.csv', header=None, names=['agf'])
pFourData = pFourRaw.pop('agf')

pFour = np.array(pFourData)

def plot_function(y, p0, p1, p2, p3, p4, stringX, stringY, stringT):
    plt.plot(y, p0, label="Trained Genetic Algorithm 1")
    plt.plot(y, p1, label="Trained Genetic Algorithm 2")
    plt.plot(y, p2, label="Trained Genetic Algorithm 3")
    plt.plot(y, p3, label="Trained Genetic Algorithm 4")
    plt.plot(y, p4, label="Trained Genetic Algorithm 5")
    plt.title(stringT)
    plt.legend()
    plt.xscale('linear')
    plt.xlabel(stringX)
    plt.ylabel(stringY)

plot_function(range(0, pZero.size), pZero, pOne, pTwo, pThree, pFour, "Round", "Owned Regions", "Owned Regions Per Player")
plt.show()