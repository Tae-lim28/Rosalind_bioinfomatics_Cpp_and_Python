from itertools import product
import time

if __name__ == "__main__":
    print("Enter the rosalind input file location and name:")
    rosalind_input_file_name = input()
    print("Enter the rosalind output file location and name:")
    rosalind_output_file_name = input()

    starting_time = time.time()

    rosalind_input_file = open(rosalind_input_file_name, "r")   
    input_lines = []
    for input_line in rosalind_input_file:
        input_lines.append(input_line.strip())
    rosalind_input_file.close()
    
    temporary_inputs = input_lines[1].split()
    text = input_lines[0]
    k = int(temporary_inputs[0])
    d = int(temporary_inputs[1])
    print("The text is:\n" + text)
    print("The value of k is:\n" + str(k))
    print("The value of d is:\n" + str(d))

    bases = ["A", "C", "G", "T"]
    d_neighbor_candidates = list(product(bases, repeat = k))

    d_neighbor_candidates_length = len(d_neighbor_candidates)
    for candidate_order in range(d_neighbor_candidates_length):
        d_neighbor_candidates[candidate_order] = "".join(d_neighbor_candidates[candidate_order])

    d_neighbor_candidate_and_frequencies = {}
    text_length = len(text)
    for pattern_location in range(0, text_length - k + 1):
        for d_neighbor_candidate in d_neighbor_candidates:
            hamming_distance = 0
            for base in range(k):
                if d_neighbor_candidate[base] != text[pattern_location + base]:
                    hamming_distance += 1
            if hamming_distance <= d:
                if d_neighbor_candidate not in d_neighbor_candidate_and_frequencies:
                    d_neighbor_candidate_and_frequencies[d_neighbor_candidate] = 1
                else:
                    d_neighbor_candidate_and_frequencies[d_neighbor_candidate] += 1

    maximum_frequency = 0
    for (d_neighbor, frequency) in d_neighbor_candidate_and_frequencies.items():
        if frequency > maximum_frequency:
            maximum_frequency = frequency

    print("The most frequent words are:")
    rosalind_output_file = open(rosalind_output_file_name, "w")
    for (d_neighbor, frequency) in d_neighbor_candidate_and_frequencies.items():
        if frequency == maximum_frequency:
            print(d_neighbor, end = " ")
            rosalind_output_file.write(d_neighbor)
            rosalind_output_file.write(" ")
    print()
    rosalind_output_file.write("\n")
    rosalind_output_file.close()

    end_time = time.time()
    print("Elapsed time is:")
    print(f"{end_time - starting_time:.5f}sec")

    print("Writting rosalind output file is done.")