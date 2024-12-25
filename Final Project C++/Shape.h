#ifndef SHAPE_H
#define SHAPE_H

#include "FrameRectangle.h"
#include <string>
#include <iostream>
#include <iomanip>

class Shape {
public:
	virtual double getArea() const = 0;
	virtual FrameRectangle getFrameRectangle() const = 0;
	virtual void move(double k) = 0;
	virtual void move(double k, double p) = 0;
	virtual void move(Point newCenter) = 0;
	virtual void scale(double k) = 0;
	virtual Shape* clone() const = 0;
	virtual std::string getName() const = 0;
	virtual void print(std::ostream& out) const = 0;

	friend std::ostream& operator << (std::ostream& out, Shape& shape);
	virtual ~Shape() = default;
};
#endif