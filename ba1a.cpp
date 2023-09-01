#include <iostream>
#include <iomanip>
#include <fstream>

# define fileNameLength (128)

using namespace std;

int main(void)
{
    char rosalindInputFileName[fileNameLength];
    char rosalindOutputFileName[fileNameLength];

    cout << "Enter the rosalind input file's location and name:" << endl;
    cin >> setw(fileNameLength) >> rosalindInputFileName;

    cout << "Enter the rosalind output file's location and name\n";
    cin >> setw(fileNameLength) >> rosalindOutputFileName;

    cout << endl;

    ifstream rosalindInput;
    rosalindInput.open(rosalindInputFileName);

    char text[2048];
    rosalindInput >> setw(2048) >> text;
    cout << "The text is:\n" << text << '\n' << endl;

    char pattern[32];
    rosalindInput >> setw(32) >> pattern;
    cout << "The pattern is:\n" << pattern << '\n' << endl;
    
    /*rosalindInput.getline(text, 2048, '\n'); /*https://cplusplus.com/reference/istream/istream/getline/
    
    char pattern[32];
    rosalindInput.getline(pattern, 32, '\n');*/
    
    rosalindInput.close();

    size_t k = strlen(pattern);
    size_t textLength = strlen(text);
    bool bSame = true;
    int count = 0;
    char* textPointer = text;
    char* patternPointer = pattern;
    for (int patternLocation = 0; patternLocation < textLength - k + 1; ++patternLocation)
    {
        bSame = true;
        for (int base = 0; base < k; ++base)
        {
            if (*textPointer++ != *patternPointer++)
            {
                bSame = false;
                textPointer -= base;
                patternPointer -= (base + 1);
                break;
            }
        }

        if (bSame == true)
        {
            count += 1;
            textPointer -= (k - 1);
            patternPointer -= k;
        }
    }

    cout << "The count is:\n" << count << '\n' << endl;

    ofstream rosalindOutput;
    rosalindOutput.open(rosalindOutputFileName);
    rosalindOutput << count << endl;
    
    rosalindOutput.close();
    cout << "Writing rosalind output is done." << endl;

    return 0;
}