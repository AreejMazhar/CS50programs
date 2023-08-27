# TODO
from cs50 import get_int

while True:
    # get user input for positiv integer between 1 to 8 inclusive
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

for row in range(1, height + 1):
    for column in range(1, height + 1):
        if column > (height - row):
            print("#", end="")
        else:
            print(" ", end="")

        #middle space
        if column == height:
            print(" ", "#" * row, end="")
    print()
