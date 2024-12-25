#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include "Shape.h"

class Triangle: public Shape {
private:
	Point a_, b_, c_, center_;
	double ab_, bc_, ac_;
public:
	Triangle();
	Triangle(Point a, Point b, Point c);
	Triangle(const Triangle& triangle);
	Triangle(Triangle&& triangle) noexcept;

	void setA(Point a);
	void setB(Point b);
	void setC(Point c);

	Point getA() const;
	Point getB() const;
	Point getC() const;
	Point getTriangleCenter() const;

	double getAB() const;
	double getBC() const;
	double getAC() const;

	bool isTriangle() const;
	double getPerimeter() const;
	void swap(Triangle& triangle) noexcept;

	virtual double getArea() const override;
	virtual FrameRectangle getFrameRectangle() const override;
	virtual void move(double k) override;
	virtual void move(double k, double p) override;
	virtual void move(Point newCenter) override;
	virtual void scale(double k) override;
	virtual Triangle* clone() const override;
	virtual std::string getName() const override;
	virtual void print(std::ostream& out) const override;

	bool operator==(const Triangle& triangle) const;
	bool operator<(const Triangle& triangle) const;
	void operator+=(double k);
	Triangle& operator=(const Triangle& triangle);
	Triangle& operator=(Triangle&& triangle) noexcept;

	friend std::istream& operator >> (std::istream& in, Triangle& triangle);
	friend std::ostream& operator << (std::ostream& out, const Triangle& triangle);

	~Triangle() = default;
};

#endif