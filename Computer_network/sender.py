def bit_stuffing(signal):
    origin = map(int, signal)
    cur = -1
    st = 0
    res = ''
    for i in origin:
        res += str(i)
        if cur == i:
            st += 1
            if st == 5:
                res += '0' if i else '1'
                st = 0
        else:
            cur = i
            st = 1
    return res

def mlt3(bits):
    signal = map(int, bits)    
    res = ''
    out = ['-', '0', '+']

    cur = 0
    direction = 1
    for s in signal:
        if s:
            cur += direction
            if cur:
                direction *= -1
        res += out[cur+1]
    return res

print(mlt3(bit_stuffing(input())))
