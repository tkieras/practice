import re

def read_file(path):
	with open(path) as infile:
		data = infile.read()
	return data


def create_passport_dicts(data):
	passport_dicts = []
	for entry in data.split("\n\n"):
		entry = re.sub("\n", " ", entry).strip()
		textfields = entry.split(" ")

		if len(entry) == 0:
			continue

		passport_dict = {}
		for tf in textfields:
			if len(tf) == 0:
				continue
			key, value = tf.split(":")
			passport_dict[key.strip()] = value.strip()

		passport_dicts.append(passport_dict)
	
	return passport_dicts


def hgt_validate(s):
	if re.match(r'^\d{2}in$', s) and \
		int(s[:-2]) <= 76 and int(s[:-2]) >= 59:
			return True
	elif re.match(r'^\d{3}cm$', s) and \
		int(s[:-2]) <= 193 and int(s[:-2]) >= 150:
			return True

	return False

validation_rules = {
		"pid" : [lambda s: re.match(r'^\d{9}$', s)],
		"eyr" : [lambda s: re.match(r'^\d{4}$', s), 
				lambda s: int(s) <= 2030 and int(s) >= 2020],
		"byr" : [lambda s: re.match(r'^\d{4}$', s), 
				lambda s: int(s) <= 2002 and int(s) >= 1920],
		"iyr" : [lambda s: re.match(r'^\d{4}$', s), 
				lambda s: int(s) <= 2020 and int(s) >= 2010],
		"ecl" : [lambda s: s in {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}],
		"hcl" : [lambda s: re.match(r'^#[0-9a-f]{6}$', s)],
		"hgt" : [hgt_validate]
		}


def validate_passport_dicts(passport_dicts):
	count_valid = 0

	required = set(("pid", "eyr", "byr", "iyr", "ecl", "hgt", "hcl"))
	
	for idx, passport in enumerate(passport_dicts):
		
		valid = True

		for key in required:
			valid = valid & (key in passport)
			if not valid:
				continue
			for rule in validation_rules[key]:
				valid = valid & bool(rule(passport.get(key)))
		
		count_valid += valid
		if not valid:
			print("invalid: {}".format(idx))
			print(passport)
			
	return count_valid

data = read_file("input.txt")

passport_dicts = create_passport_dicts(data)

print(validate_passport_dicts(passport_dicts))
print(len(passport_dicts))
