#pragma once

#include "mthdef.h"

namespace mth
{
	template<class type>
	class vec2
	{
	public:
		type X, Y;
		vec2() noexcept {}
		vec2(type A, type B) noexcept
		: X(A)
		, Y(B)
		{}
		explicit vec2(type A) noexcept
		: X(A)
		, Y(A)
		{}
		operator std::conditional_t<std::is_reference_v<type>, void, type> *() const noexcept
		{
			static_assert(!std::is_reference<type>::value, "Can not convert reference");
			return &((vec2*)this)->X;
		}
		vec2 Min(vec2 const& V) const noexcept { return vec2(std::min(X, V.X), std::min(Y, V.Y)); }
		vec2 Max(vec2 const& V) const noexcept { return vec2(std::max(X, V.X), std::max(Y, V.Y)); }
		bool operator==(vec2 const& V) const noexcept { return (X == V.X && Y == V.Y); }
		template<class type2>
		vec2(const vec2<type2>& V) noexcept
		: X(V.X)
		, Y(V.Y)
		{}
		template<class type2>
		vec2& operator=(const vec2<type2>& V) noexcept
		{
			X = V.X;
			Y = V.Y;
			return *this;
		}
		bool operator!=(vec2 const& V) const noexcept { return !(X == V.X && Y == V.Y); } /* End of 'operator!=' function */
		vec2 operator+(vec2 const& V) const noexcept { return vec2(X + V.X, Y + V.Y); }
		template<class type2>
		vec2& operator+=(const vec2<type2>& V) noexcept
		{
			X += V.X;
			Y += V.Y;
			return *this;
		}
		template<class type2>
		vec2& operator-=(const vec2<type2>& V) noexcept
		{
			X -= V.X;
			Y -= V.Y;
			return *this;
		}
		vec2 operator-(vec2 const& V) const noexcept { return vec2(X - V.X, Y - V.Y); }
		vec2 operator/(type N) const noexcept { return vec2(X / N, Y / N); }
		vec2 operator/(vec2 const& N) const noexcept
		{
			if (N.X == 0 || N.Y == 0) return vec2(0);
			return vec2(X / N.X, Y / N.Y);
		}
		vec2& operator/=(type N) noexcept
		{
			X /= N;
			Y /= N;
			return *this;
		}
		vec2 operator*(type N) const noexcept { return vec2(X * N, Y * N); }
		vec2 operator*(vec2 const& N) const noexcept { return vec2(X * N.X, Y * N.Y); }
		vec2& operator*=(type N) noexcept
		{
			X *= N;
			Y *= N;
			return *this;
		}
		vec2 operator-() const noexcept { return vec2(-X, -Y); }
		type operator&(vec2 const& V) const noexcept { return X * V.X + Y * V.Y; }
		vec2 Normalizing() const noexcept
		{
			type len = *this & *this;
			if (len != 0 && len != 1)
			{
				len = sqrt(len);
				return vec2(X / len, Y / len);
			}
			return *this;
		}
		vec2& Normalize() noexcept
		{
			type len = *this & *this;
			if (len != 0 && len != 1)
			{
				len = sqrt(len);
				X /= len;
				Y /= len;
			}
			return *this;
		}
		float Len() const noexcept { return sqrt(X * X + Y * Y); }
		float Len2() const noexcept { return X * X + Y * Y; }
		type& operator[](int I) noexcept
		{
			assert(I >= 0 && I < 2);
			return *(&X + I);
		}
	};
	template<class type>
	class vec
	{
	public:
		type X, Y, Z;
		vec() noexcept {}
		vec(type A, type B, type C) noexcept
		: X(A)
		, Y(B)
		, Z(C)
		{}
		explicit vec(type A) noexcept
		: X(A)
		, Y(A)
		, Z(A)
		{}
		template<class type2>
		vec(const vec<type2>& V) noexcept
		: X(V.X)
		, Y(V.Y)
		, Z(V.Z)
		{}
		template<class type2>
		vec& operator=(const vec<type2>& V) noexcept
		{
			X = V.X;
			Y = V.Y;
			Z = V.Z;
			return *this;
		}
		template<class type2>
		vec& operator+=(const vec<type2>& V) noexcept
		{
			X += V.X;
			Y += V.Y;
			Z += V.Z;
			return *this;
		}
		template<class type2>
		vec& operator-=(const vec<type2>& V) noexcept
		{
			X -= V.X;
			Y -= V.Y;
			Z -= V.Z;
			return *this;
		}
		operator std::conditional_t<std::is_reference<type>::value, void, type> *() const noexcept
		{
			static_assert(!std::is_reference<type>::value, "Can not convert reference");
			return &((vec*)this)->X;
		}
		vec2<type> XX() const noexcept { return vec2<type>(X, X); }
		vec2<type> XY() const noexcept { return vec2<type>(X, Y); }
		vec2<type> XZ() const noexcept { return vec2<type>(X, Z); }
		vec2<type> YX() const noexcept { return vec2<type>(Y, X); }
		vec2<type> YY() const noexcept { return vec2<type>(Y, Y); }
		vec2<type> YZ() const noexcept { return vec2<type>(Y, Z); }
		vec2<type> ZX() const noexcept { return vec2<type>(Z, X); }
		vec2<type> ZY() const noexcept { return vec2<type>(Z, Y); }
		vec2<type> ZZ() const noexcept { return vec2<type>(Z, Z); }
		vec2<type&> XXref() noexcept { return vec2<type&>(X, X); }
		vec2<type&> XYref() noexcept { return vec2<type&>(X, Y); }
		vec2<type&> XZref() noexcept { return vec2<type&>(X, Z); }
		vec2<type&> YXref() noexcept { return vec2<type&>(Y, X); }
		vec2<type&> YYref() noexcept { return vec2<type&>(Y, Y); }
		vec2<type&> YZref() noexcept { return vec2<type&>(Y, Z); }
		vec2<type&> ZXref() noexcept { return vec2<type&>(Z, X); }
		vec2<type&> ZYref() noexcept { return vec2<type&>(Z, Y); }
		vec2<type&> ZZref() noexcept { return vec2<type&>(Z, Z); }
		vec XXX() noexcept { return vec(X, X, X); }
		vec XXY() noexcept { return vec(X, X, Y); }
		vec XXZ() noexcept { return vec(X, X, Z); }
		vec XYX() noexcept { return vec(X, Y, X); }
		vec XYY() noexcept { return vec(X, Y, Y); }
		vec XYZ() noexcept { return vec(X, Y, Z); }
		vec XZX() noexcept { return vec(X, Z, X); }
		vec XZY() noexcept { return vec(X, Z, Y); }
		vec XZZ() noexcept { return vec(X, Z, Z); }
		vec YXX() noexcept { return vec(Y, X, X); }
		vec YXY() noexcept { return vec(Y, X, Y); }
		vec YXZ() noexcept { return vec(Y, X, Z); }
		vec YYX() noexcept { return vec(Y, Y, X); }
		vec YYY() noexcept { return vec(Y, Y, Y); }
		vec YYZ() noexcept { return vec(Y, Y, Z); }
		vec YZX() noexcept { return vec(Y, Z, X); }
		vec YZY() noexcept { return vec(Y, Z, Y); }
		vec YZZ() noexcept { return vec(Y, Z, Z); }
		vec ZXX() noexcept { return vec(Z, X, X); }
		vec ZXY() noexcept { return vec(Z, X, Y); }
		vec ZXZ() noexcept { return vec(Z, X, Z); }
		vec ZYX() noexcept { return vec(Z, Y, X); }
		vec ZYY() noexcept { return vec(Z, Y, Y); }
		vec ZYZ() noexcept { return vec(Z, Y, Z); }
		vec ZZX() noexcept { return vec(Z, Z, X); }
		vec ZZY() noexcept { return vec(Z, Z, Y); }
		vec ZZZ() noexcept { return vec(Z, Z, Z); }
		vec<type&> XXXref() noexcept { return vec<type&>(X, X, X); }
		vec<type&> XXYref() noexcept { return vec<type&>(X, X, Y); }
		vec<type&> XXZref() noexcept { return vec<type&>(X, X, Z); }
		vec<type&> XYXref() noexcept { return vec<type&>(X, Y, X); }
		vec<type&> XYYref() noexcept { return vec<type&>(X, Y, Y); }
		vec<type&> XYZref() noexcept { return vec<type&>(X, Y, Z); }
		vec<type&> XZXref() noexcept { return vec<type&>(X, Z, X); }
		vec<type&> XZYref() noexcept { return vec<type&>(X, Z, Y); }
		vec<type&> XZZref() noexcept { return vec<type&>(X, Z, Z); }
		vec<type&> YXXref() noexcept { return vec<type&>(Y, X, X); }
		vec<type&> YXYref() noexcept { return vec<type&>(Y, X, Y); }
		vec<type&> YXZref() noexcept { return vec<type&>(Y, X, Z); }
		vec<type&> YYXref() noexcept { return vec<type&>(Y, Y, X); }
		vec<type&> YYYref() noexcept { return vec<type&>(Y, Y, Y); }
		vec<type&> YYZref() noexcept { return vec<type&>(Y, Y, Z); }
		vec<type&> YZXref() noexcept { return vec<type&>(Y, Z, X); }
		vec<type&> YZYref() noexcept { return vec<type&>(Y, Z, Y); }
		vec<type&> YZZref() noexcept { return vec<type&>(Y, Z, Z); }
		vec<type&> ZXXref() noexcept { return vec<type&>(Z, X, X); }
		vec<type&> ZXYref() noexcept { return vec<type&>(Z, X, Y); }
		vec<type&> ZXZref() noexcept { return vec<type&>(Z, X, Z); }
		vec<type&> ZYXref() noexcept { return vec<type&>(Z, Y, X); }
		vec<type&> ZYYref() noexcept { return vec<type&>(Z, Y, Y); }
		vec<type&> ZYZref() noexcept { return vec<type&>(Z, Y, Z); }
		vec<type&> ZZXref() noexcept { return vec<type&>(Z, Z, X); }
		vec<type&> ZZYref() noexcept { return vec<type&>(Z, Z, Y); }
		vec<type&> ZZZref() noexcept { return vec<type&>(Z, Z, Z); }
		vec Min(vec const& V) const noexcept { return vec(std::min(X, V.X), std::min(Y, V.Y), std::min(Z, V.Z)); }
		vec Max(vec const& V) const noexcept { return vec(std::max(X, V.X), std::max(Y, V.Y), std::max(Z, V.Z)); }
		bool operator==(vec const& V) const noexcept { return (X == V.X && Y == V.Y && Z == V.Z); }
		bool operator!=(vec const& V) const noexcept { return !(X == V.X && Y == V.Y && Z == V.Z); }
		vec operator+(vec const& V) const noexcept { return vec(X + V.X, Y + V.Y, Z + V.Z); }
		vec operator+(type N) const noexcept { return vec(X + N, Y + N, Z + N); }
		vec operator-(vec const& V) const noexcept { return vec(X - V.X, Y - V.Y, Z - V.Z); }
		vec operator/(vec const& V) const noexcept
		{
			if (V.X == 0 || V.Y == 0 || V.Z == 0) return vec(X, Y, Z);
			return vec(X / V.X, Y / V.Y, Z / V.Z);
		}
		template<typename T>
		vec operator/(T N) const noexcept
		{
			return vec(X / N, Y / N, Z / N);
		}
		vec& operator/=(vec const& V) noexcept
		{
			if (V.X == 0 || V.Y == 0 || V.Z == 0) return *this;
			X /= V.X;
			Y /= V.Y;
			Z /= V.Z;
			return *this;
		}
		vec& operator/=(type N) noexcept
		{
			if (N == 0) return *this;
			X /= N;
			Y /= N;
			Z /= N;
			return *this;
		}
		vec operator*(vec const& N) const noexcept { return vec(X * N.X, Y * N.Y, Z * N.Z); }
		vec operator*(type N) const noexcept { return vec(X * N, Y * N, Z * N); }
		vec& operator*=(vec const& V) noexcept
		{
			X *= V.X;
			Y *= V.Y;
			Z *= V.Z;
			return *this;
		}
		vec& operator*=(type N) noexcept
		{
			X *= N;
			Y *= N;
			Z *= N;
			return *this;
		}
		vec operator-() const noexcept { return vec(-X, -Y, -Z); }
		type operator&(vec const& V) const noexcept { return X * V.X + Y * V.Y + Z * V.Z; }
		vec operator%(vec const& V) const noexcept { return vec(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
		vec operator%=(vec const& V) noexcept
		{
			X = Y * V.Z - V.Y * Z;
			Y = V.X * Z - X * V.Z;
			Z = X * V.Y - V.X * Y;
			return *this;
		}
		vec Normalizing() const noexcept
		{
			type len = *this & *this;
			len      = sqrt(len);
			return vec(X / len, Y / len, Z / len);
			return *this;
		}
		vec& Normalize() noexcept
		{
			type len = *this & *this;
			len      = sqrt(len);
			X /= len;
			Y /= len;
			Z /= len;
			return *this;
		}
		float Len() const noexcept { return sqrt(X * X + Y * Y + Z * Z); }
		float Len2() const noexcept { return X * X + Y * Y + Z * Z; }
		type& operator[](int I) noexcept
		{
			assert(I >= 0 && I < 3);
			return *(&X + I);
		}
	};
	template<class type>
	class vec4
	{
	public:
		type X, Y, Z, W;
		vec4() noexcept {}
		vec4(type A, type B, type C, type D = 1) noexcept
		: X(A)
		, Y(B)
		, Z(C)
		, W(D)
		{}
		vec4(vec<type> Vector, type D = 1) noexcept
		: X(Vector.X)
		, Y(Vector.Y)
		, Z(Vector.Z)
		, W(D)
		{}
		explicit vec4(type A) noexcept
		: X(A)
		, Y(A)
		, Z(A)
		, W(A)
		{}
		operator std::conditional_t<std::is_reference<type>::value, void, type>*() const noexcept
		{
			static_assert(!std::is_reference<type>::value, "Can not convert reference");
			return &((vec4*)this)->X;
		}
		vec4 Min(vec4 const& V) const noexcept
		{
			return vec4(std::min(X, V.X), std::min(Y, V.Y), std::min(Z, V.Z), std::min(W, V.W));
		}
		vec4 Max(vec4 const& V) const noexcept
		{
			return vec4(std::max(X, V.X), std::max(Y, V.Y), std::max(Z, V.Z), std::max(W, V.W));
		}
		bool operator==(vec4 const& V) const noexcept { return (X == V.X && Y == V.Y && Z == V.Z && W == V.W); }
		bool operator!=(vec4 const& V) const noexcept { return !(X == V.X && Y == V.Y && Z == V.Z && W == V.W); }
		vec4 operator+(vec4 const& V) const noexcept { return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W); }
		vec4& operator+=(vec4 const& V) noexcept
		{
			X += V.X;
			Y += V.Y;
			Z += V.Z;
			W += V.W;
			return *this;
		}
		vec4 operator-(vec4 const& V) const noexcept { return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W); }
		vec4& operator-=(vec4 const& V) noexcept
		{
			X -= V.X;
			Y -= V.Y;
			Z -= V.Z;
			W -= V.W;
			return *this;
		}
		template<typename T>
		vec4 operator/(T N) const noexcept { return vec4(X / N, Y / N, Z / N, W / N); }
		vec4 operator/(vec4 const& N) const noexcept
		{
			return vec4(X / N.X, Y / N.Y, Z / N.Z, W / N.W);
		}
		vec4& operator/=(type N) noexcept
		{
			X /= N;
			Y /= N;
			Z /= N;
			W /= N;
			return *this;
		}
		template<typename T>
		vec4 operator*(T N) const noexcept { return vec4(X * N, Y * N, Z * N, W * N); }
		vec4 operator*(vec4 const& N) const noexcept { return vec4(X * N.X, Y * N.Y, Z * N.Z, W * N.W); }
		vec4& operator*=(type N) noexcept
		{
			X *= N;
			Y *= N;
			Z *= N;
			W *= N;
			return *this;
		}
		vec4 operator-() const noexcept { return vec4(-X, -Y, -Z, -W); }
		type operator&(vec4 const& V) const noexcept { return X * V.X + Y * V.Y + Z * V.Z + W * V.W; }
		vec4 Normalizing() const noexcept
		{
			type len = *this & *this;
			if (len != 0 && len != 1)
			{
				len = std::sqrt(len);
				return vec4(X / len, Y / len, Z / len, W / len);
			}
			return *this;
		}
		vec4& Normalize() noexcept
		{
			type len = *this & *this;
			if (len != 0 && len != 1)
			{
				len = sqrt(len);
				X /= len;
				Y /= len;
				Z /= len;
				W /= len;
			}
			return *this;
		}
		double Len() const noexcept { return sqrt(X * X + Y * Y + Z * Z + W * W); }
		double Len2() const noexcept { return X * X + Y * Y + Z * Z + W * W; }
		type& operator[](int I) noexcept
		{
			assert(I >= 0 && I < 4);
			return *(&X + I);
		}
		static vec4 Cross(vec4 const& A, vec4 const& B, vec4 const& C) noexcept
		{
			return vec4(
					A.Y * B.Z * C.W + A.Z * B.W * C.Y + A.W * B.Y * C.Z - A.Y * B.W * C.Z - A.Z * B.Y * C.W - A.W * B.Z * C.Y,
					A.X * B.W * C.Z + A.Z * B.X * C.W + A.W * B.Z * C.X - A.X * B.Z * C.W - A.Z * B.W * C.X - A.W * B.X * C.Z,
					A.X * B.Y * C.W + A.Y * B.W * C.X + A.W * B.X * C.Y - A.X * B.W * C.Y - A.Y * B.X * C.W - A.W * B.Y * C.X,
					A.X * B.Z * C.Y + A.Y * B.X * C.Z + A.Z * B.Y * C.X - A.X * B.Y * C.Z - A.Y * B.Z * C.X - A.Z * B.X * C.Y);
		}
	};
	template<typename T, typename Y>
	vec2<T> operator*(Y const& y, vec2<T> const& v)
	{
		return {v.X * y, v.Y * y};
	}
	template<typename T, typename Y>
	vec<T> operator*(Y const& y, vec<T> const& v)
	{
		return {v.X * y, v.Y * y, v.Z * y};
	}
	template<typename T, typename Y>
	vec4<T> operator*(Y const& y, vec4<T> const& v)
	{
		return {v.X * y, v.Y * y, v.Z * y, v.W * y};
	}

	template<typename T, typename Y, typename F>
	inline void Zip(T& v1, T& v2, F const& f)
	{
		auto i1 = v1.begin();
		auto i2 = v2.begin();
		while (i1 != v1.end() && i2 != v2.end())
		{
			d(*i1, *i2);
			++i1;
			++i2;
		}
	}
	template<typename T, typename Y, typename F>
	inline void Zip(T& v1, T const& v2, F const& f)
	{
		auto i1 = v1.begin();
		auto i2 = v2.begin();
		while (i1 != v1.end() && i2 != v2.end())
		{
			d(*i1, *i2);
			++i1;
			++i2;
		}
	}
} // namespace mth
