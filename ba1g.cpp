#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int main(void)
{
    string rosalindInputFileName;
    rosalindInputFileName.reserve(128);
    string rosalindOutputFileName;
    rosalindOutputFileName.reserve(128);

    cout << "Enter the rosalind input file's location and name:" << endl;
    cin >> setw(128) >> rosalindInputFileName;

    cout << "Enter the rosalind output file's location and name" << endl;
    cin >> setw(128) >> rosalindOutputFileName;

    cout << endl;

    auto start = std::chrono::steady_clock::now();

    string firstDNA;
    firstDNA.reserve(1024);
    string secondDNA;
    secondDNA.reserve(1024);

    ifstream rosalindInput;
    rosalindInput.open(rosalindInputFileName);
    if (!rosalindInput.is_open())
    {
        cerr << "Fail to open rosalind input file." << endl;
        return 1;
    }

    rosalindInput >> firstDNA >> secondDNA;
    cout << "The DNAs are:\n" << firstDNA << '\n' << secondDNA << '\n' << endl;

    rosalindInput.close();

    int hammingDistance = 0;
    const char* baseOfFirstDNA = firstDNA.c_str();
    const char* baseOfSecondDNA = secondDNA.c_str();
    while (*baseOfFirstDNA != '\0')
    {
        if (*baseOfFirstDNA != *baseOfSecondDNA)
        {
            hammingDistance++;
        }
        baseOfFirstDNA++;
        baseOfSecondDNA++;
    }
    baseOfFirstDNA = NULL;
    baseOfSecondDNA = NULL;

    cout << "The hamming distance is:\n" << hammingDistance << '\n' << endl;

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);
    rosalindOutput << hammingDistance << endl;

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
