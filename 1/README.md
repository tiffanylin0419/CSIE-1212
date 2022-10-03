Calculate Simple Integers Easily [CSIE]
Poor calculation bothers Lisa’s life. One day, she learned how to implement an easy calculator in the DSA course. She decided to implement it to conquer her arithmetic obstacles immediately. The calculator supports the following operator on long long integers with correct precedence (Hint: https://en.cppreference.com/w/cpp/language/operator_precedence)
• arithmetic operators: +, -, *, /, %, where / means integer division. That is, a/b = ⌊ ab ⌋. • parentheses: (, )
It is guaranteed that
• the divisor for / and % would not be zero during the process of the calculation;
• a>0,b>0,foralloperationsa%b.
To be more convenient, Lisa’s calculator should support continual arithmetic. More specifically,
Lisa’s calculator follows the rules:
• At the beginning, the register of Lisa’s calculator is empty.
• When Lisa’s calculator reads any character except ’=’, it appends the character to the end of the register.
• When Lisa’s calculator reads the ’=’ character, it calculates the answer given by the expression in the register with the correct precedence. It then prints out the answer and replaces the register’s entire content with the answer.
For example, assume that Lisa inputs
 1+2=*5+(1+7+11)=%5-11=
