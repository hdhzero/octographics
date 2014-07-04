#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "OctoGraphics.h"

using namespace std;
using namespace OctoGraphics;

int main() {
	Vertex v(4.123, 7.345, 10.2345);
	VertexFixed vf(4.123, 7.345, 10.2345, 0.0);
	Fixed p;
	p = vf * vf;

	cout << (v * v) << ' ' << p.to_float() << endl;
	return 0;
}
