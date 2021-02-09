from pprint import pprint


def make_masks(m):
	set_bitmask = int("".join(map(lambda c: str(int(c == "1")), m)), 2)
	clear_bitmask = int("".join(map(lambda c: str(int(c == "X")), m)), 2)
	comb_idx = list(filter(lambda i: m[i] == "X", range(len(m))))
	

	return set_bitmask, clear_bitmask, get_masks(set_bitmask, comb_idx)

def get_combs(comb_idx, base):
	if(len(comb_idx) == 0):
		return []

	results = [base] + get_combs(comb_idx[1:], base)

	base = base | (1 << (35-comb_idx[0]))

	results += [base] + get_combs(comb_idx[1:], base)

	return results

def get_masks(s, comb_idx):
	return list(s | c for c in get_combs(comb_idx, 0))


mem = {}

with open("input.txt") as infile:
	for line in infile:
		line = line.strip()
		if not line:
			break
		
		parts = line.split(" ")
		
		if parts[0] == "mask":
			s, u, masks = make_masks(parts[2].strip())
		else:

			base_addr = int(parts[0][4:-1]) & ~u
			val = int(parts[-1])

			for m in masks:
				mem[base_addr | m] = val
				

print(sum(mem.values()))
