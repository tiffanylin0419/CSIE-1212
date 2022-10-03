# Calculate Simple Integers Easily [CSIE]

Poor calculation bothers Lisa’s life. One day, she learned how to implement an easy calculator in the DSA course. She decided to implement it to conquer her arithmetic obstacles immediately. The calculator supports the following operator on long long integers with correct precedence (Hint: https://en.cppreference.com/w/cpp/language/operator_precedence)

* arithmetic operators: +, -, *, /, %, where / means integer division. That is, a/b = ⌊ ab ⌋. • parentheses: (, )
It is guaranteed that
* the divisor for / and % would not be zero during the process of the calculation;
* a>0,b>0,foralloperationsa%b.
To be more convenient, Lisa’s calculator should support continual arithmetic. More specifically,
Lisa’s calculator follows the rules:
* At the beginning, the register of Lisa’s calculator is empty.
* When Lisa’s calculator reads any character except ’=’, it appends the character to the end of the register.
* When Lisa’s calculator reads the ’=’ character, it calculates the answer given by the expression in the register with the correct precedence. It then prints out the answer and replaces the register’s entire content with the answer.

For example, assume that Lisa inputs
 1+2=*5+(1+7+11)=%5-11=

The desired outputs are

<img width="331" alt="截圖 2022-10-03 上午12 12 05" src="https://user-images.githubusercontent.com/88768257/193500516-a42ee1c4-3852-4a6d-9268-3b5710090763.png">


This kind of functionality is common in many utility programs. You can use those programs to help you generate test data and debug by yourself. But you should of course solve this problem within your C code without calling any external programs in order to pass our judge system!

## Input
The input contains a line, recording Lisa’s input.
## Output
For each ’=’ in the input line, output a line of ’Print: [answer]’ with the answer being the calculated answer from the expression in the register.
Constraints
* 0 < the length of the input line < 106
* 0 < ai < 108 for each number ai, which is guaranteed to be an integer, in the input. 
* Every mathematical operation will not exceed the range of long long int.
* When encountering ’=’, the expression in the register is guaranteed to be legal.

## Sample Cases Sample Input 1 1+3-2*4=
### Sample Output 1
Print: -4
### Sample Input 2
1+2*(3+(8-6/3)*5)=
### Sample Output 2
Print: 67
### Sample Input 3
1+(2*3*(1+2+3*4/2*7+(1+8))+4)=/(11/5)+7-19*2=
### Sample Output 3
Print: 329
Print: 133
