///
/// @file Radiosity.cpp
///
/// @author	Thomas Kohlman
/// @date 4 January
///
/// @description
/// 	Main radiosity program.
///

#include "point.h"
#include "patch.h"
#include "radiosityreader.h"
#include "formcalculator.h"
#include "sightcalculator.h"
#include "patchcalculator.h"
#include "radiositycalculator.h"

#include <GL/glut.h>

#include <vector>
#include <cstdlib>
#include <iostream>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define WINDOW_POS_X 100
#define WINDOW_POS_Y 100
#define WINDOW_TITLE "Radiosity"

#define PI 3.141592654

bool show_los = false;
bool show_normals = false;
bool outline_patches = false;


std::vector<Radiosity::Patch*> *Patches;

//
// display
//
void display( void ) {

    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glShadeModel(GL_SMOOTH);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

    // Specify projection; this actually specifies the view Volume/
    // viewWindow
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    glFrustum(-1, 1, -1, 1, 3, 256);

    // Specify viewing/camera/eye coordinate system
    // Observer on Z axis, looking at origin, up is Y axis
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    gluLookAt( 0.0, -0.0, 100.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 );

    std::vector<Radiosity::Patch*>::iterator iter = Patches->begin();

    // Update the corner colors with the weighted average of the centers
    for (; iter != Patches->end(); ++iter) {
        Radiosity::Patch *patch = *iter;
        patch->UpdateCornerColors();
    }

    for (iter = Patches->begin(); iter != Patches->end(); ++iter) {

        Radiosity::Patch *patch = *iter;
        patch->Draw();

        if (outline_patches)
        {
        	patch->DrawOutline();
        }

        if (show_normals)
        {
        	patch->DrawNormal();
        }
    }
/*
    // Show which patches can see each other
    if (show_los) {
        iter = Patches->begin();

        glColor3f(1, 0, 0);
        int count = 0;
        // For each patch
        for (; iter != Patches->end(); ++iter) {

            std::vector<Patch*>::const_iterator cmp_iter =
                (*iter)->GetViewablePatches()->begin();

            ++count;

            for (; cmp_iter != (*iter)->GetViewablePatches()->end();
                ++cmp_iter) {

                Patch *patch1 = *iter;
                Patch *patch2 = *cmp_iter;

                //std::cout << "drawing line!" << std::endl;

                // Draw the los line
                glLineWidth(2);
                glBegin(GL_LINES);

                glVertex3f(patch1->GetCenter().x(), patch1->GetCenter().y(),
                    patch1->GetCenter().z());
                glVertex3f(patch2->GetCenter().x(), patch2->GetCenter().y(),
                    patch2->GetCenter().z());

                glEnd();

            }
        }
    }
*/
    // Display new screen
    glutSwapBuffers();
}


//
// main
//
int main(int argc, char **argv) {

    if (argc != 4) {
        std::cout << "Usage: Radiosity <patch_size> <input file>" <<
            " <num_iterations>" << std::endl;
        exit(1);
    }

    int num_iterations = strtol(argv[3], nullptr, 0);

    float patch_size = strtof(argv[1], nullptr);

    std::vector<Radiosity::Rectangle*> *quads;
    std::vector<Radiosity::Patch*> *patches = new std::vector<Radiosity::Patch*>();

    Radiosity::RadiosityReader myReader;
    quads = myReader.ParseObj(argv[2]);

    // Subdivide into patches
    Radiosity::PatchCalculator patch_calculator(patch_size);
    patch_calculator.Subdivide(quads, patches);

    std::cout << "Using " << patches->size() << " patches..." << std::endl;

    // Calculate line of sight
    Radiosity::SightCalculator sight_calculator;
    sight_calculator.CalculateLOS(patches);

    Patches = patches;

    Radiosity::FormCalculator form_calculator(quads);
    form_calculator.CalculateFormFactors(patches);

    Radiosity::RadiosityCalculator myRadiosityCalculator;
    myRadiosityCalculator.CalculateRadiosity(patches, num_iterations);

    Patches = patches;

   	glutInit( &argc, argv );
   	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
   	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
   	glutCreateWindow(WINDOW_TITLE);

   	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

   	// Callback functions
   	glutDisplayFunc( display );

   	glutMainLoop( );

    // Free up memory ---------------------------------------------------------

    std::vector<Radiosity::Patch*>::iterator patchIter = patches->begin();
    for (; patchIter != patches->end(); ++patchIter) {
        delete *patchIter;
        *patchIter = nullptr;
    }

    delete patches;
    Patches = patches = nullptr;

    return 0;
}


