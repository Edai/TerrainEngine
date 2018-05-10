FUNDAMENTALS OF COMPUTER GRAPHICS -  PROJECT REPORT

Author: Valentin KAO <valentin.kao@epitech.eu>
		张有请 - 2017280242
		
The purpose of this project is to implement an OpenGl program with particle
system : 
- The particle size varies and simulate a direction of snowflake
- Less snow at the beginning, slowly increasing over time

---------------------------------------------------------------------------
VIDEO CAPTURE
---------------------------------------------------------------------------

The video capture of my program named screenrecord.mp4, is available from
the root of the folder.
0s -> 13s : Normal speed
13s -> 24s : Speed up a lot, to show that number of snowflakes increase.
24s -> End : normal speed with a lot of snowflakes
---------------------------------------------------------------------------
REQUIREMENTS
---------------------------------------------------------------------------
•	GCC 5 or later
•	CMake 3.9 or later
•	OpenGL, GLUT and SOIL libraries.
The code hasn't been tested on Windows but should work on Visual Studio
2015 and later.

---------------------------------------------------------------------------
BUILD AND USAGE
---------------------------------------------------------------------------
From the folder in which you found this report, please enter the following
command lines.
1.		mkdir build && cd build
2.		cmake ..
3.		make

Once the compilated was successful, you can execute the program. 
Here is the usage of the program.

	./SnowStorm [--width=x] [--height=y] [--title=”Assignment”]
	
---------------------------------------------------------------------------
FLAGS – OPTIONS	DESCRIPTION	DEFAULT
---------------------------------------------------------------------------
width, w	Set the width of the window	900
height, h	Set the height of the window	900
title, t	Set the title of the window	“Assignment”


---------------------------------------------------------------------------
SOFTWARE DESIGN
---------------------------------------------------------------------------
In order to implement future project easily, I define a simple application
design. Those three classes are singletons avoiding any multiple instances.

Application class is in charge of parsing the arguments and to init the
graphical core of the program with the input window size or the input
window name. 

GraphicalCore initializes OpenGL engine : window creation, keyboard handler,
mouse handler, reshape handler, etc.

Engine is the core of the project : In change of enabling/disabling some 
features of OpenGL, it will contain the main function of update. It will
also clear the window, setup the background and call the Particle Manager

ParticleManager will be the main engine of the particles. It will init
all the particles by loading the texture, create the elements in a vector
and render each elements of the vector. 

---------------------------------------------------------------------------
ALGORITHM IMPLEMENTED
---------------------------------------------------------------------------

If you look at the function Update of the Engine class, you will this algo-
rithm :
-   After activating GL_TEXTURE_2D, it draws the background by using drawing
 a square textured.
-   It enables blending and texturing. It loads the texture if the texture is
not loaded yet. Otherwise, it binds the texture loaded.

It calls then the function Render of ParticleManager by passing the deltaTime
as parameter : Each particles has a position, a velocity and a size.
The function Render updates the positions of the particles depending on their
own velocities and the delta time. If the particle is out of the window, it
resets its position to the top of the window instead of erasing it.

A new particle is created each 0.25 second.

---------------------------------------------------------------------------
FUNCTIONNALITIES
---------------------------------------------------------------------------
By pressing the key ESC, you close the program properly.
By pressing the arrow UP, the refresh speed of the window increases and
snowflakes go down faster, otherwise, pressing the arrow DOWN decreases it.