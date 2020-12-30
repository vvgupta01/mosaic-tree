/**
 * @file point.cpp
 * Implementation of Point class.
 */

#include <math.h>

template<int Dim>
Point<Dim>::Point() {
    for (int i = 0; i < Dim; i++) {
        data[i] = 0;
    }
}

template<int Dim>
Point<Dim>::Point(double vals[Dim]) {
    for (int i = 0; i < Dim; i++) {
        data[i] = vals[i];
    }
}

template<int Dim>
double Point<Dim>::operator[](int k) const {
    if (k >= 0 && k < Dim) {
        return data[k];
    }
    return 0;
}

template<int Dim>
bool Point<Dim>::operator<(const Point<Dim> &point) const {
    return sq_mag() < point.sq_mag();
}

template<int Dim>
double Point<Dim>::sq_mag() const {
    double sq_mag = 0;
    for (int k = 0; k < Dim; k++) {
        sq_mag += pow(data[k], 2);
    }
    return sq_mag;
}

template<int Dim>
double Point<Dim>::sq_dist(const Point<Dim> &point) const {
    double sq_dist = 0;
    for (int k = 0; k < Dim; k++) {
        sq_dist += split_sqdist(point, k);
    }
    return sq_dist;
}

template<int Dim>
double Point<Dim>::split_sqdist(const Point<Dim> &point, int k) const {
    return pow(data[k] - point[k], 2);
}