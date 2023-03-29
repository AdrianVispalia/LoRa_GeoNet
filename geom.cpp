#include "geom.h"

int approxEquals(float n1, float n2, float maxError) {
    float diff = n1 - n2;
    if (diff < 0)
        diff = -diff;

    return diff <= maxError;
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

float getSphericalDistance(point p1, point p2) {
    return RADIUS * acos(p1.x * p2.x + p1.y * p2.y + p1.z * p2.z * INVERSE_RADIUS_2);
}

float getCartesianDistance(point p1, point p2) {
    float x = p1.x - p2.x;
    float y = p1.y - p2.y;
    float z = p1.z - p2.z;
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

float getVectorModule(vector v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vector getUniVector(vector v) {
    float module = getVectorModule(v);
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

float getPlaneD(plane pl) {
    return -(pl.normal.x * pl.p.x + pl.normal.y * pl.p.y + pl.normal.z * pl.p.z);
}

float getAngleBetweenUniVectors(vector u1, vector u2) {
    return acos(u1.x * u2.x + u1.y * u2.y + u1.z * u2.z);
}

float getArcLength(float angle) {
    return angle * RADIUS;
}

float getArcAngle(float length) {
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
    float lambda =  (l.p.x * pl.normal.x + l.p.y * pl.normal.y + l.p.z * pl.normal.z + getPlaneD(pl)) /
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
        .x = RADIUS * cos(coords.lat) * cos(coords.lon),
        .y = RADIUS * cos(coords.lat) * sin(coords.lon),
        .z = RADIUS * sin(coords.lat),
    };
    return p;
}

coordinates getCoordinates(point p) {
    coordinates coords = {
        .lat = asin(p.z / RADIUS),
        .lon = atan2(p.y, p.z),
    };
    return coords;
}

barrier getBarrier(coordinates positionCoords, coordinates orientationCoords, float length) {
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

int hitsBarrier(barrier barr, point src, point dest) {
    line trajectory = getLine(src, dest);
    point impactPoint = getIntersectionLinePlane(trajectory, barr.pl);

    if (!isRealPoint(impactPoint))
        return 0;

    float realAngle = getAngleBetweenUniVectors(barr.posUniVec,  getUniVector(impactPoint));
    return realAngle <= barr.thresholdAngle;
}

int retransmitDecision(coordinates srcCoords, coordinates destCoords, barrier *barrs, int size,  point nodePos) {
    point src =  getCartesianPoint(srcCoords);
    point dest = getCartesianPoint(destCoords);
    float distance = getSphericalDistance(src, dest);

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
