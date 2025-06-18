/// @ref gtx_texture

namespace glm
{
	template <length_t L, typename T, qualifier Q>
	inline T levels(vec<L, T, Q> const& Extent)
	{
		return glm::log2(compMax(Extent)) + static_cast<T>(1);
	}

	template <typename T>
	inline T levels(T Extent)
	{
<<<<<<< HEAD
		return levels(vec<1, T, defaultp>(Extent));
=======
		return vec<1, T, defaultp>(Extent).x;
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	}
}//namespace glm

