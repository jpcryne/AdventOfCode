def parse_input() :
    f = open("input.txt", "r")
    cmd = None
    dir = "/"
    file_dct = {}
    path = "/"
    for x in f :
        #print(f"""LINE: {x.strip()}""")
        #print(f"""CMD: {cmd}""")
        # * Deal with commands
        if x.startswith("$ cd") :
            dir = x.split(" ")[2].strip()
            if dir == "/" :
                dir = "home"
                path = "/home"
            elif dir == ".." :
                path = path[0:path.rfind("/")]
            else :
                path = path + "/" + dir 
            #print(f"""PATH: {path}""")
            if file_dct.get(path) is None :
                file_dct[path] = []
            cmd = "cd"
            continue
        elif x.startswith("$ ls") :
            cmd = "ls"
            continue

        # * Deal with files
        if cmd == "ls" :
            print(f"""PATH: {path}, LINE: {x}""")
            file_split = x.strip().split(" ")
            file_name = file_split[0] + " " +  str(path) + "/"  + file_split[1]
            file_dct[path].append(file_name)
            print(file_dct)

    return file_dct

def get_dir_sizes(file_dct) :
    size_dct = {}
    for key in file_dct.keys() :
        if key == ".." :
            continue
        size_dct[key] = get_dir_size(key, file_dct)
    return size_dct
        
def get_dir_size(dir, file_dct) :
    sum = 0
    print(f"""Dir: {dir} - {file_dct.get(dir)}""")
    for f in file_dct.get(dir) :
        if f.startswith("dir") :
            sum += get_dir_size(f.split(" ")[1], file_dct)
        else :
            sum += int(f.split(" ")[0])
    return sum

def part2(dir_sizes) :
    min_size = 80000000
    min_dir = ""
    required_space = 30000000 - (70000000 - dir_sizes.get("/home"))
    print(required_space)
    for k in dir_sizes.keys() :
        size = dir_sizes.get(k)
        if size < required_space :
            continue
        if size < min_size :
            min_dir = k
    return min_dir

if __name__ == "__main__" :
            file_system = parse_input()
            print(file_system)
            dir_sizes = get_dir_sizes(file_system)
            print(dir_sizes)
            print(f""" Part 1: {sum([x for x in dir_sizes.values() if x < 100000])}""")
            p2 = part2(dir_sizes)
            print(f"""Part 2: {p2}:{dir_sizes.get(p2)}""")
            
