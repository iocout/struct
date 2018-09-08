#include <iostream>
#include <functional>
#include <cstring>

using namespace std;

function<int (const char * )> print_func;

int print(const char * my)
{
    return strlen(my)+1;
}

class Cprint
{
  public:
    int operator()(const char * my)
    {
        return strlen(my)+1;
    }
};

int main()
{//利用function来代替相应的函数指针和函数符
    //用function来对函数指针进行包裹，让其类型安全
    print_func=print;
    cout<<"print: "<<print_func("hello world")<<endl;

    //用function来对函数符进行包裹，让其类型安全
    Cprint p;
    print_func=p;
    cout<<"Cprint: "<<print_func("hello world")<<endl;
}
