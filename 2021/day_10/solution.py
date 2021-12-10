from collections import deque

def read_file(filename) :

    f = open(filename, 'r')
    l = []
    for x in f :
        l.append(x.replace('\n',''))
    f.close()
    return l

def bracket_pairs() :
    return {'(':')','[':']','{':'}','<':'>'}

def left_brackets() :
    return set(['(','[','{','<'])

def right_brackets() :
    return set([')',']','}','>'])

def bracket_points() :
    return {')':3,']':57,'}':1197,'>':25137}

def is_corrupted(s) :
    corrupt = []
    lbs = left_brackets()
    rbs = right_brackets()
    bps = bracket_pairs()
    stack = deque()
    for c in s :
        if c in lbs :
            stack.append(c)
        else :
            if bps[stack.pop()] != c :
                corrupt.append(c)
                return (c, stack)
    return ('', stack)

def autocorrect_points(s) :
    pts = {')':1,']':2,'}':3,'>':4}
    total = 0
    for c in s :
        total *= 5
        total += pts[c]
    return total

def solution_1(l) :
    pts = bracket_points()
    corrupt = [is_corrupted(s)[0] for s in l]

    return sum([pts.get(c,0) for c in corrupt])

def solution_2(l) :
    bps = bracket_pairs()
    incomplete = [is_corrupted(s) for s in l]
    incomplete = [s[1] for s in incomplete if s[0] == '']
    finish_strings = []
    for stack in incomplete :
        fs = ""
        while stack :
            fs += bps[stack.pop()]
        finish_strings.append(fs)
    points = [autocorrect_points(s) for s in finish_strings]
    points.sort()
    return points[int(len(points)/2)]

if __name__ == "__main__" :
    l = read_file("input.txt")
    print(f"Part 1: {solution_1(l)}")
    print(f"Part 2: {solution_2(l)}")
