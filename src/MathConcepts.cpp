#include "MathConcepts.h"

bool withinDomain(const Domain& domain, float x) noexcept {
    bool validLeft, validRight;
    if (domain.openLeft) {
        validLeft = (x > domain.left);
    }
    else
        validLeft = (x >= domain.left);

    if (domain.openRight) {
        validRight = (x < domain.right);
    }
    else
        validRight = (x <= domain.right);

    return validRight && validLeft;
}


std::string toString(const Equation& eq) noexcept {
	if (eq.valid)
		return "";

	std::string str = "y=" + std::to_string(eq.offset);
	if (eq.slope) {
		if (eq.slope > 0) {
			str += "+" + std::to_string(eq.slope) + "x";
		}
		else {
			str += "-" + std::to_string(eq.slope) + "x";
		}
	}
	return str;
}

std::string toString(const Domain& domain) noexcept {
	std::stringstream ss1;
	if (domain.left == -100000) {
		ss1 << "-inf";
	}
	else
	{
		ss1 << std::fixed << std::setprecision(2);
		ss1 << domain.left;
	}

	std::stringstream ss2;
	if (domain.right == 100000) {
		ss2 << "inf";
	}
	else
	{
		ss2 << std::fixed << std::setprecision(2);
		ss2 << domain.right;
	}

	return (domain.openLeft) ? "(" : "[" +
		ss1.str() + "," +
	    ss2.str() + ((domain.openRight) ? ")" : "]");
}

std::string toString(float num, int precision) noexcept {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision);
	ss << num;
	return ss.str();
}

std::string toString(const sf::Vector2f& point) noexcept {
	return toString(point.x, 2) + " , " + toString(point.y, 2);
}

float floatNumber(std::string_view str) {
	try {
		float res = std::stof(str.data());
		return res;
	}
	catch (const std::invalid_argument& argument) {
		return std::numeric_limits<float>::max();
	}
}

bool digit(char ch) noexcept {
	return ch >= '0' && ch <= '9';
}