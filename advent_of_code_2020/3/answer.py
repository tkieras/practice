import math

def is_tree(c):
	return c == "#"


def read_file(path):
	with open(path) as infile:
		return [list(map(is_tree, line.strip())) for line in infile]
		

def get_points(slope, n):
	x, y = 0, 0
	while (y < n):
		yield (x, y)
		x += slope[0]
		y += slope[1]

def evaluate_slope(grid, slope):
	m = len(grid[0])
	return sum(grid[y][x%m] for x, y in get_points(slope, len(grid)))
	

grid = read_file("input.txt")

slopes = [(1,1), (3,1), (5,1), (7,1), (1,2)]

#slopes = [(3,1)]
allResults = map(lambda slope : evaluate_slope(grid, slope), slopes)

result = math.prod(allResults)
print(result)