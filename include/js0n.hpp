#pragma once

#include "js0n/fw.hpp"
#include "js0n/tags.hpp"
#include "js0n/traits.hpp"
#include "js0n/type.hpp"
#include "js0n/basic_val.hpp"
#include "js0n/impl/basic_val.hpp"
#include "js0n/operator.hpp"
#include "js0n/iterator.hpp"


namespace vrac0x { namespace js0n
{
    // convenient typedef
    typedef basic_val<tag::string, tag::vector> val;

} }
