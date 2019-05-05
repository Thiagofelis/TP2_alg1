import csv
import numpy as np
import Tkinter
import sys
import matplotlib.pyplot as plt

with open('dados.csv') as file:
	data = [row for row in csv.reader(file)]
	
num_points = int(sys.argv[1])
num_it = int(sys.argv[2])
scaler = int(sys.argv[3])


vec = np.zeros((num_points, num_it))

values = np.zeros(num_points)
stdev = np.zeros(num_points)

for i in range(num_points):
	for j in range(num_it):
		vec[i][j] = float(data[i][j]) * 1e-9
	values[i] = (vec[i]).mean()
	stdev[i] = (vec[i]).std()

	
t = scaler * np.arange(0, num_points, 1)

plt.errorbar(t, values, stdev, marker='.')
plt.plot(t, np.sqrt(values), '.')
#plt.plot(t, values, 'g.')
#plt.errorbar(yerr=stdev)
plt.show()