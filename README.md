jiahojian0228's leetcode solutions


Compile static libraries:
bash ./lib.sh


Create new problem:
bash ./new.sh xxxx


Compile & Run solution (xxxx is the problem number):
bash ./exe.sh xxxx


Hints:
1292: Store the current max length, subsequent points start enumerating from the current max length. Use 2D prefix sum to speed up the process. Time: O(MN)