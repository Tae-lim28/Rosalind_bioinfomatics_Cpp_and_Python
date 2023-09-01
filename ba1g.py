#if __name__ == "__main__":
#    with open("rosalind_ba1g.txt", "r") as f:
#        dnas = f.readlines()
#        for i in range(len(dnas)):
#            dnas[i] = dnas[i].strip()
#
#    k = len(dnas[0])
#    hamming_distance = 0
#
#    for base in range(0, k):
#        if dnas[0][base] != dnas[1][base]:
#            hamming_distance += 1
#
#    print("The hamming diatance is " + str(hamming_distance))

#with open("rosalind_ba1g.txt", "r") as f:
#    dna = f.readlines()
#    for i in range(len(dna)):
#        dna[i] = dna[i].strip()
#
#k = len(dna[0])
#hamming_distance = 0
#
#for j in range(0, k):
#    if dna[0][j] != dna[1][j]:
#        hamming_distance += 1
#
#print("The hamming distance is " + str(hamming_distance))
#with open("ba1g_output.txt", "w") as o:
#    o.write(str(hamming_distance))

with open("rosalind_ba1g.txt", "r") as f:
    dna = f.readlines()
    for i in range(len(dna)):
        dna[i] = dna[i].strip()
    print()

for j in range(0, 2):
    print(dna[j])

def calculate_hamming_distance (first_DNA, second_DNA):
    hamming_distance = 0
    k = len(first_DNA)
    for l in range(0, k):
        if first_DNA[l] != second_DNA[l]:
            hamming_distance += 1
    return hamming_distance

print (calculate_hamming_distance(dna[0], dna[1]))