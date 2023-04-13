#ifndef _GEOM_H
#define _GEOM_H

#include <math.h>
#include <stdint.h>

#define DEG_2_RAD			3.141592/180.0
#define RAD_2_DEG			180.0/3.141592

#define RADIUS					    6378137
#define INVERSE_RADIUS_2		2.4581723e-14

#define BOUNCE_DISTANCE			2000
#define ORIGIN_NODE_SEPARATION	150
#define MIN_DISTANCE			100

#define PRECISION_ERROR_COORDS			0.1f
#define PRECISION_ERROR_POINT			0.1f

#define COORD_DOUBLE_PRECISION			1

#ifdef COORD_DOUBLE_PRECISION
    typedef double coord_dt;
    typedef uint64_t coord_byte_dt;
#else
    typedef float coord_dt;
    typedef uint32_t coord_byte_dt;
#endif

struct vec3 {
    double x, y, z;
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
    double lat;
    double lon;
} coordinates;

typedef struct {
    plane pl;
    vector posUniVec;
    double thresholdAngle;
} barrier;

int approxEquals(double n1, double n2, double maxError);

bool operator==(const coordinates& c1, const coordinates& c2);

bool operator==(const point& p1, const point& p2);

double getSphericalDistance(point p1, point p2);

double getCartesianDistance(point p1, point p2);

vector getVector(point src, point dest);

line getLine(point src, point dest);

double getPlaneD(plane pl);

double getVectorModule(vector v);

vector getUniVector(vector v);

double getAngleBetweenUniVectors(vector u1, vector u2);

double getArcLength(double angle);

double getArcAngle(double length);

int isRealPoint(point p);

point getIntersectionLinePlane(line l, plane pl);

point getCartesianPoint(coordinates coords);

coordinates getCoordinates(point p);

barrier getBarrier(coordinates position_coords, coordinates orientation_coords, double length);

int hitsBarrier(barrier barr, point src, point dest);

int retransmitDecision(coordinates srcCoords, coordinates destCoords, barrier *barrs, int size,  point nodePos);

#endif
