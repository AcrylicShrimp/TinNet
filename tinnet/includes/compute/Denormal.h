
#ifndef _TINNET_COMPUTE_DENORMAL_H

#define _TINNET_COMPUTE_DENORMAL_H

namespace tinnet::compute {
	class Denormal final {
	public:
		const bool bFTZ;
		const bool bDAZ;

	public:
		Denormal();
		~Denormal();
	};
}	 // namespace tinnet::compute

#endif