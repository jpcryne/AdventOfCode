def play_round(h1, h2) :
	if h1 == h2 :
		return h2 + 4
	elif h2 - h1 in [1, -2] :
		return h2 + 7
	else :
		return h2 + 1

def play_round2(h1, h2) :
	if h2 == 1 :
		return h1 + 4
	elif h2 == 2 :
		return 7 + (h1+1)%3
	elif h2 == 0 :
		return 1 + (h1-1)%3
	


if __name__ == "__main__" :
	l1 = []
	l2 = []
	f = open("input.txt", "r")
	for x in f :
		s = x.split()
		l1.append(play_round(ord(s[0]) - 65, ord(s[1]) - 88))
		l2.append(play_round2(ord(s[0]) - 65, ord(s[1]) - 88))
	print(sum(l1))
	print(sum(l2))
