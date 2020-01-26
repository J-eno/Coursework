This is a boids simulation

NOTE: I planned on implementing food for extra credit, but I couldn't access a linux environment for a few days to test my simulation
      In an attempt to gain extra credit, I've included some cool .outs that I made by tweaking values
      MY FULL SIM IS sample00.out

USAGE:
./proj5: uses default values "sample.in" and "sample00.out"

./proj5 <input> <output>: uses input and output file of your choice

TO WATCH ANIMATION:
./viewer <outputFile>.out

INPUT:
The first line of the input file contains a number of parameters of the boids system:
size neighbor_radius num_neighbors mass collision centering velocity hunger damping dt length
size is the size of the boid. This is useful for telling if the boid has consumed food. 
neighbor_radius is the distance the boid can see, any boid farther than neighbor_radius is ignored. 
num_neighbors is the maximum number of neighboring boids to process. mass is the mass of the boid. 
collision, centering, and velocity are weights for these various forces. hunger is a weight for the force that draws boids to the nearest food. 
damping is a "mass proportional damping" constant. Multiply the velocity by this constant every timestep. 
dt is the timestep size. length is the length of the animation.
After that boids and food are specified. 
The next line has the number of boids, nboids, followed by nboids lines with two Vector3, the first is position, the second is initial velocity. Then the number of pieces of food, nfood, followed by nfood lines with two Vector3s (again, position followed by velocity) and a float that give the time that the food should be added to the system.

Output
The first line is the number of frames, nframes. This is followed by nframes of frame data. Each frame consists of boids and food. 
The first line of a boid segment contains the number of boids, nboids, followed by nboids lines with position and velocity (similar to the input). 
The food segment has the number of pieces of food, nfood, followed by nfood lines with the food position.

MAKEFILE:
I used my own makefile for this. It doesn't touch viewer.cpp or the kdTree files. I used the viewer executable given to us already.

