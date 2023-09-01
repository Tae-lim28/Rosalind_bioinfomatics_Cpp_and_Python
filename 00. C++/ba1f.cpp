#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

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

    string genome;
    genome.reserve(16384);
    rosalindInput >> genome;
    cout << "The genome is:\n" << genome << '\n' << endl;

    rosalindInput.close();

    vector<int> skew;
    skew.reserve(genome.size() + 1);
    
    const char* base = genome.c_str();
    skew.push_back(0);
    int mimimumSkew = INT_MAX;
    for (int currentSkew = 1; currentSkew < skew.capacity(); ++currentSkew)
    {
        if (*base == 'C')
        {
            skew.push_back(skew[currentSkew - 1] - 1);
            base++;

            if (skew[currentSkew] < mimimumSkew)
            {
                mimimumSkew = skew[currentSkew];
            }
        }
        else if (*base == 'G')
        {
            skew.push_back(skew[currentSkew - 1] + 1);
            base++;
        }
        else
        {
            skew.push_back(skew[currentSkew - 1]);
            base++;
        }
    }
    base = NULL;

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);

    cout << "Integers minimizing skew are:" << endl;
    int skewIndex = 0;
    for (int eachSkew = 0; eachSkew < skew.size(); ++eachSkew)
    {
        if (skew[eachSkew] == mimimumSkew)
        {
            cout << skewIndex << ' ';
            rosalindOutput << skewIndex << ' ';
        }
        skewIndex++;
    }
    cout << '\n' << endl;
    rosalindOutput << endl;

    rosalindOutput.close();
    cout << "Writing rosalind output is done." << '\n' << endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
