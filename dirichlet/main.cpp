#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>

#include "functions.h"

int main(int argc, char *argv[]) {
	size_t N = 100;
	double EPS = 0.001;
	bool to_file = false;
	std::string *fileName;

	size_t a = 1;

	int opt;
	while((opt = getopt(argc, argv, "a:n:e:o:")) != -1) {
		switch(opt) { 
			case 'n':
				N = atoi(optarg);
				break;
			case 'e':
				EPS = atof(optarg);
				break;
			case 'o':
				to_file = true;
				fileName = new std::string(optarg);
				break;
			case 'a':
				a = atoi(optarg);
				break;
		}
	}

	DirichletResult *res;

	switch(a) {
		case 0:
			res = new DirichletResult(solveDirichlet_wave(N - 2, EPS));
			break;
		case 1:
			res = new DirichletResult(solveDirichlet_wave(N - 2, EPS));
			break;
		default:
			res = new DirichletResult(solveDirichlet_wave(N - 2, EPS));
			break;
	}

	std::cout << res->benchmark();

	if (to_file) {
		std::ofstream fout(*fileName);
		fout << res->toString();
		fout.close();
		delete fileName;
	}

	return 0;
}
