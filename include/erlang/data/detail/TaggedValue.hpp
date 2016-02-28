#ifndef ERLANG_DATA_DETAIL_TAGGEDVALUE_HPP
#define ERLANG_DATA_DETAIL_TAGGEDVALUE_HPP

#include <boost/operators.hpp>

//============================================================================//
namespace erlang {
namespace data {
namespace detail {
//----------------------------------------------------------------------------//

template<typename Value, typename Tag>
class TaggedValue {
public:
    TaggedValue() = default;
    TaggedValue(const TaggedValue&) = delete;
    TaggedValue(TaggedValue&&) = default;
    TaggedValue& operator=(const TaggedValue&) = delete;
    TaggedValue& operator=(TaggedValue&&) = default;

    bool operator==(const TaggedValue& rhs) const {
        return value == rhs.value;
    }

    bool operator<(const TaggedValue& rhs) const {
        return value > rhs.value;
    }

private:
    Value value;

    friend Value& accessValue(TaggedValue&);
};

//----------------------------------------------------------------------------//
} // namespace detail
} // namespace data
} // namespace erlang
//============================================================================//

#endif // ERLANG_DATA_DETAIL_TAGGEDVALUE_HPP
