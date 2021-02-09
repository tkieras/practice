
def get_data(filepath):
    with open(filepath) as infile:
        t = int(next(infile))
        data = {}
        
        for idx, value in enumerate(next(infile).strip().split(",")):
            if value != 'x':
                v = int(value)
                data[v] = (v - idx) % v

    return t, data


def solve_congruence(data):
   # https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Search_by_sieving    
    
    base = list(sorted(data.keys(), reverse=True))
    remainders = [data[b] for b in base]
  
    x = base[0]

    while(len(base) > 1):
        c = 0
        while(x % base[1] != remainders[1]):
            c += 1
            x = remainders[0] + (c*base[0])
        
        remainders[0] = x
        base[0] = base[0]*base[1]
        remainders.pop(1)
        base.pop(1)

    return remainders[0]


t, data = get_data("input.txt")

print(solve_congruence(data))
