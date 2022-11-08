# Based Game Engine
A Game Engine built alongside TheCherno's Game Engine series.<br>
Although the original is a Windows build, this is a Mac OSX build.

#### Development Status: 
    Early Development
    Not Ready for Deployment
#### Current Assignment:
    Developing an optimal 2D Renderer   
    
### Description
This game engine is developed in C++ with a few submodules like glfw, glad, and glm that use their own language. It is a dynamic library (Based) linked to a console application (Sandbox). Eventually, there will come a change of the dynamic library to a static library. This is not as easily achievable within premake on Mac OSX as it is on Windows apparently -- *currently* is not a problem for the build -- so I have yet to make that change. The Based Engine at the moment strictly uses OpenGL as the rendering library but will in the future have the ability to incorporate other rendering libraries such as vulkan and bgfx. The ability to easily include new libraries is being setup in the early stages of development to make it much easier when the time comes to include them. The Log is made with a simple wrapper around gabime's spdlog to log on the development side of the Based Engine and the application side. The Based Engine has yet to include it's own math library so at the moment glm is the main source of math based functions. Recently, blending was implemented. While if someone was determined enough to build a game with this engine, they could definitely build a 2D game with this engine, the engine is set up more for 3D rendering at the moment so it is not advised to build a game with this engine currently.

### Difficulties
The biggest difficulty having faced this engine is the determination to create this engine on Mac OSX and within the Neovim text editor. Being a newcomer to both Mac OSX and Neovim, this was a massive task. Although, this struggle has brought a lot of knowledge regarding the introduction of compile_commands.json within C++ projects and the deprecation of OpenGL within Apple products. If I were to start this project over, I would use a different rendering library such as bgfx as it has a similar syntactical simplicity to OpenGL and is not deprecated by Apple products.

The overarching goal of this project is to understand the full process of developing AAA game engines and to hone my C++ skills. 

### Building
#### Currently only buildable on Mac OSX<br>
If you do so desire to build this project, I have incorporated all the premake files and a GenerateProject.sh that should build and run the project. This build requires `make`.<br>
Once properly cloned run `sh GenerateProject.sh` in the root of the repository. 
