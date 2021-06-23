#include <vector>
#include "particles.h"
#include "elements.h"
using std::vector;

void gravity(vector <particle> &particles, vector <vector<particle>> &pTable, vector <particle> elements) {
	for (int i = 0; i<particles.size(); ++i) {
		bool collisionInPath = false;
		int oldX, oldY;
		// check for collision
		for (int i2 = 0; i2<particles[i].yVel; ++i2) {
			if ((pTable[particles[i].yPos + i2 + 1][particles[i].xPos].name != "PTE") && !collisionInPath) {
				collisionInPath = true;
				oldX = particles[i].xPos;
				oldY = particles[i].yPos;
				particles[i].yPos += i2; // fall all the way 
				particles[i].yVel = 0; // reset velocity on the Y axis
				updatePTablePos(elements, pTable, oldX, oldY, particles[i].xPos, particles[i].yPos);
			}
		}
		if ((pTable[particles[i].yPos + 1][particles[i].xPos].name == "PTE") && !collisionInPath) {
			oldX = particles[i].xPos;
			oldY = particles[i].yPos;
			++ particles[i].yVel; // increase velocity
			particles[i].yPos += particles[i].yVel; // make particle fall using it's velocity
			updatePTablePos(elements, pTable, oldX, oldY, particles[i].xPos, particles[i].yPos);
		}
	}
}