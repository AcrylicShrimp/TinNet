
namespace TinNet::Core
{
	template<std::size_t In> FeedableNode<In>::FeedableNode(const std::array<Node *, In> &sIn) noexcept :
		sIn{sIn}
	{
		//Empty.
	}
}