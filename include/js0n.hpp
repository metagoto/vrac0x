#pragma once

#include "js0n/fw.hpp"
#include "js0n/type.hpp"
#include "js0n/basic_val.hpp"
#include "js0n/impl/basic_val.hpp"
#include "js0n/operator.hpp"
#include "js0n/iterator.hpp"
#include "js0n/traits/simple.hpp"


namespace vrac0x { namespace js0n
{
    // default convenient typedef
    typedef basic_val<tag::simple> val;

} }


#include "js0n/literal_key.hpp"
