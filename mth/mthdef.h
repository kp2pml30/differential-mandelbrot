#pragma once

#include <cassert>
#include <type_traits>
#include <cmath>
#include <utility>
#include <algorithm>
#include <string>

namespace mth
{
	double PI = M_PI;
	template<class type>
	type D2R(type AngleInDegrees) noexcept
	{
		return AngleInDegrees * PI / 180.0;
	} 
	template<typename type>
	int Sign(type const& Num) noexcept
	{
		if (Num > 0)
			return 1;
		return Num < 0 ? -1 : 0;
	} 
	template<class type>
	type R2D(type AngleInRadians) noexcept
	{
		return AngleInRadians * 180.0 / PI;
	} 
	template<class type>
	type Clamp(type Value, type A = 0, type B = 1) noexcept
	{
		return Value < A ? A : (Value > B ? B : Value);
	} 
	template<class type = double>
	static type Rnd1() noexcept
	{
		return 2 * rand() / type(RAND_MAX) - 1;
	} 
	template<class type = double>
	static type Rnd0() noexcept
	{
		return rand() / type(RAND_MAX);
	} 
	template<typename type1 = double, typename type2 = double>
	inline type1 Lerp(type1 A, type1 B, type2 T) noexcept
	{
		if (T >= 1)
			return B;
		if (T <= 0)
			return A;
		return A * (1 - T) + B * T;
	} 
	template<>
	inline std::string Rnd0<std::string>() noexcept
	{
		const int size = rand() % 100 + 1;
		std::string ret;
		ret.reserve(size);
		for (int i = 0; i < size; i++)
			ret.push_back(rand() % ('z' - 'a') + 'a');
		return ret;
	} 
	template<class type>
	static type Rnd(type First, type Last) noexcept
	{
		return First + rand() * (Last - First) / type(RAND_MAX);
	} 
	template<class type>
	type Sqr(type const& X) noexcept
	{
		return X * X;
	} 
	template<class type>
	type Cub(type const& X) noexcept
	{
		return X * X * X;
	} 
} // namespace mth

/* END OF 'tvz_mthdef.h' FILE */
