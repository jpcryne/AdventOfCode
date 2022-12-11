import re

def parse_input() :
    f = open("input.txt", "r")
    instructions = []
    crates = []
    is_crate = True
    for x in f :
        if x.startswith(" 1") :
            is_crate = False
            key = x

        if is_crate :
            crates.append(x)

        if x.startswith("move") :
            instructions.append(re.findall("[0-9]+", x))
    stacks = build_crates(key, crates)
    return stacks, instructions
    
def build_crates(key, crates) :
    i = 1
    crates.reverse()
    l = []
    for i in range(int(key[-3])) :
        l.append([])

    for li in range(len(crates)) :
        i = 1
        while True :
            index = key.find(str(i))
            if index == -1 :
                break
            crate = crates[li][index]
            if crate != " " :
                l[i-1].append(crate)
            i += 1
            
    return l

def carry_out_instructions(stacks, instructions) :
    for inst in instructions :
        for i in range(int(inst[0])) :
            s = stacks[int(inst[1]) - 1].pop()
            stacks[int(inst[2]) - 1].append(s)
    return stacks

def carry_out_instructions2(stacks, instructions) :
    for inst in instructions :
        for i in reversed(range(int(inst[0]))) :
            s = stacks[int(inst[1]) - 1].pop(-i-1)
            stacks[int(inst[2]) - 1].append(s)
    return stacks

if __name__ == "__main__" :
    stacks, instructions = parse_input()
    stacks2 = [s.copy() for s in stacks]
    part1 = carry_out_instructions(stacks, instructions)
    print([l[-1] for l in part1])
    print("".join([l[-1] for l in part1]))
    part2 = carry_out_instructions2(stacks2, instructions)   
    print("".join([l[-1] for l in part2]))
