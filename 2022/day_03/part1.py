def get_value(c) :
    if c.islower() :
        return ord(c) - 96
    else :
        return ord(c) - 38 

def find_duplicate(l) :
    n = len(l)
    return list(set(l[:int(n/2)]) & set(l[int(n/2):]))[0]
        
def find_duplicate2(l) :
    return list(set(l[0]) & set(l[1]) & set(l[2]))[0]

if __name__ == "__main__" :
    f = open("input.txt", "r")
    l = f.read().split("\n")
    l = list(filter(lambda x: x != "", l))
    l1 = list(map(find_duplicate, l))
    print(f"""Part 1: {sum(list(map(get_value, l1)))}""")
    l2 = [l[i:i + 3] for i in range(0, len(l), 3)]
    l2 = list(map(find_duplicate2, l2))
    print(f"""Part 2: {sum(list(map(get_value, l2)))}""")
    
