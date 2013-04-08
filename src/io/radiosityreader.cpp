///
/// @file RadiosityReader.cpp
///
/// @author	Thomas Kohlman
/// @date 1 January 2012
///
/// @description
/// 	Performs file input operations from radiosity files.
///

#include "radiosityreader.h"

namespace Radiosity
{

RadiosityReader::RadiosityReader()
{
}

RadiosityReader::~RadiosityReader()
{
}

std::vector<Rectangle*> *RadiosityReader::ParseObj(const char *filename)
{
    int line_num(0);

    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0)
	{
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}

	Color color;

	char *buffer = new char[INPUT_BUFFER_LEN];

	std::vector<Rectangle*> *quads = new std::vector<Rectangle*>();
	std::vector<Point> vertices;

	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);

	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file))
	{
	    // increment the line count
	    ++line_num;

	    // Parse the first character
	    char *begin = strtok(buffer, " \n");

	    float emission;

	    if (strncmp(begin, "#", 1) == 0)
	    {
	        // comment - do nothing
	    }
	    else if (strcmp(begin, "e") == 0)
	    {
	        // color information
	        char *ec = strtok(nullptr, " ");

	        emission = strtof(ec, nullptr);

	    }
	    else if (strcmp(begin, "c") == 0)
	    {
	        // color information
	        char *rc = strtok(nullptr, " ");
	        char *gc = strtok(nullptr, " ");
	        char *bc = strtok(nullptr, " ");

	        float r = strtof(rc, nullptr);
	        float g = strtof(gc, nullptr);
	        float b = strtof(bc, nullptr);

	        color = Color(r, g, b);
	    }
	    else if (strcmp(begin, "v") == 0)
	    {
	        char *xc = strtok(nullptr, " ");
	        char *yc = strtok(nullptr, " ");
	        char *zc = strtok(nullptr, " ");

	        if ((xc == nullptr) || (yc == nullptr) || (zc == nullptr))
	        {
	            std::cout << "Error parsing tokens on line " << line_num << std::endl;
	            exit(1);
	        }

	        float x = strtof(xc, nullptr);
	        float y = strtof(yc, nullptr);
	        float z = strtof(zc, nullptr);

	        Point p(x, y, z, color);

	        vertices.push_back(p);
	    }
	    else if (strcmp(begin, "f") == 0)
	    {
	        // face definition - read new quad
	        char *ac = strtok(nullptr, " ");
	        char *bc = strtok(nullptr, " ");
	        char *cc = strtok(nullptr, " ");
	        char *dc = strtok(nullptr, " ");

	        if ((ac == nullptr) || (bc == nullptr) || (cc == nullptr) || (dc == nullptr))
	        {
	            std::cout << "Error parsing tokens on line " << line_num << std::endl;
	            exit(1);
	        }

	        int index_a = strtol(ac, nullptr, 0) - 1;
	        int index_b = strtol(bc, nullptr, 0) - 1;
	        int index_c = strtol(cc, nullptr, 0) - 1;
	        int index_d = strtol(dc, nullptr, 0) - 1;

	        // Create the new quad
	        quads->push_back(new Rectangle(vertices.at(index_a),
	                                       vertices.at(index_b),
	                                       vertices.at(index_c),
	                                       vertices.at(index_d),
	                                       color,
	                                       emission));
	    }
	    else
	    {
	        std::cout << "Error detected in file "
                      << filename
                      << " on line "
                      << line_num
                      << std::endl;
	        std::cout << "Line is: " << buffer << std::endl;
	        exit(1);
	    }

    	// Clear the buffer
	    memset(buffer, 0, INPUT_BUFFER_LEN);
	}

    // Close the file
    fclose(file);
    file = nullptr;

    // Free the buffer
    delete [] buffer;
    buffer = nullptr;

    return quads;
}

std::vector<Patch*> *RadiosityReader::ParsePat(const char *filename)
{
    int line_num(0);

    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0)
	{
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}

	Color color;

	char *buffer = new char[INPUT_BUFFER_LEN];

	std::vector<Patch*> *patches = new std::vector<Patch*>();

	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);

	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file))
	{
	    // increment the line count
	    ++line_num;

	    // Parse the first character
	    char *begin = strtok(buffer, " \n");

	    if (strncmp(begin, "#", 1) == 0)
	    {
	        // comment - do nothing
	    }
	    else if (strcmp(begin, "c") == 0)
	    {
	        // color information
	        char *rc = strtok(nullptr, " ");
	        char *gc = strtok(nullptr, " ");
	        char *bc = strtok(nullptr, " ");

	        float r = strtof(rc, nullptr);
	        float g = strtof(gc, nullptr);
	        float b = strtof(bc, nullptr);

	        color = Color(r, g, b);
	    }
	    else if (strcmp(begin, "p") == 0)
	    {
	        // patch definition - read new patch

	        float Ax = strtof(strtok(nullptr, " "), nullptr);
	        float Ay = strtof(strtok(nullptr, " "), nullptr);
	        float Az = strtof(strtok(nullptr, " "), nullptr);
	        float Bx = strtof(strtok(nullptr, " "), nullptr);
	        float By = strtof(strtok(nullptr, " "), nullptr);
	        float Bz = strtof(strtok(nullptr, " "), nullptr);
	        float Cx = strtof(strtok(nullptr, " "), nullptr);
	        float Cy = strtof(strtok(nullptr, " "), nullptr);
	        float Cz = strtof(strtok(nullptr, " "), nullptr);
	        float Dx = strtof(strtok(nullptr, " "), nullptr);
	        float Dy = strtof(strtok(nullptr, " "), nullptr);
	        float Dz = strtof(strtok(nullptr, " "), nullptr);
	        float emission = strtof(strtok(nullptr, " "), nullptr);

	        Point *A = new Point(Ax, Ay, Az, color);
	        Point *B = new Point(Bx, By, Bz, color);
	        Point *C = new Point(Cx, Cy, Cz, color);
	        Point *D = new Point(Dx, Dy, Dz, color);

	        // Create the new patch
	        Patch *p = new Patch(A, B, C, D, color, emission);
	        patches->push_back(p);
	    }
	    else
	    {
	        std::cout << "Error detected in file "
                      << filename
                      << " on line "
                      << line_num
                      << std::endl;
	        std::cout << "Line is: " << buffer << std::endl;
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

std::vector<Patch*> *RadiosityReader::ParseLos(const char *filename)
{
    int line_num(0);

    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0)
	{
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}

	Color color;

	char *buffer = new char[INPUT_BUFFER_LEN];

	std::vector<Patch*> *patches = new std::vector<Patch*>();

	// Create a parallel vector of vectors for line of sight values
	std::vector< std::vector<int> > los;

	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);

	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file))
	{
	    // increment the line count
	    ++line_num;

	    // Parse the first character
	    char *begin = strtok(buffer, " \n");

	    if (strncmp(begin, "#", 1) == 0)
	    {
	        // comment - do nothing
	    }
	    else if (strcmp(begin, "c") == 0)
	    {
	        // color information
	        char *rc = strtok(nullptr, " ");
	        char *gc = strtok(nullptr, " ");
	        char *bc = strtok(nullptr, " ");

	        float r = strtof(rc, nullptr);
	        float g = strtof(gc, nullptr);
	        float b = strtof(bc, nullptr);

	        color = Color(r, g, b);
	    }
	    else if (strcmp(begin, "p") == 0)
	    {
	        // patch definition - read new patch

	        float Ax = strtof(strtok(nullptr, " "), nullptr);
	        float Ay = strtof(strtok(nullptr, " "), nullptr);
	        float Az = strtof(strtok(nullptr, " "), nullptr);
	        float Bx = strtof(strtok(nullptr, " "), nullptr);
	        float By = strtof(strtok(nullptr, " "), nullptr);
	        float Bz = strtof(strtok(nullptr, " "), nullptr);
	        float Cx = strtof(strtok(nullptr, " "), nullptr);
	        float Cy = strtof(strtok(nullptr, " "), nullptr);
	        float Cz = strtof(strtok(nullptr, " "), nullptr);
	        float Dx = strtof(strtok(nullptr, " "), nullptr);
	        float Dy = strtof(strtok(nullptr, " "), nullptr);
	        float Dz = strtof(strtok(nullptr, " "), nullptr);
	        float emission = strtof(strtok(nullptr, " "), nullptr);

	        Point *A = new Point(Ax, Ay, Az, color);
	        Point *B = new Point(Bx, By, Bz, color);
	        Point *C = new Point(Cx, Cy, Cz, color);
	        Point *D = new Point(Dx, Dy, Dz, color);

	        // Create the new patch
	        Patch *p = new Patch(A, B, C, D, color, emission);
	        patches->push_back(p);

	        // Create the corresponding los vector
	        std::vector<int> v;
	        los.push_back(v);
	    }
	    else if (strcmp(begin, "l") == 0)
	    {
	        // los definition (for the last patch read)

	        // read the patch num
	        int patch_num = strtol(strtok(nullptr, " "), nullptr, 0);

	        // insert the patch num into the last los vector
	        los.back().push_back(patch_num);
	    }
	    else
	    {
	        std::cout << "Error detected in file " << filename << " on line "
	            << line_num << std::endl;
	        std::cout << "Line is: " << buffer << std::endl;
	        exit(1);
	    }

    	// Clear the buffer
	    memset(buffer, 0, INPUT_BUFFER_LEN);
	}

	// convert the los ids into pointers
	std::vector< std::vector<int> >::iterator los_iter = los.begin();

	for (int index = 0; los_iter != los.end(); ++los_iter)
	{
	    std::vector<int>::iterator iditer = los_iter->begin();

	    for (; iditer != los_iter->end(); ++iditer)
	    {
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

std::vector<Patch*> *RadiosityReader::ParseFor(const char *filename)
{
    int line_num(0);

    // attempt to open the file
	errno = 0;
	FILE *file = fopen(filename, "r");
	if (errno != 0)
	{
		fprintf(stderr, "Could not open file: %s\n", filename);
		exit(1);
	}

	Color color;

	char *buffer = new char[INPUT_BUFFER_LEN];

	std::vector<Patch*> *patches = new std::vector<Patch*>();

	// Create a parallel vector of vectors for line of sight values
	std::vector< std::vector<int> > los;

	// Clear the buffer
	memset(buffer, 0, INPUT_BUFFER_LEN);

	// Read until EOF
	while (fgets(buffer, INPUT_BUFFER_LEN, file))
	{
	    // increment the line count
	    ++line_num;

	    // Parse the first character
	    char *begin = strtok(buffer, " \n");

	    if (strncmp(begin, "#", 1) == 0)
	    {
	        // comment - do nothing
	    }
	    else if (strcmp(begin, "c") == 0)
	    {
	        // color information
	        char *rc = strtok(nullptr, " ");
	        char *gc = strtok(nullptr, " ");
	        char *bc = strtok(nullptr, " ");

	        float r = strtof(rc, nullptr);
	        float g = strtof(gc, nullptr);
	        float b = strtof(bc, nullptr);

	        color = Color(r, g, b);
	    }
	    else if (strcmp(begin, "p") == 0)
	    {
	        // patch definition - read new patch
	        float Ax = strtof(strtok(nullptr, " "), nullptr);
	        float Ay = strtof(strtok(nullptr, " "), nullptr);
	        float Az = strtof(strtok(nullptr, " "), nullptr);
	        float Bx = strtof(strtok(nullptr, " "), nullptr);
	        float By = strtof(strtok(nullptr, " "), nullptr);
	        float Bz = strtof(strtok(nullptr, " "), nullptr);
	        float Cx = strtof(strtok(nullptr, " "), nullptr);
	        float Cy = strtof(strtok(nullptr, " "), nullptr);
	        float Cz = strtof(strtok(nullptr, " "), nullptr);
	        float Dx = strtof(strtok(nullptr, " "), nullptr);
	        float Dy = strtof(strtok(nullptr, " "), nullptr);
	        float Dz = strtof(strtok(nullptr, " "), nullptr);
	        float emission = strtof(strtok(nullptr, " "), nullptr);

	        Point *A = new Point(Ax, Ay, Az, color);
	        Point *B = new Point(Bx, By, Bz, color);
	        Point *C = new Point(Cx, Cy, Cz, color);
	        Point *D = new Point(Dx, Dy, Dz, color);

	        // Create the new patch
	        Patch *p = new Patch(A, B, C, D, color, emission);
	        patches->push_back(p);

	        // Create the corresponding los vector
	        std::vector<int> v;
	        los.push_back(v);
	    }
	    else if (strcmp(begin, "l") == 0)
	    {
	        // los definition (for the last patch read)
	        // read the patch num
	        int patch_num = strtol(strtok(nullptr, " "), nullptr, 0);

	        // insert the patch num into the last los vector
	        los.back().push_back(patch_num);
	    }
	    else if (strcmp(begin, "f") == 0)
	    {
	        // formfactor (for the last patch read)

	        // read the patch num
	        float ff = strtof(strtok(nullptr, " "), nullptr);

	        // insert the patch num into the last los vector
	        patches->back()->GetFormFactors()->push_back(ff);
	    }
	    else
	    {
	        std::cout << "Error detected in file " << filename << " on line "
	            << line_num << std::endl;
	        std::cout << "Line is: " << buffer << std::endl;
	        exit(1);
	    }

    	// Clear the buffer
	    memset(buffer, 0, INPUT_BUFFER_LEN);
	}

	// convert the los ids into pointers
	std::vector< std::vector<int> >::iterator los_iter = los.begin();

	for (int index = 0; los_iter != los.end(); ++los_iter)
	{
	    std::vector<int>::iterator iditer = los_iter->begin();

	    for (; iditer != los_iter->end(); ++iditer)
	    {
	        patches->at(index)->AddViewablePatch(patches->at(*iditer));
	    }

	    if (patches->at(index)->GetViewablePatches()->size() !=
	        patches->at(index)->GetFormFactors()->size())
        {
	        while (patches->at(index)->GetFormFactors()->size() <
	               patches->at(index)->GetViewablePatches()->size())
            {
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
