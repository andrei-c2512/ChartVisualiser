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
	if (domain.left == std::numeric_limits<float>::min()) {
		ss1 << "-inf";
	}
	else
	{
		ss1 << std::fixed << std::setprecision(2);
		ss1 << domain.left;
	}

	std::stringstream ss2;
	if (domain.right == std::numeric_limits<float>::max()) {
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
	return toString(point.x, 2) + "," + toString(point.y, 2);
}