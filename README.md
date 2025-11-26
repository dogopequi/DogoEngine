# DogoEngine
## Why am I doing this?

This is a game engine I'm writing for a better understanding of the architecture of a larger project, better C++ and graphics programming.
Afer I get the engine in a good state with OpenGL I will introduce Vulkan to get my hands on a recent API.

The engine is a static library, the editor will be a executable (once I get UI going) and the game will be a DLL so I can hot reload. Right now, the sandbox is just a static library when you build the project for Editor, though.

Will be developing on my free time out of a full-time job so it might take a while. Got other projects going on aswell.


## Build Instructions
Run "GenerateProjects.bat" or "GenerateProjectsLinux.sh".

[Premake](https://premake.github.io/docs/using-premake)

## Goals
- Lightweight
- Reasonably performant
- Easy to use

## Dependencies
The licenses can be found in their respective folder.
- [Premake](https://premake.github.io/)
- [assimp](https://github.com/assimp/assimp)
- [stb](https://github.com/nothings/stb)
- [glm](https://github.com/icaven/glm)
- [glad](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw) (submodule)
- [PhysX](https://github.com/NVIDIA-Omniverse/PhysX)
- [FreeType](https://freetype.org/)
- [DogoECS](https://github.com/dogopequi/DogoECS)
- [imgui](https://github.com/ocornut/imgui)

## Examples
Pong made with the 2D Renderer (src: Pong in Examples):

https://github.com/user-attachments/assets/ef83634d-ad5d-42e6-9592-23ba7e08ada8

## Implementation details

2D Batch Renderer which can render Quads, Lines, Circles and Triangles.

3D Renderer can render 3D Objects and Lines natively, although it is not batched. I will develop a batched version when 2D Renderer is in a good spot and make a small game.

PhysX is integrated, with more functionality to introduce. The DLLs are not included here and need to be built independently. I will consider making it part of the build process, or simply distribute them along with the engine, or build it statically aswell.

Editor is in progress, but I need more functionality with UI. Successfully draws game layer to framebuffer and renders to viewport, handling input.

3D (Just two models and a few lines, nothing exemplary yet):

![image](https://github.com/user-attachments/assets/2ed5c1ed-5513-444a-b491-f7ce831189d3)

## Usage
To be added soon. I want to make a documentation page once it's somewhat stable.

## License

[MIT](https://choosealicense.com/licenses/mit/)
