#include <string>
#include <iostream>
#include <dirent.h>
#include <map>

#include "mosaic.h"

using namespace std;

string get_input(const string &prompt) {
    string input;
    cout << prompt << ": ";
    std::getline(cin, input);
    return input;
}

void error(const string &msg) {
    cout << "Error: " << msg << endl;
    exit(0);
}

void run(const string &img_path, const string &tiles_path, int tiles, int ppt) {
    const string filename = "images/mosaic.png";
    if (tiles < 1 || ppt < 1) {
        error("Tiles and pixels per tile must be greater than 0");
    }

    PNG *img = new PNG();
    if (img -> readFromFile(img_path)) {
        cout << "Loaded " << img -> width() << "x" << img -> height() << " image" << endl;
    } else {
        error("Failed to open file for reading");
    }

    if (tiles > fmin(img -> width(), img -> height())) {
        error("Tiles must be less than minimum dimension of image");
    }

    char path[tiles_path.size() + 1];
    strcpy(path, tiles_path.c_str());

    vector<string> files;
    if (auto dir = opendir(path)) {
        while (auto file = readdir(dir)) {
            if (file -> d_name[0] != '.') {
                files.push_back(file -> d_name);
            }
        }
        closedir(dir);
    } else {
        error("Failed to open tile directory for reading");
    }


    map<Point<3>, TileImage*> color_tiles;
    cout << "Loading tile images..." << endl;
    for (unsigned long i = 0; i < files.size(); i++) {
        int bars = (int)(25.0 * (i + 1) / files.size());
        cout << "\r[" << string(bars, '=') << string(25 - bars, ' ') << 
            "] " << i + 1 << "/" << files.size() << "\r";
        cout.flush();

        PNG *img = new PNG();
        if (img -> readFromFile(tiles_path + "/" + files[i])) {
            TileImage *tile = new TileImage(img);
            tile -> resize(ppt);

            Point<3> avg_color = tile -> get_avg_color();
            if (color_tiles.count(avg_color) == 0) {
                color_tiles[avg_color] = tile;
            } else {
                delete tile;
            }
        } else {
            delete img;
        }
    }
    cout << endl << "Created " << color_tiles.size() << " " << ppt 
        << "x" << ppt << " unique tiles" << endl;

    Mosaic mosaic(img, color_tiles, tiles, ppt);
    mosaic.draw(filename);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        string img_path = get_input("Enter Image Path");
        string tiles_path = get_input("Enter Tiles Path");
        int tiles = std::stoi(get_input("Enter Number of Tiles"));
        int ppt = std::stoi(get_input("Enter Pixels Per Tile"));
        cout << endl;
        run(img_path, tiles_path, tiles, ppt);
    } else if (argc == 3) {
        run(argv[1], argv[2], 100, 50);
    } else if (argc == 5) {
        run(argv[1], argv[2], std::stoi(argv[3]), std::stoi(argv[4]));
    } else {
        error("Invalid arguments provided");
    }
}