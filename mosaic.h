/**
 * @file mosaic.h
 * Definition of Mosaic class.
 */

#pragma once

#include <string>
#include <vector>
#include <map>

#include "kdtree.h"
#include "tile-image.h"

using namespace std;
using namespace png;

/**
 * Mosaic of tile images to represent an image by using a 3-d tree to map 
 * each region to a corresponding tile with the nearest average color.
 */
class Mosaic {
    public:
        /**
         * Constructor to create mosaic from a source image, map of average 
         * colors to tile pointers, number of tiles along the shortest 
         * dimension, and pixels per tile.
         * @param img Pointer to PNG to create mosaic of.
         * @param color_tiles Map of average colors to tile pointers.
         * @param tiles Number of tiles along the shortest dimension. Calculates
         * tiles along other dimension to maintain aspect ratio.
         * @param ppt Pixels per tile.
         */
        Mosaic(PNG *img, map<Point<3>, TileImage*> &color_tiles, 
            unsigned tiles, unsigned ppt);

        //Destructor to destroy mosaic.
        ~Mosaic();

        /**
         * Draws the mosaic and saves it to a PNG.
         * @param file_path File to save mosaic to.
         */
        void draw(const string &file_path);

    private:
        PNG *img;
        double img_ppr, img_ppc;

        map<Point<3>, TileImage*> color_tiles;
        vector<vector<TileImage*>> mosaic;
        unsigned rows, cols, ppt;

        /**
         * Helper function to generate mosaic by using a 3-d tree to map each region
         * of the source image to a corresponding tile with the nearest average color.
         */
        void generate();

        /**
         * Returns the average color of a region of the source image
         * (corresponding to a tile in the mosaic) as a 3-dimensional 
         * point representing a LUVA pixel.
         * @param col Column or X-index of tile representing region.
         * @param row Row or Y-index of tile representing region.
         * @returns 3-dimensional point representing the average color of 
         * the region.
         */
        Point<3> get_region_color(unsigned col, unsigned row) const;
};