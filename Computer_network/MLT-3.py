signal = map(int, input())
cur, direction = 0, 1
for s in signal:
    cur += s * direction
    if s * cur:
        direction *= -1
    print('+' if cur > 0 else '-' if cur < 0 else '0' , end='')
