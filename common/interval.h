#pragma once

// Project
#include "utility.h"


class Interval 
{
public:
	// Ctors.
	Interval() = default;

	Interval(float min, float max)
		: min_{min}
		, max_{max}
	{	}


	// Methods.
	const bool contains(float x) const
	{
		return x >= min_ && x <= max_;
	}

	const bool surrounds(float x) const
	{
		return x > min_ && x < max_;
	}

	float clamp(float x) const
	{
		if (x < min_)
		{
			return min_;
		}

		if (x > max_)
		{
			return max_;
		}

		return x;
	}


	// Properties.
	float min_{ inifinity };
	float max_{ -inifinity };


	// Reference classes.
	static const Interval empty_;
	static const Interval universe_;
};

const Interval empty_{};
const Interval universe_{ -inifinity, inifinity };