#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <limits>

using namespace std;

int main(){

	cout << "byte" << endl;
	cout << sizeof(float) << endl;
	cout << sizeof(double) << endl;
	cout << sizeof(long double) << endl;

	cout << "vaild digits" << endl;
	cout << numeric_limits<float>::digits10 << endl;
	cout << numeric_limits<double>::digits10 << endl;
	cout << numeric_limits<long double>::digits10 << endl;

	cout << "error" << endl;
	cout << numeric_limits<float>::epsilon() << endl;
	cout << numeric_limits<double>::epsilon() << endl;
	cout << numeric_limits<long double>::epsilon() << endl;

}
