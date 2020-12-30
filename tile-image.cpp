/**
 * @file tile-image.cpp
 * Implementation of TileImage class.
 */

#include "tile-image.h"

TileImage::TileImage(PNG *img) {
    this -> img = img;
    square_crop();
}

TileImage::~TileImage() {
    delete img;
}

void TileImage::square_crop() {
    if (img -> width() != img -> height()) {
        unsigned dim = fmin(img -> width(), img -> height());
        unsigned off_x = 0, off_y = 0;

        if (img -> height() > img -> width()) {
            off_y = (img -> height() - img -> width()) / 2;
        } else {
            off_x = (img -> width() - img -> height()) / 2;
        }

        PNG *img_crop = new PNG(dim, dim);
        for (unsigned x = 0; x < dim; x++) {
            for (unsigned y = 0; y < dim; y++) {
                img_crop -> getPixel(x, y) = img -> getPixel(off_x + x, off_y + y);
            }
        }
        delete img;
        img = img_crop;
    }
}

void TileImage::resize(unsigned dim) {
    double factor = (double)dim / img -> width();
    if (factor < 1) {
        for (unsigned int x = 0; x < dim; x++) {
            for (unsigned int y = 0; y < dim; y++) {
                img -> getPixel(x, y) = img -> getPixel(x / factor, y / factor);
            }
        }
        img -> resize(dim, dim);
    } else if (factor > 1) {
        img -> resize(dim, dim);
        for (int x = dim - 1; x >= 0; x--) {
            for (int y = dim - 1; y >= 0; y--) {
                img -> getPixel(x, y) = img -> getPixel(x / factor, y / factor);
            }
        }
    }
}

Point<3> TileImage::get_avg_color() const {
    double l_sum = 0, u_sum = 0, v_sum = 0;
    for (unsigned x = 0; x < img -> width(); x++) {
        for (unsigned y = 0; y < img -> height(); y++) {
            const LUVAPixel &pixel = img -> getPixel(x, y);
            l_sum += pixel.l;
            u_sum += pixel.u;
            v_sum += pixel.v;
        }
    }

    unsigned pixels = img -> width() * img -> height();
    double vals[3] = {l_sum / pixels, u_sum / pixels, v_sum / pixels};
    return Point<3>(vals);
}

void TileImage::paste(PNG &png, unsigned start_x, unsigned start_y) const {
    for (unsigned x = 0; x < img -> width(); x++) {
        for (unsigned y = 0; y < img -> height(); y++) {
            png.getPixel(start_x + x, start_y + y) = img -> getPixel(x, y);
        }
    }
}