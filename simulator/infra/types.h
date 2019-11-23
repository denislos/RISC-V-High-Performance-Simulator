/**
 * types.h - Implementation of platform-independent types
 */


#ifndef INFRA_TYPES_H
#define INFRA_TYPES_H

#include <cstdint>


// signed types
using int8  = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t; 
using int64 = std::int64_t;


// unsigned types
using uint8  = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t; 
using uint64 = std::uint64_t;


static const uint8  MAX_VAL8  = UINT8_MAX;
static const uint16 MAX_VAL16 = UINT16_MAX;
static const uint32 MAX_VAL32 = UINT32_MAX;
static const uint64 MAX_VAL64 = UINT64_MAX;


static const uint8  NO_VAL8  = 0xBA;
static const uint16 NO_VAL16 = 0xF00D;
static const uint32 NO_VAL32 = 0xDEADBEEFul;
static const uint64 NO_VAL64 = 0xDEADBEEFF00DCAFEull;


#endif // INFRA_TYPES_H