#include <ctime>
#include "cg/cg.h"
#include "AsteroidsApp.h"

int main(int argc, char** argv) {
	srand(time(0));
	cg::Manager::instance()->runApp(new asteroids::AsteroidsApp(),60,argc,argv);
	return 0;
}
