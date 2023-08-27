# TODO

from cs50 import get_string


# prompt user for text
content = get_string("Text: ")

Letters = 0
Words = 1  # to count the last word in
Sentences = 0

for i in range(len(content)):
    if content[i].isalpha():  # check if character is an alphabet
        Letters += 1

    elif content[i].isspace():  # check if character is a whitespace
        Words += 1

    elif (
        content[i] == "." or content[i] == "?" or content[i] == "!"
    ):  # check if character is . or ? or !
        Sentences += 1

# Coleman-Liau index
L = (Letters / Words) * 100  # average number of letters per 100 words in the text
S = (Sentences / Words) * 100  # average number of sentences per 100 words in the text
result = 0.0588 * L - 0.296 * S - 15.8
X = round(result)

# printing out grade (Before Grade 1, Grade 2 - 16, Grade 16+)
if X < 1:
    print("Before Grade 1\n")
elif X >= 1 and X <= 16:
    print(f"Grade {X}\n")
elif X > 16:
    print("Grade 16+\n")
