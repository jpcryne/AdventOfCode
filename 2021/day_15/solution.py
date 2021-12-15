import heapq

class Maze :
    def __init__(self,values,R,C) :
        self.values=values
        self.R=R
        self.C=C

    def __repr__(self) :
        s = ""
        for i in range(self.R) :
            for j in range(self.C) :
                s += str(self.values[i][j])
            s += "\n"
        return s

    def tostring(self,extended) :
        R = self.R
        C = self.C
        if extended :
            R*=5
            C*=5
        s = ""
        for i in range(R) :
            for j in range(C) :
                s += str(self.get(tuple([i,j]), extended))
            s += "\n"
        return s

    def get(self,pos,extended) :
        if not extended :
            return self.values[pos[0]][pos[1]]
        else :
            pos0=pos[0] % self.R;
            pos1=pos[1] % self.C;
            add = pos[0] // self.R + pos[1] // self.C
            old_val = self.values[pos0][pos1]
            if old_val + add > 9 :
                return (old_val + add) % 10 + 1
            else :
                return (old_val + add) % 10

    def get_neighbours(self,pos,extended) :
        i = pos[0]
        j = pos[1]
        ns = [(i-1,j),(i+1,j),(i,j+1),(i,j-1)]
        if not extended :
            return [n for n in ns if n[0] >= 0 and n[1] >= 0 and n[0] < self.R and n[1] < self.C]
        else :
            return [n for n in ns if n[0] >= 0 and n[1] >= 0 and n[0] < self.R*5 and n[1] < self.C*5]

def read_file(filename) :
    f = open(filename, 'r')
    l = []
    for x in f :
        l.append([int(i) for i in list(x.strip())])

    f.close()

    return Maze(l, len(l[0]), len(l))

def deep_copy(x) :
    return set([i for i in x])

def dijkstra(maze, start, end, extended = False) :
    R = maze.R
    C = maze.C

    if extended :
        R*=5
        C*=5

    unvisited = set([tuple([i,j]) for i in range(R) for j in range(C)])

    dist = {p:100000 for p in unvisited}

    dist[start] = 0

    pq = []
    heapq.heappush(pq, (0, start))

    while unvisited :
        current = heapq.heappop(pq)[1]

        if current not in unvisited :
            continue

        unvisited.remove(current)

        if current == end :
            return dist[end]

        nbrs = maze.get_neighbours(current,extended)
        nbrs = [n for n in nbrs if n in unvisited]
        for n in nbrs :
            new_dist = dist.get(current) + maze.get(n,extended)
            if new_dist < dist.get(n) :
                dist[n] = new_dist
            heapq.heappush(pq,(dist[n], n))

    return dist[end]


if __name__ == "__main__" :
    m = read_file("input.txt")
    print(f"Part 1: {dijkstra(m, tuple([0,0]), tuple([m.R-1,m.C-1]))}")
    print(f"Part 2: {dijkstra(m, tuple([0,0]), tuple([m.R*5-1,m.C*5-1]), True)}")
