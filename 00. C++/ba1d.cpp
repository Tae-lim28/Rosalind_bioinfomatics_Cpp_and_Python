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
    pattern.reserve(16);
    string genome;
    genome.reserve(16384); /*2^14 = 16384*/
    rosalindInput >> pattern >> genome;
    cout << "The pattern is:\n" << pattern << '\n' << endl;
    cout << "The genome is:\n" << genome << '\n' << endl;

    rosalindInput.close();

    size_t k = pattern.length();
    size_t genomeLength = genome.length();
    const char* patternPointer = pattern.c_str();
    const char* genomePointer = genome.c_str();
    bool bSame;
    string startingPositions;
    startingPositions.reserve(2048);
    for (int patternLocation = 0; patternLocation < genomeLength - k + 1; ++patternLocation)
    {
        bSame = true;
        for (int base = 0; base < k; ++base)
        {
            if (*genomePointer++ != *patternPointer++)
            {
                bSame = false;
                genomePointer -= base;
                patternPointer -= (base + 1);
                break;
            }
        }

        if (bSame == true)
        {
            string startingPositon = to_string(patternLocation);
            startingPositions.append(startingPositon);
            startingPositions.push_back(' ');
            genomePointer -= (k - 1);
            patternPointer -= k;
        }
    }
	patternPointer = NULL;
	genomePointer = NULL;

    cout << "Starting positions are:\n" << startingPositions << '\n' << endl;

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);
    rosalindOutput << startingPositions << endl;

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
