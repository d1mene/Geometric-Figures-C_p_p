#include <iostream>
#include <sstream>
#include <string>

#include "Shape.h"
#include "Triangle.h"
#include "Ring.h"
#include "CompositeShape.h"
#include "Support.h"

void clearConsole();

void inTriangle(Triangle& triangle);
void outTriangle(const Triangle& newTriangle, const Triangle* oldTriangle);
void inRing(Ring& ring);
void outRing(Ring& const newRing, const Ring* oldRing);
void moveShape(Shape& shape, std::string option);
void scaleShape(Shape& shape);
void processError(const std::string& error, std::string& input);

int main() {
	int k = 0;
	std::string input;

	while (true) {
		clearConsole();
		std::cout << "Enter the option:\n" << "1 - Test Geometric Figures;\n" << "2 - Test Figure Scaling;\n"
			<< "3 - Test Composite Shape;\n" << "Press any other key to quit\n";

		std::getline(std::cin, input);

		
		try {
			k = std::stoi(input);
			if (k != std::stod(input) || k < 1 || k > 3) {
				std::cout << "Exiting..." << '\n';
				break;
			}
		}
		catch (std::invalid_argument&) {
			std::cout << "Exiting..." << '\n';
			break;
		}
		catch (std::out_of_range&) {
			std::cout << "Exiting..." << '\n';
			break;
		}

		k = std::stod(input);

		switch (k) {
		case 1:
			clearConsole();
			std::cout << "Test Geometric Figures:\n\n";
			std::cout << "Enter figure option:\nt - Triangle,\nr - Ring;\nPress any other key to go back to Test options;\n";

			std::getline(std::cin, input);
			clearConsole();

			if (input == "t") {

				Triangle triangle;
				Point newCenter;

				try {
					inTriangle(triangle);

					Triangle* triangleCopy = triangle.clone();
					std::cout << "Enter the value(s) to move the Triangle on: ";

					moveShape(triangle, MOVE_OPTION_SHIFT);
					outTriangle(triangle, triangleCopy);

					Triangle* triangleCopy2 = triangle.clone();

					std::cout << "Enter the point to move the center of the Triangle: ";

					moveShape(triangle, MOVE_OPTION_POINT);
					outTriangle(triangle, triangleCopy2);
					std::cout << "\n\n";

					std::cout << "Final Triangle: " << triangle << "\n\n" << "Initial Triangle: " << *triangleCopy << "\n\n";

					std::cout << "Press any key to continue\n";
					std::getline(std::cin, input);
				}
				catch (const std::string& error) {
					processError(error, input);
				}
			}


			else if (input == "r") {

				Ring ring;
				Point newCenter;
				double shift = 0.0;
				double shiftY = 0.0;
				bool xyMove = false;

				try {
					inRing(ring);

					Ring* ringCopy = ring.clone();
					std::cout << "Enter the value(s) to move the Ring on: ";

					moveShape(ring, MOVE_OPTION_SHIFT);
					outRing(ring, ringCopy);


					Ring* ringCopy2 = ring.clone();

					std::cout << "Enter the point to move the center of the Ring: ";

					moveShape(ring, MOVE_OPTION_POINT);
					outRing(ring, ringCopy2);
					std::cout << "\n\n";

					std::cout << "Final Ring: " << ring << "\n\n" << "Initial Ring: " << *ringCopy << "\n\n";
					std::cout << "Press any key to continue\n";
					std::getline(std::cin, input);
				}
				catch (const std::string& error) {
					processError(error, input);
				}
			}
			break;

		case 2:
			clearConsole();
			std::cout << "Test Figure Scaling:\n\n";
			std::cout << "Enter figure to scale:\nt - Triangle,\nr - Ring;\nPress any other key to go back to Test options;\n";

			std::getline(std::cin, input);
			clearConsole();

			if (input == "t") {
				Triangle triangle;

				try {
					inTriangle(triangle);

					Triangle* initialTriangle = triangle.clone();

					std::cout << "Enter the value to scale the Triangle on: ";

					scaleShape(triangle);

					std::cout << "Scaled triangle: " << triangle << "\n\n" << "Initial triangle: " << *initialTriangle << '\n';

					std::cout << "Press any key to continue\n";
					std::getline(std::cin, input);

				}
				catch (const std::string& error) {
					processError(error, input);
				}
			}


			else if (input == "r") {
				Ring ring;

				try {
					inRing(ring);
					Ring* initialRing = ring.clone();
					std::cout << "Enter the value to scale the Ring on: ";

					scaleShape(ring);

					std::cout << "Scaled ring: " << ring << "\n\n" << "Initial ring: " << *initialRing << "\n\n";

					std::cout << "Press any key to continue\n";
					std::getline(std::cin, input);
				}
				catch (const std::string& error) {
					processError(error, input);
				}
			}
			break;
		case 3:
			clearConsole();
			std::cout << "Test Composite Shape:\n\n";
			std::cout << "Enter max number of shapes: ";

			int maxNumber = 0;
			CompositeShape compositeShape;

			try {
				std::getline(std::cin, input);
				std::istringstream inputStream(input);
				std::string leftover;

				if (!(inputStream >> maxNumber) || maxNumber != std::stod(input)) {
					throw INVALID_INPUT;
				}

				if (inputStream >> leftover) {
					throw INVALID_INPUT;
				}

				compositeShape = CompositeShape(maxNumber);

				std::cout << "\n\n" << "Enter shapes to include in Composite Shape: <Triangle/Ring> <Triangle three vertices/Ring center + Outer & Inner Radiuses>"
					<< '\n';

				std::getline(std::cin, input);
				std::istringstream inputStreamShapes(input);

				while (inputStreamShapes >> input) {

					if (input == "Triangle") {
						Triangle* pTriangle = new Triangle;

						inputStreamShapes >> *pTriangle;
						compositeShape += pTriangle;

						std::cout << "Triangle was included" << '\n';
					}
					else if (input == "Ring") {
						Ring* pRing = new Ring;

						inputStreamShapes >> *pRing;
						compositeShape += pRing;

						std::cout << "Ring was included" << '\n';
					}
					else {
						throw INVALID_INPUT;
					}
				}

				std::cout << "\n\n" << "Enter the value(s) to move the Composite Shape on: ";
				moveShape(compositeShape, MOVE_OPTION_SHIFT);
				std::cout << "Composite Shape's moved, new position: " << compositeShape << "\n\n";

				std::cout << "Enter the point to move the Composite Shape to: ";
				moveShape(compositeShape, MOVE_OPTION_POINT);
				std::cout << "Composite Shape's moved, new position: " << compositeShape << "\n\n";

				std::cout << "Enter the value to scale Composite Shape on: ";
				scaleShape(compositeShape);

				std::cout << "Final Composite Shape: " << compositeShape;

				std::cout << "Press any key to continue\n";
				std::getline(std::cin, input);

			}
			catch (const std::string& error) {
				processError(error, input);
			}
			break;
		}
	}

	return EXIT_SUCCESS;
}

void clearConsole() {
	std::cout << "\033[2J\033[H";
}

void inTriangle(Triangle& triangle) {
	std::cout << "Enter coordinates of Triangle's vertices: ";

	std::string input;
	std::getline(std::cin, input);
	std::istringstream inputTriangleStream(input);

	inputTriangleStream >> triangle;

	if (inputTriangleStream >> input) {
		throw AMBIGUOUS_TRIANGLE_ERROR;
	}

	std::cout << "You've entered: " << triangle.getA() << " " << triangle.getB() << " " << triangle.getC() << "\n\n";
}

void outTriangle(const Triangle& newTriangle, const Triangle* oldTriangle) {
	std::cout << "Triangle's moved, new position: " << newTriangle << "\n\n"
		<< "Old position: " << *oldTriangle << "\n\n";
}

void inRing(Ring& ring) {
	std::cout << "Enter Rings's coordinates of center and values of outer and inner radiuses: ";

	std::string input;
	std::getline(std::cin, input);
	std::istringstream inputTriangleStream(input);

	inputTriangleStream >> ring;

	if (inputTriangleStream >> input) {
		throw AMBIGUOUS_RING_ERROR;
	}

	std::cout << "You've entered: " << ring.getCenter() << " " << ring.getOuterRadius() << " " << ring.getInnerRadius() << "\n\n";
}

void outRing(Ring& const newRing, const Ring* oldRing) {
	std::cout << "Ring's moved, new position: " << newRing << "\n\n" 
		<< "Old position: " << *oldRing << "\n\n";
}

void moveShape(Shape& shape, std::string option) {
	double shift = 0.0;
	double shiftY = 0.0;
	bool xyMove = false;
	std::string input;
	Point newCenter;

	std::getline(std::cin, input);
	std::istringstream inputStream(input);

	if (option == MOVE_OPTION_SHIFT) {
		if (!(inputStream >> shift)) {
			throw INVALID_SHIFT_ERROR;
		}

		if (inputStream >> input) {
			try {
				shiftY = std::stod(input);
				xyMove = true;
			}
			catch (std::invalid_argument&) {
				throw INVALID_SHIFT_ERROR;
			}
		}

		if (inputStream >> input) {
			throw AMBIGUOS_SHIFT_ERROR;
		}
		std::cout << '\n';
		xyMove ? shape.move(shift, shiftY) : shape.move(shift);
	}
	else if (option == MOVE_OPTION_POINT) {
		inputStream >> newCenter;

		if (inputStream >> input) {
			throw AMBIGUOUS_CENTER_ERROR;
		}
		std::cout << '\n';

		shape.move(newCenter);
	}
}

void processError(const std::string& error, std::string& input) {
	std::cin.clear();
	std::cout << error << '\n';
	std::cout << "Press any key to continue\n";
	std::getline(std::cin, input);
}

void scaleShape(Shape& shape) {
	std::string input;
	double scale = 0.0;

	std::getline(std::cin, input);
	std::istringstream inputStream(input);
	std::string leftover;

	if (!(inputStream >> scale)) {
		throw INVALID_INPUT;
	}

	if (inputStream >> leftover) {
		throw INVALID_INPUT;
	}
	std::cout << "\n\n";

	shape.scale(scale);
}