/**
 * @file tile-image.h
 * Definition of TileImage class.
 */

#pragma once

#include "point.h"
#include "png/PNG.h"

using namespace png;

class TileImage {
    public:
        /**
         * Constructor to create tile from image.
         * @param img Pointer to image.
         */
        TileImage(PNG *img);

        //Destructor to destroy tile image.
        ~TileImage();

        /**
         * Crops the image to a square with side length equal to the
         * smallest dimension and centered on the original image.
         */
        void square_crop();

        /**
         * Resizes the image to the given dimension. Assumes tile is
         * square.
         * @param dim Dimension in pixels to resize image to.
         */
        void resize(unsigned dim);

        /**
         * Returns the average color of the tile as a 3-dimensional point
         * representing a LUVA pixel.
         * @returns 3-dimensional point representing the average color of 
         * the tile.
         */
        Point<3> get_avg_color() const;

        /**
         * Draws the tile on the given image starting at the given coordinates.
         * @param png Image to draw tile on.
         * @param start_x X-coordinate of the image to draw the tile on.
         * @param start_y Y-coordinate of the image to draw the tile on.
         */
        void paste(PNG &png, unsigned start_x, unsigned start_y) const;

    private:
        PNG *img;
};