# Sdf Render
A simple signed distance field based renderer.

![Example Render](/output/example2.png)

---

### Features
- Several sdf shapes that can be combined with hard and soft boolean operations
- Directional and point lights
- Blinn-Phong shader with settings for color, roughness and light influencess
- Loading scenes from files (see syntax in `scenes/syntax.md`)

---

### Requirements
- C++17 or later
- Tested on Linux, should probably work on other OSs as well
- Ability to display or convert pnm image files

---

### Running
You can configure the shader by editing `src/settings.h`. There, at the bottom, you should also set the output path and optionally at the top the scene file to be loaded.  
Run `compile.sh` or its equivalent on your system to generate the executable. You will need to recompile every time you change `src/settings.h`.
