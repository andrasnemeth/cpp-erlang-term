#ifndef ERLANG_TERM_HPP
#define ERLANG_TERM_HPP

#include "data/DataTypes.hpp"

#include <boost/operators.hpp>
#include <boost/variant/variant.hpp>

#include <type_traits>

//============================================================================//
namespace erlang {
namespace detail {
//----------------------------------------------------------------------------//

struct Empty {
};

using TermValue = boost::make_variant_over<boost::mpl::push_front<
        data::DataTypes, Empty>::type>::type;

//----------------------------------------------------------------------------//
}  // detai
//============================================================================//

class term : boost::totally_ordered<term> {
public:
    term() : value(Empty()) {
    }

    template<typename T>
    explicit term(std::enable_if<boost::mpl::contains<data::DataTypes,
            T>::value, T&&>::type value) : value(value) {
        static_assert(std::is_rvalue<T>::value, "Only rvalues are accepted");
    }

    term(const term&) = delete;
    term(term&&) = default;
    term& operator=(const term&) = delete;
    term& operator=(term&&) = default;x

    bool operator==(const term& rhs) const {
        return value == rhs.value;
    }

    bool operator>(const term& rhs) const {
        return value > rhs.value;
    }

private:
    TermValue value;
};

//----------------------------------------------------------------------------//
} // namespace erlang
//============================================================================//

#endif // ERLANG_TERM_HPP
