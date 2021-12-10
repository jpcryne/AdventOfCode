
def read_file(filename) :
    l = []
    f = open(filename, "r")

    for x in f :
        l.append(int(x))

    f.close()

    return l

def solution_1(l) :
    count = 0
    for i in range(1,len(l)) :
        if l[i] > l[i-1] :
            count = count + 1
    return count

def rolling_sum(l) :
    new_list = []
    for i in range(2,len(l)) :
        new_list.append(l[i] + l[i-1] + l[i-2])
    return new_list

if __name__ == "__main__" :
    l = read_file("input.txt")
    sol_1 = solution_1(l)
    roll_sum = rolling_sum(l)
    sol_2 = solution_1(roll_sum)
    print(sol_2)
