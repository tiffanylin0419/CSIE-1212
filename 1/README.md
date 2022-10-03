# Greatest Common Divisor of Big Integers
The greatest common divisor gcd(a,b) between two positive integers a and b is defined as the largest positive integer that divides both a and b without a remainder. Mathematically speaking, for any positive integers a and b, gcd(a, b) satisfies the following properties:
* a≡0 modgcd(a,b)
* b≡0 modgcd(a,b)
* ∀k∈Nandk>gcd(a,b),(a!≡0 modk)or(b!≡0 modk)

GCD is a very powerful tool in modern cryptography, and when the target integers to be calculated are small (less than 108), GCD can be calculated in a few seconds with a naïve method. However, the numbers in modern cryptography requires at least 512 digits to prevent attackers from using a brute-force method to derive the secret key. This required number is too large for the naïve methods to calculate GCD in a reasonable time and the numbers exceeds the limit of even long long in the C language. In this problem, we will guide you to calculate the GCD of two big integers eﬀiciently.
## Implementation

First, to deal with the big integers, we need a “data structure”, such as an integer array in C to represent larger values. We will call it BigInt. For instance, you can use an integer array where each element represents one (decimal) digit, like representing 17202 by the following code snippet.
```c=
int digits[10]={2,0,2,7,1};
```
It is not required to use the representation above, though. You can use any representation that facilitates your implementation of the following algorithm. It is an opportunity to think about how “well-designed data structures” can lead to “eﬀicient algorithms.”

Next, please implement the following algorithm, called Binary Algorithm, using the C language. Then you will miraculously get the correct GCD. Note that you need to implement four components: a comparator between two BigInts, subtraction between two BigInts, division by 2 for one BigInt, and multiplication by 2k for one BigInt with some k. It is strongly recommended to implement the four components as separate functions, and test their correctness separately, before combining them with the Binary Algorithm.


<img width="756" alt="截圖 2022-10-03 下午12 40 12" src="https://user-images.githubusercontent.com/88768257/193632182-1c6ccaa3-8f07-4529-aef8-7be8535e7b64.png">

## Input
One line containing two integers, a and b, where 0 < a, b < 10256 . Output


Please output an integer representing gcd(a, b). 
##Sample Cases
### Sample Input 1
20210208 80201202
### Sample Output 1
6
### Sample Input 2
987654321987654321987654321 123456789123456789123456789
### Sample Output 2
9000000009000000009
