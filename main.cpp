#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string NUMSPL1[] = {
    "zero", "one", "two", "three", "four", "five", "six",
    "seven", "eight", "nine", "ten", "eleven", "twelve",
    "thirteen", "fourteen", "fifteen", "sixteen",
    "seventeen", "eighteen", "nineteen"
};
const string NUMSPL2[] = {
    "twenty", "thirty", "forty", "fifty", "sixty",
    "seventy", "eighty", "ninety"
};
const string NUMSPL3[] = {
    "hundred", "thousand", "million", "billion", "trillion",
    "quadrillion", "quintillion", "sextillion", "septillion",
    "octillion", "nonillion", "decillion", "undecillion",
    "duodecillion", "tredecillion", "quattuordecillion", "quindecillion",
    "sexdecillion", "septendecillion", "octodecillion", "novemdecillion",
    "vigintillion"
};

string numSp(const string& num);

int main()
{
    cout << "0" << ": " << numSp("0") << "." << endl << endl;
    cout << "1204" << ": " << numSp("1204") << "." << endl << endl;
    cout << "023.456.951.743.236.125.000.012.000" << ":\n"
         << numSp("023456951743236125000012000") << "." << endl << endl;
    cout << "777.777.777.777.777.777.777.777.777.777.777.777.777.777.777."
            "777.777.777.777.777.777.777" ":\n"
         << numSp("777777777777777777777777777777777777777777777777777777"
                  "777777777777")
         << "." << endl << endl;

    return 0;
}

string numSpLt100(int n)
{
    string ret = "";
    if (n < 20)
        ret = NUMSPL1[n];
    else if (n < 100)
        ret = NUMSPL2[n/10 - 2] + (n%10 ? " " + NUMSPL1[n%10] : "");
    return ret;
}

string numSpLt1000(int n)
{
    string ret = "";
    if (n < 100)
        ret = numSpLt100(n);
    else if (n < 1000)
        ret = NUMSPL1[n/100] + " " + NUMSPL3[0] +
              (n%100 ? " " + numSpLt100(n%100) : "");
    return ret;
}

vector<int> numSpList(const string& num)
{   //   21041989 -> [989,41,21]
    //25000012000 -> [0,12,0,25]
    //          0 -> [0]
    vector<int> p;
    unsigned i = 1;
    while (num.length() > 3*i)
        p.push_back( atoi( num.substr(num.length()-3*i++, 3).c_str() ) );
    p.push_back( atoi( num.substr(0, num.length()-3*--i).c_str() ) );
    return p;
}

vector<string> numSpStrList(const vector<int>& p)
{   //[  989,41,21] -> ["...", "... thousand", "... million"]
    //[0, 12, 0,25] -> ["... thousand", "... billion"]
    //[          0] -> ["zero"] 
    vector<string> s;
    if (p.size() == 1)
        s.push_back(numSpLt1000(p[0]));
    else
        for (unsigned i = 0; i < p.size(); ++i)
            if (p[i])
                s.push_back(numSpLt1000(p[i]) + " " + NUMSPL3[i]);
    return s;
}

string numSp(const string& num)
{
    vector<int> p = numSpList(num);
    vector<string> s = numSpStrList(p);
    //join with ", " separator
    string ret = s.back();
    for (int i = s.size() - 2; i >= 0; --i)
        ret += ", " + s[i];
    return ret;
}
