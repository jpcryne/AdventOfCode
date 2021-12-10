
class BingoCard :
    def __init__(self, values) :
        self.values = values
        self.dimension = (len(values), len(values[0]))

    def check_card(self, numbers) :
        ## Create map of number to turn drawn.
        number_map = {}
        for i in range(len(numbers)) :
            number_map[numbers[i]] = i

        ## Find out how long the card takes to solve.
        order_picked = [[number_map.get(val) for val in r] for r in self.values]
        row_solved = min([max(r) for r in order_picked])
        col_solved = min([max(r) for r in transpose(order_picked)])
        round_solved = min([row_solved, col_solved])

        ## Find the score if winner.
        sum = 0
        for i in range(len(self.values)) :
            for j in range(len(self.values[0])) :
                if order_picked[i][j] > round_solved :
                    sum += self.values[i][j]

        return (round_solved, sum * numbers[round_solved])

def copy_list(lst) :
    return [[val for val in r] for r in lst]

def transpose(lst) :
    t = copy_list(lst)
    for i in range(len(t[0])) :
        for j in range(len(t)) :
            t[i][j] = lst[j][i]
    return t

def score_cards(filename) :
    is_first = True
    f = open(filename, "r")
    l = []
    scores = []
    for x in f :
        if x == "\n" :
            is_first = False
            if len(l) > 0 :
                scores.append(BingoCard(l).check_card(bingo_numbers))
                l.clear()
            continue
        if is_first :
            bingo_numbers = x.split(',')
            bingo_numbers = [int(n.replace('\n','')) for n in bingo_numbers]
        else :
            row = x.split(' ')
            row = [int(r.replace('\n','')) for r in row if r != '']
            l.append(row)
    ## Capture the last one.
    scores.append(BingoCard(l).check_card(bingo_numbers))
    f.close()
    ## Find the winning card score
    first_win = [s[0] for s in scores]
    first_win = first_win.index(min(first_win))

    return scores #scores[first_win][1]

if __name__ == "__main__" :
    scores = score_cards("input.txt")

    ## Find Solution 1 (Winning Card)
    finish_rounds = [s[0] for s in scores]
    first_win = finish_rounds.index(min(finish_rounds))
    print(f"Part 1: {scores[first_win][1]}")

    ## Find Solution 2 (Losing Card)
    last_win = finish_rounds.index(max(finish_rounds))
    print(f"Part 2: {scores[last_win][1]}")
