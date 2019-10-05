#File Objects

#åpne filen


with open("data.txt", "r") as f:
    for line in f:
        print(line,end="")
