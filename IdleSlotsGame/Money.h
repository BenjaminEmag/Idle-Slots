#include <cmath>
#include <sstream>
#include <string>

class Money {
private:
	static const int TEN_TO_6_POWER = 1000000;
	double mValue = 0.0;
	int mExp = 0;
	static const char* MAGNITUDE[];

	void alignExponents(Money& other);
	void normalize();
	int indexToMangitude(int magni);
public:
	Money(int value, int exp);
	Money();
	Money operator+(const Money& other) const;
	Money operator-(const Money& other) const;
	Money operator+(int num) const;
	Money operator-(int num) const;

	Money& operator=(const Money& other);

	std::string toString();
};
