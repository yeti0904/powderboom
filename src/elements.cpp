#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "particles.h"
using std::vector;
using std::string;

particle getPT(vector <vector<particle>> pTable, int X, int Y) {
	if ((X > pTable[0].size()) || (Y > pTable.size())) {
		printf("Segmentation fault prevented on getPT function.\nPlease show this to MESYETI\n");
	}
	return pTable[Y][X];
}

void updatePTablePos(vector <particle> elements, vector <vector<particle>> &pTable, int oldX, int oldY, int newX, int newY) {
	if ((oldX > pTable[0].size()) || (oldY > pTable.size())) {
		printf("Segmentation fault prevented on old position values in the updatePTablePos function.\nPlease show this error to MESYETI\n");
		exit(1);
	}
	if ((newX > pTable[0].size()) || (newY > pTable.size())) {
		printf("Segmentation fault prevented on new position values in the updatePTablePos function.\nPlease show this error to MESYETI\n");
		exit(1);
	}
	pTable[newY][newX] = pTable[oldY][oldX]; // copy particle in particle table to a new index
	pTable[oldY][oldX] = elements[0]; // PTE
}

void setPTable(particle sparticle, vector<vector<particle>> &pTable, int X, int Y) {
	pTable[Y][X] = sparticle;
}

particle createParticle(string name, int solidTemp, int liquidTemp, int gasTemp, int canConduct, unsigned char r, unsigned char g, unsigned char b, unsigned char a, int defaultTemperature, int permState, int permStateType) {
	particle p; // particle to create
	p.name = name;
	p.solidTemp = solidTemp;
	p.liquidTemp = liquidTemp;
	p.gasTemp = gasTemp;
	p.canConduct = canConduct;
	p.colour.r = r;
	p.colour.g = g;
	p.colour.b = b;
	p.colour.a = a;
	p.temperature = defaultTemperature;
	p.permState = permState;
	p.permStateType = permStateType;
	p.xVel = 0;
	p.yVel = 0;
	return p;
}

void generateElements(vector <particle> &elements) {
	elements.push_back(createParticle("PTE", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
	elements.push_back(createParticle("Water", 0, 1, 100, 1, 0, 0, 255, 255, 25, 0, 0));
	elements.push_back(createParticle("Plant", 0, 9999999, 99999, 0, 0, 255, 0, 255, 25, 1, 0));
	elements.push_back(createParticle("Lava", 99999, 99999999, 99999, 0, 255, 0, 0, 255, 150, 0, 0));
}