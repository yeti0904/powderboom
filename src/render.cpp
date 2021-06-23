#include <SDL2/SDL.h>
#include <vector>
#include <cstdio>
#include "particles.h"
using std::vector;

void refresh(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer); // clear
}

void renderParticles(SDL_Renderer * renderer, vector <particle> particles) {
	refresh(renderer);
	for (int i = 0; i<particles.size(); ++i) {
		SDL_SetRenderDrawColor(renderer, particles[i].colour.r, particles[i].colour.g, particles[i].colour.b, particles[i].colour.a);
		SDL_RenderDrawPoint(renderer, particles[i].xPos, particles[i].yPos);
	}
	SDL_RenderPresent(renderer);
}
