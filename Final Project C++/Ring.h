#ifndef RING_H
#define RING_H

#include "Shape.h"
#include "Point.h"

class Ring : public Shape {
private:
	double radius1_, radius2_;
	Point center_;
public:
	Ring();
	Ring(Point center, double r1, double r2);
	Ring(const Ring& otherRing);
	Ring(Ring&& otherRing) noexcept;

	double getOuterRadius() const;
	double getInnerRadius() const;
	Point getCenter() const;

	void setOuterRadius(double r1);
	void setInnerRadius(double r2);
	void setCenter(Point newCenter);

	void swap(Ring& newRing);

	virtual double getArea() const override;
	virtual FrameRectangle getFrameRectangle() const override;
	virtual void move(double k) override;
	virtual void move(double k, double p) override;
	virtual void move(Point newCenter) override;
	virtual void scale(double k) override;
	virtual Ring* clone() const override;
	virtual std::string getName() const override;
	virtual void print(std::ostream& out) const override;
	
	Ring& operator=(const Ring& otherRing);
	Ring& operator=(Ring&& otherRing) noexcept;

	friend std::istream& operator >> (std::istream& in, Ring& ring);
	friend std::ostream& operator << (std::ostream& out, const Ring& ring);

	~Ring() = default;
};
#endif 