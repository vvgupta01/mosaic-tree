/**
 * @file point.h
 * Definition of Point class.
 */

#pragma once

/**
 * Represents a point in k-dimensional space.
 * @author Vaibhav Gupta
 */
template <int Dim>
class Point {
    public:
        // Default constructor for point. Initializes all values to 0.
        Point();

        /**
         * Constructor to create point from an array of values.
         * @param vals Array of values representing point.
         */
        Point(double vals[Dim]);

        /**
         * Returns the value of the point at the kth index/dimension.
         * @param k Dimension of the point.
         * @returns Value at the index/dimension.
         */
        double operator[](int k) const;

        /**
         * Compares whether a given point is less than the point.
         * @param point Point to compare.
         * @returns Boolean indicating if the given point is less than
         * the point or not.
         */
        bool operator<(const Point<Dim> &point) const;

        /**
         * Returns the squared magnitude of the point (equivalent to the 
         * squared distance from 0).
         * @returns Squared magnitude of the point.
         */
        double sq_mag() const;

        /**
         * Returns the squared distance from the given point.
         * @param point Point to calculate distance from.
         * @returns Squared distance from the given point.
         */
        double sq_dist(const Point<Dim> &point) const;

        /**
         * Returns the squared distance from the given point at the 
         * kth dimension.
         * @param point Point to calculate distance from.
         * @param k Dimension to calculate distance at.
         * @returns Squared distance from the given point at the kth dimension.
         */
        double split_sqdist(const Point<Dim> &point, int k) const;

    private:
        double data[Dim];
};

#include "point.cpp"
