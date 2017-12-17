

————————

<!-- TOC -->

- [50. Pow(x, n)](#50-powx-n)
- [371. Sum of Two Integers](#371-sum-of-two-integers)
- [412. Fizz Buzz](#412-fizz-buzz)
- [461](#461)
- [476 Number Complement](#476-number-complement)
- [500. Keyboard Row](#500-keyboard-row)
- [530. Minimum Absolute Difference in BST](#530-minimum-absolute-difference-in-bst)
- [535. Encode and Decode TinyURL](#535-encode-and-decode-tinyurl)
- [538. Convert BST to Greater Tree](#538-convert-bst-to-greater-tree)
- [543. Diameter of Binary Tree](#543-diameter-of-binary-tree)
- [575 Distribute Candies](#575-distribute-candies)
- [673. Number of Longest Increasing Subsequence](#673-number-of-longest-increasing-subsequence)
- [674. Longest Continuous Increasing Subsequence](#674-longest-continuous-increasing-subsequence)
- [728. Self Dividing Numbers](#728-self-dividing-numbers)
- [724. Find Pivot Index](#724-find-pivot-index)
- [733. Flood Fill](#733-flood-fill)

<!-- /TOC -->
—————————

# 50. Pow(x, n)
Implement pow(x, n).

file : ALG050_Pow.cpp


# 371. Sum of Two Integers 

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.

file ： ALG371_SumofTwoIntegers.cpp


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

# 500. Keyboard Row

> file: ALG500_KeyboardRow.cpp

# 530. Minimum Absolute Difference in BST

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:
``` 
Input:

   1
    \
     3
    /
   2

Output:
1
``` 
Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
Note: There are at least two nodes in this BST.

> file: ALG530_MinimumAbsoluteDifferenceBST.cpp

# 535. Encode and Decode TinyURL

> Note: This is a companion problem to the System Design problem: Design TinyURL.
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.



file : ALG535_EncodeAndDecodeTinyURL.cpp

# 538. Convert BST to Greater Tree


file : ALG538_ConvertBST2GreaterTree.cpp


# 543. Diameter of Binary Tree
Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

Example:
```
Given a binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
```



> file: ALG543_DiameterofBinaryTree.cpp

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



# 673. Number of Longest Increasing Subsequence

> file : ALG673_NumberOfLongestIncreasingSubsequence.cpp

_________

# 674. Longest Continuous Increasing Subsequence


> file: ALG674_LongestContinuousIncreasingSubsequence.cpp


# 728. Self Dividing Numbers


> file: ALG728_SelfDividingNumbers.cpp


# 724. Find Pivot Index


> file :ALG724_FindPivotIndex.cpp



# 733. Flood Fill
> file: ALG733_Flood_Fill.cpp