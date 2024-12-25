#include "Point.h"

#include <cmath>
#include <iostream>
#include <string>

const std::string INPUT_ERROR = "ERROR: invalid input";

Point::Point(const Point& ob) {
	x_ = ob.x_;
	y_ = ob.y_;
}

Point::Point(Point&& otherPoint) noexcept: x_(otherPoint.x_), y_(otherPoint.y_) {
	otherPoint.x_ = 0;
	otherPoint.y_ = 0;
}

void Point::setX(double x) {
	x_ = x;
}

void Point::setY(double y) {
	y_ = y;
}

void Point::move(double k) {
	x_ += k;
	y_ += k;
}

void Point::move(double kX, double kY) {
	x_ += kX;
	y_ += kY;
}

double Point::getX() const {
	return x_;
}

double Point::getY() const {
	return y_;
}

bool Point::operator==(const Point& rightDot) const {
	return (x_ == rightDot.x_) && (y_ == rightDot.y_);
}

bool Point::operator<(const Point& rightDot) const {
	return ((*this).x_ + this->y_ < rightDot.y_ + rightDot.x_);
}

Point Point::operator+(double k) {
	return Point(this->x_ + k, (*this).y_ + k);
}

Point Point::operator+=(double k) {
	this->x_ += k;
	(*this).y_ += k;

	return *this;
}

Point Point::operator-(double k) {
	return Point(this->x_ - k, (*this).y_ - k);
}

Point Point::operator+(Point& rightDot) {
	return Point(x_ + rightDot.x_, y_ + rightDot.y_);
}

Point Point::operator-(Point& rightDot) {
	return Point(x_ + rightDot.x_, y_ + rightDot.y_);
}

Point Point::operator*(double k) {
	return Point(x_ * k, y_ * k);
}

Point::operator double() const {
	return std::sqrt(x_ * x_ + y_ * y_);
}

double Point::getDistance(const Point& otherDot) const {
	return std::sqrt(std::pow((x_ - otherDot.x_), 2) + std::pow((y_ - otherDot.y_), 2));
}

std::istream& operator >> (std::istream& in, Point& dot) {
	if (!(in >> dot.x_ >> dot.y_)) {
		throw INPUT_ERROR;
	}
	return in;
}

std::ostream& operator<< (std::ostream& out, const Point& dot) {
	return (out << '(' << dot.x_ << ',' << dot.y_ << ')');
}

Point& Point::operator=(const Point& ob) {
	if (*this != ob) {
		x_ = ob.x_;
		y_ = ob.y_;
	}
	return *this;
}

Point& Point::operator=(Point&& otherPoint) noexcept {
	if (*this != otherPoint) {
		x_ = otherPoint.x_;
		y_ = otherPoint.y_;

		otherPoint.x_ = 0;
		otherPoint.y_ = 0;
	}

	return *this;
}