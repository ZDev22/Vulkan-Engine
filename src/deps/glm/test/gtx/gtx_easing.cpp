#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/easing.hpp>

namespace
{
	template<typename T>
	static void _test_easing()
	{
		T a = static_cast<T>(0.5);
		T r;

		r = glm::linearInterpolation(a);
<<<<<<< HEAD
		(void)r;

		r = glm::quadraticEaseIn(a);
		(void)r;
		r = glm::quadraticEaseOut(a);
		(void)r;
		r = glm::quadraticEaseInOut(a);
		(void)r;

		r = glm::cubicEaseIn(a);
		(void)r;
		r = glm::cubicEaseOut(a);
		(void)r;
		r = glm::cubicEaseInOut(a);
		(void)r;

		r = glm::quarticEaseIn(a);
		(void)r;
		r = glm::quarticEaseOut(a);
		(void)r;
		r = glm::quinticEaseInOut(a);
		(void)r;

		r = glm::sineEaseIn(a);
		(void)r;
		r = glm::sineEaseOut(a);
		(void)r;
		r = glm::sineEaseInOut(a);
		(void)r;

		r = glm::circularEaseIn(a);
		(void)r;
		r = glm::circularEaseOut(a);
		(void)r;
		r = glm::circularEaseInOut(a);
		(void)r;

		r = glm::exponentialEaseIn(a);
		(void)r;
		r = glm::exponentialEaseOut(a);
		(void)r;
		r = glm::exponentialEaseInOut(a);
		(void)r;

		r = glm::elasticEaseIn(a);
		(void)r;
		r = glm::elasticEaseOut(a);
		(void)r;
		r = glm::elasticEaseInOut(a);
		(void)r;

		r = glm::backEaseIn(a);
		(void)r;
		r = glm::backEaseOut(a);
		(void)r;
		r = glm::backEaseInOut(a);
		(void)r;

		r = glm::bounceEaseIn(a);
		(void)r;
		r = glm::bounceEaseOut(a);
		(void)r;
		r = glm::bounceEaseInOut(a);
		(void)r;
=======

		r = glm::quadraticEaseIn(a);
		r = glm::quadraticEaseOut(a);
		r = glm::quadraticEaseInOut(a);

		r = glm::cubicEaseIn(a);
		r = glm::cubicEaseOut(a);
		r = glm::cubicEaseInOut(a);

		r = glm::quarticEaseIn(a);
		r = glm::quarticEaseOut(a);
		r = glm::quinticEaseInOut(a);

		r = glm::sineEaseIn(a);
		r = glm::sineEaseOut(a);
		r = glm::sineEaseInOut(a);

		r = glm::circularEaseIn(a);
		r = glm::circularEaseOut(a);
		r = glm::circularEaseInOut(a);

		r = glm::exponentialEaseIn(a);
		r = glm::exponentialEaseOut(a);
		r = glm::exponentialEaseInOut(a);

		r = glm::elasticEaseIn(a);
		r = glm::elasticEaseOut(a);
		r = glm::elasticEaseInOut(a);

		r = glm::backEaseIn(a);
		r = glm::backEaseOut(a);
		r = glm::backEaseInOut(a);

		r = glm::bounceEaseIn(a);
		r = glm::bounceEaseOut(a);
		r = glm::bounceEaseInOut(a);
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}
}

int main()
{
	int Error = 0;

	_test_easing<float>();
	_test_easing<double>();

	return Error;
}

