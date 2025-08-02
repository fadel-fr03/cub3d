# cub3D

![Language](https://img.shields.io/badge/language-C-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)

cub3D is a graphical 3D rendering engine developed as part of the 42 School curriculum. It mimics the mechanics of early 90s first-person shooters like Wolfenstein 3D using raycasting to simulate a 3D perspective from a 2D map. The player navigates through a grid-based world rendered in real time using custom textures and controls.

## 📚 Table of Contents

* [🧠 Project Objective](#-project-objective)
* [📁 Project Structure](#-project-structure)
* [🚀 How to Run](#-how-to-run)
* [🔍 Features](#-features)
* [🧪 Map Format and Configuration](#-map-format-and-configuration)
* [📸 Example Code Snippets](#-example-code-snippets)
* [⚙️ Core Components Breakdown](#️-core-components-breakdown)
* [🛠️ Requirements](#️-requirements)
* [✅ Testing & Validation](#-testing--validation)
* [📜 License & Credits](#-license--credits)

## 🧠 Project Objective

The goal is to build a fully working 3D renderer using raycasting principles. It includes map parsing, texture rendering, user interaction, and game loop mechanics.

Key Objectives:

* Parse and validate `.cub` map files.
* Set up a 2D grid representing a game world.
* Use raycasting to render vertical wall slices.
* Apply textures to walls based on direction.
* Handle user input via keyboard and mouse (bonus).
* Ensure proper map constraints (closure, player spawn, texture format).

## 📁 Project Structure

```
cub3d/
├── Makefile
├── includes/
│   ├── cub3d.h
│   ├── structs.h
│   └── bonus.h
├── libft/
│   └── (Libft source files...)
├── maps/
│   ├── good/
│   └── bad/
├── minilibx-linux/
│   └── (MLX source files...)
├── src/
│   ├── bonus/               # Minimap, mouse POV rotation
│   ├── events/              # Keyboard input logic
│   ├── graphics/            # MLX and image rendering
│   ├── parsing/             # Map and texture parsing
│   ├── raycasting/          # Rendering engine
│   ├── utils/               # Cleanup, error handling
│   └── main.c               # Entry point
├── textures/                # XPM texture sets (Minecraft, test...)
```

## 🚀 How to Run

```bash
make
./cub3D maps/good/subject_map.cub
```

## 🔍 Features

### ✅ Mandatory

* Parse `.cub` configuration and map files
* Validate map integrity (closed, one player, texture paths)
* Raycasting rendering engine
* 4-way textured walls based on ray hit direction
* Color-coded floor and ceiling
* Player movement using `W`, `A`, `S`, `D` keys
* Left/right camera rotation with arrow keys

### ✨ Bonus Features

* Wall collision system (no clipping through walls)
* Minimap showing position and vision cone
* Mouse movement to rotate player's field of view
* Window close detection (graceful exit)

## 🧪 Map Format and Configuration

A valid `.cub` file must contain:

* Texture paths:

  ```
  NO ./textures/north.xpm
  SO ./textures/south.xpm
  WE ./textures/west.xpm
  EA ./textures/east.xpm
  ```
* RGB values:

  ```
  F 220,100,0     # Floor color
  C 225,30,0      # Ceiling color
  ```
* A valid map layout with `1`, `0`, and one `N`, `S`, `E`, or `W`:

  ```
  111111
  100001
  1000N1
  111111
  ```

## 📸 Example Code Snippets

### 🧱 Raycasting Loop

```c
while (x < WIN_WIDTH)
{
    init_ray(&ray, game, x);
    calculate_step_and_side_dist(&ray, game);
    perform_dda(&ray, game);
    calculate_wall_height(&ray, game);
    calculate_texture_coordinates(&ray, game, &tex_num);
    draw_vertical_line(game, x, &ray, tex_num);
    x++;
}
```

### 🎮 Player Input (WASD + Arrows)

```c
if (keycode == KEY_W) game->keys[K_W] = 1;
else if (keycode == KEY_D) game->keys[K_D] = 1;
else if (keycode == KEY_ESC) close_window(game);
```

### 🎨 Texture Drawing

```c
while (y <= ray->draw_end)
{
    tex_y = (int)tex_pos;
    color = get_texture_color(&game->textures[tex_num], ray->tex_x, tex_y);
    my_mlx_pixel_put(&game->mlx, x, y, color);
    tex_pos += step;
    y++;
}
```

### 🪟 MLX Setup

```c
game->mlx.mlx = mlx_init();
game->mlx.win = mlx_new_window(...);
game->mlx.img = mlx_new_image(...);
game->mlx.addr = mlx_get_data_addr(...);
```

## ⚙️ Core Components Breakdown

* **raycasting/** – Implements the DDA algorithm, wall height logic, camera projection.
* **graphics/** – Low-level MLX calls for drawing pixels, applying textures.
* **events/** – Keyboard and mouse hooks (keypress/release, movement).
* **parsing/** – File reader, map validation (walls closed, valid characters).
* **utils/** – General-purpose helpers, cleanup, RGB conversion.
* **bonus/** – Minimap rendering, mouse POV support, etc.

## 🛠️ Requirements

* GCC/Clang compiler
* Linux or macOS
* `make`
* X11 (included via minilibx)

## ✅ Testing & Validation

* ✅ Valid maps with each direction: `N`, `S`, `E`, `W`
* ❌ Maps with multiple player spawns ➜ Error
* ❌ Open maps ➜ Error
* ✅ Correct texture path ➜ Success
* ❌ Bad `.xpm` path ➜ Error
* ✅ Floor and ceiling RGB values within `0–255`

## 📜 License & Credits

This project is part of the 42 School curriculum. Educational use only.

**Credits (GitHub usernames):**

* [fadel-fr03](https://github.com/fadel-fr03)
* [ahmadmnsur](https://github.com/ahmadmnsur)
