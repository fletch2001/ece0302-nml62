#ifndef FANCYPOWER_HPP
#define FANCYPOWER_HPP

int fancyPower(int n, int m)
{
	//base case
	if(n == 0){
		return 1;
	} else {
		// n % 2 == 0 condition reduces power until n / 2 == 1.
		// m * fancyPower... does the actual exponentiation once
		// n % 2 == 0 condition is no longer met
		if(n % 2 == 0){
			return fancyPower(n/2, m*m);
		} else {
			return m * fancyPower((n-1)/2, m*m);
		}
	}
}

#endif