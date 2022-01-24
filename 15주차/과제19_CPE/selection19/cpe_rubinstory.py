import sys
import re

with open(sys.stdin.fileno(), encoding='utf8') as std_input:
	N = int(std_input.readline())
	eng_reg = re.compile(r'[a-zA-Z]')

	set_arr = []
	for _ in range(N):
		string = std_input.readline()
		new_string = ''.join(c for c in string if (not c.isdigit()) and ((not eng_reg.match(c)) and c.isalpha()))
		temp = set()
		for i in range(len(new_string) - 1):
			temp.add(new_string[i:i+2])
		set_arr.append(temp)

	max_val = -100.0
	max_i = 0
	max_j = 1
	for i in range(N):
		for j in range(i + 1, N):
			if len(set_arr[i] | set_arr[j]) == 0: continue
			else: similarity = (len(set_arr[i] & set_arr[j]) / len(set_arr[i] | set_arr[j]))

			if similarity > max_val:
				max_i = i
				max_j = j
				max_val = similarity
	print(max_i + 1, max_j + 1)