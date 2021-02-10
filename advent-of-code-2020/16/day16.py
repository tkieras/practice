
from collections import defaultdict

def parse_file(filepath):
    notes = {}
    my_ticket = None
    nearby_tickets = []

    with open(filepath) as infile:
        data = infile.read()

    data = data.split("\n\n")
    assert(len(data) == 3)
    
    notes_r, my_ticket_r, nearby_tickets_r = data

    notes_r = notes_r.strip().split("\n")

    for n in notes_r:
        n_parts = n.strip().split(":")
        n_key = n_parts[0].strip()
        n_vals = []
        for n_val in n_parts[1].split("or"):
            n_val_range = n_val.strip().split("-")
            n_vals.append((int(n_val_range[0]), int(n_val_range[1])))

        notes[n_key] = n_vals

    my_ticket_r = my_ticket_r.split("\n")[1].strip()
    my_ticket = tuple(int(v) for v in my_ticket_r.split(","))


    nearby_tickets_r = nearby_tickets_r.split("\n")[1:]

    for n in nearby_tickets_r:
        n = n.strip()
        if len(n) == 0:
            break
        nearby_tickets.append(tuple(int(v) for v in n.split(",")))

    return notes, my_ticket, nearby_tickets

def make_valid_map(notes):
    valids = {}
    
    for valid_ranges in notes.values():
        for r in valid_ranges:
            for i in range(r[0], r[1]+1):
                valids[i] = True
    
    return valids


def is_valid(num, rules):
    rule_states = []

    for r in rules:
        if num < r[0] or num > r[1]:
            rule_states.append(False)
        else:
            rule_states.append(True)

    return any(rule_states)
    

notes, my_ticket, nearby_tickets = parse_file("input.txt")


valid_map = make_valid_map(notes)

valid_tickets = []
error_rate = 0

for t in nearby_tickets:
    ticket_valid = True
    for v in t:
        if not valid_map.get(v, False):
            error_rate += v
            ticket_valid = False

    if ticket_valid:
        valid_tickets.append(t)


possible_map = defaultdict(list)


for i in range(len(notes)):
    for name in notes:
        is_possible = True
        for j in range(len(valid_tickets)):
            if not is_valid(valid_tickets[j][i], notes[name]):
                is_possible = False
        if is_possible:
            possible_map[i].append(name)


eval_ordered_cols = sorted(possible_map.keys(), key=lambda k:len(possible_map[k]))


def solve(eval_ordered_cols, possible_map, result):
    if not eval_ordered_cols:
        return True
    
    col = eval_ordered_cols[0]

    adjusted_possibles = list(filter(lambda n: n not in result, possible_map[col]))

    success = True

    if(len(adjusted_possibles) == 1):
        result[adjusted_possibles[0]] = col
        sucess = solve(eval_ordered_cols[1:], possible_map, result)
    else:
        for p in adjusted_possibles:
            result[p] = col
            tmp = solve(eval_ordered_cols[1:], possible_map, result)
            if not tmp:
                result.pop(p)
                success = False
            else:
                break

    return success

result = {}
print(solve(eval_ordered_cols, possible_map, result))
print(result)


submission_answer = 1
departure_field_counts = 0
for k in result:
    if(k.startswith("departure")):
        departure_field_counts += 1
        submission_answer *= my_ticket[result[k]]

print(departure_field_counts)
print(submission_answer)
