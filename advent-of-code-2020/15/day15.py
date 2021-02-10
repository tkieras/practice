start = [2,20,0,4,1,17]
#start = [0,3,6]
mem = {}

max_it = 30000000
last = None

for it in range(1, max_it+1):

	if it < len(start)+1:
		speak = start[it-1]
	else:
		speak = next_num
	
	if speak in mem:
		next_num = it - mem[speak]
	else:
		next_num = 0

	last = (it, speak)

	mem[speak] = it
	if(it % 1000000 == 0):
		print(it)

print(last)