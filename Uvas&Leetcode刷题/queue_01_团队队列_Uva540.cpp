#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<algorithm>

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
                team[x] = i;  // ��¼�����Ŷӱ��
            }
        }
        //ģ���ŶӶ���
        queue<int> q, q2;
        while(true)
        {
            int x;
            string cmd;
            cin >> cmd;
            if (cmd[0] == 'S') break;
            if (cmd[0] == 'E')  //���
            {
                int t =
            }
            else if (cmd[0] == 'D') //����
            {

            }
        }
    }

    return 0;
}
