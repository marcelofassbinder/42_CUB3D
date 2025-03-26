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
Raycasting is a rendering technique used to create a 3D perspective based on a 2D map.Through the launch of rays a partir da posicao do player, faz-se o calculo da distancia deste raio desde seu ponto de partida ate o encontro de uma parede. Baseado nisso, calculamos qual vai ser a altura da parede para aquele determinado raio. Cada pixel horizontalmente recebe um raio, portanto se temos uma tela de 200 pixels, 200 raios serao lancados a cada renderizacao. 

