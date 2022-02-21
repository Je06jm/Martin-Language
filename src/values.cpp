#include <values.hpp>
#include <stdint.h>
#include <string.h>

#include <unicode.hpp>

#include <vector>

#define ValueClass(name, type, size)\
class name : public ValueBase {\
    Type GetType() const override {\
        return type;\
    }\
    bool IsConstant() const {\
        return constant;\
    }\
    bool SetConstant(bool is_constant) override {\
        constant = is_constant;\
        return true;\
    }\
    void SetData(void* data) override {\
        if (!constant)\
            value = *((size*)data);\
    }\
    void GetData(void* data) const override {\
        *((size*)data) = value;\
    }\
private:\
    size value;\
    bool constant = false;\
};

#define StringClass(name, type, unitype, unisize, size)\
class name : public ValueBase {\
    Type GetType() const override {\
        return type;\
    }\
    bool IsConstant() const {\
        return constant;\
    }\
    bool SetConstant(bool is_constant) override {\
        constant = is_constant;\
        return true;\
    }\
private:\
    bool constant = false;\
};

class NoneValue : public ValueBase {
public:
    Type GetType() const override {
        return None;
    }
};

class UnknownValue : public ValueBase {
public:
    Type GetType() const override {
        return Unknown;
    }
};

ValueClass(Int8Value, Int8, int8_t);
ValueClass(Int16Value, Int16, int16_t);
ValueClass(Int32Value, Int32, int32_t);
ValueClass(UInt8Value, UInt8, uint8_t);
ValueClass(UInt16Value, UInt16, uint16_t);
ValueClass(UInt32Value, UInt32, uint32_t);
#ifdef bits_64
ValueClass(Int64Value, Int64, int64_t);
ValueClass(UInt64Value, UInt64, uint64_t);
#endif
ValueClass(IntMaxValue, IntMax, intmax_t);
ValueClass(IntPtrValue, IntPtr, intptr_t);
ValueClass(UIntMaxValue, UIntMax, uintmax_t);
ValueClass(UIntPtrValue, UIntPtr, uintptr_t);

class IDValue : public ValueBase {
public:
    Type GetType() const override {
        return ID;
    }
};

StringClass(String8Value, String8, UnicodeType_8Bits, 1, uint8_t);
StringClass(String16lValue, String16l, UnicodeType_16BitsLittle, 2, uint16_t);
StringClass(String32lValue, String32l, UnicodeType_32BitsLittle, 4, uint32_t);
StringClass(String16bValue, String16b, UnicodeType_16BitsBig, 2, uint16_t);
StringClass(String32bValue, String32b, UnicodeType_32BitsBig, 4, uint32_t);
ValueClass(Float32Value, Float32, float);
ValueClass(Float64Value, Float64, double);
ValueClass(BooleanValue, Boolean, bool);

class TupleValue : public ValueBase {
public:
    Type GetType() const override {
        return Tuple;
    }

    bool IsConstant() const override {
        return constant;
    }

    bool SetConstant(bool is_constant) {
        constant = is_constant;
        return true;
    }
private:
    bool constant = false;
};

Value ValueBase::MakeValue(Type type) {
    if (type == nullptr)
        return Value(new UnknownValue);

    else if (type->IsType(None))
        return Value(new NoneValue);

    else if (type->IsType(Int8))
        return Value(new Int8Value);
    
    else if (type->IsType(Int16))
        return Value(new Int16Value);
    
    else if (type->IsType(Int32))
        return Value(new Int32Value);
    
    else if (type->IsType(UInt8))
        return Value(new UInt8Value);
    
    else if (type->IsType(UInt16))
        return Value(new UInt16Value);
    
    else if (type->IsType(UInt32))
        return Value(new UInt32Value);
    
#ifdef bits_64
    else if (type->IsType(Int64))
        return Value(new Int64Value);
    
    else if (type->IsType(UInt64))
        return Value(new UInt64Value);
#endif

    else if (type->IsType(IntMax))
        return Value(new IntMaxValue);
    
    else if (type->IsType(IntPtr))
        return Value(new IntPtrValue);
    
    else if (type->IsType(UIntMax))
        return Value(new UIntMaxValue);
    
    else if (type->IsType(UIntPtr))
        return Value(new UIntPtrValue);
    
    else if (type->IsType(ID))
        return Value(new IDValue);

    else if (type->IsType(String8))
        return Value(new String8Value);
    
    else if (type->IsType(String16l))
        return Value(new String16lValue);
    
    else if (type->IsType(String32l))
        return Value(new String32lValue);
    
    else if (type->IsType(String16b))
        return Value(new String16bValue);
    
    else if (type->IsType(String32b))
        return Value(new String32bValue);

    else if (type->IsType(Float32))
        return Value(new Float32Value);
    
    else if (type->IsType(Float64))
        return Value(new Float64Value);
    
    else if (type->IsType(Boolean))
        return Value(new BooleanValue);

    else if (type->IsType(Tuple))
        return Value(new TupleValue);

    return Value(new UnknownValue);
}