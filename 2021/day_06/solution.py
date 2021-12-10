
def read_file(filename) :
    l = []
    f = open(filename, 'r')

    for x in f :
        l = x.split(',')
        l = [int(i.rstrip()) for i in l]

    f.close()

    return l

def simulate_lanternfish(lfs, max_days=80, max_time = 8) :
    dct = {i:0 for i in range(0,max_time+1)}
    for lf in lfs :
        dct[lf] = dct.get(lf) + 1
    day = 0
    while day < max_days :
        new_dct = {i:dct[i+1] for i in [0,1,2,3,4,5]}
        new_dct[6] = dct[0]+dct[7]
        new_dct[7] = dct[8]
        new_dct[8] = dct[0]
        dct = new_dct
        day += 1

    return sum(dct.values())



if __name__ == "__main__" :
    l = read_file("input.txt")
    print(f"Part 1: {simulate_lanternfish(l, max_days=80)}")
    print(f"Part 2: {simulate_lanternfish(l, max_days = 256)}")
