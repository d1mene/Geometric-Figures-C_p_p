#include "Shape.h"

std::ostream& operator << (std::ostream& out, Shape& shape) {
	out << std::fixed << std::setprecision(1);
	shape.print(out);
	return out;
}