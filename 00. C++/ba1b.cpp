#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
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

    string text;
    rosalindInput >> text;
    cout << "The text is:\n" << text << '\n' << endl;

    int k;
    rosalindInput >> k;
    cout << "The value of k is:\n" << k << '\n' << endl;

    rosalindInput.close();

    size_t textLength = text.length();
    map<string, int> kMerAndAppearances;
    for (int patternLocation = 0; patternLocation < textLength - k + 1; ++patternLocation)
    {
        kMerAndAppearances[text.substr(patternLocation, k)] += 1;
    }

    int maximumAppearance = 0;
    for (map<string, int>::iterator eachKMerAndAppearance = kMerAndAppearances.begin(); eachKMerAndAppearance != kMerAndAppearances.end(); ++eachKMerAndAppearance)
    {
        if (eachKMerAndAppearance->second > maximumAppearance)
        {
            maximumAppearance = eachKMerAndAppearance->second;
        }
    }

    string mostFrequentKMers;
    mostFrequentKMers.reserve(256);
    for (map<string, int>::iterator eachKMerAndAppearance = kMerAndAppearances.begin(); eachKMerAndAppearance != kMerAndAppearances.end(); ++eachKMerAndAppearance)
    {
        if (eachKMerAndAppearance->second == maximumAppearance)
        {
            const char* addedbase = eachKMerAndAppearance->first.c_str();
            for (int base = 0; base < k; ++base)
            {
                mostFrequentKMers.push_back(*addedbase++);
            }
            mostFrequentKMers.push_back(' ');
        }
    }

    cout << "The most frequent k-mers are:\n" << mostFrequentKMers << '\n' << endl;

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);
    rosalindOutput << mostFrequentKMers << endl;

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
