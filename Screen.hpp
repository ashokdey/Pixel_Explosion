#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>


namespace particleEX {

	class Screen {
		// public constants
	public:
		static const int POSX { 100 };
		static const int POSY { 200 };
		static const int SCREEN_WIDTH{ 800 };
		static const int SCREEN_HEIGHT{ 600 };
		// public methods here
	public:
		Screen();
		bool init();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void update();
		bool processEvents();
		void boxBlur();
		void close();
	private:
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_Texture *_texture;
		Uint32 *_buffer;
		Uint32 *_bufferBlur;
		Mix_Music *_backgroundMusic;
	};

}