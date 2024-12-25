#include "FrameRectangle.h"

FrameRectangle::FrameRectangle(): width_(0), height_(0), center_(Point(0, 0)) {}

FrameRectangle::FrameRectangle(double width, double height, Point center): width_(width), height_(height), center_(center) {}

FrameRectangle::FrameRectangle(const FrameRectangle& otherFrameRectangle) {
	width_ = otherFrameRectangle.width_;
	height_ = otherFrameRectangle.height_;
	center_ = otherFrameRectangle.center_;
}

FrameRectangle::FrameRectangle(FrameRectangle&& otherFrameRectangle) noexcept {
	width_ = otherFrameRectangle.width_;
	height_ = otherFrameRectangle.height_;
	center_ = otherFrameRectangle.center_;

	otherFrameRectangle.width_ = 0;
	otherFrameRectangle.height_ = 0;
	otherFrameRectangle.center_ = Point();
}


double FrameRectangle::getWidth() const {
	return width_;
}

double FrameRectangle::getHeight() const {
	return height_;
}

Point FrameRectangle::getCenter() const {
	return center_;
}

Point FrameRectangle::getLowerLeftPoint() const {
	return Point(center_.getX() - width_ / 2, center_.getY() - height_ / 2);
}
Point FrameRectangle::getHigherRightPoint() const {
	return Point(center_.getX() + width_ / 2, center_.getY() + height_ / 2);
}

void FrameRectangle::setWidth(double width) {
	width_ = width;
}

void FrameRectangle::setHeight(double height) {
	height_ = height;
}

void FrameRectangle::setCenter(Point center) {
	center_ = center;
}


void FrameRectangle::swap(FrameRectangle& otherFrameRectangle) noexcept {
	std::swap(width_, otherFrameRectangle.width_);
	std::swap(height_, otherFrameRectangle.height_);
	std::swap(center_, otherFrameRectangle.center_);
}


FrameRectangle& FrameRectangle::operator=(const FrameRectangle& otherFrame) {
	if (this != &otherFrame) {
		FrameRectangle tempFrame(otherFrame);
		swap(tempFrame);
	}
	return *this;
}

FrameRectangle& FrameRectangle::operator=(FrameRectangle&& otherFrame) noexcept {
	if (this != &otherFrame) {
		swap(otherFrame);

		otherFrame.width_ = otherFrame.height_ = 0;
		otherFrame.center_ = Point();
	}
	return *this;
}