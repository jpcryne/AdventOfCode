
def read_file(filename) :
    f = open(filename, 'r')

    folds = []
    points = []
    is_fold = False
    for x in f :
        if x == "\n" :
            is_fold = True
            continue
        if is_fold :
            folds.append(x.strip().split('='))
            continue
        else :
            points.append(tuple(int(n) for n in x.strip().split(',')))

    return (set(points),folds)

def apply_fold(points, fold) :
    print(fold)
    fold[1] = int(fold[1])
    axis = int(fold[0] == "fold along y")
    new_points = set()
    for p in points :
        if p[axis] > fold[1] :
            new_axis = 2*fold[1] - p[axis]
            new_points.add(tuple([p[0], new_axis]) if axis == 1 else tuple([new_axis, p[1]]))
        elif p[axis] < fold[1] :
            new_points.add(p)

    return new_points

def print_points(points) :
    xlims = [100000,-100000]
    ylims = [100000,-100000]
    for p in points :
        if p[0] < xlims[0] :
            xlims[0] = p[0]
        if p[1] < ylims[0] :
            ylims[0] = p[1]
        if p[0] > xlims[1] :
            xlims[1] = p[0]
        if p[1] > ylims[1] :
            ylims[1] = p[1]
    s = ""

    for j in range(ylims[0],ylims[1]+1) :
        for i in range(xlims[0],xlims[1]+1) :
            s += "#" if tuple([i,j]) in points else "."
        s += "\n"
    print(s)


def solution_1(points, folds) :
    return len(apply_fold(points, folds[0]))

def solution_2(points, folds) :
    for f in folds :
        points = apply_fold(points, f)
    print_points(points)

if __name__ == "__main__" :
    points, folds = read_file("input.txt")
    print(f"Part 1: {solution_1(points, folds)}")
    solution_2(points, folds)
