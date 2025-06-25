# Mini DOOM-like Renderer (C, CPU-only)

A lightweight 2.5D rendering engine inspired by DOOM, built purely in C using MiniLibX.

## Main Features

* Built-in map editor
* Custom internal window manager with event dispatching
* Full CPU-based 2.5D rendering
* Dynamic BSP partitioning and portals for optimized rendering
* Software-based post-processing effects: shading, posterization, camera deformation
* Basic entity system
* Smooth player controls with collision handling

## Technologies

* Pure C implementation without standard libc (custom implementation)
* [MiniLibX](https://github.com/42paris/minilibx-linux) (basic wrapper on X11)

## Demo

### Gameplay 
![game screenshot](docs/screenshots/game.avif)

### Map Editor
![editor screenshot](docs/screenshots/editor.avif)


## 🔧 Build and Run (Linux Only)

```bash
# Recursive clone (includes MiniLibX)
git clone --recurse-submodules <repo>

# Compile
make

# Run with example map
./cub3D maps/nice_map.cub
```


## Resources

* [Doom-style 3D engine in C (Bisqwit)](https://www.youtube.com/watch?v=HQYsFshbkYw)
* [Quake renderer overdraw optimization](https://www.youtube.com/watch?v=zdXsHWHxeBY)
* [Binary Space Partitioning in 3D rendering](https://www.youtube.com/watch?v=yTRzfKh4Tg0)
* [Texture mapping and rasterisation (Wikipedia)](https://en.wikipedia.org/wiki/Texture_mapping#Rasterisation_algorithms)
