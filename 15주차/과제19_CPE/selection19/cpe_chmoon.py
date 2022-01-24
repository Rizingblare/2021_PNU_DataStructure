import sys


def CPE_input(mer_l):
    with open(sys.stdin.fileno(), encoding='utf8') as std_input:
        N = int(std_input.readline())
        for i in range(N):
            s = set()
            line = std_input.readline()
            buf = ""
            for c in line:
                if (0x3131 <= ord(c) and ord(c) <= 0x3163) or (0xac00 <= ord(c) and ord(c) <= 0xd7a3):
                    buf += c
            for i in range(len(buf) - 1):
                s.add(buf[i] + buf[i+1])
            mer_l.append(s)
    return N


def sim(N, mer_l):
    ans = (N + 1, N + 1)
    max_sim = 0
    for i in range(N - 1):
        for j in range(i + 1, N):
            sim = len(mer_l[i] & mer_l[j]) / len(mer_l[i] | mer_l[j])
            if sim > max_sim:
                max_sim = sim
                ans = (i + 1, j + 1)
    print(ans[0], ans[1])


if __name__ == '__main__':
    mer_l = []
    N = CPE_input(mer_l)
    sim(N, mer_l)
