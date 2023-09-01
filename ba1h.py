with open("rosalind_ba1h.txt", "r") as f:
    input_lines = f.readlines()
    for i in range(len(input_lines)):
        input_lines[i] = input_lines[i].strip()
    print()

for j in range(len(input_lines)):
    print(input_lines[j])

pattern = input_lines[0]
text = input_lines[1]
d = int(input_lines[2])

def calculate_hamming_distance(first_DNA, second_DNA):
    hamming_distance = 0
    k = len(first_DNA)
    for l in range(0, k):
        if first_DNA[l] != second_DNA[l]:
            hamming_distance += 1
    return hamming_distance

def find_approximate_occurrences(pattern, text, d):
    k = len(pattern)
    text_length = len(text)
    starting_positions = []
    for l in range(0, text_length - k + 1):
        hamming_distance = calculate_hamming_distance(pattern, text[l : l + k])
        if hamming_distance <= d:
            starting_positions.append(str(l))
    return starting_positions

print(' '.join(find_approximate_occurrences(pattern, text, d)))