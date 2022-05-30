# OpenGL-Game

This program is a game based on something i started in SDL2. This was in 2D so had to start from scratch, using some ideas from the original. 

![image](https://user-images.githubusercontent.com/74846782/170986966-149e9725-1199-4d54-b198-2d6b24698446.png)
    -- Original game idea --

Most this program is referenced from series of tutorials found here http://www.opengl-tutorial.org/ 
many of the files are exact copies including source files - controls.cpp, objloader.cpp, shader.cpp, text2D.cpp, texture.cpp, vbdoindexer.cpp,
and header files - controls.hpp, objloader.hpp, shader.hpp, text2D.hpp, texture.hpp, vboindexer.hpp 
and shader files - StandardShading.fragmentshader, StandardShading.vertexshader, TextVertexShader.fragmentshader and TextVertexShader.vertexshader.

The main Source.cpp is also based on the tutorials but heavily modifed by me. The main idea was to create a simple scrolling shooter but in 3D and using simple cubes for the retro look/design. It has the player shoot the cubes for points and looses a life if the cubes hit the player. Also loosly based on the Google Dinosaur game as it gradually gets faster the more you progress and try to get a high score.

The main algorithms made the cubes move from right to left and instead of creating new objects the cubes would 'respawn' back to the right when destroyed or went off screen. They also used random functions to reposition themselves on the x or y axis. Every time one cube would repsawn from going off screen the game speeds up, motivating the player never to let one pass.

Collision detection was needed for the cubes to hit the player to lose a life, and for the cubes to be destroyed by the players laser. I used a simple AABB collision from the 2D version of the game. This system seemed fine for this situation as I didnt use the z axis too much and the game was close to being 2D.

I did have a fully working camera but i locked it in position to get the '2D' view. I also implemetned simple controls for the player, i didnt end up needing gravity as player is hovering like a space craft. I also added a simple text UI to show score, lives, time passed.

If i had more time I would add sound and particle effects to the laser and cubes being destroyed. I could of also had shooting enemies and power ups/events etc.

Controls:

Esc = Quit
WASD = Player Movement
Space = Shoot

![image](https://user-images.githubusercontent.com/74846782/170994293-1c5e49a2-7ea3-4487-87f3-72f831124bd5.png)
-- Screenshot -- 





