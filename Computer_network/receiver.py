def bit_unstuffing(signal):
    origin = list(map(int, signal))
    st = 1
    i = 1
    res = str(origin[0])
    while i < len(origin):
        res += str(origin[i])
        if origin[i] == origin[i-1]:
            st += 1
            if st == 5:
                i += 1
        else:
            st = 1
        i += 1
    return res

def d_mlt3(stream):
    bef = '0'
    res = ''
    for bit in stream:
        res += '0' if bef == bit else '1'
        bef = bit
    return res

print(bit_unstuffing(d_mlt3(input())))
