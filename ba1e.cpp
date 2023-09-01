#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
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

    string genome;
    genome.reserve(16384);
    int k;
    int L;
    int t;
    rosalindInput >> genome >> k >> L >> t;
    cout << "The genome is:\n" << genome << '\n' << endl;
    cout << "The value of k is:\n" << k << '\n' << endl;
    cout << "The value of L is:\n" << L << '\n' << endl;
    cout << "The value of t is:\n" << t << '\n' << endl;

    rosalindInput.close();

    size_t genomeLength = genome.length();
    unordered_map<string, int> kMerAndAppearances;
    kMerAndAppearances.reserve(1024);
    unordered_set<string> kMers;
    kMers.reserve(16);
    for (int patternLocation = 0; patternLocation < L - k + 1; ++patternLocation)
    {
        kMerAndAppearances[genome.substr(patternLocation, k)] += 1;
    }
    for (unordered_map<string, int>::iterator kMer = kMerAndAppearances.begin(); kMer != kMerAndAppearances.end(); ++kMer)
    {
        if (kMer->second >= t)
        {
            kMers.insert(kMer->first);
        }
    }

    string addedKMer;
    addedKMer.reserve(k);
    for (int windowLocation = 1; windowLocation < genomeLength - L + 1; ++windowLocation)
    {
        addedKMer = genome.substr(windowLocation + L - k, k);
        kMerAndAppearances[genome.substr(windowLocation - 1, k)] -= 1;
        kMerAndAppearances[addedKMer] += 1;
        if (kMerAndAppearances[addedKMer] >= t)
        {
            kMers.insert(addedKMer);
        }
    }

    string kMerFormingClump;
    kMerFormingClump.reserve(128);
    for (unordered_set<string>::iterator kMer = kMers.begin(); kMer != kMers.end(); ++kMer)
    {
        kMerFormingClump.append(*kMer);
        kMerFormingClump.push_back(' ');
    }

    cout << "The k-mers which form clump are:\n" << kMerFormingClump << '\n' << endl;

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);
    rosalindOutput << kMerFormingClump << endl;

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
