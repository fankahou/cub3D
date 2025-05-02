# cub3D

To-do list:

Parsing:
- check_map() for enclosed map
- check all ./ texture paths in the file

Drawing:
- Need to make draw_floor and draw_ceiling better since theres a lot of protections missing.
- Dda algo can be shorter and more protected as well, but images are being generated and redisplayed all at once 👍

Ka Hou:

1.5
Basic parsing done


Valentino:

0.85 of raycasting done.

Added scaling for texture generation, if raycast is out of bounds we generate texture based on orientation,
but you can still walk out of the matrix if its not enclosed.
There are some issues when the map is not exactly rectangular since for testing purposes the map is hardcoded.
Still no segfaults and no leaks 👍
(+++) Added +5 texture packs with crazy examples (+++)
