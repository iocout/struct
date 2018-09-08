/**
* @projectName   c11_bind
* @brief        bind函数能够对函数
*               所有的参数进行绑定
*               ，用这种方法可以更
*               方便的交换参数，对
*               参数进行判断。
*               值得注意的是bind返
*               回值是可调用实体，
*               可以直接调用functi
*               -on函数。
* @author        HF
* @date          2018-09-06
*/

#include <iostream>
#include <functional>
#include <ostream>


using namespace  std;

void Func(int a,int b)
{
    cout<<"a : "<<a<<" b: "<<b<<endl;
}

class A
{
public:
    void Func(int a,int b)
    {
        cout<<"a : "<<a<<" b: "<<b<<endl;
    }
};

int main()
{
    //对普通函数进行赋值
    auto bf1=bind(Func,placeholders::_1,placeholders::_2);
    bf1(1,2);//赋值并调用


    //交换参数值，注意其返回值是一个带参数的函数实体。
    function<void(int,int )>  bf2=bind(Func,placeholders::_2,placeholders::_1);
    bf2(1,2);

    //对类成员函数进行赋值
    A a;
    auto bf3=bind(&A::Func,a,placeholders::_1,100);
    bf3(10);
}
