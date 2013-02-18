///
/// @file RadiosityReader.h
/// 
/// @author	Thomas Kohlman
/// @date 1 January 2012
///
/// @description
/// 	Performs file input operations from radiosity files.
///

#ifndef RADIOSITY_READER_H
#define RADIOSITY_READER_h

#define INPUT_BUFFER_LEN 255

#include "Rectangle.h"
#include "Point.h"
#include "Patch.h"
#include "Color.h"

#include <vector>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
using namespace std;

namespace Radiosity {

class RadiosityReader {

public:

    ///
    /// @name RadiosityReader
    /// 
    /// @description
    /// 	Constructor
    ///
    /// @return - void
    ///
    RadiosityReader();

    ///
    /// @name ~RadiosityReader
    /// 
    /// @description
    /// 	Destructor
    ///
    /// @return - void
    ///
    ~RadiosityReader();

    ///
    /// @name ParseObj
    /// 
    /// @description
    /// 	Parses a .obj file into a vector of quads.
    ///
    /// @param filename - name of .obj file
    /// @return - vector of quads
    ///
    vector<Rectangle*> *ParseObj(const char *filename);
    
    ///
    /// @name ParsePat
    /// 
    /// @description
    /// 	Parses a .pat file into a vector of patches.
    ///
    /// @param filename - name of input file
    /// @return - vector of patches
    ///
    vector<Patch*> *ParsePat(const char *filename);
    
    ///
    /// @name ParseLos
    /// 
    /// @description
    /// 	Parses a .los file into a vector of patches with line of sight
    ///     information.
    ///
    /// @param filename - name of input file
    /// @return - vector of patches
    ///
    vector<Patch*> *ParseLos(const char *filename);
    
    ///
    /// @name ParseFor
    /// 
    /// @description
    /// 	Parses a .for file into a vector of patches with line of sight
    ///     information and form factor information.
    ///
    /// @param filename - name of input file
    /// @return - vector of patches
    ///
    vector<Patch*> *ParseFor(const char *filename);

};  // class RadiosityReader

}   // namespace Radiosity

#endif


