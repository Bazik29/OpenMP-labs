#include <unistd.h>
#include <iostream>

#include "functions.h"

int main(int argc, char *argv[]) {

	char *opts = "dim:eps"; 

	size_t N = 99;
	double EPS = 0.001;
	int opt;
    while((opt = getopt(argc, argv, opts)) != -1) {
        switch(opt) {
            case 'dim':
	            N = atoi(optarg);
	            break;
             case 'eps':
	            EPS = atoi(optarg);
	            break;
        }
    }

	std::cout << solveDirichlet(N, EPS).toStr();
	return 0;
}
