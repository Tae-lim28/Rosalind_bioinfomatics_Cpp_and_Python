#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_set<string> GenerateDNeighborhoodsRecursive(string pattern, int d)
{
    if (d < 1)
    {
        cout << "The value of d is smaller than 1." << endl;

        unordered_set<string> givingSequence;
        givingSequence.reserve(1);

        givingSequence.insert(pattern);

        return givingSequence;
    }
    else
    {
        if (pattern.size() == 1)
        {
            unordered_set<string> oneBaseSequences;
            oneBaseSequences.reserve(4);

            oneBaseSequences.insert("A");
            oneBaseSequences.insert("C");
            oneBaseSequences.insert("G");
            oneBaseSequences.insert("T");

            return oneBaseSequences;
        }
        else
        {
            string shortedPattern = pattern.substr(1, pattern.size() - 1);
            unordered_set<string> givenSequences;
            givenSequences.reserve(128);
            givenSequences = GenerateDNeighborhoodsRecursive(shortedPattern, d);

            unordered_set<string> givingSequences;
            givingSequences.reserve(1024);

            for (unordered_set<string>::iterator eachSequence = givenSequences.begin(); eachSequence != givenSequences.end(); ++eachSequence)
            {
                int hammingDistance = 0;
                const char* givenBase = (*eachSequence).c_str();
                const char* patternBase = pattern.c_str();
                patternBase++;

                while (*patternBase != '\0')
                {
                    if (*patternBase != *givenBase)
                    {
                        hammingDistance++;
                    }

                    patternBase++;
                    givenBase++;
                }
                givenBase = NULL;
                patternBase = NULL;


                if (hammingDistance < d)
                {
                    const string BASES = "ACGT";
                    for (int baseOrder = 0; baseOrder < 4; ++baseOrder)
                    {
                        string addedString;
                        addedString.reserve(16);
                        addedString.push_back(BASES[baseOrder]);

                        givenBase = (*eachSequence).c_str();
                        while (*givenBase != '\0')
                        {
                            addedString.push_back(*givenBase);
                            givenBase++;
                        }
                        givenBase = NULL;

                        givingSequences.insert(addedString);
                    }
                }
                else
                {
                    string addedString;
                    addedString.reserve(16);
                    addedString.push_back(pattern[0]);

                    givenBase = (*eachSequence).c_str();
                    while (*givenBase != '\0')
                    {
                        addedString.push_back(*givenBase);
                        givenBase++;
                    }
                    givenBase = NULL;

                    givingSequences.insert(addedString);
                }
            }

            return givingSequences;
        }
    }
}

int main(void)
{
    string rosalindInputFileName;
    rosalindInputFileName.reserve(128);
    string rosalindOutputFileName;
    rosalindOutputFileName.reserve(128);

    cout << "Enter the rosalind input file's location and name:" << endl;
    cin >> rosalindInputFileName;

    cout << "Enter the rosalind output file's location and name" << endl;
    cin >> rosalindOutputFileName;

    cout << endl;

    auto start = std::chrono::steady_clock::now();

    ifstream rosalindInput;
    rosalindInput.open(rosalindInputFileName);
    if (!rosalindInput.is_open())
    {
        cerr << "Fail to open rosalind input file." << endl;
        return 1;
    }

    string text;
    text.reserve(1024);
    rosalindInput >> text;
    cout << "The text is:\n" << text << '\n' << endl;

    int k;
    rosalindInput >> k;
    cout << "The value of k is:\n" << k << '\n' << endl;

    int d;
    rosalindInput >> d;
    cout << "The value of d is:\n" << d << '\n' << endl;

    rosalindInput.close();

    unordered_map<string, int> dNeighborsAndCounts;
    dNeighborsAndCounts.reserve(1024);
    size_t textLength = text.length();
    for (int subTextLocation = 0; subTextLocation < textLength - k + 1; ++subTextLocation)
    {
        string subText;
        subText.reserve(k);
        subText = text.substr(subTextLocation, k);
        unordered_set<string> dNeighbors = GenerateDNeighborhoodsRecursive(subText, d);

        for (unordered_set<string>::iterator eachDNeighbor = dNeighbors.begin(); eachDNeighbor != dNeighbors.end(); ++eachDNeighbor)
        {
            dNeighborsAndCounts[*eachDNeighbor] += 1;
        }
    }

    int maximumCount = 0;
    for (unordered_map<string, int>::iterator eachDNeighborAndCount = dNeighborsAndCounts.begin(); eachDNeighborAndCount != dNeighborsAndCounts.end(); ++eachDNeighborAndCount)
    {
        if (eachDNeighborAndCount->second > maximumCount)
        {
            maximumCount = eachDNeighborAndCount->second;
        }
    }

    string mostFrequentKMers;
    mostFrequentKMers.reserve(128);
    for (unordered_map<string, int>::iterator eachDNeighborAndCount = dNeighborsAndCounts.begin(); eachDNeighborAndCount != dNeighborsAndCounts.end(); ++eachDNeighborAndCount)
    {
        if (eachDNeighborAndCount->second == maximumCount)
        {
            const char* addedBase = eachDNeighborAndCount->first.c_str();
            for (int base = 0; base < k; ++base)
            {
                mostFrequentKMers.push_back(*addedBase);
                addedBase++;
            }
            addedBase = NULL;
            mostFrequentKMers.push_back(' ');
        }
    }

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);

    cout << "The most frequent k-mers are:\n" << mostFrequentKMers << '\n' << endl;
    rosalindOutput << mostFrequentKMers << endl;

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
