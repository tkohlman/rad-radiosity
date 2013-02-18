///
/// @file RadiosityReader.cpp
/// 
/// @author	Thomas Kohlman
/// @date 1 January 2012
///
/// @description
/// 	Performs file input operations from radiosity files.
///

#include "RadiosityReader.h"

namespace Radiosity {

//
// Constructor
//
RadiosityReader::RadiosityReader() {
}

//
// Destructor
//
RadiosityReader::~RadiosityReader() {
}

//
// ParseObj
//
vector<Rectangle*> *RadiosityReader::ParseObj(const char *filename) {

    int line_num(0);
    
    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}
	
	Color color;
	
	char *buffer = new char[INPUT_BUFFER_LEN];
	
	vector<Rectangle*> *quads = new vector<Rectangle*>();
	vector<Point> vertices;
	
	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);
	
	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file)) {
	
	    // increment the line count
	    ++line_num;
	    
	    // Parse the first character
	    char *begin = strtok(buffer, " \n");

	    float emission;
	    
	    if (strncmp(begin, "#", 1) == 0) {
	    
	        // comment - do nothing
	        
	    } else if (strcmp(begin, "e") == 0) {
	    
	        // color information
	        char *ec = strtok(NULL, " ");

	        emission = strtof(ec, NULL);;
	    
	    } else if (strcmp(begin, "c") == 0) {
	    
	        // color information
	        char *rc = strtok(NULL, " ");
	        char *gc = strtok(NULL, " ");
	        char *bc = strtok(NULL, " ");
	        
	        float r = strtof(rc, NULL);
	        float g = strtof(gc, NULL);
	        float b = strtof(bc, NULL);
	        
	        color = Color(r, g, b);
	    
	    } else if (strcmp(begin, "v") == 0) {
	        
	        char *xc = strtok(NULL, " ");
	        char *yc = strtok(NULL, " ");
	        char *zc = strtok(NULL, " ");
	        
	        if ((xc == NULL) || (yc == NULL) || (zc == NULL)) {
	            cout << "Error parsing tokens on line " << line_num << endl;
	            exit(1);
	        }
	        
	        float x = strtof(xc, NULL);
	        float y = strtof(yc, NULL);
	        float z = strtof(zc, NULL);
	        
	        Point p(x, y, z, color);

	        vertices.push_back(p);
	    
	    } else if (strcmp(begin, "f") == 0) {
	        
	        // face definition - read new quad       
	        char *ac = strtok(NULL, " ");
	        char *bc = strtok(NULL, " ");
	        char *cc = strtok(NULL, " ");
	        char *dc = strtok(NULL, " ");

	        
	        if ((ac == NULL) || (bc == NULL) || (cc == NULL) || (dc == NULL)) {
	            cout << "Error parsing tokens on line " << line_num << endl;
	            exit(1);
	        }
	        
	        int index_a = strtol(ac, NULL, 0) - 1;
	        int index_b = strtol(bc, NULL, 0) - 1;
	        int index_c = strtol(cc, NULL, 0) - 1;
	        int index_d = strtol(dc, NULL, 0) - 1;

	        // Create the new quad
	        quads->push_back(new Rectangle(vertices.at(index_a),
	                                       vertices.at(index_b),
	                                       vertices.at(index_c),
	                                       vertices.at(index_d),
	                                       color,
	                                       emission));
	        
	    } else {
	    
	        cout << "Error detected in file " << filename << " on line " 
	            << line_num << endl;
	        cout << "Line is: " << buffer << endl;
	        exit(1);
	    }
	    
    	// Clear the buffer
	    memset(buffer, 0, INPUT_BUFFER_LEN);
	
	}

    // Close the file
    fclose(file);
    file = NULL;
    
    // Free the buffer
    delete [] buffer;
    buffer = NULL;

    return quads;
}

//
// ParsePat
// 
vector<Patch*> *RadiosityReader::ParsePat(const char *filename) {


    int line_num(0);
    
    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}
	
	Color color;
	
	char *buffer = new char[INPUT_BUFFER_LEN];
	
	vector<Patch*> *patches = new vector<Patch*>();
	
	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);
	
	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file)) {
	
	    // increment the line count
	    ++line_num;
	    
	    // Parse the first character
	    char *begin = strtok(buffer, " \n");
    
	    if (strncmp(begin, "#", 1) == 0) {
	    
	        // comment - do nothing
	        
	    } else if (strcmp(begin, "c") == 0) {
	    
	        // color information
	        char *rc = strtok(NULL, " ");
	        char *gc = strtok(NULL, " ");
	        char *bc = strtok(NULL, " ");
	        
	        float r = strtof(rc, NULL);
	        float g = strtof(gc, NULL);
	        float b = strtof(bc, NULL);
	        
	        color = Color(r, g, b);
	    
	    } else if (strcmp(begin, "p") == 0) {
	    
	        // patch definition - read new patch
	        
	        float Ax = strtof(strtok(NULL, " "), NULL);
	        float Ay = strtof(strtok(NULL, " "), NULL);
	        float Az = strtof(strtok(NULL, " "), NULL);
	        float Bx = strtof(strtok(NULL, " "), NULL);
	        float By = strtof(strtok(NULL, " "), NULL);
	        float Bz = strtof(strtok(NULL, " "), NULL);
	        float Cx = strtof(strtok(NULL, " "), NULL);
	        float Cy = strtof(strtok(NULL, " "), NULL);
	        float Cz = strtof(strtok(NULL, " "), NULL);
	        float Dx = strtof(strtok(NULL, " "), NULL);
	        float Dy = strtof(strtok(NULL, " "), NULL);
	        float Dz = strtof(strtok(NULL, " "), NULL);
	        float emission = strtof(strtok(NULL, " "), NULL);
	        
	        Point *A = new Point(Ax, Ay, Az, color);
	        Point *B = new Point(Bx, By, Bz, color);
	        Point *C = new Point(Cx, Cy, Cz, color);
	        Point *D = new Point(Dx, Dy, Dz, color);
	        
	        // Create the new patch
	        Patch *p = new Patch(A, B, C, D, color, emission);
	        patches->push_back(p);
	    
	    } else {
	    
	        cout << "Error detected in file " << filename << " on line " 
	            << line_num << endl;
	        cout << "Line is: " << buffer << endl;
	        exit(1);
	    }
 
    	// Clear the buffer
	    memset(buffer, 0, INPUT_BUFFER_LEN);
	
	}
	
	// Delete the buffer
	delete [] buffer;

    // Close the file
    fclose(file);

    return patches;
}
    
//
// ParseLos
//
vector<Patch*> *RadiosityReader::ParseLos(const char *filename) {


    int line_num(0);
    
    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}
	
	Color color;
	
	char *buffer = new char[INPUT_BUFFER_LEN];
	
	vector<Patch*> *patches = new vector<Patch*>();
	
	// Create a parallel vector of vectors for line of sight values
	vector< vector<int> > los;
	
	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);
	
	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file)) {
	
	    // increment the line count
	    ++line_num;
	    
	    // Parse the first character
	    char *begin = strtok(buffer, " \n");
	    
	    if (strncmp(begin, "#", 1) == 0) {
	    
	        // comment - do nothing
	        
	    } else if (strcmp(begin, "c") == 0) {
	    
	        // color information
	        char *rc = strtok(NULL, " ");
	        char *gc = strtok(NULL, " ");
	        char *bc = strtok(NULL, " ");
	        
	        float r = strtof(rc, NULL);
	        float g = strtof(gc, NULL);
	        float b = strtof(bc, NULL);
	        
	        color = Color(r, g, b);
	    
	    } else if (strcmp(begin, "p") == 0) {
	    
	        // patch definition - read new patch
	        
	        float Ax = strtof(strtok(NULL, " "), NULL);
	        float Ay = strtof(strtok(NULL, " "), NULL);
	        float Az = strtof(strtok(NULL, " "), NULL);
	        float Bx = strtof(strtok(NULL, " "), NULL);
	        float By = strtof(strtok(NULL, " "), NULL);
	        float Bz = strtof(strtok(NULL, " "), NULL);
	        float Cx = strtof(strtok(NULL, " "), NULL);
	        float Cy = strtof(strtok(NULL, " "), NULL);
	        float Cz = strtof(strtok(NULL, " "), NULL);
	        float Dx = strtof(strtok(NULL, " "), NULL);
	        float Dy = strtof(strtok(NULL, " "), NULL);
	        float Dz = strtof(strtok(NULL, " "), NULL);
	        float emission = strtof(strtok(NULL, " "), NULL);
	           
	        Point *A = new Point(Ax, Ay, Az, color);
	        Point *B = new Point(Bx, By, Bz, color);
	        Point *C = new Point(Cx, Cy, Cz, color);
	        Point *D = new Point(Dx, Dy, Dz, color);
	        
	        // Create the new patch
	        Patch *p = new Patch(A, B, C, D, color, emission);
	        patches->push_back(p);
	        
	        // Create the corresponding los vector
	        vector<int> v;
	        los.push_back(v);
	        
	    
	    } else if (strcmp(begin, "l") == 0) {
	    
	        // los definition (for the last patch read)

	        // read the patch num
	        int patch_num = strtol(strtok(NULL, " "), NULL, 0);
	        
	        // insert the patch num into the last los vector
	        los.back().push_back(patch_num);
	      	    
	    } else {
	    
	        cout << "Error detected in file " << filename << " on line " 
	            << line_num << endl;
	        cout << "Line is: " << buffer << endl;
	        exit(1);
	    }
 
    	// Clear the buffer
	    memset(buffer, 0, INPUT_BUFFER_LEN);
	
	}
	
	// convert the los ids into pointers
	vector< vector<int> >::iterator los_iter = los.begin();
	
	int index = 0;
	for (; los_iter != los.end(); ++los_iter) {
	
	    vector<int>::iterator iditer = los_iter->begin();
	    
	    for (; iditer != los_iter->end(); ++iditer) {
	        
	        patches->at(index)->AddViewablePatch(patches->at(*iditer));
	        
	    }
	    ++index;
	}
	
	// delete the buffer
	delete [] buffer;
	
    // Close the file
    fclose(file);

    return patches;
}    
    
    
vector<Patch*> *RadiosityReader::ParseFor(const char *filename) {

    int line_num(0);
    
    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}
	
	Color color;
	
	char *buffer = new char[INPUT_BUFFER_LEN];
	
	vector<Patch*> *patches = new vector<Patch*>();
	
	// Create a parallel vector of vectors for line of sight values
	vector< vector<int> > los;
	
	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);
	
	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file)) {
	
	    // increment the line count
	    ++line_num;

	    // Parse the first character
	    char *begin = strtok(buffer, " \n");
	    
	    if (strncmp(begin, "#", 1) == 0) {
	    
	        // comment - do nothing
	        
	    } else if (strcmp(begin, "c") == 0) {
	    
	        // color information
	        char *rc = strtok(NULL, " ");
	        char *gc = strtok(NULL, " ");
	        char *bc = strtok(NULL, " ");
	        
	        float r = strtof(rc, NULL);
	        float g = strtof(gc, NULL);
	        float b = strtof(bc, NULL);
	        
	        color = Color(r, g, b);
	    
	    } else if (strcmp(begin, "p") == 0) {
	    
	        // patch definition - read new patch

	        float Ax = strtof(strtok(NULL, " "), NULL);
	        float Ay = strtof(strtok(NULL, " "), NULL);
	        float Az = strtof(strtok(NULL, " "), NULL);
	        float Bx = strtof(strtok(NULL, " "), NULL);
	        float By = strtof(strtok(NULL, " "), NULL);
	        float Bz = strtof(strtok(NULL, " "), NULL);
	        float Cx = strtof(strtok(NULL, " "), NULL);
	        float Cy = strtof(strtok(NULL, " "), NULL);
	        float Cz = strtof(strtok(NULL, " "), NULL);
	        float Dx = strtof(strtok(NULL, " "), NULL);
	        float Dy = strtof(strtok(NULL, " "), NULL);
	        float Dz = strtof(strtok(NULL, " "), NULL);
	        float emission = strtof(strtok(NULL, " "), NULL);
	        
	        Point *A = new Point(Ax, Ay, Az, color);
	        Point *B = new Point(Bx, By, Bz, color);
	        Point *C = new Point(Cx, Cy, Cz, color);
	        Point *D = new Point(Dx, Dy, Dz, color);
	        
	        // Create the new patch
	        Patch *p = new Patch(A, B, C, D, color, emission);
	        patches->push_back(p);
	        
	        // Create the corresponding los vector
	        vector<int> v;
	        los.push_back(v);
	        
	    
	    } else if (strcmp(begin, "l") == 0) {
	    
	        // los definition (for the last patch read)

	        // read the patch num
	        int patch_num = strtol(strtok(NULL, " "), NULL, 0);
	        
	        // insert the patch num into the last los vector
	        los.back().push_back(patch_num);
	      	    
	    } else if (strcmp(begin, "f") == 0) {
	    
	        // formfactor (for the last patch read)

	        // read the patch num
	        float ff = strtof(strtok(NULL, " "), NULL);
	        
	        // insert the patch num into the last los vector
	        patches->back()->GetFormFactors()->push_back(ff);
	      	    
	    } else {
	    
	        cout << "Error detected in file " << filename << " on line " 
	            << line_num << endl;
	        cout << "Line is: " << buffer << endl;
	        exit(1);
	    }
 
    	// Clear the buffer
	    memset(buffer, 0, INPUT_BUFFER_LEN);
	
	}
	
	// convert the los ids into pointers
	vector< vector<int> >::iterator los_iter = los.begin();
	
	int index = 0;
	for (; los_iter != los.end(); ++los_iter) {
	
	    vector<int>::iterator iditer = los_iter->begin();
	    
	    for (; iditer != los_iter->end(); ++iditer) {
	        
	        patches->at(index)->AddViewablePatch(patches->at(*iditer));
	        
	    }
	    
	    if (patches->at(index)->GetViewablePatches()->size() !=
	        patches->at(index)->GetFormFactors()->size()) {
 
	        while (patches->at(index)->GetFormFactors()->size() < 
	            patches->at(index)->GetViewablePatches()->size()) {
	            patches->at(index)->GetFormFactors()->push_back(0);
	        }
        }

	    ++index;
	}
	
	// delete the buffer
	delete [] buffer;
	

    // Close the file
    fclose(file);

    return patches;

}  
    
    
    
}   // namespace Radiosity
    


