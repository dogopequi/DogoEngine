# Dogo
Dogo Engine

A game engine I'm writing for a better understanding of the architecture of a larger project, better C++ and graphics programming.
Right now OpenGL and Direct3D11 are pretty much at the same stage, I think I will focus more on OpenGL as I test it both on Windows and Linux right after I'm done with Linux input and events, and soon later bring D3D11 up to speed.
Of course once I get it into a nicer state, I want to add Vulkan and D3D12.

The engine is a static lib, the editor will be a executable (once I get UI going) and the game will be a DLL so I can hot reload. Once it's time to build for distribuition the editor will be disregarded and the game will be built as an executable. At least that's the plan.
I know with cmake there's a way to load all function pointers of the DLL so everything gets loaded even if not used, but I'd rather if premake had that option, I'll have to look it up.

Will be developing on my free time out of a full-time job so it might take a while.
