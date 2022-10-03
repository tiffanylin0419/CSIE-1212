# Everybody Loves Brian
Brian is an intelligent and considerate student with many friends. His friends love asking him questions about stock analysis. In particular, each question is about the k-th “sweet point” among the inquiring friend’s favorite stocks, which is defined as the k-th smallest price among those stocks within the last 109 days. Here the definition of the k-th smallest value is 1-based and takes repetition into account. That is, the 3rd smallest value within {1, 1, 2, 6} is 2, and the 1st (& 2nd) smallest value is 1.

Answering each question eﬀiciently, even with the help of computers, is a challenging task. Nevertheless, Brian has lots of background knowledge about stocks that can facilitate com- putation. One property for each stock, because of the inflation nature, is that its price will eventually rise after N days. Formally speaking, let p(s,t) be the price for stock s on day t, then p(s, t + n) > p(s, t) for all n ≥ N .

In addition, Brian’s friends often share similar interests to him in terms of the favorite stocks. Formally speaking, assume that the set of Brian’s favorite stocks is A = {s1, s2, . . . , sA}. Then the set of favorite stocks for each of Brian’s friend would be either A or A ∪ {s}, where s is an extra stock that is not in A.

Given the properties above, can you write a program to help Brian eﬀiciently answer the many questions from his friends?

## Input
The first line contains three integers A,Q,N, separated by space.
* A denotes the number of Brian’s favorite stocks
* Q denotes the number of questions
* N defines how long each stock is guaranteed to increase its price, as mentioned above
The second line contains A integers s1, s2, ...sA, separated by space. • si denotes the i-th stock in A
Each of the following Q lines contains two integers s and k, separated by space.
* s denote the extra stock chosen by the inquiring friend, where s = 0 means that no extra stock is chosen.

## Output
For each question, you should print one line, containing an integer that represents the k-th “sweet point” for that question.

## Constraints
* 0≤s,si ≤109 andsi ̸=0 • 1≤k≤106
* 1≤Q, A, N ≤1024

## Important Notes
You are given price.h on NTU COOL, which contains the function   that helps you calculate the price of stock s at day t. You can simply download and
within your code, and there is no need to understand or modify the code in order to get accepted. We guarantee that:
* You can expect price(s, t) to run in constant time. Additionally, you can assume that you can run at least 107 times of per second on the judge.
* The valid input range of is 1 ≤ s, t ≤ 109, and the output range is within unsigned long long . Inputs that are out of range cause undefined behaviors.
* Theprivateprice.honthejudgesystemmaynotbeexactlythesameasthepubliconeon your hand. So you should only use the properties illustrated above to solve your problem, rather than relying on any other hacks within the public price.h. Nevertheless, you are welcomed to check the public price.h to understand how such a (random) function can be constructed.

## Sample Cases
### Sample Input 1
121\
1\
01\
0 1000000
### Sample Output 1
8 \
2448802476
### Sample Input 2
9 3 1 \
1 2 3 4 5 6 7 8 9 \
0 1000000\
0 16384\
0 121
### Sample Output 2
19841729\
29667\
59
### Sample Input 3
1 2 1000\
1000000000\
0 1000000\
0 333333
### Sample Output 3
18434768613\
12617963493
### Sample Input 4
3 3 1000\
999999991 999999992 999999993\
0 1000000\
999999994 1000000\
900000005 123456
### Sample Output 4
24875743063\
11851171780\
144499628
