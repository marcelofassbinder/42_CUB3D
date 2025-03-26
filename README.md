<h1 align=center>
 42_CUB3D 🕹️
</h1>

<div align=center>
  A 3D FPS game exploring Raycasting algorithm.
</div>
<br />

<h2 align=center>
MANDATORY
</h2>

<div align=center>
 
![cub3d_demonstration](gif/cub.gif "cub3d")

</div>

<h2 align=center>
BONUS
</h2>

<div align=center>
 
![cub_bonus](gif/cub_bonus.gif "cub3d bonus")

</div>

# About ✍
As part of the Milestone 04 of the 42 Common Core curriculum, Cub3D is a fun project, aiming to make a dynamic view inside a maze, in which you’ll have to find your way. Inspired by Wolfenstein, the first "First Person Shooter" game ever, we utilize the raycasting algorithm to create the sense of tridimensional views through the game. The goal of this project is not to develop a fully playable game, but rather to study and understand 3D rendering and explore graphics management techniques.

# Raycasting ⚡
Raycasting is a rendering technique used to create a 3D perspective from a 2D map. By casting rays from the player's position, we calculate the distance from the starting point of each ray to the point where it intersects a wall. Based on this distance, we determine the height of the wall for that specific ray. Each horizontal pixel on the screen receives a ray; therefore, if the screen is 200 pixels wide, 200 rays are cast in each frame.

I based my implementation on the article [Raycasting](https://lodev.org/cgtutor/raycasting.html) by Lode Vandevenne, which was incredibly helpful in guiding me step by step through the algorithm.

# Parsing 🧩
The parsing was also a big deal in the project. The program receives, as an argument, a ``.cub`` file, which must contain the following atributes:
- a map, composed of only 6 possible characters: ``0`` for an empty space, ``1`` for a wall, and ``N``,``S``,``E`` or ``W`` for the player’s start position and spawning orientation;
- four textures, that is the path to the image to be rendered at the wall, for North (``NO``), South (``SO``), East (``EA``), West (``WE``);
- two colors, written as an RGB code, for Floor (``F``) and Ceiling (``C``);

Example of a valid ``.cub`` file:
```text
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
# How to play 🎮



