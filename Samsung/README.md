# [ 14501 ] Retirement

Tags: 1st week, Retry, Samsung
URL: https://www.acmicpc.net/problem/14501

## Solution

[khr0407/coding-study](https://github.com/khr0407/coding-study/blob/master/Samsung/14501.cpp)

## Score

![14501%20Retirement/Untitled.png](https://user-images.githubusercontent.com/29090060/79953338-a4156000-84b6-11ea-9d7e-958b66e49f1b.png)

769: 위 코드

919: 기억 안남. 아마 위 코드랑 바뀐 거 거의 없었던 듯.

## Time taken

약 2시간

## Think about

- **Skipping**

    최대 수익을 내기 위해서는, 경우에 따라 날짜를 건너 뛰고 일을 하는 것이 더 나을 수도 있다.
    예를 들어, 문제의 예시에서 1일차의 *T*가 7이면, 이틀을 쉬고 3일차 상담부터 시작하는 것이 더 큰 수익을 낼 수 있다.

    정리해보면,

    1. Skipping을 하지 않아도 되는 경우: T가 1인 경우, N번째 날
    2. Skipping을 해야하는 경우: n + 1 < N인 경우 (n: 0 ≤ n < N인 정수)

    따라서, 재귀함수를 만들 때 이 부분에 유의해서 만들어야 한다.

- **재귀함수**

    내가 바라던 건 재귀함수로 DFS를 짜는 것이었는데, 잘 만들어졌는지 모르겠다

    재귀함수 *counsel(int n, int sum)*을 돌며 각 경우의 수익인 *sum*을 계산해 *max_sum*을 산출한다. *next_n*은 n번째 날의 상담을 맡기로 했을 때 다음 상담이 가능한 날짜고, *next_sum*은 n번째 날의 상담을 맡기로 했을 때 누적되는 수익이다.

    1. 일반적인 경우 (Skipping)

            void counsel (int n, int sum) {
            
            	int next_n = n + sd[n].t;
            	int next_sum = sum + sd[n].p;
            
            	counsel(next_n, next_sum);
            	for (int i=1; i<N-n; i++) { // skip
            		if (n+i < N && n+i+sd[n+i].t <= N) counsel(n+i, sum);
            	}
            
            }

    2. Skipping 없는 경우 - T가 1인 경우

            void counsel (int n, int sum) {
            
            	if (sd[n].t == 1) return counsel(next_n, next_sum);
            
            }

    3. 거의 마지막 날?

            void counsel (int n, int sum) {
            	
            	if (next_n >= N) {
            		if (next_n == N && next_sum > max_sum) max_sum = next_sum;
            		if (next_n > N && sum > max_sum) max_sum = sum;
            		for (int i=n+1; i<N; i++) return counsel(i, sum);	// skip
            		return;
            	}
            
            }

        *next_n*이 *N*과 같다면 n번째 날이 마지막 상담의 날이고, *next_n*이 *N*보다 크다면 모든 상담이 이미 끝났다는 의미다. 따라서 *max_sum*과 비교해 더 큰 값을 남기고 *return*한다.

        return 하기 전, 만약 n+1가 N보다 작다면, n번째 날의 상담을 진행하지 않고 다음 날로 넘어간 경우(skipping)도 고려해야 한다.

- **회고록**

    다른 data type을 쓰면 더 효율적이지 않을까? malloc?

    너무 많은 경우를 일일이 계산하는 것 같다. 더 생략할 수 있는 방법이 있지 않을까?

# Retry

Meetup 후 훨씬 간단한 알고리즘이 있음을 알게 됐다. O(n)

## Solution

[khr0407/coding-study](https://github.com/khr0407/coding-study/blob/master/Samsung/14501_retry.cpp)

## Score

![14501%20Retirement/Untitled%201.png](https://user-images.githubusercontent.com/29090060/79953410-c4ddb580-84b6-11ea-9f27-bd942223790a.png)

## Code details

오늘이 i번째 날이라 할 때, 고려해야 할 점은 다음과 같다. (i번째 날 당일의 헤프닝에 대해서만 생각하자)

1. i-1번째 날에 상담을 하지 않은 경우 vs. 그 외 (**과거에 대해서** 생각하자!)
2. i번째 날에 상담을 한 경우 vs. i번째 날에 상담을 하지 않은 경우 (**미래에 대해서** 생각하자!)

1에 대해서는 다음과 같다.

    if (i > 0)
    		profit.at(i) = std::max(profit.at(i), profit.at(i-1));

- *profit.at(i-1) > profit.at(i)* 인 경우: **i-1번째 날에 상담을 하지 않을 때** 수익이 더 크다.
- *profit.at(i) > profit.at(i-1)* 인 경우: **상담에 x일이 걸리는 i-x번째 날에 상담을 할 때** 수익이 더 크다.

(for문을 돌면서 i-2번째 날 상담을 하지 않은 것과 (i-1)-1번째 날 상담을 하지 않은 것은 같은 경우가 된다. → i-1번째 날에 상담을 하지 않은 경우만 생각하면 된다.)

2에 대해서는 다음과 같다.

    if (i+T.at(i) <= N)
    		profit.at(i+T.at(i)) = std::max(profit.at(i+T.at(i)), profit.at(i)+P.at(i));

- profit.at(i+T.at(i)) > profit.at(i)+P.at(i) 인 경우: **i번째 날보다 y번째 날(y<i)에 상담을 할 때** 수익이 더 크다.
- profit.at(i)+P.at(i) > profit.at(i+T.at(i)) 인 경우: **y번째 날(y<i)보다 i번째 날에 상담을 할 때** 수익이 더 크다.

y번째 날(y<i)에 상담을 해서 y+T.at(y)번째 날로 넘어가기

vs. i번째 날 상담을 해서 i+T.at(i)번째 날로 넘어가기

(y+T.at(y) = i+T.at(i))

추가)

    for (int i=0; i<N; i++) {
    		std::cin >> t >> p;
    		T.push_back(t);
    		P.push_back(p);
    	}
    	T.push_back(0);
    	P.push_back(0);

계산의 편의를 위해 vector 끝에 0을 추가했다.

예시)

![14501%20Retirement/Untitled%202.png](https://user-images.githubusercontent.com/29090060/79953350-abd50480-84b6-11ea-8d0b-e3ef4d615f2e.png)

초기 상태

![14501%20Retirement/Untitled%203.png](https://user-images.githubusercontent.com/29090060/79953389-be4f3e00-84b6-11ea-8ecb-729b8e985064.png)

i=2) 1-1 경우
i-1번째 날에 상담을 하지 않을 경우 수익이 더 크다

![14501%20Retirement/Untitled%204.png](https://user-images.githubusercontent.com/29090060/79953399-c0b19800-84b6-11ea-8ccb-deda6692e421.png)

i=2 되기 직전

![14501%20Retirement/Untitled%205.png](https://user-images.githubusercontent.com/29090060/79953408-c313f200-84b6-11ea-9f43-d16221f20953.png)

i=2) 2-2 경우
i번째 날에 상담을 할 경우 수익이 더 크다
