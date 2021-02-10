row_map = {"F" : "0", "B" : "1"}
col_map = {"L" : "0", "R" : "1"}


def read_file(path):
	with open("input.txt") as infile:
		for line in infile:
			yield line.strip()

def parse_line(line):
	col = "".join(map(col_map.get, line[-3:]))
	row = "".join(map(row_map.get, line[:-3]))

	return row, col

def get_id(line):
	row_address, col_address = parse_line(line)
	return int(row_address, 2) * 8 + int(col_address, 2)


max_id = 0
min_id = float("inf")
ids = set()
for line in read_file("input.txt"):
	seat_id = get_id(line)
	ids.add(seat_id)
	max_id = max(max_id, seat_id)
	min_id = min(min_id, seat_id)
	

print("max: {}".format(max_id))
print("min: {}".format(min_id))
for i in range(min_id, max_id):
	if i not in ids and i-1 in ids and i+1 in ids:
		print("missing (neighbors present): {}".format(i))
