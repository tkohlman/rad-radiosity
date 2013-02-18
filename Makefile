#
# Created by gmakemake (Ubuntu Dec 29 2011) on Sat Jul 14 08:35:48 2012
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.s) -o $@ $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

AS =		as
CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.s = $(AS) $(ASFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

#
# This header.mak file will set up all necessary options for compiling
# and linking C and C++ programs which use OpenGL and/or GLUT on the
# Ubuntu systems.
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
INCLUDE =
LIBDIRS =

LDLIBS = -lglut -lGLU -lGL -lXext -lX11 -lm

CFLAGS = -g $(INCLUDE)
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES =	Color.cpp FormCalculator.cpp Hemicube.cpp Patch.cpp PatchCalculator.cpp Point.cpp Radiosity.cpp RadiosityCalculator.cpp RadiosityReader.cpp Rectangle.cpp Shape.cpp SightCalculator.cpp Vector.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	Color.h FormCalculator.h Hemicube.h Patch.h PatchCalculator.h Point.h RadiosityCalculator.h RadiosityReader.h Rectangle.h Shape.h SightCalculator.h Vector.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Color.o FormCalculator.o Hemicube.o Patch.o PatchCalculator.o Point.o RadiosityCalculator.o RadiosityReader.o Rectangle.o Shape.o SightCalculator.o Vector.o 

#
# Main targets
#

all:	Radiosity 

Radiosity:	Radiosity.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o Radiosity Radiosity.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Color.o:	Color.h
FormCalculator.o:	Color.h FormCalculator.h Hemicube.h Patch.h Point.h Rectangle.h Shape.h Vector.h
Hemicube.o:	Color.h Hemicube.h Patch.h Point.h Rectangle.h Shape.h Vector.h
Patch.o:	Color.h Patch.h Point.h Vector.h
PatchCalculator.o:	Color.h Patch.h PatchCalculator.h Point.h Rectangle.h Shape.h Vector.h
Point.o:	Color.h Point.h
Radiosity.o:	Color.h FormCalculator.h Hemicube.h Patch.h PatchCalculator.h Point.h RadiosityCalculator.h RadiosityReader.h Rectangle.h Shape.h SightCalculator.h Vector.h
RadiosityCalculator.o:	Color.h Patch.h Point.h RadiosityCalculator.h Vector.h
RadiosityReader.o:	Color.h Patch.h Point.h RadiosityReader.h Rectangle.h Shape.h Vector.h
Rectangle.o:	Color.h Point.h Rectangle.h Shape.h Vector.h
Shape.o:	Color.h Point.h Shape.h Vector.h
SightCalculator.o:	Color.h Patch.h Point.h SightCalculator.h Vector.h
Vector.o:	Vector.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) Radiosity.o core

realclean:        clean
	-/bin/rm -f Radiosity 
