import numpy as np 

cap = 4000000

phi = (1 + np.sqrt(5)) / 2

fn = lambda n: np.round((phi**n) / np.sqrt(5))

# i = 0
# v = fn(i)
# result = 0
# while(v < cap):
# 	if v % 2 == 0:
# 		result += v
# 	i += 1
# 	v = fn(i)

# print(result)

vals = [2]
prev = 2


while(True):
	nxt = np.round(prev * (phi**3))
	if(nxt >= cap):
		break
	vals.append(nxt)
	prev = nxt

print(np.sum(vals))
