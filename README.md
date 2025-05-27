# DogoEngine
## Why am I doing this?

This is a game engine I'm writing for a better understanding of the architecture of a larger project, better C++ and graphics programming.
Afer I get the engine in a good state with OpenGL I will introduce Vulkan to get my hands on a recent API.

The engine is a static library, the editor will be a executable (once I get UI going) and the game will be a DLL so I can hot reload. Once it's time to build for distribuition the editor will be disregarded and the game will be built as an executable. At least that's the plan.
I know with cmake there's a way to load all function pointers of the DLL so everything gets loaded even if not used, but I'd rather if premake had that option, I'll have a look.

Will be developing on my free time out of a full-time job so it might take a while. Got other projects going on aswell.


## Build Instructions
Run "GenerateProjects.bat" or "GenerateProjectsLinux.sh".

It's made to create a VS2022 solution file on Windows and makefiles on Linux by default, alter as you wish by consulting premake's supported targets:

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

## Examples
Pong made with the 2D Renderer (src: Pong in Examples):

https://github.com/user-attachments/assets/ef83634d-ad5d-42e6-9592-23ba7e08ada8

## Implementation details

2D Batch Renderer which can render Quads, Lines (2 vertices or 4 vertices), Circles and Triangles.

3D Renderer can render 3D Objects and Lines natively, although it is not batched. I will develop a batched version when 2D Renderer is in a good spot and make a small game.

PhysX is integrated, with more functionality to introduce. The DLLs are not included here and need to be built independently. I will consider making it part of the build process, or simply distribute them along with the engine, or build it statically aswell.

Editor is in progress, but I need more functionality with UI. Successfully draws game layer to framebuffer and renders to viewport, handling input.

3D (Just two models and a few lines, nothing exemplary yet):

![image](https://github.com/user-attachments/assets/2ed5c1ed-5513-444a-b491-f7ce831189d3)

## Usage
To be added soon.

## License

[MIT](https://choosealicense.com/licenses/mit/)
