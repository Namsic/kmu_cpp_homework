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

print(bit_unstuffing(input()))
