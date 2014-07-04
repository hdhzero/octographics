#include <iostream>
#include "OctoGraphics.h"
using namespace std;
using namespace OctoGraphics;

int main() {
	Fixed d(-3.1415, 16, 16);
	Fixed e(-7.4578, 16, 16);
	Fixed f;
	Fixed f2;
	Fixed g(0.015625, 16, 16);
	Fixed h(0.0078125, 16, 16);
	double k = 3.141592;

	f = d * e;
	f2 = d / e;
	cout << f.num << ' ' << f2.num << endl;
	cout << f.to_float() << ' ' << f2.to_float() << endl;
	cout << g.to_float() << endl;
	cout << h.to_float() << endl;

/*	for (int i = 0; i < 16; ++i) {
		Fixed p(k, 6, 26);
		cout << i << ": " << k << ' ' << p.to_float() << ' ' << p.num << ' ' << (k - p.to_float()) << endl;
		k *= 0.5;
	}*/

	return 0;
}
