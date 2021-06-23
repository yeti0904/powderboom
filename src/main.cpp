#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <SDL2/SDL.h>
#include <unistd.h>
#include "particles.h"
#include "elements.h"
#include "render.h"
#include "physics.h"
using std::vector;
using std::string;
using std::thread;
using std::to_string;

bool fexists(std::string p_name) { // by reinhold
	return access(p_name.c_str(), F_OK) != -1;
}

std::string ftostr(std::string p_fname) { // by reinhold
	std::string fstr = "";
	std::ifstream fhnd (p_fname.c_str());
	if (fhnd.is_open()) {
		std::string fln = "";
		while (getline(fhnd, fln))
		fstr += fln + '\n';
	}
	fhnd.close();
	return fstr;
}

void strtof(std::string p_txt, std::string p_fname) { // by reinhold
	std::ofstream fhnd(p_fname.c_str());
	fhnd << p_txt;
}

int main() {
	printf("Welcome to PowderBOOM\nContributors: MESYETI (creator) Reinhold\n");
	vector <particle> particles;      // vector for particles
	vector <vector<particle>> pTable; // table of particles (easy look up by x and y position)
	char run = 1;                     // if the game should still run
	int draw = 0;                     // if the player is drawing particles right now
	int elementSelected = 0;          // element selected
	particle newParticle;             // used when a new particle is being created (only for simplicity)
	int frame1;                       // used for fps
	int frame2;                       // also used for fps
	int fps;                          // frames per second
	const int resX = 320;             // resolution X
	const int resY = 180;             // resolution Y

	// check for font
	printf("Checking for font\n");
	if (!(fexists("/usr/share/fonts/truetype/freefont/FreeMono.ttf"))) {
		printf("ERROR! FreeMono font is not installed, please install it\n");
		exit(1);
	}
	printf("Font found, creating particle table.\n");

	// create particle table
	vector <particle> temp;
	particle empty;
	empty.name = "PTE"; // Particle Table Empty
	for (int i = 0; i<resX; ++i) {
		temp.push_back(empty);
	}
	for (int i = 0; i<resY; ++i) {
		pTable.push_back(temp);
	}
	printf("Created particle table, starting SDL2 renderer and window.\n");

	// initialize SDL2
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("PowderBOOM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event event;
	SDL_RenderSetLogicalSize(renderer, resX, resY); // scales it to a pixel-y enviroment

	printf("Done. Now initializing elements.\n");

	// intialize elements
	vector <particle> elements;
	generateElements(elements);
	printf("All preparation complete. The game has now started.\n");

	while (run) {
		// gravity(particles, pTable, elements); (disabled for now, segmentation fault issue :( )
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					printf("Program quit.\n");
					run = 0; // end this while loop so the program can end
					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					draw = 1;
					break;
				}
				case SDL_MOUSEBUTTONUP: {
					draw = 0;
					break;
				}
			}
		}
		if (draw) {
			// create new particle
			// comments about these values are located inside of particles.h
			newParticle = elements[elementSelected];
			newParticle.xPos = event.motion.x;
			newParticle.yPos = event.motion.y;
			particles.push_back(newParticle); // add the particle
			//pTable[event.motion.y][event.motion.x] = newParticle; // add particle to Particle Table
		}
		renderParticles(renderer, particles); // render everything
		frame1 = SDL_GetTicks() - frame2;
		frame2 = SDL_GetTicks();
		if (!(frame1 == 0)) fps = 1000 / frame1;
		SDL_SetWindowTitle(window, ("PowderBOOM   FPS: " + to_string(fps) + "  Particles: " + to_string(particles.size())).c_str());
	}

	// quit SDL2
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}