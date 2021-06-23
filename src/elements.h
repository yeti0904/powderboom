using std::vector;

particle createParticle(string name, int solidTemp, int liquidTemp, int gasTemp, int canConduct, unsigned char r, unsigned char g, unsigned char b, unsigned char a, int defaultTemperature);
void generateElements(vector <particle> &elements);
void updatePTablePos(vector <particle> elements, vector <vector<particle>> &pTable, int oldX, int oldY, int newX, int newY);