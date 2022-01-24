import sys
import re

with open(sys.stdin.fileno(), encoding='utf8') as std_input:
    N = int(std_input.readline())
    li = []
    for i in range(N):
        mystr = std_input.readline()
        char_list = []
        for char in mystr:
            if len(re.findall(u'[㄰-㆏가-힣]+', char)) == 1:
                char_list.append(char)
        myset = set()
        for i in range(len(char_list) - 1):
            myset.add(char_list[i]+char_list[i+1])
        li.append(myset)
    max = -1
    maxi = -1
    maxj = -1
    for i in range(len(li)-1):
        for j in range(i+1, len(li)):
            lm = len(li[i] | li[j])
            ls = len(li[i] & li[j])
            if (ls/lm) > max:
                max = ls/lm
                maxi = i + 1
                maxj = j + 1

    print(maxi, maxj)