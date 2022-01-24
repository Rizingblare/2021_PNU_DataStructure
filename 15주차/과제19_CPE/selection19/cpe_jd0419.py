#coding : UTF-8

import re, sys

def cpe_input():
    f = open(sys.stdin.fileno(),encoding='utf8')
    global n
    global sentense_list
    n = int(f.readline())
    sentense_list = list()
    for i in range(n):
        sentense_list.append(f.readline())

def cpe_korean_extraction():
    hangul = re.compile('[^ㄱ-ㅣ가-힣]+')
        
    for i in range(len(sentense_list)):
        sentense_list[i] = hangul.sub('',sentense_list[i])

def cpe_decomposition():
    global sub_list
    sub_list = list()
    for i in sentense_list:
        temp_set = set()
        for j in range(len(i)):
            if j==0 : continue
            temp_str = ""
            temp_str += i[j-1]
            temp_str += i[j]
            temp_set.add(temp_str)
        sub_list.append(temp_set)


def cpe_syncTest():
    global num1,num2
    max_sync = 0
    min_num1 = 1234567890
    min_num2 = 1234567890
    for i in range(len(sub_list)):
        for j in range(i+1,len(sub_list)):
            cur_sync = len(sub_list[i] & sub_list[j]) / len(sub_list[i] | sub_list[j])
            if (max_sync < cur_sync):
                max_sync = cur_sync
                num1 = i+1
                num2 = j+1

def cpe_output():
    print(num1,num2)
    
if __name__ == "__main__":
    cpe_input()
    cpe_korean_extraction()
    cpe_decomposition()
    cpe_syncTest()
    cpe_output()
