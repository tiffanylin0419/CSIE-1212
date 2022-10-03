# Purple Cow Revenge
One day, Purple Cow will be back.

Time passes, the 118 alley no longer looks like before, but becomes a ”MERGE” mode. If a shop goes bankrupt, it would merge with another one. The boss of Purple Cow, Mr. Pao, noticed this, and want to record it.

Mr. Pao also noticed that some merges could result in an unstable state. For instance, when steak meets Vanilla Ice, it would explode, causing some trouble in the 118 alley. But the phenomenon is too complicated, please help Mr. Pao record the whole process.
One and only one situation happens in one day. The day starts from day1.

## Input Format
The first line contains two integers, N, representing the numbers of shops, and, M, the number of days for data collection. The shops are denoted by (shop1, shop2, ..., shopN ). Each of the next M lines represent what each day happens and is given in one of the following formats:
1. merge is followed by two integers i, j separated by spaces. This means that shopi merge into shopj . Note that if shopm was merged by shopi before the current merge operation takes place, shopm would also become part of shopj after the current operation.
2. query For each query your program needs to output a line containing a single number representing the current number of shops in the 118 alley.
3. boom followed by a integer k. This means a Steak + Vanilla Ice event; there will be an instant explosion, which the status of all shops in the 118 alley is reverted back to day k (after the operation on that day happens).

## Output Format
For each query you need to output one line, representing the number of shops in the 118 alley at that time.

## Constraint
1. $1 ≤ N, M ≤ 1 · 10^6$
2. for mergei j,1≤i,j≤N, i≠j
3. for boom in day d, 0 ≤ k < d, k = 0 represents the initial state (all shop are pairwise independent)

## Sample Cases
### Sample Input 1
4 7\
query\
merge 1 2\
query\
merge 3 4\
query \
merge 1 3\
query

### Sample Output 1
4\
3\
2\
1

### Sample Input 2
4 11\
merge 1 2\
merge 1 3\
query\
boom 1\
query\
merge 1 3\
merge 2 4\
boom 4\
query\
boom 0\
query
### Sample Output 2
2\
3\
3\
4
