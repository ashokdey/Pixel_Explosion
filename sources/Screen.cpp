#include "headers/Screen.hpp"

namespace particleEX
{
	Screen::Screen() : _window(nullptr), _renderer(nullptr), _texture(nullptr), _buffer(nullptr), _bufferBlur(nullptr){}

	bool Screen::init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
		{
			//std::cout << "Failed to initialize SDL. Error = " << SDL_GetError() << std::endl;
			return false;
		}
		std::cout << "SDL initiated Successfully" << std::endl;

		_window = SDL_CreateWindow("Pixel Explosion", POSX, POSY, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (_window == nullptr) 
		{
			//std::cout << "Failed to create window" << std::endl;
			close();
			return false;
		}
		std::cout << "Window created successfully" << std::endl;

		//create a renderer
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

		if (_renderer == nullptr) 
		{
			//std::cout << "Failed to create renderer. Error = " << SDL_GetError() << std::endl;
			close();
			return false;
		}

		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (_texture == nullptr) 
		{
			//std::cout << "Failed to create texture. Error = " << SDL_GetError() << std::endl;
			close();
			return false;
		}
		std::cout << "Texture created successfully." << std::endl;


		// create a pixel buffer
		_buffer = nullptr;

		try {
			_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
			_bufferBlur = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

			// setting value to the buffer
			std::memset(_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
			std::memset(_bufferBlur, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

		}
		catch (std::bad_alloc& aerr) 
		{
			std::cerr << "Failed to allocate memory. Error = " << aerr.what() << std::endl;
			close();
			return false;
		}


		//Initialize SDL_mixer

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			return false;
		}

		_backgroundMusic = nullptr;

		_backgroundMusic = Mix_LoadMUS("assets/music.wav");

		if (_backgroundMusic == nullptr) {
			return false;
		}

		//Lets play the music 
		Mix_PlayMusic(_backgroundMusic, -1);

		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) 
	{
		Uint32 color = 0;

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) 
		{
			return;
		}

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		_buffer[(y * SCREEN_WIDTH) + x] = color;
 	}



	void Screen::update() 
	{
		SDL_UpdateTexture(_texture, nullptr, _buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(_renderer);
		SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
		SDL_RenderPresent(_renderer);
	}

	bool Screen::processEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return false;
			}
		}
		return true;
	}

	void Screen::boxBlur() 
	{
		Uint32 *temp = _buffer;
		_buffer = _bufferBlur;
		_bufferBlur = temp;

		for (int y = 0; y < SCREEN_HEIGHT; ++y)
		{
			for (int x = 0; x < SCREEN_WIDTH; ++x) {
				
				int redTotal = 0; 
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; ++row)
				{
					for (int col = -1; col <= 1; ++col)
					{
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < SCREEN_WIDTH  && currentY >= 0 && currentY < SCREEN_HEIGHT) 
						{
							Uint32 color = _bufferBlur[currentY * SCREEN_WIDTH + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}

				Uint8 red	= redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue	= blueTotal / 9;

				setPixel(x, y, red, green, blue);	
			}
		}
	}

	void Screen::close()
	{
		if (_buffer != nullptr) {
			delete[] _buffer;
		}

		if (_bufferBlur != nullptr) {
			delete[] _bufferBlur;	
		}

		if (_renderer != nullptr) {
			SDL_DestroyRenderer(_renderer);
		}

		if (_texture != nullptr) {
			SDL_DestroyTexture(_texture);
		}
		
		if (_window != nullptr) {
			SDL_DestroyWindow(_window);
		}

		SDL_Quit();
	}
}