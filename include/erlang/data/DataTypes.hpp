#ifndef ERLANG_DATA_DATATYPES_HPP
#define ERLANG_DATA_DATATYPES_HPP

#include "detail/TaggedValue.hpp"

#include <boost/mpl/vector.hpp>

#include <cstdint>
#include <string>
#include <vector>

//============================================================================//
namespace erlang {
namespace data {
//----------------------------------------------------------------------------//

//
// According to the Erlang data type spec.
//

// There are numbers: integers and floats.
using Int = std::int64_t;
using Float = double;

// There are atoms. TODO: map atom strings to integers?
using Atom = detail::TaggedValue<std::string, struct AtomTag>;

// There are bit strings and binaries.
using String = detail::TaggedValue<std::string, struct StringTag>;
using Binary = detail::TaggedValue<std::string, struct BinaryTag>;

// Tere are reference funs, ports and pids. These are excluded now.

// There are tuples.
template <typename Term>
using Tuple = detail::TaggedValue<std::vector<Term>, struct TupleTag>;

// There are lists.
template <typename Term>
using List = detail::TaggedValue<std::vector<Term>, struct ListTag>;

// This is the ordering between the types. Try to compare a float and a string
// in Erlang.
template <typename Term>
using OrderedDataTypes = boost::mpl::vector<Int, Float, Atom, String,
        List<Term>, Tuple<Term>, Binary>;

struct MakeOrderedTypeSequence {
    template<typename Term>
    struct apply {
        using type = OrderedDataTypes<Term>;
    };
};

//----------------------------------------------------------------------------//
} // namespace data
} // namespace erlang
//============================================================================//

#endif // ERLANG_DATA_DATATYPES_HPP
