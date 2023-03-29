#include "geomTests.h"


int testConvAngleLength() {
	float length = 3.367f;
	return approxEquals(length, getArcLength(getArcAngle(length)), PRECISION_ERROR_CONV);
}

int testConvLengthAngle() {
	float angle = 77.12f;
	return approxEquals(angle, getArcAngle(getArcLength(angle)), PRECISION_ERROR_CONV);
}

int testConvCoordinatesCartesianPoint() {
	point p = { .x = 1.14, .y = 0.6, .z = 0.2 };
	std::cout << "Point: " << p.x << "," << p.y << "," << p.z << "  vs  ";
	point p2 = getCartesianPoint(getCoordinates(p));
	std::cout << "Point2: " << p2.x << "," << p2.y << "," << p2.z << std::endl;
	return p == getCartesianPoint(getCoordinates(p));
}

int testConvCartesianPointCoordinates() {
	coordinates coords = { .lat = 61.34, .lon = 87.3 };
	std::cout << "Coordinates: " << coords.lat << "," << coords.lon << "  vs  ";
	coordinates coords2 = getCoordinates(getCartesianPoint(coords));
	std::cout << "Coordinates2: " << coords2.lat << "," << coords2.lon << std::endl;
	return coords == getCoordinates(getCartesianPoint(coords));
}


int testGeom() {
	test tests[] = {
		{ .function = testConvAngleLength, .name = "testConvAngleLength" },
		{ .function = testConvLengthAngle, .name = "testConvLengthAngle" },
		{ .function = testConvCoordinatesCartesianPoint, .name = "testConvCoordinatesCartesianPoint" },
		{ .function = testConvCartesianPointCoordinates, .name = "testConvCartesianPointCoordinates" }
	};
	int testsLength = sizeof(tests) / sizeof(tests[0]);

	return testGroup("Geom", tests, testsLength);
}
