jiahojian0228's leetcode solutions


Compile static libraries:
bash ./lib.sh


Create new problem:
bash ./new.sh xxxx


Compile & Run solution (xxxx is the problem number):
bash ./exe.sh xxxx


Hints:

1292: Store the current max length, subsequent points start enumerating from the current max length. Use 2D prefix sum to speed up the process. Time: O(MN)

3814: prefix max, the index of the second element is before the first one

3816: monotonic stack, discard bigger characters only when they are encountered more than once or have more than zero remaining