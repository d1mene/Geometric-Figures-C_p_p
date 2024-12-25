#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "Shape.h"
#include "Triangle.h"
#include "Ring.h"

class CompositeShape: public Shape {
private:
	size_t maxNumberShapes_{ 0 }, currentNumberShapes_{ 0 };
	Shape** shapeArray_{ nullptr };
public:
	CompositeShape();
	CompositeShape(int size);
	CompositeShape(const CompositeShape& otherCompShape);
	CompositeShape(CompositeShape&& otherCompShape) noexcept;

	virtual double getArea() const;
	virtual FrameRectangle getFrameRectangle() const;
	virtual void move(double k);
	virtual void move(double k, double p);
	virtual void move(Point newCenter);
	virtual void scale(double k);
	virtual CompositeShape* clone() const;
	virtual std::string getName() const;
	virtual void print(std::ostream& out) const;
	void swap(CompositeShape& otherCompShape) noexcept;

	CompositeShape& operator+=(const Shape* newShape);
	CompositeShape& operator=(const CompositeShape& otherCompShape);
	CompositeShape& operator=(CompositeShape&& otherCompShape) noexcept;

	friend std::ostream& operator << (std::ostream& out, CompositeShape& compShape);

	~CompositeShape();
};
#endif