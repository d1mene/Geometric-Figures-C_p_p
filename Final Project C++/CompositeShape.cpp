#include "CompositeShape.h"

const std::string COMPOSITE_SHAPE_NAME = "COMPOSITE SHAPE";
const std::string INVALID_MAX_NUMBER = "ERROR: max number must be positive integer";
const std::string EMPTY_ARRAY_ERROR = "ERROR: no shapes in Composite Shape";
const std::string MEMORY_DUMP = "ERROR: not enough memory to allocate";
const std::string OUT_OF_RANGE_ERROR = "ERROR: the number of Shapes exceeds the maximum";


CompositeShape::CompositeShape() : maxNumberShapes_(0), currentNumberShapes_(0) {}

CompositeShape::CompositeShape(int size) : maxNumberShapes_(size), currentNumberShapes_(0) {
	if (size <= 0) {
		throw INVALID_MAX_NUMBER;
	}
	try {
		shapeArray_ = new Shape * [size];
		for (size_t i = 0; i < size; ++i) {
			shapeArray_[i] = nullptr;
		}
	}
	catch (std::bad_alloc&) {
		throw MEMORY_DUMP;
	}
}

CompositeShape::CompositeShape(const CompositeShape& otherCompShape) {

	maxNumberShapes_ = otherCompShape.maxNumberShapes_;
	currentNumberShapes_ = otherCompShape.currentNumberShapes_;

	try {
		shapeArray_ = new Shape * [maxNumberShapes_];
		for (size_t i = 0; i < currentNumberShapes_; ++i) {
			shapeArray_[i] = otherCompShape.shapeArray_[i]->clone();
		}
	}
	catch (std::bad_alloc&) {
		throw MEMORY_DUMP;
	}
}

CompositeShape::CompositeShape(CompositeShape&& otherCompShape) noexcept {

	maxNumberShapes_ = otherCompShape.maxNumberShapes_;
	currentNumberShapes_ = otherCompShape.currentNumberShapes_;
	shapeArray_ = otherCompShape.shapeArray_;

	otherCompShape.maxNumberShapes_ = 0;
	otherCompShape.currentNumberShapes_ = 0;
	otherCompShape.shapeArray_ = nullptr;

}


double CompositeShape::getArea() const {
	double compositeArea = 0.0;

	for (size_t i = 0; i < currentNumberShapes_; ++i) {
		compositeArea += shapeArray_[i]->getArea();
	}

	return compositeArea;
}

FrameRectangle CompositeShape::getFrameRectangle() const {
	if (currentNumberShapes_ > 0) {
		double maxX = shapeArray_[0]->getFrameRectangle().getHigherRightPoint().getX();
		double maxY = shapeArray_[0]->getFrameRectangle().getHigherRightPoint().getY();
		double minX = shapeArray_[0]->getFrameRectangle().getLowerLeftPoint().getX();
		double minY = shapeArray_[0]->getFrameRectangle().getLowerLeftPoint().getY();

		for (size_t i = 0; i < currentNumberShapes_; ++i) {
			double maxX_i = shapeArray_[i]->getFrameRectangle().getHigherRightPoint().getX();
			double maxY_i = shapeArray_[i]->getFrameRectangle().getHigherRightPoint().getY();
			double minX_i = shapeArray_[i]->getFrameRectangle().getLowerLeftPoint().getX();
			double minY_i = shapeArray_[i]->getFrameRectangle().getLowerLeftPoint().getY();

			if (maxX_i > maxX) {
				maxX = maxX_i;
			}
			if (minX_i < minX) {
				minX = minX_i;
			}
			if (maxY_i > maxY) {
				maxY = maxY_i;
			}
			if (minY_i < minY) {
				minY = minY_i;
			}
		}

		return FrameRectangle(maxX - minX, maxY - minY, Point((maxX - minX) / 2, (maxY - minY) / 2));
	}
	else {
		throw EMPTY_ARRAY_ERROR;
	}
}
void CompositeShape::move(double k) {
	if (currentNumberShapes_ > 0) {
		for (size_t i = 0; i < currentNumberShapes_; ++i) {
			shapeArray_[i]->move(k);
		}
	}
	else {
		throw EMPTY_ARRAY_ERROR;
	}
}

void CompositeShape::move(double k, double p) {
	if (currentNumberShapes_ > 0) {
		for (size_t i = 0; i < currentNumberShapes_; ++i) {
			shapeArray_[i]->move(k, p);
		}
	}
	else {
		throw EMPTY_ARRAY_ERROR;
	}
}

void CompositeShape::move(Point newCenter) {
	if (currentNumberShapes_ > 0) {
		Point center = this->getFrameRectangle().getCenter();
		double shiftX = newCenter.getX() - center.getX();
		double shiftY = newCenter.getY() - center.getY();

		for (size_t i = 0; i < currentNumberShapes_; ++i) {
			shapeArray_[i]->move(shiftX, shiftY);
		}
	}
	else {
		throw EMPTY_ARRAY_ERROR;
	}
}
void CompositeShape::scale(double k) {
	Point center = (*this).getFrameRectangle().getCenter();

	for (size_t i = 0; i < currentNumberShapes_; ++i) {
		shapeArray_[i]->scale(k);
		double shiftX = (k - 1) * (shapeArray_[i]->getFrameRectangle().getCenter().getX() - center.getX());
		double shiftY = (k - 1) * (shapeArray_[i]->getFrameRectangle().getCenter().getY() - center.getY());

		shapeArray_[i]->move(shiftX, shiftY);
	}
}
CompositeShape* CompositeShape::clone() const {
	return new CompositeShape(*this);
}


std::string CompositeShape::getName() const {
	return COMPOSITE_SHAPE_NAME;
}

void CompositeShape::print(std::ostream& out) const {

	for (size_t i = 0; i < currentNumberShapes_; ++i) {
		out << *shapeArray_[i] << '\n';
	}
}

void CompositeShape::swap(CompositeShape& otherCompShape) noexcept {
	std::swap(maxNumberShapes_, otherCompShape.maxNumberShapes_);
	std::swap(currentNumberShapes_, otherCompShape.currentNumberShapes_);
	std::swap(shapeArray_, otherCompShape.shapeArray_);
}


CompositeShape& CompositeShape::operator+=(const Shape* newShape) {
	if (currentNumberShapes_ < maxNumberShapes_) {
		shapeArray_[currentNumberShapes_++] = newShape->clone();
	}
	else {
		throw OUT_OF_RANGE_ERROR;
	}
	return *this;
}

CompositeShape& CompositeShape::operator=(const CompositeShape& otherCompShape) {
	if (this != &otherCompShape) {
		CompositeShape tempCompShape(otherCompShape);
		swap(tempCompShape);
	}
	return *this;
}

CompositeShape& CompositeShape::operator=(CompositeShape&& otherCompShape) noexcept {
	if (this != &otherCompShape) {
		swap(otherCompShape);

		otherCompShape.maxNumberShapes_ = otherCompShape.currentNumberShapes_ = 0;
		otherCompShape.shapeArray_ = nullptr;
	}
	return *this;
}


std::ostream& operator << (std::ostream& out, CompositeShape& compShape) {
	out << COMPOSITE_SHAPE_NAME << "\n\n";
	compShape.print(out);
	return out;
}

CompositeShape::~CompositeShape() {
	for (size_t i = 0; i < currentNumberShapes_; ++i) {
		delete shapeArray_[i];
	}
	delete[] shapeArray_;
}