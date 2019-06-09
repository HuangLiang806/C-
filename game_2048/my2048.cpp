#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <curses.h>
using namespace std;

#define N 4  //游戏界面的长宽格子数
#define WIDTH  5  //每个格子的宽度
#define SUCCESS  2048  //成功条件

/*游戏状态*/
#define FAIL 0
#define WIN 1
#define NORMAL 2
#define QUIT 3

class My2048
{
public:
    /* 获取游戏状态 */
    int getStatus();
    /* 处理键盘输入*/
    void input();
    // 打印游戏界面
    void draw();
    void restart();
    //void setTestData();
private:
    //判断是否结束
    bool isOver();
    bool moveLeft();
    //将游戏矩阵逆时针旋转90°
    void rotate();
    //随机生成新的数值，2或4，4的出现概率为10%
    bool randNew();
    void drawItem(int row, int col, char c);
    void drawNum(int row, int col, int num);
private:
    int data[N][N];
    int status;    
};



void My2048::draw()
{
    clear();
    const int offset =12;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            // 打印交点字符
            drawItem(i*2, 1+j*WIDTH+offset,'+');
            // 打印竖线
            if (i != N) drawItem(i*2+1,1+j*WIDTH+offset, '|');
            //打印横线
            for(int k=1; j!=N && k<WIDTH; k++) drawItem(i*2, 1+j*WIDTH+k+offset, '-');

            //打印数字
            if(i != N && j != N)
            {
                drawNum(i*2+1, (j+1)*WIDTH+offset, data[i][j]);
            }
        }       
    }
    //打印提示信息
     mvprintw(2 * N + 2, (5 * (N - 4) - 1) / 2, "W(UP),S(DOWN),A(LEFT),D(RIGHT),R(RESTART),Q(QUIT)");
        mvprintw(2 * N + 3, 12 + 5 * (N - 4) / 2, "enjoy it , from HL.");
        if (status == WIN)
        {
            mvprintw( N, 5 * N / 2 - 1, " YOU WIN,PRESS R TO CONTINUE ");
        } 
        else if (status == FAIL) 
        {
            mvprintw( N, 5 * N / 2 - 1, " YOU LOSE,PRESS R TO CONTINUE ");
        }
}

bool My2048::isOver()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if ((j + 1 < N) && (data[i][j] * data[i][j+1] == 0 || data[i][j] == data[i][j+1])) return false;
            if ((i + 1 < N) && (data[i][j] * data[i+1][j] == 0 || data[i][j] == data[i+1][j])) return false;
        }
    }
    return true;
}

bool My2048::moveLeft()
{
    int temp[N][N];
    for (int i =0; i<N; i++)
    {
        int current = 0;
        int lastValue = 0;
        for(int j=0; j<N; j++)
        {
            temp[i][j] = data[i][j];

            if(data[i][j] == 0) continue;

            if(lastValue == 0) lastValue = data[i][j];
            else
            {
                if(lastValue == data[i][j])
                {
                    data[i][current] = lastValue *2;
                    lastValue = 0;
                    if(data[i][current] == SUCCESS)
                        status = WIN;                   
                }
                else
                {
                    data[i][current] = lastValue;
                    lastValue = data[i][j];                 
                }
                current++;
            }
            data[i][j] = 0;
        }
        if(lastValue != 0) data[i][current] = lastValue;
    }

    //检测是否发生变化
    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
    {
        if(data[i][j] != temp[i][j]) return true;
    }
    return false;

}


//逆时针旋转90°
void My2048::rotate()
{
    int temp[N][N] = {0};
    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
        temp[i][j] = data[j][N-1-i];

    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
        data[i][j] = temp[i][j];

}

void My2048::restart()
{
    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
        data[i][j] = 0;
    randNew();
    status = NORMAL;
}

bool My2048::randNew()
{
    vector<int> emptyPos;

    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
        if (data[i][j] == 0) emptyPos.push_back(i*N + j);

    if(emptyPos.size() == 0) return false;
    int value = emptyPos[rand()%emptyPos.size()];
    data[value / N][value % N] = rand()%10==1?4:2;
    return true;
}

void My2048:: drawItem(int row, int col, char c) 
{
    move(row, col);
    addch(c);
}

void My2048:: drawNum(int row, int col, int num) 
{
    while (num > 0) 
    {
        drawItem(row, col, num % 10 + '0');
        num /= 10;
        --col;
    }
}

void My2048::input() {
    char ch = getch();
    // 转化成大写
    if (ch >= 'a' && ch <= 'z') {
        ch -= 32;
    }
    if (status == NORMAL) {
        bool updated = false;
        if (ch == 'A') {
            updated = moveLeft();
        } else if (ch == 'S') {
            // 向下移动 = 旋转270度，向左移动，再旋转90度
            rotate();
            rotate();
            rotate();
            updated = moveLeft();
            rotate();
        } else if (ch == 'D') {
            rotate();
            rotate();
            updated = moveLeft();
            rotate();
            rotate();
        } else if (ch == 'W') {
            rotate();
            updated = moveLeft();
            rotate();
            rotate();
            rotate();
        }
        if (updated) {
            randNew();
            if (isOver()) {
                status = FAIL;
            }
        }
    }
    if (ch == 'Q') {
        status = QUIT;
    } else if (ch == 'R') {
        restart();
    }
}


int My2048::getStatus()
{
    return status;
}


void init()
{
    //初始化ncurse库
    initscr();
    //设置按键不需要回车直接交互
    cbreak;
    //不显示按键
    noecho();
    //隐藏光标
    curs_set(0);
    //随机
    srand(time(NULL));
}

void exit()
{
    endwin();
}


int main()
{
    init();
    My2048 game;
    game.restart();
    do
    {
        game.draw();
        game.input();   

    }while(QUIT != game.getStatus());

    exit();
    return 0;
}
