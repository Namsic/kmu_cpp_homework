
private
```int elapse``` : 게임이 시작되고 흐른 tick 수 입니다.
```int width, height``` : 게임판의 가로와 세로 크기입니다.
```int **field```: 게임판의 각 좌표에 대한 정보를 담고 있는 2차원 배열입니다. 각 좌표의 값은 다음과 같은 의미를 갖습니다.
0: 아무것도 없는 빈 공간입니다.
1: 벽입니다. snake가 지나갈 수 없으며, gate가 생성될 수 있습니다.
2: 벽입니다. snake가 지나갈 수 없으며, gate가 생성될 수 없습니다.
3: snake의 머리입니다.
100 ~ 199: snake의 몸통입니다.
200 ~ 299: growth 아이템입니다. snake의 머리가 지나가면 snake의 길이가 1 증가합니다.
300 ~ 399: poison 아이템입니다. snake의 머리가 지나가면 snake의 길이가 1 감소합니다.
400 ~ 499: gate 입니다. 필드 상에 동시에 2개 존재하며, 한 gate를 통과하면 다른 gate에서 나오게 됩니다.
```int head_row, head_col```: snake의 머리가 위치하는 행, 열 값입니다.
```int next_row, next_col```: snake의 머리가 다음 tick에 이동할 행, 열 값입니다.
```int direction```: snake의 현재 진행 방향입니다.
```int length, max_length```: snake의 현재 몸 길이와, 가장 길었던 때의 몸 길이입니다.
```int itemProbability[3]```: 각 아이템 및 gate의 등장 확률입니다. 각 값은 다음과 같은 의미를 갖습니다.
itemProbability[0]: growth 아이템의 등장 확률입니다.
itemProbability[1]: poison 아이템의 등장 확률입니다.
itemProbability[2]: gate의 등장 확률입니다.
```int itemMaximum[3]```: 각 아이템 및 gate가 동시에 존재할 수 있는 최대 갯수입니다. 각 값은 다음과 같은 의미를 갖습니다.
itemMaximum[0]: growth 아이템의 최대 갯수입니다.
itemMaximum[1]: poison 아이템의 최대 갯수입니다.
itemMaximum[2]: gate의 최대 갯수입니다.(홀수일 경우 그보다 큰 수 중에 가장 작은 짝수 값만큼 존재할 수 있습니다)
```int itemLife[3]```: 각 아이템 및 gate의 등장 후 사라질 때까지 걸리는 tick 수 입니다. 각 값은 다음과 같은 의미를 갖습니다.
itemLife[0]: growth 아이템의 수명입니다.
itemLife[1]: poison 아이템의 수명입니다.
itemLife[2]: gate의 수명입니다.

