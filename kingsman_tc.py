import random

def gen_random_str(n):
    s=''
    for i in range(n):
        s = s + chr(random.randint(ord('a'),ord('z')))
    return s

n = int(input())
l = []
code = list(range(0,26))
random.shuffle(code)


def decode(s):
    r = ''
    for c in s:
        r = r + chr(code[ord(c)-ord('a')]+ord('a'))
    return r

for _ in range(n):
    l.append(gen_random_str(random.randint(1,n)))

ls = []

for s in l:
    ls.append(decode(s))

for _ in range(0,n*2):
    ls.append(gen_random_str(random.randint(1,n)))

random.shuffle(ls)

res = ''
ans = ''
print(3*n)
for s in ls:
    print(s)

for s in l:
    res = res + s + " "
    ans = ans + decode(s) + " "

print(res.strip())
print(ans.strip())
