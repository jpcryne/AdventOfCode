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
    print(f"Literal, version {packet_version}")
    has_next = True
    b = b[6:]
    new_bin = ""

    while has_next :
        if b[0] == '0' :
            has_next = False
        new_bin += b[1:5]
        b = b[5:]
        # print(f"b in loop: {b}")
    value = bin_to_dec(new_bin)
    print(f"Value: {value}")
    return (b,packet_version)

def process_operator(b, depth = 0) :
    total_version = bin_to_dec(b[0:3])

    print(f"Operator, version {total_version}")

    b = b[6:]
    if b[0] == '0' :
        print(f"Process Length")
        sub_packet_length = bin_to_dec(b[1:16])
        b = b[16:]
        old_s = '%s' % b
        while len(old_s) - len(b) < sub_packet_length :
            b, tv = process_packet(b, depth + 1)
            total_version += tv
        return (b,total_version)
    else :
        number_sub_packets = bin_to_dec(b[1:12])
        print(f"Process Number: {number_sub_packets}")
        b = b[12:]
        literals = []
        for _ in range(number_sub_packets) :
            b, tv = process_packet(b, depth + 1)
            total_version += tv
        return (b,total_version)


if __name__ == "__main__" :
    h = read_file("input.txt")
    b = hex_to_bin(h)
    d = bin_to_dec(b)
    print(b)
    print(process_packet(b))
