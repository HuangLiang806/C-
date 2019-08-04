#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<cctype>

using namespace std;

map <string, int> cnt;
vector <string> words;

// 将传入的字符串标准化：全部变为小写，每个单词按字母序由小到大排序
string repr(const string& s)
{
    string ans = s;
    for(int i=0; i<ans.length(); i++)
        ans[i] = tolower(ans[i]);
    sort(ans.begin(), ans.end());

    return ans;
}


int main()
{
    int n = 0;
    string s;
    while(cin >> s)
    {
        if(s[0] == '#') break;
        words.push_back(s);
        string r = repr(s);
        if (cnt.count(r) == 0) cnt[r] = 0;
        else cnt[r]++;  //...
    }

    vector<string> ans;
    for(int i=0; i<words.size(); i++)
        if(cnt[repr(words[i])] == 0) ans.push_back(words[i]);
    sort(ans.begin(), ans.end());

    //print
    for (int i=0; i<ans.size(); i++)
        cout << ans[i] << endl;

    return 0;
}
