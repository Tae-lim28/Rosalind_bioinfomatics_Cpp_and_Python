#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>

# define fileNameLength (128)

using namespace std;

int main(void)
{
    char rosalindInputFileName[fileNameLength];
    char rosalindOutputFileName[fileNameLength];

    cout << "Enter the rosalind input file's location and name:" << endl;
    cin >> setw(fileNameLength) >> rosalindInputFileName;

    cout << "Enter the rosalind output file's location and name" << endl;
    cin >> setw(fileNameLength) >> rosalindOutputFileName;

    cout << endl;

    auto start = std::chrono::steady_clock::now();

    ifstream rosalindInput;
    rosalindInput.open(rosalindInputFileName);

    string pattern;
    rosalindInput >> pattern;
    cout << "The pattern is:\n" << pattern << '\n' << endl;

    rosalindInput.close();

    size_t patternLength = pattern.length();
    string reverseComplementOfPattern;
    reverseComplementOfPattern.reserve(patternLength);
    const char* patternPointer = pattern.c_str();
    patternPointer += patternLength - 1;
    for (int base = 0; base < patternLength; ++base)
    {
        if (*patternPointer == 'A')
        {
            reverseComplementOfPattern.push_back('T');
        }
        else if (*patternPointer == 'C')
        {
            reverseComplementOfPattern.push_back('G');
        }
        else if (*patternPointer == 'G')
        {
            reverseComplementOfPattern.push_back('C');
        }
        else if (*patternPointer == 'T')
        {
            reverseComplementOfPattern.push_back('A');
        }

        patternPointer--;
    }
    patternPointer = NULL;

    cout << "The reverse complement of pattern is:\n" << reverseComplementOfPattern << '\n' << endl;

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);
    rosalindOutput << reverseComplementOfPattern << endl;

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}