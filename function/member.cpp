#include <iostream>
using namespace std;

class B
{
	public:
		B()
		{
			cout<<"B()"<<endl;
		}
		B(int a)
		{
			cout<<"B(int a)"<<endl;
		}
};
class A
{
	public:
		B a;
		B b;
		A()
		{
			cout<<"A()"<<endl;
			A(1,2);
		}

		A(int a,int b):a(a),b(b)
		{
			cout<<"A(int a,int b)"<<endl;
		}
};

int  main(int argc ,char ** argv)
{
	A a;
	return 0;
}
