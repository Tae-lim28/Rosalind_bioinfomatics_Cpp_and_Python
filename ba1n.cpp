#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>

using namespace std;

unordered_set<string> GenerateDNeighborhoodsRecursive(string pattern, int d)
{
    if (d < 1)
    {
        cout << "The value of d is smaller than 1." << endl;

        unordered_set<string> patternItself;
        patternItself.reserve(1);

        patternItself.insert(pattern);

        return patternItself;
    }
    else
    {
        if (pattern.size() == 1)
        {
            unordered_set<string> nucleotides;
            nucleotides.reserve(4);

            nucleotides.insert("A");
            nucleotides.insert("C");
            nucleotides.insert("G");
            nucleotides.insert("T");

            return nucleotides;
        }
        else
        {
            string shortedPattern = pattern.substr(1, pattern.size() - 1);
            unordered_set<string> dNeighborsSuffix;
            dNeighborsSuffix.reserve(128);
            dNeighborsSuffix = GenerateDNeighborhoodsRecursive(shortedPattern, d);

            unordered_set<string> dNeighborhood;
            dNeighborhood.reserve(1024);

            for (unordered_set<string>::iterator eachSequence = dNeighborsSuffix.begin(); eachSequence != dNeighborsSuffix.end(); ++eachSequence)
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

                        dNeighborhood.insert(addedString);
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

                    dNeighborhood.insert(addedString);
                }
            }

            return dNeighborhood;
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

    string pattern;
    pattern.reserve(16);
    rosalindInput >> pattern;
    cout << "The genome is:\n" << pattern << '\n' << endl;

    int d;
    rosalindInput >> d;
    cout << "The value of d is:\n" << d << '\n' << endl;

    rosalindInput.close();

    unordered_set<string> dNeighborhoods = GenerateDNeighborhoodsRecursive(pattern, d);

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);

    for (unordered_set<string>::iterator eachDNeighborhood = dNeighborhoods.begin(); eachDNeighborhood != dNeighborhoods.end(); ++eachDNeighborhood)
    {
        cout << *eachDNeighborhood << endl;
        rosalindOutput << *eachDNeighborhood << endl;
    }

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}