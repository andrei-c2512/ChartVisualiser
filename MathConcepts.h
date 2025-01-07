#pragma once
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>
#include "SFML/Graphics.hpp"

struct Interv
{
	double a;
	double b;
	Interv() = default;
	Interv(double a_val, double b_val) : a(a_val), b(b_val) {}

};

enum class AsymptoteType {
	MINUS_X,
	PLUS_X,
	MINUS_Y,
	PLUS_Y,
	COUNT
};

struct Equation {
	double offset = 0;
	double slope = 0;
	bool valid = false;
	Equation() = default;
	Equation(double offset_val, double slope_val, bool valid_val) : offset(offset_val), slope(slope_val), valid(valid_val) {}
};

struct Domain {
	float left = std::numeric_limits<float>::min();
	float right = std::numeric_limits<float>::max();

	bool openLeft = false;
	bool openRight = false;

	bool valid = false;
};

bool withinDomain(const Domain& domain, float x) noexcept;
std::string toString(const Domain& domain) noexcept;
std::string toString(const Equation& eq) noexcept;
std::string toString(float num, int precision) noexcept;
std::string toString(const sf::Vector2f& point) noexcept;