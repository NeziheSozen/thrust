#pragma once

#include <thrust/system/error_code.h>

namespace thrust
{

namespace experimental
{

namespace system
{

error_code
  ::error_code(void)
    :m_val(0),m_cat(&system_category())
{
  ;
} // end error_code::error_code()


error_code
  ::error_code(int val, const error_category &cat)
    :m_val(val),m_cat(&cat)
{
  ;
} // end error_code::error_code()


template <typename ErrorCodeEnum>
  error_code
    ::error_code(ErrorCodeEnum e,
                 typename thrust::detail::enable_if<is_error_code_enum<ErrorCodeEnum>::value>::type *)
{
  *this = make_error_code(e);
} // end error_code::error_code()


error_code
  ::assign(int val, const error_category &cat)
{
  m_val = val;
  m_cat = &cat;
} // end error_code::assign()


template <typename ErrorCodeEnum>
  typename thrust::detail::enable_if<is_error_code_enum<ErrorCodeEnum>::value>::type &
    error_code
      ::operator=(ErrorCodeEnum e)
{
  *this = make_error_code(e);
} // end error_code::operator=()


void error_code
  ::clear(void)
{
  m_val = 0;
  m_cat = system_category();
} // end error_code::clear()


int error_code
  ::value(void) const
{
  return m_val;
} // end error_code::value()


const error_category &error_code
  ::category(void) const
{
  return *m_cat;
} // end error_code::category()


const error_condition &error_code
  ::default_error_condition(void) const
{
  return category().default_error_condition();
} // end error_code::default_error_condition()


std::string error_code
  ::message(void) const
{
  return category().message(value());
} // end error_code::message()


error_code
  ::operator bool (void) const
{
  return value() != 0;
} // end error_code::operator bool ()


error_code make_error_code(errc::errc_t e)
{
  return error_code(static_cast<int>(e), generic_category());
} // end make_error_code()


bool operator<(const error_code &lhs, const error_code &rhs)
{
  return (lhs.category() < rhs.category()) || (lhs.category() == rhs.category() && lhs.value() < rhs.value());
} // end operator==()


template<typename charT, typename traits>
  std::basic_ostream<charT,traits>&
    operator<<(std::basic_ostream<charT,traits> &os, const error_code &ec)
{
  return os << ec.category().name() << ':' << ec.value();
} // end operator<<()


bool operator==(const error_code &lhs, const error_code &rhs)
{
  return lhs.category() == rhs.category() && lhs.value() == rhs.value();
} // end operator==()


bool operator==(const error_code &lhs, const error_condition &rhs)
{
  return lhs.category().equivalent(lhs.value(), rhs) || rhs.category().equivalent(lhs,rhs.value());
} // end operator==()


bool operator==(const error_condition &lhs, const error_code &rhs)
{
  return rhs.category().equivalent(lhs.value(), lhs) || lhs.category().equivalent(rhs, lhs.value());
} // end operator==()


bool operator==(const error_condition &lhs, const error_condition &rhs)
{
  return lhs.category() == rhs.category() && lhs.value() == rhs.value();
} // end operator==()


bool operator!=(const error_code &lhs, const error_code &rhs)
{
  return !(lhs == rhs);
} // end operator!=()


bool operator!=(const error_code &lhs, const error_condition &rhs)
{
  return !(lhs == rhs);
} // end operator!=()


bool operator!=(const error_condition &lhs, const error_code &rhs)
{
  return !(lhs == rhs);
} // end operator!=()


bool operator!=(const error_condition &lhs, const error_condition &rhs)
{
  return !(lhs == rhs);
} // end operator!=()


} // end system

} // end experimental

} // end thrust
