## Wolfenstein3D
_[full version in pdf](https://github.com/gerus66/wolfenstein3d/blob/master/readme/wolf3d.en.pdf)_ \
Simplyfied version of Wolfenstein3D engine _[(wiki)](https://en.wikipedia.org/wiki/Wolfenstein_3D)_, using raycasting rendering

### Run
_macos:_ \
`make & ./wolf [path_to_map]`

_linux: in progress_

`map` should be table of zeros and non-zero numbers (see [default.map](https://github.com/gerus66/wolfenstein3d/blob/master/default.map), for example). \
Height of walls isn't implemented, so the value of numbers doesn't matter.

### Control options:
* move by `WASD`
* turn by `<` `>` or by mouse
* move head by `up` `down` or by mouse
* turn on / off mouse by `space`

### Features
* minimap (on / off by `M`)
* music, sounds of steps and wall collisions (on / off by `]`)
* textures on walls and floor (on / off by `T`)
* auto sliding along walls
  
### Screenshots
![wolf](https://github.com/gerus66/wolfenstein3d/blob/master/readme/wolf_1.png)
![wolf](https://github.com/gerus66/wolfenstein3d/blob/master/readme/wolf_2.png)

### Codestyle
Developed in strict accordance with _[Norminette codestyle](https://github.com/gerus66/norme)_ \
Based on selfmade _[libft library](https://github.com/gerus66/libft)_
