import math
def read_file(filename) :
    f = open(filename)
    hex = f.readline().strip()
    f.close()
    return hex

def hex_to_bin(str) :
    return bin(int(str, 16))[2:].zfill(len(str)*4)

def bin_to_dec(str) :
    return int(str,2)

def process_packet(b, depth = 0) :
    packet_type_id = bin_to_dec(b[3:6])

    if packet_type_id == 4 :
        return process_literal(b, depth + 1)
    else :
        return process_operator(b, depth + 1)

def process_literal(b, depth = 0) :
    packet_version = bin_to_dec(b[0:3])
    has_next = True
    b = b[6:]
    new_bin = ""

    while has_next :
        if b[0] == '0' :
            has_next = False
        new_bin += b[1:5]
        b = b[5:]
    value = bin_to_dec(new_bin)
    return (b,packet_version,value)

def process_operator(b, depth = 0) :
    total_version = bin_to_dec(b[0:3])
    packet_type_id = bin_to_dec(b[3:6])
    literals = []

    b = b[6:]
    if b[0] == '0' :
        sub_packet_length = bin_to_dec(b[1:16])
        b = b[16:]
        old_s = '%s' % b
        while len(old_s) - len(b) < sub_packet_length :
            b, tv, value = process_packet(b, depth + 1)
            total_version += tv
            literals.append(value)
        return (b,total_version,apply_function(literals, packet_type_id))
    else :
        number_sub_packets = bin_to_dec(b[1:12])
        b = b[12:]
        for _ in range(number_sub_packets) :
            b, tv, value = process_packet(b, depth + 1)
            total_version += tv
            literals.append(value)
        apply_function(literals, packet_type_id)
        return (b,total_version,apply_function(literals, packet_type_id))

def apply_function(l, id) :
    match id :
        case 0 :
            return sum(l)
        case 1 :
            return math.prod(l)
        case 2 :
            return min(l)
        case 3 :
            return max(l)
        case 5 :
            return int(l[0] > l[1])
        case 6 :
            return int(l[0] < l[1])
        case 7 :
            return int(l[0] == l[1])
    return None


if __name__ == "__main__" :
    h = read_file("input.txt")
    b = hex_to_bin(h)
    d = bin_to_dec(b)
    print(process_packet(b))
