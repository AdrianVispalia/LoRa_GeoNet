#include "geomTests.h"


int testConvAngleLength() {
	double length = 3.367f;
	return approxEquals(length, getArcLength(getArcAngle(length)), PRECISION_ERROR_CONV);
}

int testConvLengthAngle() {
	double angle = 77.12f;
	return approxEquals(angle, getArcAngle(getArcLength(angle)), PRECISION_ERROR_CONV);
}

int testConvCoordinatesCartesianPoint() {
	point pex = getCartesianPoint({77.3f, 28.1f});
	point p = { .x = 1.23693e+06, .y = 660458, .z = 6.22209e+06 };
	point p2 = getCartesianPoint(getCoordinates(p));
	return p == getCartesianPoint(getCoordinates(p));
}

int testConvCartesianPointCoordinates() {
	coordinates coords = { .lat = 61.34, .lon = 87.3 };
	coordinates coords2 = getCoordinates(getCartesianPoint(coords));
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
