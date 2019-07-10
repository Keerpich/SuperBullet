#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <limits>

namespace SuperBullet
{
#pragma region Vector2<T>
	template<typename T>
	class Vector2 : public sf::Vector2<T>
	{
	public:
		Vector2();
		Vector2(T x, T y);
		Vector2(const sf::Vector2<T>& v);
		Vector2(const Vector2<T>& v);

		Vector2<T>& operator=(const sf::Vector2<T>& v);
		operator sf::Vector2<T>();
	};

	template <typename T>
	inline Vector2<T>::Vector2() :
		sf::Vector2<T>()
	{
	}

	template <typename T>
	inline Vector2<T>::Vector2(T x, T y) :
		sf::Vector2<T>(x, y)
	{
	}

	template <typename T>
	inline Vector2<T>::Vector2(const sf::Vector2<T>& v) :
		sf::Vector2<T>(v.x, v.y)
	{
	}

	template <typename T>
	inline Vector2<T>::Vector2(const Vector2<T>& v) :
		sf::Vector2<T>(v.x, v.y)
	{
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator=(const sf::Vector2<T> & v)
	{
		this->x = v.x;
		this->y = v.y;
		return *this;
	}

	template<typename T>
	inline Vector2<T>::operator sf::Vector2<T>()
	{
		return sf::Vector2<T> {x, y};
	}

#pragma endregion Vector2<T>

#pragma region Vector2<float>
	template<>
	class Vector2<float> : public sf::Vector2<float>
	{
	public:
		Vector2();
		Vector2(float x, float y);
		Vector2(const sf::Vector2<float>& v);
		Vector2(const Vector2<float>& v);

		float Magnitude() const;
		Vector2<float> Normalize() const;

		Vector2<float>& operator=(const Vector2<float>& other);
		operator sf::Vector2f();
	};

	inline Vector2<float>::Vector2() :
		sf::Vector2<float>()
	{
	}

	inline Vector2<float>::Vector2(float x, float y) :
		sf::Vector2<float>(x, y)
	{
	}

	inline Vector2<float>::Vector2(const sf::Vector2<float> & v) :
		sf::Vector2<float>(v.x, v.y)
	{
	}

	inline Vector2<float>::Vector2(const Vector2<float>& v) :
		sf::Vector2<float>(v.x, v.y)
	{
	}

	inline Vector2<float>& Vector2<float>::operator=(const Vector2<float> & other)
	{
		this->x = other.x;
		this->y = other.y;

		return *this;
	}

	inline Vector2<float>::operator sf::Vector2f()
	{
		return sf::Vector2f{ x, y };
	}

	inline float Vector2<float>::Magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	inline Vector2<float> Vector2<float>::Normalize() const
	{
		float magnitude = Magnitude();
		return magnitude < std::numeric_limits<float>::epsilon() ? 
			Vector2<float>(0.f, 0.f) : Vector2<float>(x / magnitude, y / magnitude);
	}
#pragma endregion Vector2<float>

	using Vector2f = Vector2<float>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2i = Vector2<int>;
}