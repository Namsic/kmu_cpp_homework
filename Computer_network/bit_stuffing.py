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

print(bit_stuffing(input()))
