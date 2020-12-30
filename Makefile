EXENAME = main
OBJS = mosaic.o tile-image.o PNG.o LUVAPixel.o lodepng.o ColorSpace.o Comparison.o Conversion.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O2 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

$(EXENAME) : main.o $(OBJS) 
	$(CXX) main.o $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp mosaic.h
	$(CXX) $(CXXFLAGS) main.cpp

mosaic.o : mosaic.cpp kdtree.h tile-image.h
	$(CXX) $(CXXFLAGS) mosaic.cpp

tile-image.o : tile-image.cpp point.h png/PNG.h
	$(CXX) $(CXXFLAGS) tile-image.cpp

PNG.o : png/PNG.cpp png/LUVAPixel.h png/RGB_LUV.h png/lodepng/lodepng.h png/ColorSpace/ColorSpace.h
	$(CXX) $(CXXFLAGS) png/PNG.cpp

LUVAPixel.o : png/LUVAPixel.cpp
	$(CXX) $(CXXFLAGS) png/LUVAPixel.cpp

lodepng.o : png/lodepng/lodepng.cpp
	$(CXX) $(CXXFLAGS) png/lodepng/lodepng.cpp

ColorSpace.o : png/ColorSpace/ColorSpace.cpp png/ColorSpace/Comparison.h png/ColorSpace/Conversion.h
	$(CXX) $(CXXFLAGS) png/ColorSpace/ColorSpace.cpp

Comparison.o : png/ColorSpace/Comparison.cpp png/ColorSpace/ColorSpace.h png/ColorSpace/Utils.h
	$(CXX) $(CXXFLAGS) png/ColorSpace/Comparison.cpp

Conversion.o : png/ColorSpace/Conversion.cpp png/ColorSpace/ColorSpace.h png/ColorSpace/Utils.h
	$(CXX) $(CXXFLAGS) png/ColorSpace/Conversion.cpp

clean:
	-rm -f *.o *.gch $(EXENAME)