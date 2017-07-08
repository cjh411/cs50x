import sys
import cs50

print("Input Credit Card Number: ")
ccnum = cs50.get_int()
checkdiv = ccnum//1000000000000 

if checkdiv == 51 or checkdiv == 52 or checkdiv == 53 or checkdiv == 54 or checkdiv == 55:
    type = "MASTERCARD"
elif checkdiv//10 == 34 or checkdiv//10 == 37:
    type = "AMEX"
elif checkdiv//10 == 4 or checkdiv//1000 == 4:
    type="VISA"
else:
    type = "INVALD"
    
oddsum = 0
evensum = 0
i = 0
while (ccnum > 0):
    if i%2 == 0:
        evensum += ccnum%10
    else:
        tmp = (ccnum%10)*2
        while (tmp > 0):
            oddsum += tmp%10
            tmp = tmp // 10
    
    ccnum = ccnum //10
    i+=1
    
if (oddsum+evensum)%10 !=0:
    print("INVALID")
else:
    print(type)