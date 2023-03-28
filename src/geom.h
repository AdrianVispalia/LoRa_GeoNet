#ifndef _GEOM_H
#define _GEOM_H

#include <math.h>

#define RADIUS					    6378137
#define INVERSE_RADIUS_2		2.4581723e-14

#define BOUNCE_DISTANCE			2000
#define ORIGIN_NODE_SEPARATION	150
#define MIN_DISTANCE			100

#define PRECISION_ERROR_COORDS			0.1f
#define PRECISION_ERROR_POINT			0.1f

struct vec3 {
	float x, y, z;
};

typedef struct vec3 point;

typedef struct vec3 vector;

typedef struct {
	point p;
    vector normal;
} plane;

typedef struct {
	point p;
    vector direction;
} line;

typedef struct {
	float lat;
	float lon;
} coordinates;

typedef struct {
	plane pl;
	vector posUniVec;
    float thresholdAngle;
} barrier;

int approxEquals(float n1, float n2, float maxError);

bool operator==(const coordinates& c1, const coordinates& c2);

bool operator==(const point& p1, const point& p2);

float getSphericalDistance(point p1, point p2);

float getCartesianDistance(point p1, point p2);

vector getVector(point src, point dest);

line getLine(point src, point dest);

float getPlaneD(plane pl);

float getVectorModule(vector v);

vector getUniVector(vector v);

float getAngleBetweenUniVectors(vector u1, vector u2);

float getArcLength(float angle);

float getArcAngle(float length);

int isRealPoint(point p);

point getIntersectionLinePlane(line l, plane pl);

point getCartesianPoint(coordinates coords);

coordinates getCoordinates(point p);

barrier getBarrier(coordinates position_coords, coordinates orientation_coords, float length);

int hitsBarrier(barrier barr, point src, point dest);

int retransmitDecision(coordinates srcCoords, coordinates destCoords, barrier *barrs, int size,  point nodePos);

#endif
