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

    ifstream rosalindInput;
    rosalindInput.open(rosalindInputFileName);
    if (!rosalindInput.is_open())
    {
        cout << "Fail to open rosalind input file." << endl;
        return 1;
    }

    while ((char)rosalindInput.get() != '\n')
    {

    }
    size_t k = rosalindInput.tellg();
    rosalindInput.seekg(0);

    char* firstDNA = (char*)malloc((k + 1));
    if (firstDNA == NULL)
    {
        cout << "Fail to get memories." << endl;
        rosalindInput.close();
        return 1;
    }
    memset(firstDNA, 0, k + 1);
    rosalindInput >> firstDNA;
    cout << "The first DNA is:\n" << firstDNA << '\n' << endl;

    char* secondDNA = (char*)malloc((k + 1));
    if (secondDNA == NULL)
    {
        cout << "Fail to get memories." << endl;
        rosalindInput.close();
        free(firstDNA);
        firstDNA = NULL;
        return 1;
    }
    memset(secondDNA, 0, k + 1);
    rosalindInput >> secondDNA;
    cout << "The second DNA is:\n" << secondDNA << '\n' << endl;

    rosalindInput.close();

    int hammingDistance = 0;
    const char* baseOfFirstDNA = firstDNA;
    const char* baseOfSecondDNA = secondDNA;
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
	
	free(firstDNA);
    firstDNA = NULL;
    free(secondDNA);
    secondDNA = NULL;

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
