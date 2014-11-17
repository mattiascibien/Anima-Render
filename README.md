# Anima Render

Anima Render is a OpenGL 2.0 scene renderer that started as a university project and then eveolved into an open-source (BSD licensed) one.

[![Build status](https://ci-beta.appveyor.com/api/projects/status/bka7f0u6915xieb0)](https://ci-beta.appveyor.com/project/mattiascibien/anima-render-456)

## Features

 * Rendering of obj models
 * Support for TGA, PNG and BMP textures
 * Experimental support for drawing optimized primitives
    * Cube
    * Quad
    * Geosphere
    * Tesselated sphere
 * Support for shaders including fullscreen effects (some of them are included in the repository [anima-render-content](https://bitbucket.org/anima-render/anima-render-content))
 	* PhongBlinn Lighting
 	* Cook Torrance Lighing
 * Multiple cameras (cycle with 'O' and 'P')