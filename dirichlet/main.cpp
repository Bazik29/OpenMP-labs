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

	int opt;
    while((opt = getopt(argc, argv, "n:e:o:")) != -1) {
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
        }
    }

    DirichletResult res = solveDirichlet(N - 2, EPS);

    std::cout << res.benchmark();

    if (to_file) {
	    std::ofstream fout(*fileName);
	    fout << res.toString();
	    fout.close();
	    delete fileName;
	}

	return 0;
}

