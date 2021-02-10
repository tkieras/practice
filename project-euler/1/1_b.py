def arithmetic_series(n, a1, an):
	return n*(a1 + an) / 2

def sum_series_x(x, base):
	n = (x-1) // base
	a1 = base
	an = n * base
	return arithmetic_series(n, a1, an)

def sum_series_x_many(x, bases):
	result = 0
	for b in bases:
		result += sum_series_x(x, b)

	result -= sum_series_x(x, bases[0] * bases[1])

	return result

print(sum_series_x_many(1000, [3,5]))

