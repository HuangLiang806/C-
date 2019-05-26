#include <iostream>
#include <cstring>
using namespace std;

/* __author__ = "huangliang"

*/

class Student
{
private:
    int _num;
    char _name[20];
    int _score;
    int _math_score;
public:
    int num = 123;
    Student(int num, char *name, int score);  // 构造函数
    ~Student();  // 析构函数
    Student(Student &a);  // 拷贝构造函数
    int print();
    friend class Teacher;
    friend int friend_f(Student &a); // 友元函数（类），不能使用this，不可继承，可访问内部私有变量。
};


int Student::print()
{
    cout<<"name:"<<_name<<endl;
    cout<<"number:"<<_num<<endl;
    cout<<"score:"<<_score<<endl;
    return 0;
}
/* 构造函数，类似于Python中的__init__方法
无返回值，名字与类名相同*/
Student::Student(int num, char *name, int score)
{
    _num = num;
    strcpy(_name, name);
    _score = score;
}

/*析构函数, 类似于Python中的__del__方法*/
Student::~Student()
{
    cout<<_name<<"实例被销毁"<<endl;
}

/*拷贝构造函数，用于实例之间的初始化
深拷贝：开辟内存
浅拷贝：新建指针指向原内存*/
Student::Student(Student &a)
{
    cout<<"我们现在正在利用一个实例初始化另外一个实例"<<endl;
    this->_num = a._num+1;  // this 指针相当于Python中的Self参数，指向对象本身
    strcpy(this->_name, "UnKnow");  // 啰嗦。。。不能直接赋值
    this->_score = 0;
}

/*友元函数, 记得加&引用
可访问类中的私有变量*/
int friend_f(Student &a)
{
    cout<<"in friend，print num:"<<a._num<<endl;
    return 0;
}


class Teacher
{
public:
    set_score(Student &a)
    {
        cout<<"请输入学号为"<<a._num<<"同学的成绩："<<endl;
        cin>>a._score;
    }

};


/*继承的三种情况
1.公有继承：
*/
class MathTeacher:public Teacher //注意public
{
    ;
};


int main()
{
    Student a(1, "jack", 76);
    a.print();
    Student b(a);
    b.print();
    //cout<<a._num<<"---------test------"<<endl;  //不能访问内部私有变量
    friend_f(a);

    Teacher prof;
    prof.set_score(a);
    a.print();

    //继承
    MathTeacher Mr_Li;
    Mr_Li.set_score(a);
    a.print();

    return 0;
}
