# Voronoi-Diagram-Sweep-Circle-Algorithm-
The program is to construct a 2D Voronoi Diagram for several given points by a gradually expanding sweep circle centered at a given query point

The main source code is Sweepcircle.cpp. 

# Prerequisite

OpenGL 

Webpage: https://www.opengl.org/

# Description

The program computes the Voronoi Diagram of a set of given points in the 2D plane. We simply generate 1000 random ponts as shown in Line 43. The program construct the Voronoi Diagram by using a sweeping circle algorithm. Specifically, it maintains a circle centered at a query point (in this implementation (0, 0)) and the part of Voronoi Diagram inside the circle is fully constructed. The circle initially has a zero radius and it is enlarged gradually until the Voronoi Diagram is totally constructed. 

The program could be very useful in a Voronoi Diagram-based algorithm A which also has a query point. A benefit of constructing the Voronoi Diagram with this sweeping circle is that the construction could stop earlier when enough points are considered in A and a large amount of distant points with respect to the query point is pruned. 
