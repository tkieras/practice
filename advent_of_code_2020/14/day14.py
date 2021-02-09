def make_masks(m):
	set_bitmask = int("".join(map(lambda c: str(int(c == "1")), m)), 2)
	unset_bitmask = ~int("".join(map(lambda c: str(int(c == "0")), m)), 2)
	return set_bitmask,unset_bitmask, x

s = None
u = None
mem = {}

cmd = " & u | s"

with open("input.txt") as infile:
	for line in infile:
		parts = line.strip().split(" ")
		if parts[0] == "mask":
			s, u = make_masks(parts[2])
			
		else:
			exec(line.strip() + cmd)

print(sum(mem.values()))