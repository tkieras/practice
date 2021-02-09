
with open("input.txt") as infile:
    t = int(next(infile))
    bus_ids = list(map(lambda v: int(v), filter(lambda v: v != 'x', next(infile).split(","))))
    print(t)
    print(bus_ids)

min_id = None
min_wait = float('inf')

for i in bus_ids:
    wait = i - (t % i)
    if wait < min_wait:
        min_wait = wait
        min_id = i

print(min_id)
print(min_wait)
print(min_id * min_wait)


