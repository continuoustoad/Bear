#pragma once
#include <cstdlib>
#include <cinttypes>
#include <Exception.h>

using Size   = std::size_t   ;
using Char   = std::int8_t   ;
using Byte   = std::uint8_t  ;
using Int16  = std::int16_t  ;
using Int32  = std::int32_t  ;
using Int64  = std::int64_t  ;
using UInt16 = std::uint16_t ;
using UInt32 = std::uint32_t ;
using UInt64 = std::uint64_t ;
const auto &DefaultAllocator = std::malloc;
