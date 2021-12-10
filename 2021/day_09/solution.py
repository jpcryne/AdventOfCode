class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class Floor :
    def __init__(self, values, nrow, ncol) :
        self.nrow = nrow
        self.ncol = ncol
        self.values = values

    def is_lowpoint(self, i, j) :
        bools = [True]*4
        this_val = self.values[i][j]
        if i > 0 :
            bools[0] = self.values[i-1][j] > this_val
        if j > 0 :
            bools[1] = self.values[i][j-1] > this_val
        if i < self.nrow-1 :
            bools[2] = self.values[i+1][j] > this_val
            # print(f"{self.values[i+1][j]} > {this_val}")
        if j < self.ncol-1 :
            bools[3] = self.values[i][j+1] > this_val
        return all(bools)

    def __repr__(self) :
        str = ""
        for i in range(self.nrow) :
            for j in range(self.ncol) :
                if self.is_lowpoint(i,j) :
                    str += f"{bcolors.WARNING}{self.values[i][j]}{bcolors.ENDC}"
                else :
                    str += f"{self.values[i][j]}"
            str += "\n"
        return str

    def get_neighbours(self,points) :
        i = points[0]
        j = points[1]
        ns = [(i-1,j),(i+1,j),(i,j+1),(i,j-1)]
        return [n for n in ns if n[0] >= 0 and n[1] >= 0 and n[0] < self.nrow and n[1] < self.ncol]

    def find_baisin(self, pt, baisin, checked) :
        # print(f"Checking Point: {pt}")
        if pt in checked :
            return None

        checked.add(pt)
        if self.values[pt[0]][pt[1]] < 9 :
            baisin.add(pt)
        else :
            return None

        nbrs = self.get_neighbours(pt)
        nbrs = [n for n in nbrs if n not in checked]
        # print(f"Neighbours: {nbrs}")

        for n in nbrs :
            if n not in checked :
                self.find_baisin(n, baisin, checked)

        return None

def read_file(filename) :
    l = []
    f = open(filename, 'r')

    for x in f :
        tmp = [int(c) for c in x if c != '\n']
        l.append(tmp)
    f.close()

    return l

def solution_1(l) :
    f = Floor(l, len(l), len(l[0]))
    # print(f.is_lowpoint(0,0))
    print(f)
    sum = 0
    for i in range(f.nrow) :
        for j in range(f.ncol) :
            sum += int(f.is_lowpoint(i,j)) * (f.values[i][j] + 1)

    return sum

def solution_2(l) :
    f = Floor(l, len(l), len(l[0]))
    lowpoints = []
    for i in range(f.nrow) :
        for j in range(f.ncol) :
            if f.is_lowpoint(i,j) :
                lowpoints.append((i,j))

    baisins = []
    for lp in lowpoints :
        baisin = set([])
        checked = set([])
        f.find_baisin(lp, baisin, checked)
        baisins.append(baisin)
    b_sizes = [len(b) for b in baisins]
    b_sizes.sort(reverse = True)

    return b_sizes[0]*b_sizes[1]*b_sizes[2]


if __name__ == "__main__" :
    l = read_file("input.txt")
    print(l)
    print(f"Part 1: {solution_1(l)}")
    print(f"Part 2: {solution_2(l)}")
