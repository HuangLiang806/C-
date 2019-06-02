#include <iostream>

using namespace std;

// 基类
/*NOTE：public可在类外访问,protect只可在类内访问,
private仅可在类内访问且其子类不可访问*/
class Shape
{
   public:
      void setWidth(int w)
      {
         width = w;
      }
      void setHeight(int h)
      {
         height = h;
      }

      /*虚函数，如去掉virtual则54行将调用父类的getArea。
         Python中则子类覆盖掉父类的同名方法。*/
      int virtual getArea()  //
      {
          cout<<"in area"<<endl;
          return 0;
      }
   protected:
      int width;
      int height;
};

// 派生类
/*NOTE:通常使用public继承，public继承下子类可在类内访问父类的public和private
可在类外访问父类的public，不可在类外访问父类的private；*/
class Rectangle: public Shape
{
   public:
      int getArea()
      {
         return (width * height);
      }
};

int main(void)
{
   Rectangle son;

   son.setWidth(5);
   son.setHeight(7);

   // 输出对象的面积
   cout << "Total area: " << son.getArea() << endl;
   Shape *p = &son;
   cout <<"area:"<<p->getArea()<<endl;

   return 0;
}
