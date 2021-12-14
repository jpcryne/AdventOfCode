
def read_file(filename) :
    f = open(filename,'r')
    g = {}
    for x in f :
        tmp = x.strip().split("-")

        s = g.get(tmp[0],set([]))
        s.add(tmp[1])
        g[tmp[0]] = s

        s = g.get(tmp[1],set([]))
        s.add(tmp[0])
        g[tmp[1]] =  s

    f.close()

    ## Tidy up
    g["end"] = set([])
    for x in g.values() :
        if "start" in x :
            x.remove("start")

    return g

def deep_copy(st, lst = False) :
    tmp = [s for s in st]
    if not lst :
        tmp = set(tmp)
    return tmp

def explore_paths_1(g, path, visited, complete_paths) :
    current = path[-1]

    visited.add(current)

    options = g[current]
    options = [o for o in options if not (o in visited and o.lower() == o)]

    # print(f"Depth: {depth}, Current: {current}, Path {path}, Options: {options}, Visited: {visited}, Complete: {complete_paths}")

    if len(options) == 0 :
        if current == "end" :
            complete_paths.append(path)
        return None

    for o in options :
        new_path = deep_copy(path, True)
        new_visited = deep_copy(visited)
        new_visited.add(o)
        explore_paths_1(g, new_path+[o], new_visited, complete_paths)

    return None

def explore_paths_2(g, path, visited, complete_paths, visited_twice=False) :
    current = path[-1]

    visited.add(current)

    options = g[current]
    if visited_twice :
        options = [o for o in options if not (o in visited and o.lower() == o)]

    if path == ['start', 'A', 'b', 'A', 'c', 'A'] :
        print(f"Current: {current}, VisitedTwice: {visited_twice}, Path {path}, Options: {options}, Visited: {visited}, Complete: {complete_paths}")

    if len(options) == 0 :
        if current == "end" :
            complete_paths.append(path)
        return None

    for o in options :
        new_visited_twice = visited_twice
        if o in visited and o.lower() == o :
            new_visited_twice = True
        new_path = deep_copy(path, True)
        new_visited = deep_copy(visited)
        new_visited.add(o)
        explore_paths_2(g, new_path+[o], new_visited, complete_paths, new_visited_twice)

    return None

def solution_1(g) :
    paths = []
    explore_paths_1(g, ["start"], set([]), paths)
    return len(paths)

def solution_2(g) :
    paths = []
    explore_paths_2(g, ["start"], set([]), paths)
    return len(paths)

if __name__ == "__main__" :
    g = read_file("input.txt")
    print(g)
    print(f"Part 1: {solution_1(g)}")
    print(f"Part 2: {solution_2(g)}")
