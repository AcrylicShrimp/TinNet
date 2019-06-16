
/*
	2019.03.31
	Created by AcrylicShrimp.
*/

#include "Sum.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Sum)

	Sum::Sum(Core::Graph *pGraph, std::string_view sName, bool bSqueeze) :
		Node(pGraph, sName),
		bSqueeze{bSqueeze},
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOpInput(pDy); }},
		sInputAxis{this, "axis", [this](const auto *pDy) { /* Do nothing. */ }}
	{
		this->sNodeInputMap["input"] = &this->sInput;
		this->sNodeInputMap["axis"] = &this->sInputAxis;
	}

	void Sum::__evaluateShape()
	{
		if (!this->sInput.inputNode())
			throw std::runtime_error{"no node attached at 'input'"};

		const auto &sShape{this->sInput.inputNode()->evalShape().shape()};

		if (!this->sInputAxis.inputNode())
		{
			this->sShape = {1};
			return;
		}

		const auto &sAxisShape{this->sInputAxis.inputNode()->evalShape().shape()};

		auto sAxisOutput{this->sInputAxis.inputNode()->evalOutput().output()};

		if (!sAxisShape.rank() || sAxisShape.rank() == 1 && sAxisShape.size() == 1)
		{
			this->sShape = sAxisOutput[0] < .5f ? this->bSqueeze ? sShape.squeeze() : sShape : Core::Shape{1};
			return;
		}

		if (sAxisShape.rank() != 1)
			throw std::runtime_error{"'axis' must be a scalar or vector"};

		if (sAxisShape.size() != sShape.rank())
			throw std::runtime_error{"the size of 'axis' must be equal to the rank of 'input'"};

		this->sShape = sShape;

		for (std::size_t nIndex{0}, nMaxIndex{sShape.rank()}; nIndex < nMaxIndex; ++nIndex)
			if (sAxisOutput[nIndex] >= .5f)
				this->sShape[nIndex] = 1;

		if (this->bSqueeze)
			this->sShape = this->sShape.squeeze();
	}

	void Sum::__evaluateOutput()
	{


		auto fPassIndex{[](std::size_t nIndex)
		{

		}};


	}

	void Sum::__backwardOpInput(const Node *pDy)
	{

	}
}