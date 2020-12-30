/**
 * @file kdtree.cpp
 * Implementation of KDTree class. 
 */

#include <iostream>

template<int Dim>
KDTree<Dim>::KDTree(vector<Point<Dim>> &points) {
    root = NULL;
    if (points.size() > 0) {
        add_node(points, root, 0, points.size() - 1, 0);
    }
}

template<int Dim>
void KDTree<Dim>::add_node(vector<Point<Dim>> &points, Node *& node, int a, int b, int k) {
    if (a == b) {
        node = new Node(points[a]);
    } else {
        sort(points, a, b, k);
        int median_idx = (a + b) / 2;
        node = new Node(points[median_idx]);

        if (median_idx > a) {
            add_node(points, node -> left, a, median_idx - 1, (k + 1) % Dim);
        }
        add_node(points, node -> right, median_idx + 1, b, (k + 1) % Dim);
    }
}

template<int Dim>
KDTree<Dim>::~KDTree() {
    destroy(root);
}

template<int Dim>
void KDTree<Dim>::destroy(Node *node) {
    if (node != NULL) {
        destroy(node -> left);
        destroy(node -> right);
        delete node;
    }
}

template<int Dim>
Point<Dim> KDTree<Dim>::nns(const Point<Dim> &point) const {
    return nns(point, root, 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::nns(const Point<Dim> &point, Node *curr, int k) const {
    if (curr -> left == NULL && curr -> right == NULL) {
        return curr -> point;
    }

    Point<Dim> nearest = curr -> point;
    bool smaller = has_min_k(point, curr -> point, k);

    Node *to_traverse = smaller ? curr -> left : curr -> right;
    Node *opposite = smaller ? curr -> right : curr -> left;
    if (to_traverse != NULL) {
        nearest = nns(point, to_traverse, (k + 1) % Dim);
    }

    if (is_closer(point, curr -> point, nearest)) {
        nearest = curr -> point;
    }

    if (opposite != NULL && curr -> point.split_sqdist(point, k) < nearest.sq_dist(point)) {
        Point<Dim> temp_nearest = nns(point, opposite, (k + 1) % Dim);
        if (is_closer(point, temp_nearest, nearest)) {
            nearest = temp_nearest;
        }
    }
    return nearest;  
}

template<int Dim>
void KDTree<Dim>::sort(vector<Point<Dim>> &points, int a, int b, int k) {
    for (int i = a; i < b; i++) {
        int min_i = i;
        for (int j = i + 1; j <= b; j++) {
            if (has_min_k(points[j], points[min_i], k)) {
                min_i = j;
            }
        }
        std::swap(points[min_i], points[i]);
    }
}

template<int Dim>
bool KDTree<Dim>::has_min_k(const Point<Dim> &a, const Point<Dim> &b, int k) const {
    if (a[k] == b[k]) {
        return a < b;
    }
    return a[k] < b[k];
}

template<int Dim>
bool KDTree<Dim>::is_closer(const Point<Dim> &target, const Point<Dim> &a, 
        const Point<Dim> &b) const {
    double a_dist = target.sq_dist(a);
    double b_dist = target.sq_dist(b);

    if (a_dist == b_dist) {
        return a < b;
    }
    return a_dist < b_dist;
}