class Octapii :
    def __init__(self, l, nrow, ncol) :
        self.l=l
        self.nrow=nrow
        self.ncol=ncol

    def get(self,pos) :
        return self.l[pos[0]][pos[1]]

    def set(self,pos,val) :
        self.l[pos[0]][pos[1]] = val

    def __repr__(self) :
        s = ""
        for i in range(self.nrow) :
            for j in range(self.ncol) :
                s += str(self.get((i,j)))
            s += "\n"
        return s

    def get_neighbours(self,pos) :
        i = pos[0]
        j = pos[1]
        ns = [(i-1,j),(i+1,j),(i,j+1),(i,j-1),(i-1,j-1),(i-1,j+1),(i+1,j+1),(i+1,j-1)]
        return [n for n in ns if n[0] >= 0 and n[1] >= 0 and n[0] < self.nrow and n[1] < self.ncol]

    def energy_increase(self) :
        flashes = []

        for i in range(self.nrow) :
            for j in range(self.ncol) :
                pos = (i,j)
                next_val = (self.get(pos)+1)
                if next_val == 10 :
                    flashes.append(pos)
                self.set(pos, next_val)

        return self.flash_step(flashes, 0)

    def flash_step(self, flashes, flash_count) :

        if len(flashes) == 0 :
            return flash_count

        new_flashes = []
        for pos in flashes :
            self.set(pos,0)
            nbrs = self.get_neighbours(pos)
            for npos in nbrs :
                nval = self.get(npos)
                if nval == 0 :
                    continue
                else :
                    self.set(npos, nval + 1)
                    if nval == 9 :
                        new_flashes.append(npos)
        flash_count += len(flashes)
        return self.flash_step(new_flashes, flash_count)




def solution_1(l) :
    octs = Octapii(l, len(l), len(l[0]))
    flashes = 0
    for i in range(100) :
        flashes += octs.energy_increase()

    return flashes

def solution_2(l) :
    octs = Octapii(l, len(l), len(l[0]))
    flashes_required = octs.nrow*octs.ncol
    i=0
    while octs.energy_increase() != flashes_required :
        i += 1
    return i+1

def read_file(filename) :
    f = open(filename, 'r')
    l = []
    for x in f :
        tmp = [c for c in str(x).rstrip()]
        tmp = [a for a in tmp if len(a) > 0]
        l.append([int(t) for t in tmp])

    f.close()

    return l


if __name__ == "__main__" :
    l1 = read_file("input.txt")
    l2 = [[s for s in l] for l in l1]

    print(f"Part 1: {solution_1(l1)}")
    print(f"Part 2: {solution_2(l2)}")
