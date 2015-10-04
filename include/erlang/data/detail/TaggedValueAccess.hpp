#ifndef ERLANG_DATA_DETAIL_TAGGEDVALUEACCESS_HPP
#define ERLANG_DATA_DETAIL_TAGGEDVALUEACCESS_HPP

#include "TaggedValue.hpp"

//============================================================================//
namespace erlang {
namespace data {
namespace detail {
//----------------------------------------------------------------------------//

template<typename Value, typename Tag>
Value& accessValue(TaggedValue<Value, Tag>& accessedValue) {
    return accessedValue.value;
}

//----------------------------------------------------------------------------//
} // namespace detail
} // namespace data
} // namespace erlang
//============================================================================//

#endif // ERLANG_DATA_DETAIL_TAGGEDVALUEACCESS_HPP
