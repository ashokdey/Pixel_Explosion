# Pixel Explosion Animation
This application is made using **SDL2** and **C++**. 

###What it does?
It draws the pixels on the screen with **_swirl animation_** with little amount of blur to make the animation smooth. 
A sample video has been attached to the repository. Watch the video _**[here](https://youtu.be/h1LhbyHl7dI)**_

####Tools Used
* Visual Studio 2015 Community Edition. _**[Get it here](https://www.visualstudio.com/")**_
*  _**Simple DirectMedia Layer**_ is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D.
 
####How to setup 
* Download the SDL2 Library **_[Download it here](https://www.libsdl.org/download-2.0.php)_**
* Setup Visual Studio with SDL. I will add a tutorial shortly
* Get the Visual Studio Project Folder is **_[here](https://drive.google.com/drive/folders/0Byqg5mck_vdLOS1UV2ZQUEE1amc?usp=sharing)_**
* Now if you got the **ParticleExplosionSDL** folder, simply Open VisualStudio -> File -> Open -> Project/Solution and then open **ParticleExplosionSDL.sln**
* Hit **Ctrl + F5**
* Have Fun

###Note:
It uses the 64-bit libs and 64-bit compilier which you can set from the **Standard Toolbar** just below the **FILE** menu

####Simple Hacks
If you're really very interested in changing the amination and the number of pixels then there are two files that are of your interest.
* Chaange the number of particles : _Head towards the file names as **Swarm.hpp** and change the value of **static const int NPARTICLES**. Currently it is set to **8000**_
* Want to change the animation as well? : _Head towards the file **Particle.cpp**, change the value of **double literal** in the expression **direction += interval * double_literal**. The default value of the **double_literal is: 0.000688**

You can use it as a mini project. 
Thanks


