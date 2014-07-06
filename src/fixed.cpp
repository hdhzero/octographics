#include <iostream>
#include <cstdio>
#include "OctoGraphics.h"
using namespace std;
using namespace OctoGraphics;

int main() {
    Fixed n(-10.0);
    Fixed f(-100.0);
    Fixed d(2.0);
    Fixed a(1.5);
    Fixed b(-1.5);
    Fixed c = -a;
    Fixed r = d / (n - f);

    cout << r.to_float() << ' ' << r.num << endl;
    cout << a.num << ' ' << b.num << ' ' << c.num << endl;
    printf("%X %X\n", a.num, b.num);

	return 0;
}
