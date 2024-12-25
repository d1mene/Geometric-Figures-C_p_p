#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
private:
	double x_, y_;
public:
	Point() : x_(0.0), y_(0.0) {};
	Point(double x, double y) : x_(x), y_(y) {};
	Point(const Point& ob);
	Point(Point&& otherPoint) noexcept;

	void setX(double x);
	void setY(double y);
	void move(double k);
	void move(double kX, double kY);

	double getX() const;
	double getY() const;
	double getDistance(const Point& otherDot) const;


	bool operator==(const Point& rightDot) const;
	bool operator<(const Point& rightDot) const;
	Point operator+(double k);
	Point operator+=(double k);
	Point operator-(double k);
	Point operator+(Point& rightDot);
	Point operator-(Point& rightDot);
	Point operator*(double k);
	operator double() const;
	Point& operator=(const Point& ob);
	Point& operator=(Point&& otherPoint) noexcept;

	friend std::istream& operator>> (std::istream& in, Point& dot);
	friend std::ostream& operator<< (std::ostream& out, const Point& dot);


	~Point() = default;
};

#endif