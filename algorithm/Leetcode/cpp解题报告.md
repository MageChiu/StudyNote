

————————

<!-- TOC -->

- [412. Fizz Buzz](#412-fizz-buzz)
- [461](#461)
- [476 Number Complement](#476-number-complement)
- [535. Encode and Decode TinyURL](#535-encode-and-decode-tinyurl)
- [575 Distribute Candies](#575-distribute-candies)

<!-- /TOC -->
—————————


# 412. Fizz Buzz
Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

Example:
``` shell
n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
```

> file: ALG412_FizzBuzz.cpp



# 461 

# 476 Number Complement

# 535. Encode and Decode TinyURL

> Note: This is a companion problem to the System Design problem: Design TinyURL.
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.



file : ALG535_EncodeAndDecodeTinyURL.cpp



# 575 Distribute Candies

Given an integer array with even length, where different numbers in this array represent different kinds of candies. Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and sister. Return the maximum number of kinds of candies the sister could gain.

Example 1:
``` 
Input: candies = [1,1,2,2,3,3]
Output: 3
```
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3], too. 
The sister has three different kinds of candies. 
Example 2:
``` 
Input: candies = [1,1,2,3]
Output: 2
```
Explanation: For example, the sister has candies [2,3] and the brother has candies [1,1]. 
The sister has two different kinds of candies, the brother has only one kind of candies. 
Note:

1. The length of the given array is in range [2, 10,000], and will be even.
2. The number in given array is in range [-100,000, 100,000].


> file:ALG575_DistributeCandies.cpp