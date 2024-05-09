#include "Money.h"
#include <cmath>

const char* Money::MAGNITUDE[] = { "","M", "B", "T", "Qa", "Qi", "Sx", "Sp", "Oc", "No", "De"};
Money::Money() {}

void Money::alignExponents(Money& other)
{
	int diff = std::abs(mExp - other.mExp);

	if (mExp > other.mExp)
	{
		other.mValue = other.mValue / pow(10, diff);
		other.mExp = mExp;
	}

	if (mExp < other.mExp)
	{
		mValue = mValue / pow(10, diff);
		mExp = other.mExp;
	}
}


void Money::normalize()
{
	while (mValue >= 1000)
	{
		mValue /= 1000;
		mExp += 3;
	}
}

Money::Money(int value, int exp) : mValue(value), mExp(exp)
{
	if (mValue > TEN_TO_6_POWER)
		while (mExp % 3 != 0)
		{
			mValue *= 10;
			mExp--;
		}

	this->normalize();
}


Money Money::operator+(const Money& other) const
{
	Money result = *this;
	Money tempOther = other;
	result.alignExponents(tempOther);
	result.mValue += tempOther.mValue;
	result.normalize();
	return result;
}

Money Money::operator-(const Money& other) const
{
	Money result = *this;
	Money tempOther = other;
	result.alignExponents(tempOther);
	result.mValue -= tempOther.mValue;
	result.normalize();
	return result;
}

Money& Money::operator=(const Money& other)
{
	if (this != &other)
	{
		mValue = other.mValue;
		mExp = other.mExp;
	}
	return *this;
}

Money Money::operator-(int num) const
{
	Money other(num, 0);
	return *this - other;
}

Money Money::operator+(int num) const
{
	Money other(num, 0);
	return *this + other;
}

std::string Money::toString()
{
	std::ostringstream oss;
	oss << mValue << MAGNITUDE[indexToMangitude(mExp)];
	return oss.str();
}

int Money::indexToMangitude(int magni)
{
	if (magni < 6)
		return 0;

	return (magni / 3) - 1;
}