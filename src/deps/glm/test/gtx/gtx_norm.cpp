#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
<<<<<<< HEAD
#include <glm/ext/scalar_relational.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3

static int test_lMaxNorm()
{
	int Error(0);
	
	{
		float norm = glm::lMaxNorm(glm::vec3(-1, -2, -3));
<<<<<<< HEAD
		Error += glm::equal(norm, 3.f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(norm, 3.f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}

	{
		float norm = glm::lMaxNorm(glm::vec3(2, 3, 1));
<<<<<<< HEAD
		Error += glm::equal(norm, 3.f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(norm, 3.f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}
  
	return Error;
}

static int test_lxNorm()
{
	int Error(0);

	{
		unsigned int depth_1 = 1;
		float normA = glm::lxNorm(glm::vec3(2, 3, 1), depth_1);
		float normB = glm::l1Norm(glm::vec3(2, 3, 1));
<<<<<<< HEAD
		Error += glm::equal(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::equal(normA, 6.f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::epsilonEqual(normA, 6.f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}

	{
		unsigned int depth_1 = 1;
		float normA = glm::lxNorm(glm::vec3(-1, -2, -3), depth_1);
		float normB = glm::l1Norm(glm::vec3(-1, -2, -3));
<<<<<<< HEAD
		Error += glm::equal(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::equal(normA, 6.f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::epsilonEqual(normA, 6.f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}

	{
		unsigned int depth_2 = 2;
		float normA = glm::lxNorm(glm::vec3(2, 3, 1), depth_2);
		float normB = glm::l2Norm(glm::vec3(2, 3, 1));
<<<<<<< HEAD
		Error += glm::equal(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::equal(normA, 3.741657387f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::epsilonEqual(normA, 3.741657387f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}

	{
		unsigned int depth_2 = 2;
		float normA = glm::lxNorm(glm::vec3(-1, -2, -3), depth_2);
		float normB = glm::l2Norm(glm::vec3(-1, -2, -3));
<<<<<<< HEAD
		Error += glm::equal(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::equal(normA, 3.741657387f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(normA, normB, 0.00001f) ? 0 : 1;
		Error += glm::epsilonEqual(normA, 3.741657387f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}

	{
		unsigned int oddDepth = 3;
		float norm = glm::lxNorm(glm::vec3(2, 3, 1), oddDepth);
<<<<<<< HEAD
		Error += glm::equal(norm, 3.301927249f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(norm, 3.301927249f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}

	{
		unsigned int oddDepth = 3;
		float norm = glm::lxNorm(glm::vec3(-1, -2, -3), oddDepth);
<<<<<<< HEAD
		Error += glm::equal(norm, 3.301927249f, 0.00001f) ? 0 : 1;
=======
		Error += glm::epsilonEqual(norm, 3.301927249f, 0.00001f) ? 0 : 1;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_lMaxNorm();
	Error += test_lxNorm();

	return Error;
}
