/**
 * @file kdtree.h
 * Definition of KDTree class.
 */

#pragma once

#include <vector>

#include "point.h"

using namespace std;


/**
 * Represents a k-d tree to partition points into convex hyperrectangles 
 * along hyperplanes in k-dimensional space.
 * @author Vaibhav Gupta
 */
template<int Dim>
class KDTree {
    private:
        // Internal structure representing a node of the k-d tree.
        struct Node {
            Point<Dim> point;
            Node *left, *right;

            //Default constructor for node.
            Node() : point(), left(NULL), right(NULL) {}

            /**
             * Constructor to create node from a k-dimensional point.
             * @param point Point to create node from.
             */
            Node(const Point<Dim> &point) : point(point), left(NULL), right(NULL) {}
        };

        Node *root;

        /**
         * Recursive helper function to destroy tree.
         * @param node Pointer to node to delete.
         */
        void destroy(Node *node);

        /**
         * Recursive helper function to add a given node to the tree by 
         * sorting the points by magnitude in the kth dimension and 
         * finding the median point between the two given indices.
         * @param points Vector of points to add to tree.
         * @param node Pointer to node to add.
         * @param a Lower index bound of points vector to find node in.
         * @param b Upper index bound of points vector to find node in.
         * @param k Dimension to sort points in.
         */
        void add_node(vector<Point<Dim>> &points, Node *& node, int a, int b, int k);

        /**
         * Recursive helper function to find the nearest neighbor of the given point.
         * Traverses down the tree to find the smallest hyperrectangle containing 
         * the given point (binary search) before searching closer points within the 
         * current radius during back-traversal. If the distance from the splitting
         * plane to the given point is less than the radius, than the opposite subtree
         * is also searched.
         * @param point Point to find nearest neighbor of.
         * @param curr Pointer to current node.
         * @param k Splitting dimension of current level/depth.
         */
        Point<Dim> nns(const Point<Dim> &point, Node *curr, int k) const;

        /**
         * Helper function to perform insertion sort on a given vector of points
         * between the two given indices based on the value of the point at the
         * kth dimension.
         * @param points Vector of points to sort.
         * @param a Lower index bound of points vector to sort.
         * @param b Upper index bound of points vector to sort.
         * @param k Dimension to compare/sort points in. 
         */
        void sort(vector<Point<Dim>> &points, int a, int b, int k);

        /**
         * Returns whether or not the first given point has a lower value 
         * than the second given point in the kth dimension.
         * @param a First point to compare.
         * @param b Second point to compare.
         * @param k Dimension to compare points in.
         * @returns Boolean indicating if the first point has a lower value
         * than the second point in the kth dimension. 
         */
        bool has_min_k(const Point<Dim> &a, const Point<Dim> &b, int k) const;

        /**
         * Returns whether or not the first given point is closer to the 
         * given target point than the second given point. 
         * @param target Point to calculate distance to.
         * @param a First point to calculate distance to target.
         * @param b Second point to calculate distance to target.
         * @returns Boolean indicating if the first point is closer to 
         * the target than the second point.
         */
        bool is_closer(const Point<Dim> &target, const Point<Dim> &a, 
            const Point<Dim> &b) const;

    public:
        /**
         * Constructor to create tree from a vector of points.
         * @param points Vector of points to create tree from.
         */
        KDTree(vector<Point<Dim>> &points);

        //Destructor to destroy tree.
        ~KDTree();

        /**
         * Performs nearest neighbor search to find the closest point
         * to the given point.
         * @param point Point to find the nearest neighbor of.
         * @returns Point that is closest to the given point.
         */
        Point<Dim> nns(const Point<Dim> &point) const;
};

#include "kdtree.cpp"