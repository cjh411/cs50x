import sys
import cs50


def getval(i,m):
    if i <= m:
        return " "
    else:
        return "#"

print ("Input Integer:")
inint = cs50.get_int()

s=""
for i in range(1,int(inint)+1):
    for j in range(2):
        for k in range(1,int(inint)+1):
            if j==0:
                s = s + getval(i,int(inint)-k)
            else:
                s = s + getval(i,k-1)
        s = s + "  "
    print(s)
    s = ""
            