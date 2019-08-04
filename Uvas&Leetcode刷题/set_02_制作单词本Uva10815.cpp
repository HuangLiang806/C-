#include<iostream>
#include<string>
#include<set>
#include<sstream>

using namespace std;

set <string> dict;

int main()
{
    string s, buf;
    while(s != "quit")
    {
        cin >> s;
        for (int i=0; i<s.length(); i++)
            if (isalpha(s[i])) s[i] = tolower(s[i]); else s[i] = ' ';

        stringstream ss(s);
        while(ss >> buf) dict.insert(buf);
    }
    // output
    int i = 0;
    for(set<string>::iterator it=dict.begin(); it!=dict.end(); it++, i++)
        cout << *it << " ";
        if (i%10 == 0)  cout << "\n";

    return 0;
}
