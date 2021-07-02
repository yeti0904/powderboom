#include <vector>
#include "particles.h"
#include "elements.h"
using std::vector;

void gravity(vector <particle> &particles, vector <vector<particle>> &pTable, vector <particle> elements, int X, int Y) {
	for (int i = 0; i<particles.size(); ++i) {
		bool collisionInPath = false;
		int oldX, oldY;
		// check for collision
		for (int i2 = 0; i2<particles[i].yVel; ++i2) {
			if ((getPT(pTable, particles[i].yPos + i2 + 1, particles[i].xPos).name != "PTE") && !collisionInPath) {
				collisionInPath = true;
				oldX = particles[i].xPos;
				oldY = particles[i].yPos;
				particles[i].yPos += i2; // fall all the way 
				particles[i].yVel = 0; // reset velocity on the Y axis
				if (!((particles[i].yPos >= pTable.size()) || (particles[i].xPos >= pTable[i].size())) && (particles[i].yPos < Y)) {
					updatePTablePos(elements, pTable, oldX, oldY, particles[i].xPos, particles[i].yPos);
				}
				else if (particles[i].yPos > Y) {
					particles[i].yVel = 0;
					particles[i].yPos = oldY;
				}
			}
		}
		if ((getPT(pTable, particles[i].yPos + 1, particles[i].xPos).name == "PTE") && !collisionInPath) {
			oldX = particles[i].xPos;
			oldY = particles[i].yPos;
			++ particles[i].yVel; // increase velocity
			particles[i].yPos += particles[i].yVel; // make particle fall using it's velocity
			if (!((particles[i].yPos >= pTable.size()) || (particles[i].xPos >= pTable[i].size())) && (particles[i].yPos < Y)) {
				updatePTablePos(elements, pTable, oldX, oldY, particles[i].xPos, particles[i].yPos);
			}
			else if (particles[i].yPos > Y) {
				particles[i].yVel = 0;
				particles[i].yPos = oldY;
			}
		}
	}
}