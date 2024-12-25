#ifndef FRAME_RECTANGLE_H
#define FRAME_RECTANGLE_H

#include "Point.h"

class FrameRectangle {
private:
	double width_, height_;
	Point center_;
public:
	FrameRectangle();
	FrameRectangle(double width, double height, Point center);
	FrameRectangle(const FrameRectangle& otherFrameRectangle);
	FrameRectangle(FrameRectangle&& otherFrameRectangle) noexcept;

	double getWidth() const;
	double getHeight() const;
	Point getCenter() const;
	Point getLowerLeftPoint() const;
	Point getHigherRightPoint() const;

	void setWidth(double width);
	void setHeight(double height);
	void setCenter(Point center);

	void swap(FrameRectangle& otherFrameRectangle) noexcept;

	FrameRectangle& operator=(const FrameRectangle& otherFrame);
	FrameRectangle& operator=(FrameRectangle&& otherFrame) noexcept;

	~FrameRectangle() = default;
};

#endif