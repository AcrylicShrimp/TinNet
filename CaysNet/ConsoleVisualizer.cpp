
/*
	2017.08.14
	Created by AcrylicShrimp.
*/

#include "ConsoleVisualizer.h"

namespace CaysNet::Visualizer
{
	void ConsoleVisualizer::clear()
	{
		system("cls");
	}

	void ConsoleVisualizer::visualize(const float *pNetworkOutput)
	{
		const int MaxX = 60;
		const int MaxY = 22;
		const int YOffset = 5;
		const int BeziorPointCount = 4;
		const int InputCount = 10;

		ConsoleVisualizer::clear();

		Vector2 vPoint[BeziorPointCount];
		float vGraphPoint[MaxX];
		const float nPointMultiple{static_cast<float>(MaxX - BeziorPointCount) / MaxX * (static_cast<float>(InputCount - BeziorPointCount) / MaxX)};

		for (auto nIndex{0}; nIndex < MaxX; ++nIndex)
		{
			const float nTime{static_cast<float>(nIndex) / MaxX};
			
			for (auto nNum{0}; nNum < BeziorPointCount; ++nNum)
			{
				const float nResultIndex{nIndex * nPointMultiple + nNum};
				const int nI{static_cast<int>(nResultIndex)};
				const float nResultIndexFP{nResultIndex - nI};

				vPoint[nNum].y = pNetworkOutput[nI] * (1.f - nResultIndexFP);

				if (nResultIndexFP > .01f)
					vPoint[nNum].y += pNetworkOutput[nI + 1] * nResultIndexFP;
			}

			Vector2 sPoint{ConsoleVisualizer::calcBezierPoint(nTime * 1.4f, vPoint[0], vPoint[1], vPoint[2], vPoint[3])};
			
			vGraphPoint[nIndex] = ConsoleVisualizer::renderDot(nIndex, sPoint.y, MaxY, YOffset);
		}

		const float nSpaceWidth{static_cast<float>(MaxX) / InputCount};

		for (auto nIndex{0}; nIndex < InputCount; ++nIndex)
		{
			const int nPosX{static_cast<int>(nSpaceWidth * nIndex)};
			const std::string sFirst{std::to_string(nIndex)};
			const std::string sSecond{std::to_string(pNetworkOutput[nIndex]).substr(0, 5)};

			ConsoleVisualizer::writeString(sFirst.data(), nPosX, MaxY + YOffset + 3);
			ConsoleVisualizer::writeString("¡à", nPosX, static_cast<int>(vGraphPoint[nPosX]));
			ConsoleVisualizer::writeString(sSecond.data(), nPosX, static_cast<int>(vGraphPoint[nPosX]) - 2);
		}

		ConsoleVisualizer::setPos(0, MaxY + YOffset + 4);
	}

	void ConsoleVisualizer::setPos(int nX, int nY)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<short>(nX * 2), static_cast<short>(nY)});
	}

	void ConsoleVisualizer::writeChar(char nChar, int nX, int nY)
	{
		ConsoleVisualizer::setPos(nX, nY);
		putchar(nChar);
	}

	void ConsoleVisualizer::writeString(const char *pString, int nX, int nY)
	{
		ConsoleVisualizer::setPos(nX, nY);
		puts(pString);
	}

	float ConsoleVisualizer::renderDot(int nX, float nValue, int nMaxY, int nYOffset)
	{
		const int nFixMaxY{nMaxY - nYOffset};
		float nGraphValue{nFixMaxY - nValue * nFixMaxY + nYOffset};

		for (std::size_t nIndex{0}; nIndex < nFixMaxY; ++nIndex)
			ConsoleVisualizer::writeChar(' ', nX, static_cast<short>(nIndex));

		if (nGraphValue < 0)
			nGraphValue = 0;
		else if (nGraphValue > nMaxY)
			nGraphValue = nMaxY;
		else
		{
			nGraphValue += nYOffset;
			if (static_cast<int>(nGraphValue + .2f) > nGraphValue)
				ConsoleVisualizer::writeChar('_', nX, static_cast<short>(nGraphValue));
			else if (static_cast<int>(nGraphValue + .4f) > nGraphValue)
				ConsoleVisualizer::writeChar('.', nX, static_cast<short>(nGraphValue));
			else if (static_cast<int>(nGraphValue + .6f) > nGraphValue)
				ConsoleVisualizer::writeChar('-', nX, static_cast<short>(nGraphValue));
			else if (static_cast<int>(nGraphValue + .8f) > nGraphValue)
				ConsoleVisualizer::writeChar('\'', nX, static_cast<short>(nGraphValue));
			else
				ConsoleVisualizer::writeChar('`', nX, static_cast<short>(nGraphValue));
		}
		
		ConsoleVisualizer::writeString("¦¬", nX, nYOffset);
		ConsoleVisualizer::writeString("¦¬", nX, nMaxY + 1 + nYOffset);

		return static_cast<int>(nGraphValue);
	}

	Vector2 ConsoleVisualizer::calcBezierPoint(float t, const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3)
	{
		float u = 1 - t;
		float tt = t * t;
		float uu = u * u;
		float uuu = uu * u;
		float ttt = tt * t;

		Vector2 p = uuu * p0; //first term
		p += 3 * uu * t * p1; //second term
		p += 3 * u * tt * p2; //third term
		p += ttt * p3; //fourth term

		return p;
	}
}