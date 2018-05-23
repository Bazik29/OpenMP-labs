#ifndef __CONDI_H__
#define __CONDI_H__

double f(double x, double y) {
	return 0;
}

double g(double x, double y) {
	if	(x == 0)
		return -30*(y-0.5)*(y-0.5);
	if	(x == 1)
		return -30*(y-0.5)*(y-0.5);
	if	(y == 0)
		return -30*(x-0.5)*(x-0.5);
	if 	(y == 1)
		return -30*(x-0.5)*(x-0.5);
	return 0;
}

#endif //__CONDI_H__
