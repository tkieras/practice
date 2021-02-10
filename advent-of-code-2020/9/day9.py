
def read_file(filepath):
    with open(filepath) as infile:
        for line in infile:
            val = int(line)
            yield val  

def build_preamble(values, n):
    data = {}
    i = iter(values)
    for _ in range(n):
        data[next(i)] = True

    return data

def check_validity(values, data):

    for val in values:
        if(is_valid(val, data)):
            data.pop(next(iter(data)))
            data[val] = True
        else:
            return val

def is_valid(val, data):
    
    for i in data:
        c = val - i
        if c in data:
            return True

    return False


def make_subarray_sums(int_list):
    subsums = [int_list[0]] 

    for i in range(1, len(int_list)):
        subsums.append(subsums[i-1] + int_list[i])

    return subsums

def find_subarray_sum(subsums, target):
    d = {}
    for idx, val in enumerate(subsums):
        assert(val not in d)
        d[val] = idx
    
    for val in d:
        complement = val - target
        if complement in d:
            return d[complement], d[val]+1

    return None, None 

def find_min_max(int_list, start, end):
    max_val = 0
    min_val = float('inf')
    #print("start: {}, end: {}".format(start, end))
    for idx in range(start, end):
        max_val = max(max_val, int_list[idx])
        min_val = min(min_val, int_list[idx])

    return max_val, min_val

int_stream = read_file("input.txt")
data = build_preamble(int_stream, 25)

invalid = check_validity(int_stream, data)
print("invalid number is: {}".format(invalid))

int_list = list(read_file("input.txt"))
subarray_sums = make_subarray_sums(int_list)

start, end = find_subarray_sum(subarray_sums, invalid)

print("contiguous array with sum of {} is ({},{})".format(invalid, start, end))
max_val, min_val = find_min_max(int_list, start, end)

print("min: {}, max: {}, sum: {}".format(min_val, max_val, min_val + max_val))

