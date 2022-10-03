# Magic Certification II
see prob. 9 first

During the test, some elder fairies found that some magic are too similar, and they suspect there might be a plagiarism. Since any form of cheating, lying, or plagiarism will not be tolerated, they decided to investigate it.

For two strings with the same length, we call them “similar” if it at most one character is different. (Formally, two strings s, s′ are similar if there exists at most one i ∈ N s.t. s[i] ̸= s′[i]) However, there are too many fairies pursuing the magic certification. The elder fairies can barely remember all the magic, but couldn’t figure out whether there are similar magic. Can you determine for them?

## Input Format
The first line contains three integers k, l, flag, indicating the number of magic and the length of the magic.\
Each of the following k lines contain a string s with length l, indicating the magic performed. The use of flag will be explained in the output section.
## Output Format
If there are no similar magic, output a line “No” (without quotes). Otherwise, output two lines: “Yes”, following a line, depending on flag:
* If flag = 0, containing two integers i j, where the i-th magic is similar to j-th. (0-based) If there are multiple pairs of magic that are similar, output either of them.
* If flag = 1, print out one integer, indicating the number of similar pairs. Constraint
* 1≤k·l≤106
* s consists of ASCII codes from 0x21 to 0x7E only

## Sample Testcases 
### Sample Input 1
3 3 0 \
yee \
yay \
yee
### Sample Output 1
Yes \
0 2

### Sample Input 2
7 4 0 \
qwer \
qwxx \
qxex \
qxxr \
xwex \
xwxr \
xxer
### Sample Output 2
No

### Sample Input 3
1 2 0\
\>\<
### Sample Output 3
No

### Sample Input 4
8 4 0\
qwer\
qwxx\
qxex\
qxxr\
xwex\
xwxr\
xxer\
xxxr
### Sample Output 4
Yes\
7 6

### Sample Input 5
9 4 1\
qwer\
qwxx\
qxex\
qxxr\
xwex\
xwxr\
xxer\
xxer\
xxxr
### Sample Output 5
Yes\
5
