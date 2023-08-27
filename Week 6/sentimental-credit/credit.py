import sys


card = int(input("Number: "))

while card < 0:
    card = int(input("Number: "))

# checking length
length = len(str(card))

# checking if length is valid
if (length != 13) and (length != 15) and (length != 16):
    print("INVALID\n")
    sys.exit(0)


# calculatin checksum
# Luhn algorithm explanation and code: https://allwin-raju-12.medium.com/credit-card-number-validation-using-luhns-algorithm-in-python-c0ed2fac6234
def digits_of(n):
    return [int(d) for d in str(n)]


num = digits_of(card)
odd = num[-1::-2]
even = num[-2::-2]

sum1 = 0
sum2 = 0

sum1 += sum(odd)
for d in even:
    sum2 += sum(digits_of(d * 2))

total = sum1 + sum2
checksum = total % 10

num = str(card)

# If valid
if checksum == 0:
    digit1 = int(num[0])
    digit2 = int(num[1])
else:
    print("INVALID\n")
    sys.exit(0)

if length == 16 and digit1 == 5 and (1 <= digit2 <= 5):
    print("MASTERCARD\n")

elif length == 15 and digit1 == 3 and (digit2 == 4 or digit2 == 7):
    print("AMEX\n")

elif (length == 13 or length == 16) and digit1 == 4:
    print("VISA\n")

else:
    print("INVALID\n")
    sys.exit(0)
