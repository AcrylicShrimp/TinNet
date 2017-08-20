
/*
	2017.08.14
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_VISUALIZER_CONSOLE_VISUALIZER_H

#define _CLASS_CAYSNET_VISUALIZER_CONSOLE_VISUALIZER_H

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>

namespace CaysNet::Visualizer
{
	struct Vector2;

	struct Vector2
	{
	public:
		float x;
		float y;

		inline Vector2() {
			this->x = .0f;
			this->y = .0f;
		}

		inline Vector2(float nx, float ny) {
			this->x = nx;
			this->y = ny;
		}

		inline Vector2 operator+(const Vector2 &right) {
			return Vector2(this->x + right.x, this->y + right.y);
		}

		inline Vector2 operator-(const Vector2 &right) {
			return Vector2(this->x - right.x, this->y - right.y);
		}

		inline Vector2 operator*(float right) {
			return Vector2(this->x * right, this->y * right);
		}

		inline Vector2 operator/(float right) {
			return Vector2(this->x / right, this->y / right);
		}

		inline Vector2 &operator+=(const Vector2 &right) {
			this->x += right.x;
			this->y += right.y;

			return *this;
		}

		inline Vector2 &operator-=(const Vector2 &right) {
			this->x -= right.x;
			this->y -= right.y;

			return *this;
		}

		inline Vector2 &operator*=(float right) {
			this->x *= right;
			this->y *= right;

			return *this;
		}

		inline Vector2 &operator/=(float right) {
			this->x /= right;
			this->y /= right;

			return *this;
		}

		inline float length() {
			return std::sqrt(Vector2::dot(*this, *this));
		}

		inline float lengthSq() {
			return Vector2::dot(*this, *this);
		}

		inline static float dot(const Vector2 &left, const Vector2 &right) {
			return left.x * right.x + left.y * right.y;
		}
	};

	inline Vector2 operator*(float left, const Vector2 &right) {
		return Vector2(left * right.x, left * right.y);
	}

	class ConsoleVisualizer final
	{
	public:
		ConsoleVisualizer() = delete;
		ConsoleVisualizer(const ConsoleVisualizer &sSrc) = delete;
		ConsoleVisualizer(ConsoleVisualizer &&sSrc) = delete;
		~ConsoleVisualizer() = delete;

	public:
		ConsoleVisualizer &operator=(const ConsoleVisualizer &sSrc) = delete;
		ConsoleVisualizer &operator=(ConsoleVisualizer &&sSrc) = delete;

	public:
		static void clear();
		static void visualize(const float *pNetworkOutput);
		
	private:
		static void setPos(int nX, int nY);
		static void writeChar(char nChar, int nX, int nY);
		static void writeString(const char *pString, int nX, int nY);
		static float renderDot(int nX, float nValue, int nMaxY, int nYOffset);
		static Vector2 calcBezierPoint(float t, const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);
	};
}

#endif