# Syntax of .sdfscene files

Here you can see the syntax the .sdfscene files use. See the other files in this directory for examples. If you load a .sdfscene file, it will replace the *Camera*, *Objects* and *Lighting* sections in `src/settings.h`.
Key characters are **case-sensitive**!  
If a parameter has multiple elements, write them separated by spaces: a b c (not a, b, c)  
There are currently barely any error messages regarding the syntax, but if it throws a segmentation fault, gets stuck or does something else weird it's probably a mistake in the scene file. You can use the terminal output to figure out roughly where the problem was.

---

### General syntax
`Key: parameter1 | parameter2 | parameter3`...  

### Comments
Lines starting with a `#` are ignored.

---

### Set camera
If not set, defaults to settings in `src/settings.h`.  

`C: position | rotation | fov`


### Add objects
You always have to add **at least one** object! The first one you add will always be treated like a hard union object, no matter what you specify.  

modes:
- `1` for union
- `2` for difference
- `3` for intersect

###### Sphere
`s: position | scale | rotation | mode | smoothing`

###### Cube
`c: position | scale | rotation | mode | smoothing`

###### Cylinder
`y: position | scale | rotation | mode | smoothing`

###### Floor
`f: position | scale | rotation | mode | smoothing`


### Add lights
Optional

###### Directional light
`d: direction | color | power`

###### Point light
`p: position | color | power`
