/**
 * @file mosaic.cpp
 * Implementation of Mosaic class.
 */

#include <iostream>
#include <chrono>

#include "mosaic.h"

Mosaic::Mosaic(PNG *img, map<Point<3>, TileImage*> &color_tiles, 
        unsigned tiles, unsigned ppt) {
    this -> img = img;
    this -> color_tiles = color_tiles;
    this -> ppt = ppt;

    auto start = chrono::steady_clock::now();
    if (img -> width() >= img -> height()) {
        rows = tiles;
        cols = round((double)img -> width() / img -> height() * tiles);
    } else {
        cols = tiles;
        rows = round((double)img -> height() / img -> width() * tiles);
    }
    img_ppc = (double)img -> width() / cols;
    img_ppr = (double)img -> height() / rows;

    mosaic.resize(cols, vector<TileImage*>(rows, NULL));
    generate();
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << endl << "Generated " << cols << "x" << rows << " tile mosaic in " 
        << time << "ms" << endl;
}

Mosaic::~Mosaic() {
    delete img;
    for (auto &pair : color_tiles) {
        delete pair.second;
    }
}

void Mosaic::generate() {
    vector<Point<3>> points;
    for (const auto &pair : color_tiles) {
        points.push_back(pair.first);
    }

    KDTree<3> tree(points);
    for (unsigned col = 0; col < cols; col++) {
        for (unsigned row = 0; row < rows; row++) {
            Point<3> nearest_color = tree.nns(get_region_color(col, row));
            mosaic[col][row] = color_tiles[nearest_color];
        }
    }
}

void Mosaic::draw(const string &file_path) {
    PNG mosaic_img(cols * ppt, rows * ppt);

    cout << "Drawing " << mosaic_img.width() << "x" << mosaic_img.height() 
        << " mosaic..." << flush;
    for (unsigned col = 0; col < cols; col++) {
        for (unsigned row = 0; row < rows; row++) {
            mosaic[col][row] -> paste(mosaic_img, col * ppt, row * ppt);
        }
    }
    mosaic_img.writeToFile(file_path);
    cout << "Done" << endl;
}

Point<3> Mosaic::get_region_color(unsigned col, unsigned row) const {
    double l_sum = 0, u_sum = 0, v_sum = 0;

    unsigned start_x = round(col * img_ppc), end_x = round((col + 1) * img_ppc);
    unsigned start_y = round(row * img_ppr), end_y = round((row + 1) * img_ppr);
    for (unsigned x = start_x; x < end_x; x++) {
        for (unsigned y = start_y; y < end_y; y++) {
            const LUVAPixel &pixel = img -> getPixel(x, y);
            l_sum += pixel.l;
            u_sum += pixel.u;
            v_sum += pixel.v;
        }
    }

    unsigned pixels = (end_x - start_x) * (end_y - start_y);
    double vals[3] = {l_sum / pixels, u_sum / pixels, v_sum / pixels};
    return Point<3>(vals);
}