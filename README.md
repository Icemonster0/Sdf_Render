# Sdf Render
A simple signed distance field based renderer.

---

### Features
- Several sdf shapes that can be combined with hard and soft boolean operations
- Directional and point lights
- Blinn-Phong shader with settings for color, roughness and light influencess

---

### Requirements
- C++17 or later
- Tested on Linux, should probably work on other OSs as well?
- Ability to display or convert pnm image files

---

### Running
You can configure the shader by editing `src/settings.h`. There, at the bottom, you should also set the output path.  
Run `compile.sh` or its equivalent on your system to generate the executable.
