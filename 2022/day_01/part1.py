if __name__ == '__main__' :
	f = open("input.txt", "r")
	l = []
	max_val = 0
	val = 0
	for x in f:
		if x != "\n" :
  			val = val + int(x)
		else : 
			l.append(val)
			val = 0
		if val > max_val :
			max_val = val

	l.sort(reverse = True)
	print(f"""Part 1: {l[0]}""")
	print(f"""Part 2: {l[0]+l[1]+l[2]}""")
