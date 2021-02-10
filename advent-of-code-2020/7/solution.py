

def read_file(filepath):
	with open(filepath) as infile:
		for line in infile:
			yield line

def parse_line(line):
	top = line.split("contain")
	outer_words = top[0].split(" ")
	
	outer_string = " ".join(outer_words[:2])
	
	inner_strings = []

	if top[1].strip() == "no other bags.":
		inner_strings.append(None)
		return outer_string, inner_strings

	inner_parts = top[1].split(",")

	for inner_part in inner_parts:
		inner_words = inner_part.split(" ")
		inner_count = int(inner_words[1])
		inner_string = " ".join(inner_words[2:4])
		inner_strings.append((inner_string, inner_count))

	return outer_string, inner_strings


def make_successor_graph(filepath):

	graph = {}

	for line in read_file(filepath):
		outer_string, inner_strings = parse_line(line)
		#print("{} --> {}".format(outer_string, inner_strings))
		for inner in inner_strings:
			if inner is not None:
				graph[inner[0]] = graph.get(inner[0], []) + [outer_string]

	return graph


def make_predecessor_graph(filepath):

	graph = {}

	for line in read_file(filepath):
		outer_string, inner_strings = parse_line(line)
		#print("{} --> {}".format(outer_string, inner_strings))
		for inner in inner_strings:
			if inner is not None:
				graph[outer_string] = graph.get(outer_string, []) + [inner]

	return graph

from pprint import pprint

successor_graph = make_successor_graph("input.txt")
#pprint(successor_graph)
predecessor_graph = make_predecessor_graph("input.txt")
#pprint(predecessor_graph)

def count_successors(graph, node):

	queue = [node]
	visited = set()

	while(queue):
		current = queue.pop(0)
		visited.add(current)

		for successor in graph.get(current, []):
			if successor not in visited:
				queue.append(successor)

	return len(visited)-1

print(count_successors(successor_graph, "shiny gold"))

def count_weighted_predecessors(graph, node):

	if node not in graph:
		return 0

	count = 0
	for predecessor, weight in graph[node]:
		count += (weight * count_weighted_predecessors(graph, predecessor)) + weight

	return count

print(count_weighted_predecessors(predecessor_graph, "shiny gold"))