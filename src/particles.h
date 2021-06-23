#include <SDL2/SDL.h>
#include <string>
using std::string;

struct particle {
	// basic info
	int xPos;             // X position
	int yPos;             // Y position
	int temperature;      // temperature of the particle in C
	char state;           // state of the particle (0 = Solid, 1 = Powder, 2 = Liquid, 3 = Gas)
	int currentlySparked; // if the particle is currently conducting
	int yVel;             // Y velocity
	int xVel;             // X velocity

	// properties
	string name;
	int solidTemp;      // the temperature required to turn the particle into a solid
	int liquidTemp;     // the temperature required to turn the particle into a liquid
	int gasTemp;        // the temperature required to turn the particle into a gas
	char canConduct;    // if the particle is able to conduct
	SDL_Color colour;   // colour of the particle
	char permState;     // bool if the element can only be 1 state (useful for special elements)
	char permStateType; // the state the particle has to be
	char solidpowder;   // if the powder's solid state will be solid (no gravity) or powder (solid with gravity)
};