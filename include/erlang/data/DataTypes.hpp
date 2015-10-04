#ifndef ERLANG_DATA_DATATYPES_HPP
#define ERLANG_DATA_DATATYPES_HPP

#include "../TermFwd.hpp"
#include "detail/TaggedValue.hpp"

#include <boost/mpl/vector.hpp>

#include <cstdint>
#include <string>

//============================================================================//
namespace erlang {
namespace data {
//----------------------------------------------------------------------------//

//
// According to the Erlang data type spec.
//

// There are numbers: integers and floats.
using Inteer = std::int64_t;
using Float = double;

// There are atoms. TODO: map to integers?
// Erlang offers C-style APIs, so wrapping a C-style string and tagging it
// seems to be enough, at least for now.
using Atom = detail::TaggedValue<std::string, struct AtomTag>;

// There are bit strings and binaries.
using String = detail::TaggedValue<std::string, struct StringTag>;
using Binary = detail::TaggedValue<std::string, struct BinaryTag>;

// Tere are reference, fun, port and pids. These are excluded now.

// There are tuples.
using Tuple = detail::TaggedValue<std::vector<term>, struct TupleTag>;

// There are lists.
using List = detail::TaggedValue<std::vector<term>, struct ListTag>;


// This is the ordering between the types. Try to compare a float and a string
// in Erlang.
// TODO: move it to a separate header.
typedef boost::mpl::vector<Integer, Float, Atom, String, List, Tuple, Binary>
        DataTypes;

//----------------------------------------------------------------------------//
} // namespace data
} // namespace erlang
//============================================================================//

#endif // ERLANG_DATA_DATATYPES_HPP
