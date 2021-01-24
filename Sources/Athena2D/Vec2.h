#pragma once
#include <simplesquirrel/vm.hpp>

#include <cereal/access.hpp>

struct Vec2
{
	Vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	
	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2 operator+(const Vec2 &a)
	{
		x += a.x;
		y += a.y;
		return *this;
	}
	
	Vec2 operator+=(const Vec2& a)
	{
		x += a.x;
		y += a.y;
		return *this;
	}

	float x;
	float y;

	static void expose(ssq::VM &vm)
	{
		ssq::Class cls = vm.addClass("Vec2", ssq::Class::Ctor<Vec2(float, float)>());
		cls.addVar("x", &Vec2::x);
		cls.addVar("y", &Vec2::y);
	}

private:
	friend class cereal::access;
	
	template <class Archive>
	void serialize(Archive &ar)
	{
		ar(x, y);
	}
};
