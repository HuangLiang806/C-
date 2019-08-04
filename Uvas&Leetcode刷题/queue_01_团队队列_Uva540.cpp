#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<algorithm>

//  待调试
using namespace std;

const int maxt = 1000 + 10;

int main()
{

    int t, kase = 0;
    while(cin>>t && t!=0)
    {
        //input
        cout << "Scenario #" << ++kase;
        map <int, int> team;
        for(int i=0; i<t; i++)
        {
            int n, x;
            cin >> n;
            while(n--)
            {
                cin >> x;
                team[x] = i;  // 记录所在团队编号
            }
        }
        //模拟团队队列
        queue<int> q, q2[maxt];
        while(true)
        {
            int x;
            string cmd;
            cin >> cmd;
            if (cmd[0] == 'S') break;
            if (cmd[0] == 'E')  //入队
            {
                cin >> x;
                int t = team[x];
                if(q2[t].empty()) q.push(t);  // 判断此团队是否在队列中，如否则入队
                q2[t].push(x);
            }
            else if (cmd[0] == 'D') //出队
            {
                int t = q.front();
                cout << q2[t].front() << endl;
                q2[t].pop();
                if(q2[t].empty()) q.pop();

            }
        }
        cout << endl;
    }

    return 0;
}
