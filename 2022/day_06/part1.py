def parse_signal() :
    f = open("input.txt", "r")
    return [x for x in f.readline() if x != "\n"]

if __name__ == "__main__" :
    signal = parse_signal()
    p1 = True
    for i in range(4, len(signal)+1) :
        s1 = set(signal[(i-4):i])
        if p1 and len(s1) == 4 :
            print(f"""Part 1: {i}""")
            p1 = False
        if i >= 14 :
            s2 = set(signal[(i-14):i])
            if len(s2) == 14 :
                print(f"""Part 2: {i}""")
                break
