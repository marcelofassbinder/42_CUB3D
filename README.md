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
The player starts at the spawn position ``N``, ``S``, ``W`` or ``E`` with the corresponding orientation and can walk through the map, using the following buttons:

### Movement
- ``W`` - Moves the player front.
- ``A`` - Moves the player to the left.
- ``S`` - Moves the player back.
- ``D`` - Moves the player to the right.

### Rotation
- ``⬅️`` - Rotates the player to the right (clockwise).
- ``➡️`` - Rotates the player to the left (counterclockwise).

### Window management
- ``ESC`` or click ❌ - Closes the window.

### Bonus Buttons
- ``Backspace`` - Opens/closes the door.
- ``Left mouse button`` - Fires the shotgun. 
- ``Right mouse button`` - Reloads the shotgun. 
- ``Move mouse cursor to the right`` - Rotates the player to the right (clockwise).
- ``Move mouse cursor to the left`` - Rotates the player to the left (counterclockwise).

# Bonus ⭐
For the bonus section, we were required to add some extra features as:
- A minimap system.
- Doors which can open and close.
- Adding some sprite animation (shotgun and reload)
- Rotate the point of view with the mouse.
  
# Usage 🖥️
To install and play Cub3D, follow these steps:
- First, make sure you have the following dependencies installed in your machine: GCC (GNU Compiler Collection), X11 libraries and development headers and Minilibx: a simple X-Window (X11R6)
- Clone the repository:
```bash
git clone git@github.com:marcelofassbinder/42_CUB3D.git
```
- Navigate to the project directory and run ``make`` to compile the program:
```bash
cd 42_CUB3D
make
```
- Run the program providing a valid map, for example:
```bash
./cub3D maps/mandatory/game.cub
```
You can replace the ```maps/mandatory/game.cub``` for any valid map of your choice. The program will read the input and start the game. Good luck!

- To enjoy the bonus part, follow:
```bash
make bonus
```
- Run the program providing a valid map, for example:
```bash
./cub3D_bonus maps/bonus/game.cub
```
You can replace the ```maps/bonus/game.cub``` for any valid map of your choice. The program will read the input and start the game. Good luck!

# Grade  <p><img height="30px" src="https://img.shields.io/badge/-125%20%2F%20100-success" /></p>

# Norminette 💂🏻
At 42 School, we need to follow some strict rules when writing our code. These rules are described in the Norm and checked by the formidable `norminette`. Here are some of them:
```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be maximum 25 lines
- One single variable declaration per line
- You can’t declare more than 5 variables per function
- You can't write more than 5 functions per file
...
```
[Click here](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) to review the complete Norm document.
