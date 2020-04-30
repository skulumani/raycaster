![map](./doc/map.gif) ![proj](./doc/proj.gif)


# Raycaster

* [ ] Render everything using Vulkan
* [ ] Setup KB inputs using GLFW
* [ ] Link to teensy for attitude
* [ ] Procedural generation of a random 2D map with walls/obstacles
* [x] Method to add blocks to map
* [x] Different colors of cubes in map
* [ ] draw floors and ceilings
* [ ] [texture mapping](https://lodev.org/cgtutor/raycasting.html)
* [x] Shade wall colors based on h_dist or v_dist
* [x] fix reference frame between grid coord, output map, and point coord

## Gifs

~~~
convert -delay 10 -loop 0 {0..359}_rotate_map.jpg map.gif
~~~

# References

* https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
* https://lodev.org/cgtutor/raycasting2.html
* https://github.com/ssloy/tinyraycaster/wiki/Part-2:-texturing-the-walls
* https://github.com/ahuth/raycast/
* http://www.playfuljs.com/a-first-person-engine-in-265-lines/
* https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
* [Wolf textures](http://www.wolfenvault.com/resources.html)
