#ifndef MARTIN_NODES_TYPES
#define MARTIN_NODES_TYPES

#include <memory>
#include <string>
#include "platform.hpp"

class TypeBase;
typedef std::shared_ptr<TypeBase> Type;

const extern Type None;
const extern Type Unknown;

const extern Type Int8;

const extern Type Int16;
const extern Type Int32;
const extern Type UInt8;
const extern Type UInt16;
const extern Type UInt32;

#ifdef bits_64
const extern Type Int64;
const extern Type UInt64;
#endif

const extern Type IntMax;
const extern Type IntPtr;
const extern Type UIntMax;
const extern Type UIntPtr;

const extern Type ID;

const extern Type String8;
const extern Type String16l;
const extern Type String32l;
const extern Type String16b;
const extern Type String32b;

const extern Type Float32;
const extern Type Float64;

const extern Type Boolean;

const extern Type Tuple;

/*
const extern Type Tuple;

const extern Type Struct;
const extern Type Union;
const extern Type Enum;

const extern Type TypeDef;
const extern Type FuncDef;
*/


class TypeBase : public std::enable_shared_from_this<TypeBase> {
public:
    virtual ~TypeBase() = default;

    enum class PrimitiveType {
        NONE,
        UNKNOWN,

        INT8,
        INT16,
        INT32,
        UINT8,
        UINT16,
        UINT32,
    
#ifdef bits_64
        INT64,
        UINT64,
#endif

        INTMAX,
        INTPTR,
        UINTMAX,
        UINTPTR,

        ID,

        STRING8,
        STRING16L,
        STRING32L,
        STRING16B,
        STRING32B,

        FLOAT32,
        FLOAT64,

        BOOLEAN,

        TUPLE
    };

    static Type MakeType(PrimitiveType type);

    virtual bool IsType(Type type) const = 0;
    virtual std::string GetName() const = 0;

    virtual bool IsNone() const { return false; }
    virtual bool IsUnknown() const { return false; }
    virtual bool IsInteger() const { return false; }
    virtual bool IsFloat() const { return false; }
    virtual bool IsString() const { return false; }
    virtual bool IsBoolean() const { return false; }
    virtual bool IsNativeEndianness() const { return false; }
    virtual bool IsBigEndianness() const { return false; }

    virtual PrimitiveType GetPrimitiveType() const = 0;
};

#endif