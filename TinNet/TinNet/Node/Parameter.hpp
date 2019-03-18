
namespace TinNet::Node
{
	template<class T> void Parameter::initialize(T sInitializer)
	{
		/*
			TODO :
				Throw an error if this parameter node is already initialized.
		*/

		this->sParameter.resize(this->evalShape().shape().size());

		static_cast<Initializer::InitializerBase &>(sInitializer)(this->sParameter.span());
	}

	template<class I> void Parameter::initialize(I iBegin, I iEnd)
	{
		/*
			TODO :
				Throw an error if this parameter node is already initialized.
		*/

		this->sParameter.resize(this->evalShape().shape().size());
		this->sParameter.span().copyFrom(iBegin, iEnd);
	}
}