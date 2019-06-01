## Wolfenstein3D
Движок одноименной игры ([здесь](https://github.com/gerus66/wolfenstein3d/blob/master/readme/wolf3d.en.pdf) подробнее).

Вычисления по принципу _raycasting_, текстуры и озвучка на _SDL2_
### Run
_macos_: `make & ./wolf [path_to_map]`

_linux_: в процессе тестирования

При запуске без аргументов откроется карта _maps/default.map_, но Вы можете указать путь к любому другому файлу.

Карта прямоугольная, состоит из нулей(открытое пространство) и любых других чисел(стены).
### Управление

`WASD` передвижение

`left` `right` поворот (то же на мышке)

`up` `down` поднять / опустить голову (то же на мышке)

`M` включить / выключить миникарту

`T` включить / выключить текстуры на стенах и полу

`]Ъ` включить / выключить музыку и звуки

`space` включить / выключить мышку
### Эффекты
* музыка
* звук шагов при передвижении
* звук при столкновении со стенами
* скольжение вдоль стен
### Скриншоты
![wolf](https://github.com/gerus66/wolfenstein3d/blob/master/readme/wolf_1.png)
![wolf](https://github.com/gerus66/wolfenstein3d/blob/master/readme/wolf_2.png)
### Codestyle
Проект написан в строгом соответствии с [Norminette codestyle](https://github.com/gerus66/norme)
