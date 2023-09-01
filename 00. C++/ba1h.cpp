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

    string pattern;
    pattern.reserve(16);
    string text;
    text.reserve(16384);
    int d;

    ifstream rosalindInput;
    rosalindInput.open(rosalindInputFileName);

    rosalindInput >> pattern >> text >> d;
    cout << "The pattern is:\n" << pattern << '\n' << endl;
    cout << "The text is:\n" << text << '\n' << endl;
    cout << "The vlaue of d is:\n" << d << '\n' << endl;

    rosalindInput.close();

    const char* patternBase = pattern.c_str();
    const char* textBase = text.c_str();
    size_t k = pattern.length();
    size_t textLength = text.length();
    string startingPositions;
    startingPositions.reserve(2048);
    int hammingDistance = 0;
    for (int patternLocation = 0; patternLocation < textLength - k + 1; ++patternLocation)
    {
        hammingDistance = 0;
        for (int base = 0; base < k; ++base)
        {
            /*if (hammingDistance > d)
            {
                patternBase -= base;
                textBase -= (base - 1);
                break;
            } 이거 넣는게 더 느린 것 같아서 주석처리함. 이거 있을 때는 0.2XXX초 정도 걸림*/

            /*빼니까 0.1XXX초 정도 걸림*/

            if (*patternBase != *textBase)
            {
                hammingDistance++;
            }

            patternBase++;
            textBase++;
        }

        if (hammingDistance <= d)
        {
            string currentPosition = to_string(patternLocation); /*이걸 없애니까 조금 빠르긴 한데 아주 큰 차이는 아니다.*/
            startingPositions.append(to_string(patternLocation));
            startingPositions.push_back(' ');
        }

        patternBase -= k;
        textBase -= (k - 1);
    }
    patternBase = NULL;
    textBase = NULL;

    cout << "Strating positions are:\n" << startingPositions << '\n' << endl;

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
