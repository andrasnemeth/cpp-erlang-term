#ifndef ERLANG_TERM_HPP
#define ERLANG_TERM_HPP

#include "data/DataTypes.hpp"

#include <boost/mpl/contains.hpp>
#include <boost/operators.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>

#include <type_traits>

//============================================================================//
namespace erlang {
namespace detail {
//----------------------------------------------------------------------------//

// struct Unbound {
// };

// using TermValue = boost::make_variant_over<boost::mpl::push_front<
//         data::OrderedDataTypes, Unbound>::type>::type;

struct EqualityComparer {
    template<typename T>
    bool operator()(const T& lhs, const T& rhs) {
        return lhs == rhs;
    }
};

struct LessThanComparer {
    template<typename T>
    bool operator()(const T& lhs, const T& rhs) {
        return lhs < rhs;
    }
};

//----------------------------------------------------------------------------//

template<typename DataVariant, typename Comparer>
class CompareVisitor : public boost::static_visitor<bool> {
public:
    CompareVisitor(const DataVariant& lhsValue) : lhsValue(lhsValue) {
    }

    template<typename T>
    bool operator()(const T& rhsValue) {
        return comparer(boost::get<T>(lhsValue), rhsValue);
    }

private:
    Comparer comparer;
    const DataVariant& lhsValue;
};

// This could be a typedef to boost::variant, the only reason the boilerplate
// is needed to avoid default initialization of variant without giving a value
// and to do not allow to use it as a variant in client code, it is rather an
// opaque type.
template<typename MetaTypeSequence>
class term : boost::totally_ordered<term<MetaTypeSequence>> {
private:
    using DataTypes = typename MetaTypeSequence::template apply<term>::type;
    using Value = typename boost::make_variant_over<DataTypes>::type;
    template <typename T>
    using TypeIsKnown = typename std::enable_if<boost::mpl::contains<DataTypes,
            T>::value>::type;

public:
    // FIXME: Allow to be unbound only if it is unavoidable! (use optional?).
    // An Erlang term can be unbound, but it is better to avoid that case here.
    //term() : value(Unbound()) {
    //}

    template <typename T, typename = TypeIsKnown<T>>
    explicit term(const T& value) : value(value) {
    }

    template <typename T, typename = TypeIsKnown<T>>
    explicit term(T&& value) : value(std::move(value)) {
        // FIXME: assert is required
        // static_assert(std::is_rvalue_reference<T>::value,
        //         "Only rvalues are accepted");
    }

    term(const term&) = delete;
    term(term&&) = default;
    term& operator=(const term&) = delete;
    term& operator=(term&&) = default;
    ~term() = default;

    bool operator==(const term& rhs) const {
        if (this->value.which() == rhs.value.which()) {
            detail::CompareVisitor<Value, detail::EqualityComparer> visitor(
                    value);
            return boost::apply_visitor(visitor, rhs.value);
        }
        return false;
    }

    bool operator<(const term& rhs) const {
        if (this->value.which() == rhs.value.which()) {
            detail::CompareVisitor<Value, detail::LessThanComparer> visitor(
                    value);
            return boost::apply_visitor(visitor, rhs.value);
        }
        return value.which() < rhs.value.which();
    }

private:
    Value value;
};

//----------------------------------------------------------------------------//
}  // namespace detail
//============================================================================//

using term = detail::term<data::MakeOrderedTypeSequence>;

//----------------------------------------------------------------------------//
} // namespace erlang
//============================================================================//

#endif // ERLANG_TERM_HPP
