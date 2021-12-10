
def read_file(filename) :
    signals = []
    outputs = []
    f = open(filename, 'r')
    for x in f :
        tmp = x.split('|')
        signals.append(tmp[0].rstrip().split(" "))
        outputs.append(tmp[1].rstrip().lstrip().split(" "))
    f.close()

    return (signals, outputs)

def seven_display() :
    dct = {0:['a','b','c','e','f','g'],1:['c','f'],2:['a','c','d','e','g'],3:['a','c','d','f','g'],4:['b','c','d','f'],5:['a','b','d','f','g'],6:['a','b','d','e','f','g'],7:['a','c','f'],8:['a','b','c','d','e','f','g'],9:['a','b','c','d','f','g']}
    return dct

def solution_1(l) :
    sum = 0
    for o in l[1] :
        sum += len([s for s in o if len(s) in [2,3,4,7]])

    return sum

def string_split(str) :
    new_str = [c for c in str]
    new_str.sort()
    return new_str

def test(l) :
    set_signals = []
    set_outputs = []
    sols = []
    signals = l[0]
    outputs = l[1]
    for sigs in signals :
        set_signals.append([string_split(s) for s in sigs])
    for o in outputs :
        set_outputs.append([string_split(s) for s in o])

    for s in set_signals :
        sols.append(try_solve(s))
    # print(sols)
    # print(sols[0])
    # print([''.join(o) for o in set_outputs[0]])
    # print([''.join(o) for o in set_outputs[-1]])
    sum = 0
    for i in range(len(sols)) :
        tmp = [sols[i][''.join(o)] for o in set_outputs[i]]
        print(tmp)
        sum += 1000*tmp[0]+100*tmp[1]+10*tmp[2]+tmp[3]

    return sum

def try_solve(signals) :
    solved = {}
    unsolved = [s for s in signals]
    lens = [len(s) for s in unsolved]

    ## Solve the easy ones.
    for i in [(1,2),(4,4),(7,3),(8,7)] :
        ind = lens.index(i[1])
        solved[i[0]] = unsolved[ind]
        del unsolved[ind]
        del lens[ind]

    solve_helper(5,7,3,3,solved,unsolved)
    solve_helper(6,7,2,6,solved,unsolved)
    solve_helper(6,4,4,9,solved,unsolved)
    solve_helper(5,4,3,5,solved,unsolved)
    solve_helper(5,4,2,2,solved,unsolved)
    solved[0] = unsolved[0]
    # if len(unsolved[0]) == 6 :
    #     solved[0] = unsolved[0]
    #     solved[2] = unsolved[1]
    # else :
    #     solved[0] = unsolved[1]
    #     solved[2] = unsolved[0]

    dct = {}
    for i in range(10) :
        dct[''.join(solved[i])] = i
    return dct

def solve_helper(check_len, compare_to, intersect_len, check_for, solved, unsolved) :
    for s in unsolved :
        if len(s) == check_len :
            if len(set(solved[compare_to]) & set(s)) == intersect_len :
                ind = unsolved.index(s)
                solved[check_for] = unsolved[ind]
                del unsolved[ind]
                break

if __name__ == "__main__" :

    l = read_file("input.txt")
    print(f"Part 1: {solution_1(l)}")
    print(test(l))
