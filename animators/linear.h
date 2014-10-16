#ifndef POLYCHRHAUM_LINEAR_ANIMATOR
#define POLYCHRHAUM_LINEAR_ANIMATOR

#include "animator.h"

class LinearAnimator: public polychrhaum::Animator {
	public:
		LinearAnimator();
		void set_knee(float k);
		virtual float transfert(float percent);

	private:
		float knee;
};

#endif
