import csv
import numpy as np
import Tkinter
import sys
import matplotlib.pyplot as plt
from scipy import stats

with open('dados.csv') as file:
	data = [row for row in csv.reader(file)]

with open('saidas.csv') as file:
	saida = [row for row in csv.reader(file)]
	
num_points = int(sys.argv[1])
num_it = int(sys.argv[2])
scaler = int(sys.argv[3])

out = open('out.csv', 'w')

vec = np.zeros((num_points, num_it))
vec2 = np.zeros((num_points, num_it))

values = np.zeros(num_points)
stdev = np.zeros(num_points)

values_saida = np.zeros(num_points)
stdev_saida = np.zeros(num_points)

for i in range(num_points):
	for j in range(num_it):
		vec[i][j] = float(data[i][j]) * 1e-9
		vec2[i][j] = int(saida[i][j])
	values[i] = (vec[i]).mean()
	stdev[i] = (vec[i]).std()
	values_saida[i] = (vec2[i]).mean()
	stdev_saida[i] = (vec2[i]).std()
	out.write(str(values[i]) + ',' + str(stdev[i]) + ',' + str(100 * stdev[i] / values[i]) + '\n')

	
t = scaler * np.arange(0, num_points, 1)

slope, intercept, r_value, p_value, std_err = stats.linregress(t,np.sqrt(values))
line = slope*t+intercept

t = t + scaler

plt.plot(t, values, '.', label='Tempo real')

plt.plot(t, np.sqrt(values), '.', label='Tempo linearizado (raiz quadrada dos valores)')
plt.plot(t, line, label='Ajuste linear do tempo linearizado')

plt.legend()
plt.title("Media x Numero de vertices")
plt.xlabel("Numero de vertices")
plt.ylabel("Tempo de execucao [s]")
plt.grid()
plt.savefig('valores.pdf')
plt.clf()

plt.plot(t, 100 * stdev / values, '.')
plt.title("Desvio padrao percentual x Numero de vertices")
plt.xlabel("Numero de vertices")
plt.ylabel("Desvio padrao percentual [%]")
plt.grid()
plt.savefig('stdev.pdf')
plt.clf()

plt.plot(t, values_saida, '.')
plt.title("Media da saida x Numero de vertices")
plt.xlabel("Numero de vertices")
plt.ylabel("Media da saida")
plt.grid()
plt.savefig('valores_saida.pdf')
plt.clf()



plt.plot(t, 100 * stdev_saida / values_saida, '.')
plt.title("Desvio padrao percentual da saida x Numero de vertices")
plt.xlabel("Numero de vertices")
plt.ylabel("Desvio padrao percentual [%]")
plt.grid()
plt.savefig('stdev_saida.pdf')
plt.clf()
