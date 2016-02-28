#include <erlang/data/DataTypes.hpp>
#include <erlang/term.hpp>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>

#include <gtest/gtest.h>

#include <tuple>

//============================================================================//
namespace {
//----------------------------------------------------------------------------//

void assertEquality(const erlang::term& lhs, const erlang::term& rhs) {
    EXPECT_EQ(lhs, rhs);
    EXPECT_LE(lhs, rhs);
    EXPECT_GE(lhs, rhs);
    EXPECT_FALSE(lhs != rhs);
    EXPECT_FALSE(lhs < rhs);
    EXPECT_FALSE(lhs > rhs);
}

void assertLessThan(const erlang::term& lhs, const erlang::term& rhs) {
    EXPECT_NE(lhs, rhs);
    EXPECT_LT(lhs, rhs);
    EXPECT_LE(lhs, rhs);
    EXPECT_FALSE(lhs == rhs);
    EXPECT_FALSE(lhs > rhs);
    EXPECT_FALSE(lhs >= rhs);
}

//----------------------------------------------------------------------------//

template <unsigned BASE, unsigned I, typename...Ts>
typename std::enable_if<I == sizeof...(Ts), void>::type
compareToBase(const std::tuple<Ts...>& tuple) {
    // end of recursion
}

template <unsigned BASE, unsigned I, typename...Ts>
typename std::enable_if<I < sizeof...(Ts), void>::type
compareToBase(const std::tuple<Ts...>& tuple) {
    assertLessThan(erlang::term{std::get<BASE>(tuple)},
            erlang::term{std::get<I>(tuple)});
    compareToBase<BASE, I + 1>(tuple);
}

//----------------------------------------------------------------------------//

template <unsigned I, typename...Ts>
typename std::enable_if<I == sizeof...(Ts), void>::type
compareOrderedSequence(const std::tuple<Ts...>& tuple) {
    // end of recursion
}

template <unsigned I, typename...Ts>
typename std::enable_if<I < sizeof...(Ts), void>::type
compareOrderedSequence(const std::tuple<Ts...>& tuple) {
    assertEquality(erlang::term{std::get<I>(tuple)},
            erlang::term{std::get<I>(tuple)});
    compareToBase<I, I + 1>(tuple);
    compareOrderedSequence<I + 1>(tuple);
}

//----------------------------------------------------------------------------//

const auto values = std::make_tuple(
        static_cast<erlang::data::Int>(-154321234),
        static_cast<erlang::data::Int>(0),
        static_cast<erlang::data::Int>(6),
        static_cast<erlang::data::Int>(34985453598532),
        static_cast<erlang::data::Float>(-343254),
        static_cast<erlang::data::Float>(0.0));

//----------------------------------------------------------------------------//
} // unnamed namespace
//============================================================================//

TEST(Compare, Values) {
    compareOrderedSequence<0>(values);
}
