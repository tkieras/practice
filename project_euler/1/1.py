import numpy as np 

max_candidate = 1000
bases = [3]


candidates = np.zeros((max_candidate,))

n = 1
x = bases[0] * n

for base in bases:
	n = 1
	x = base

	while(x < max_candidate):
		candidates[x] = 1
		n += 1
		x = base * n


result = 0
count = 0
for i in range(max_candidate):
	if candidates[i] == 1:
		result += i
		count += 1


print(result)
print(count)
