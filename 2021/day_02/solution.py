
def read_file(filename) :
    l = []
    f = open(filename, "r")

    for x in f :
        l.append(x.split())

    f.close()

    return l

def solution_1(l) :
    dct = {}
    for x in l :
        dct[x[0]] = dct.get(x[0], 0) + int(x[1])
    return dct

def solution_2(l) :
    forward = 0
    aim = 0
    depth = 0

    for x in l :
        if x[0] == "forward" :
            forward = forward + int(x[1])
            depth = depth + int(x[1])*aim
        elif x[0] == "down" :
            aim = aim + int(x[1])
        else :
            aim = aim - int(x[1])

    return depth*forward


if __name__ == "__main__" :
    l = read_file("input.txt")
    sol_1 = solution_1(l)
    print(f"Part 1 Solution: {sol_1['forward']*(sol_1['down']-sol_1['up'])}")

    print(f"Part 2 Solution: {solution_2(l)}")
