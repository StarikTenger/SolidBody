#pragma once

class Spring {
public:
	int index = 0;

	double k = 1;
	double l0 = 0;
	double limit = 1.2;

	Spring();
	Spring(int _index, double _k, double _l0);
};

