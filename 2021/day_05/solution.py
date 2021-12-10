
class Vent :
    def __init__(self, start, end) :
        self.start=start
        self.end=end

    def is_horizontal(self) :
        return (self.start[1]==self.end[1])

    def is_vertical(self) :
        return (self.start[0]==self.end[0])

    def __repr__(self) :
        return f"{self.start} -> {self.end}"

    def visited_points(self) :
        is_incx = self.start[0] <= self.end[0]
        is_incy = self.start[1] <= self.end[1]
        xrng = (self.start[0],self.end[0]) if is_incx else (self.end[0], self.start[0])
        yrng = (self.start[1],self.end[1]) if is_incy else (self.end[1], self.start[1])
        xrng = range(xrng[0],xrng[1]+1);yrng = range(yrng[0],yrng[1]+1);
        if self.is_horizontal() :
            return [(x,self.end[1]) for x in xrng]
        elif self.is_vertical() :
            return [(self.end[0],y) for y in yrng]
        else :
            if is_incx != is_incy :
                xrng = reversed(xrng)
            xrng = list(xrng);yrng=list(yrng);
            l = []
            for i in range(len(xrng)) :
                l.append((xrng[i],yrng[i]))
            return l



def read_file(filename) :
    l = []
    f = open(filename, 'r')

    for x in f :
        vals = x.replace(" -> ", ",").split(',')
        vals = [int(v.rstrip()) for v in vals]
        l.append(Vent(vals[0:2], vals[2:4]))

    f.close()

    return l

def solution_1(vents) :
    vents = [v for v in vents if v.is_horizontal() or v.is_vertical()]
    return find_duplicates(vents)

def solution_2(vents) :
    return find_duplicates(vents)

def find_duplicates(vents) :
    seen_twice = set()
    seen_once = set()
    for v in vents :
        for p in v.visited_points() :
            if p in seen_once :
                seen_twice.add(p)
            else :
                seen_once.add(p)
    return len(seen_twice)

def list_plot(lst) :
    str = ""
    for i in range(0,10) :
        for j in range(0,10) :
            if (i,j) in lst :
                str += "1"
            else :
                str += "."
        str += "\n"
    return str


if __name__ == "__main__" :
    vents = read_file("input.txt")
    print(solution_1(vents))
    print(solution_2(vents))
