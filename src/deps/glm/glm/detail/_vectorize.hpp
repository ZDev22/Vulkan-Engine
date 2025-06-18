#pragma once

namespace glm{
namespace detail
{
	template<template<length_t L, typename T, qualifier Q> class vec, length_t L, typename R, typename T, qualifier Q>
	struct functor1{};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 1, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, R, Q> call(R (*Func) (T x), vec<1, T, Q> const& v)
		{
			return vec<1, R, Q>(Func(v.x));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 2, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, R, Q> call(R (*Func) (T x), vec<2, T, Q> const& v)
		{
			return vec<2, R, Q>(Func(v.x), Func(v.y));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 3, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, R, Q> call(R (*Func) (T x), vec<3, T, Q> const& v)
		{
			return vec<3, R, Q>(Func(v.x), Func(v.y), Func(v.z));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 4, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, R, Q> call(R (*Func) (T x), vec<4, T, Q> const& v)
		{
			return vec<4, R, Q>(Func(v.x), Func(v.y), Func(v.z), Func(v.w));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, length_t L, typename T, qualifier Q>
	struct functor2{};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 1, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, T, Q> call(T (*Func) (T x, T y), vec<1, T, Q> const& a, vec<1, T, Q> const& b)
		{
			return vec<1, T, Q>(Func(a.x, b.x));
		}
<<<<<<< HEAD

		template<typename Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, T, Q> call(Fct Func, vec<1, T, Q> const& a, vec<1, T, Q> const& b)
		{
			return vec<1, T, Q>(Func(a.x, b.x));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 2, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, T, Q> call(T (*Func) (T x, T y), vec<2, T, Q> const& a, vec<2, T, Q> const& b)
		{
			return vec<2, T, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
<<<<<<< HEAD

		template<typename Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, T, Q> call(Fct Func, vec<2, T, Q> const& a, vec<2, T, Q> const& b)
		{
			return vec<2, T, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 3, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, T, Q> call(T (*Func) (T x, T y), vec<3, T, Q> const& a, vec<3, T, Q> const& b)
		{
			return vec<3, T, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
<<<<<<< HEAD

		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, T, Q> call(Fct Func, vec<3, T, Q> const& a, vec<3, T, Q> const& b)
		{
			return vec<3, T, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 4, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, T, Q> call(T (*Func) (T x, T y), vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
<<<<<<< HEAD

		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(Fct Func, vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<template<length_t L, typename T, qualifier Q> class vec, length_t L, typename T, qualifier Q>
	struct functor2_vec_sca{};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 1, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, T, Q> call(T (*Func) (T x, T y), vec<1, T, Q> const& a, T b)
		{
			return vec<1, T, Q>(Func(a.x, b));
		}
<<<<<<< HEAD
		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, T, Q> call(Fct Func, vec<1, T, Q> const& a, T b)
		{
			return vec<1, T, Q>(Func(a.x, b));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 2, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, T, Q> call(T (*Func) (T x, T y), vec<2, T, Q> const& a, T b)
		{
			return vec<2, T, Q>(Func(a.x, b), Func(a.y, b));
		}
<<<<<<< HEAD

		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, T, Q> call(Fct Func, vec<2, T, Q> const& a, T b)
		{
			return vec<2, T, Q>(Func(a.x, b), Func(a.y, b));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 3, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, T, Q> call(T (*Func) (T x, T y), vec<3, T, Q> const& a, T b)
		{
			return vec<3, T, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b));
		}
<<<<<<< HEAD

		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, T, Q> call(Fct Func, vec<3, T, Q> const& a, T b)
		{
			return vec<3, T, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 4, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, T, Q> call(T (*Func) (T x, T y), vec<4, T, Q> const& a, T b)
		{
			return vec<4, T, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b), Func(a.w, b));
		}
<<<<<<< HEAD
		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(Fct Func, vec<4, T, Q> const& a, T b)
		{
			return vec<4, T, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b), Func(a.w, b));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<length_t L, typename T, qualifier Q>
	struct functor2_vec_int {};

	template<typename T, qualifier Q>
	struct functor2_vec_int<1, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, int, Q> call(int (*Func) (T x, int y), vec<1, T, Q> const& a, vec<1, int, Q> const& b)
		{
			return vec<1, int, Q>(Func(a.x, b.x));
		}
<<<<<<< HEAD

		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, int, Q> call(Fct Func, vec<1, T, Q> const& a, vec<1, int, Q> const& b)
		{
			return vec<1, int, Q>(Func(a.x, b.x));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<typename T, qualifier Q>
	struct functor2_vec_int<2, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, int, Q> call(int (*Func) (T x, int y), vec<2, T, Q> const& a, vec<2, int, Q> const& b)
		{
			return vec<2, int, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
<<<<<<< HEAD
		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, int, Q> call(Fct Func, vec<2, T, Q> const& a, vec<2, int, Q> const& b)
		{
			return vec<2, int, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<typename T, qualifier Q>
	struct functor2_vec_int<3, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, int, Q> call(int (*Func) (T x, int y), vec<3, T, Q> const& a, vec<3, int, Q> const& b)
		{
			return vec<3, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
<<<<<<< HEAD
		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, int, Q> call(Fct Func, vec<3, T, Q> const& a, vec<3, int, Q> const& b)
		{
			return vec<3, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};

	template<typename T, qualifier Q>
	struct functor2_vec_int<4, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, int, Q> call(int (*Func) (T x, int y), vec<4, T, Q> const& a, vec<4, int, Q> const& b)
		{
			return vec<4, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
<<<<<<< HEAD

		template<class Fct>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, int, Q> call(Fct Func, vec<4, T, Q> const& a, vec<4, int, Q> const& b)
		{
			return vec<4, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
=======
>>>>>>> 98512c69f4a6c0c95d0f6de65cd416eae7b987c3
	};
}//namespace detail
}//namespace glm
