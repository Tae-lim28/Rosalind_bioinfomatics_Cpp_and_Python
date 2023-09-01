with open("rosalind_ba1f.txt","r") as f:
    string = f.readline()
    print()

print(string)

def find_minimized_skew_position(string):
    skew = []
    skew.append(0)
    min_skew = 0
    min_position = []
    for i in range(1, len(string)):
        if string[i] == "C":
            skew.append(skew[i - 1] - 1)
        elif string[i] == "G":
            skew.append(skew[i - 1] + 1)
        else:
            skew.append(skew[i - 1])
    for j in range(len(skew)):
        if skew[j] < min_skew:
            min_skew = skew[j]
    for k in range(len(skew)):
        if skew[k] == min_skew:
            min_position.append(str(k))
    return ' '.join(min_position)

print(find_minimized_skew_position(string))
