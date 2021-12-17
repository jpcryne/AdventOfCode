
def read_file(filename) :
    f = open(filename,'r')
    x = f.readline().strip().split('=')[1:]
    x = [s.split(",")[0] for s in x]
    f.close()
    return ([int(s) for s in x[0].split('..')] , [int(s) for s in x[1].split('..')])


def in_target_x(vel, x_target) :
    pos = 0
    steps = set()
    for step in range(vel) :
        pos += vel
        change = vel // abs(vel)
        vel -= change
        if pos <= max(x_target) and pos >= min(x_target) :
            steps.add(step)
            if vel == 0 :
                steps.add(-step)
    return steps

def in_target_y(vel, y_target) :
    step = 0 if vel <= 0 else 2*vel+1
    vel = vel if vel <= 0 else -vel-1
    pos = 0
    steps = set()
    while pos >= min(y_target) :
        pos += vel
        vel -= 1
        if pos <= max(y_target) and pos >= min(y_target) :
            steps.add(step)
            if vel == 0 :
                steps.add(-step)
        step += 1
    return steps


def get_max_y(vel) :
    if vel < 0 :
        return 0
    else :
        return vel*(vel+1) / 2

def solution_1(target) :
    x_list = []
    x_steps = set()
    for v in range(1,max(target[0])+1) :
        x_step = in_target_x(v, target[0])
        if x_step :
            x_steps.update(x_step)
            x_list.extend([(v,s) for s in x_step])
    print(x_steps)

    y_steps = set()
    y_list = []
    y_in = {}
    for v in range(min(target[1]), -min(target[1])+1) :
        y_step = in_target_y(v, target[1])
        if y_step :
            y_steps.update(y_steps)
            y_in[v] = y_step
            y_list.extend([(v,s) for s in y_step])

    ## P1
    print(get_max_y(max(y_in.keys())))

    ## P2
    pairs = []
    for x in x_list :
        if x[1] < 0 :
            pairs.extend([(x[0], t[0]) for t in y_list if t[1] >= -x[1]])
        else :
            pairs.extend([(x[0],t[0]) for t in y_list if t[1] == x[1]])
    print(len(set(pairs)))




if __name__ == "__main__" :
    x = read_file("input.txt")
    print(x)
    solution_1(x)
