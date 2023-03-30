#include "geom.h"

int approxEquals(double n1, double n2, double maxError) {
    double diff = n1 - n2;
    if (diff < 0)
        diff = -diff;

    return diff / n1 <= maxError;
}

bool operator==(const coordinates& c1, const coordinates& c2) {
    return approxEquals(c1.lat, c2.lat, PRECISION_ERROR_COORDS) &&
        approxEquals(c1.lon, c2.lon, PRECISION_ERROR_COORDS);
}

bool operator==(const point& p1, const point& p2) {
    return approxEquals(p1.x, p2.x, PRECISION_ERROR_POINT) &&
        approxEquals(p1.y, p2.y, PRECISION_ERROR_POINT) &&
        approxEquals(p1.z, p2.z, PRECISION_ERROR_POINT);
}

double getSphericalDistance(point p1, point p2) {
    return RADIUS * acos(p1.x * p2.x + p1.y * p2.y + p1.z * p2.z * INVERSE_RADIUS_2);
}

double getCartesianDistance(point p1, point p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    double z = p1.z - p2.z;
    return sqrt(x * x + y * y + z * z);
}

vector getVector(point src, point dest) {
    vector v = {
        .x = dest.x - src.x,
        .y = dest.y - src.y,
        .z = dest.z - src.z
    };
    return v;
}

double getVectorModule(vector v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vector getUniVector(vector v) {
    double module = getVectorModule(v);
    vector result = {
        .x = v.x / module,
        .y = v.y / module,
        .z = v.z / module,
    };
    return result;
}

line getLine(point src, point dest) {
    line l = {
        .p = src,
        .direction = getVector(src, dest),
    };
    return l;
}

double getPlaneD(plane pl) {
    return -(pl.normal.x * pl.p.x + pl.normal.y * pl.p.y + pl.normal.z * pl.p.z);
}

double getAngleBetweenUniVectors(vector u1, vector u2) {
    return acos(u1.x * u2.x + u1.y * u2.y + u1.z * u2.z);
}

double getArcLength(double angle) {
    return angle * RADIUS;
}

double getArcAngle(double length) {
    return length / RADIUS;
}

int isRealPoint(point p) {
    if (isnan(p.x) || isinf(p.x)
        || isnan(p.y) || isinf(p.y)
        || isnan(p.z) || isinf(p.z))
        return 0;
    return 1;
}

point getIntersectionLinePlane(line l, plane pl) {
    double lambda =  (l.p.x * pl.normal.x + l.p.y * pl.normal.y + l.p.z * pl.normal.z + getPlaneD(pl)) /
                    (l.direction.x * pl.normal.x + l.direction.y * pl.normal.y + l.direction.z * pl.normal.z);
    point p = {
        .x = l.p.x + l.direction.x * lambda,
        .y = l.p.y + l.direction.y * lambda,
        .z = l.p.z + l.direction.z * lambda,
    };
    return p;
}

point getCartesianPoint(coordinates coords) {
    point p = {
        .x = RADIUS * cos(coords.lat * DEG_2_RAD) * cos(coords.lon * DEG_2_RAD),
        .y = RADIUS * cos(coords.lat * DEG_2_RAD) * sin(coords.lon * DEG_2_RAD),
        .z = RADIUS * sin(coords.lat * DEG_2_RAD),
    };
    return p;
}

coordinates getCoordinates(point p) {
    coordinates coords = {
        .lat = asin(p.z / RADIUS) * RAD_2_DEG,
        .lon = atan2(p.y, p.x) * RAD_2_DEG,
    };
    return coords;
}

barrier getBarrier(coordinates positionCoords, coordinates orientationCoords, double length) {
    point position = getCartesianPoint(positionCoords);
    vector orientation = getUniVector(
        getVector(position, getCartesianPoint(orientationCoords))
    );
    barrier barr = {
        .pl = {
            .p = position,
            .normal = orientation
        },
        .posUniVec = getUniVector(position),
        .thresholdAngle = getArcAngle(length),
    };
    return barr;
}

int hitsBarrier(barrier barr, point src, point dest) { // TODO: take account sphere
    line trajectory = getLine(src, dest);
    point impactPoint = getIntersectionLinePlane(trajectory, barr.pl);

    if (!isRealPoint(impactPoint))
        return 0;

    double realAngle = getAngleBetweenUniVectors(barr.posUniVec,  getUniVector(impactPoint));
    return realAngle <= barr.thresholdAngle;
}

int retransmitDecision(coordinates srcCoords, coordinates destCoords, barrier *barrs, int size,  point nodePos) {
    point src =  getCartesianPoint(srcCoords);
    point dest = getCartesianPoint(destCoords);
    double distance = getSphericalDistance(src, dest);

    if (distance < MIN_DISTANCE)
        return 0;

    if (distance >= BOUNCE_DISTANCE)
        return getSphericalDistance(nodePos, dest) < distance - ORIGIN_NODE_SEPARATION;

    for (int i = 0; i < size; i++) {
        if (hitsBarrier(barrs[i], src, dest))
            return 1;
    }

    return 0;
}
