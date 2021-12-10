import statistics

def read_file(filename) :
    f = open(filename, 'r')

    for x in f :
        l = x.split(',')
        l = [int(n.replace('\n','')) for n in l]
    f.close()

    return l

def solution_1(l) :
    mdn = statistics.median(l)
    return sum([abs(n-mdn) for n in l])

def cost(l, x) :
    return sum([(abs(n-x)*(abs(n-x)+1)/2) for n in l])

def solution_2(l) :
    min_pos = min(l)
    max_pos = max(l)

    costs = [cost(l,x) for x in range(min_pos, max_pos+1)]

    return min(costs)

if __name__ == "__main__" :
    l = read_file("input.txt")
    print(l)
    print(f"Part 1: {solution_1(l)}")
    print(f"Part 2: {solution_2(l)}")
