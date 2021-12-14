
def read_file(filename) :
    f =  open(filename, 'r')
    pair_dct = {}
    char_dct = {}
    input = True
    for x in f :
        if x == "\n":
            input = False
            continue
        if input :
            in_str = x.strip()
        else :
            tmp = x.strip().split(" -> ")
            pair_dct[tmp[0]] = [tmp[0][:1] + tmp[1], tmp[1] + tmp[0][1:]]
            char_dct[tmp[0]] = tmp[1]
    return (in_str, pair_dct, char_dct)

def solution_1(in_str, rules, char_dct, its = 10) :
    str_dct = {}
    for i in range(len(in_str)-1) :
        s = in_str[i:(i+2)]
        str_dct[s] = str_dct.get(s,0) + 1

    char_count = {}
    for c in in_str :
        char_count[c] = char_count.get(c,0) + 1

    new_dct = {}
    for i in range(its) :
        for s in str_dct :
            char_count[char_dct[s]] = char_count.get(char_dct[s],0) + str_dct[s]
            for r in rules[s] :
                new_dct[r] = new_dct.get(r,0) + str_dct[s]
        str_dct = {key: value for key, value in new_dct.items()}
        new_dct = {}

    return max(char_count.values())-min(char_count.values())


if __name__ == "__main__" :
    in_str, pair_dct, char_dct = read_file("input.txt")
    print(f"Part 1: {solution_1(in_str, pair_dct, char_dct)}")
    print(f"Part 2: {solution_1(in_str, pair_dct, char_dct, 40)}")
