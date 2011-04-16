#ifndef _NYXALGORITHM_HPP_
#define _NYXALGORITHM_HPP_


namespace Nyx
{
  /**
   *  @brief This does what you think it does.
   *  @param  a  A thing of arbitrary type.
   *  @param  b  Another thing of arbitrary type.
   *  @return   The lesser of the parameters.
   *
   *  This will work on temporary expressions, since they are only evaluated
   *  once, unlike a preprocessor macro.
  */
  template<typename _Tp>
    inline const _Tp&
    Min(const _Tp& __a, const _Tp& __b)
    {
      if (__b < __a)
		return __b;
      return __a;
    }

  /**
   *  @brief This does what you think it does.
   *  @param  a  A thing of arbitrary type.
   *  @param  b  Another thing of arbitrary type.
   *  @return   The greater of the parameters.
   *
   *  This will work on temporary expressions, since they are only evaluated
   *  once, unlike a preprocessor macro.
  */
  template<typename _Tp>
    inline const _Tp&
    Max(const _Tp& __a, const _Tp& __b)
    {
      if (__b > __a)
		return __b;
      return __a;
    }
}


#endif // _NYXALGORITHM_HPP_
