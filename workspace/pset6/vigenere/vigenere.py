import sys
import cs50

if len(sys.argv) != 2:
    print("Input Only one Argument")
    exit(1)

keywrd = sys.argv[1]
stringIn = cs50.get_string()
strlength = len(keywrd)
stringOut = ""
k = 0
n = 0
for c in stringIn:
    if 65<= ord(c) <= 90:
        if strlength == 1:
            kindex = 0
        else:
            kindex = k%strlength
        stringOut = stringOut + chr(65+(((ord(stringIn[n])+((ord(keywrd[kindex].upper()))%65)))%65)%26)
        k+=1
    elif 97<= ord(c) <= 122:
        if strlength == 1:
            kindex = 0
        else:
            kindex = k%strlength
        stringOut = stringOut + chr(97+((ord(stringIn[n])+((ord(keywrd[kindex].upper()))%65))%97)%26)
        k+=1
    else:
        stringOut = stringOut + stringIn[n]
    n+=1

print(stringOut)   
    
    