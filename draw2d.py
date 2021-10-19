import matplotlib.pyplot as plt
import numpy as np
import csv

n=2

def draw(filename,param='',width=1):
    df = csv.reader(open(filename))
    x=[]
    for i in range(n):
        x.append([])
    for data in df:
        for i in range(n):
            x[i].append(data[i])
    for i in range(n):
        del x[i][0]
    for j in range(n):
        for i in range(len(x[0])):
            x[j][i]=float(x[j][i])
    plt.plot(x[0],x[1],param,linewidth=width)


def drawDiscretePoints(filename,width=1):
    df = csv.reader(open(filename))
    x=[]
    for i in range(n):
        x.append([])
    for data in df:
        for i in range(n):
            x[i].append(data[i])
    for i in range(n):
        del x[i][0]
    for j in range(n):
        for i in range(len(x[0])):
            x[j][i]=float(x[j][i])
    for i in range(len(x[0])):
        plt.text(x[0][i], x[1][i]+0.5, r'$P_'+str(i)+'$', fontsize=10)
    plt.plot(x[0],x[1],'o',linewidth=width)

 

draw('csv/controlpolygon.csv')
drawDiscretePoints('csv/controlpolygon.csv')

plt.show()

