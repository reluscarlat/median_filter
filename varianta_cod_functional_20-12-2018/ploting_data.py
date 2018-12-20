

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv('data.csv')

data = dataset.iloc[:,:].values

data_serial=dataset[data[:,1] == './serial.o'].reset_index() ## doar prima linie are tim de serial
data_omp=dataset[data[:,1] == "./openmp.o"].reset_index()
data_mpi=dataset[data[:,1] == "./mpi.o"].reset_index()
data_pthread=dataset[data[:,1] == "./pthread.o"].reset_index()
nr_linii=data_pthread.shape[0]-1
data_serial=data_serial.append([data_serial]*nr_linii).reset_index()


del data_serial['Framework']
del data_omp['Framework']
del data_mpi['Framework']
del data_pthread['Framework']
del data_serial['index']


data_omp['Time']=data_serial['Time']/data_omp['Time']
data_mpi['Time']=data_serial['Time']/data_mpi['Time']
data_pthread['Time']=data_serial['Time']/data_pthread['Time']
data_serial['Time']=data_serial['Time']/data_serial['Time']

import matplotlib.pyplot as plt
fig = plt.figure(figsize=(25, 10 ), dpi=80)
plt.ylabel('Scalare %')
plt.xlabel('Threadrui')
plt.xticks(data_omp['Threads'])
plt.yticks(np.arange(0, 4, 0.1))

plt.scatter(data_serial['Threads'], data_serial['Time'], label='serial')
plt.plot(data_omp['Threads'], data_omp['Time'], label="omp",color='red')
plt.plot(data_mpi['Threads'], data_mpi['Time'], label='mpi',color='green')
plt.plot(data_pthread['Threads'], data_pthread['Time'], label='pthread',color='orange')

plt.legend()
fig.savefig('grafic.png',dp=100)
plt.show()

