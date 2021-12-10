
def read_file(filename) :
    l = []
    f = open(filename, "r")

    for x in f :
        l.append(x.replace('\n',''))

    f.close()

    return l

def solution_1(l) :
    gamma = [0]*len(l[0])
    for x in l :
        for i in range(len(x)) :
            gamma[i] = gamma[i] + int(x[i])

    gamma = [int(d > len(l)/2) for d in gamma]
    epsilon = [1-d for d in gamma]

    return binary_to_int(gamma)*binary_to_int(epsilon)

def most_common_bit(l, stem, least = False) :
    if len(l) == 1 :
        return f"{stem}{l[0]}"
    bit = 0
    for x in l :
        bit += int(x[0])
    bit = int(bit >= len(l)/2)
    if least :
        bit = 1-bit
    return most_common_bit([x[1:] for x in l if x[0] == str(bit)], f"{stem}{bit}", least)

def solution_2(l) :
    ogr = most_common_bit(l, '')
    print(ogr)
    csr = most_common_bit(l, '', least = True)
    return binary_to_int([int(c) for c in csr])*binary_to_int([int(c) for c in ogr])


def binary_to_int(b) :
    b.reverse()
    sum = 0
    for i in range(len(b)) :
        sum += b[i]*(2**i)
    return sum

if __name__ == "__main__" :
    l = read_file("input.txt")
    sol_1 = solution_1(l)
    print(sol_1)
    sol_2 = solution_2(l)
    print(sol_2)
