#include <values.hpp>
#include <stdint.h>
#include <string.h>

#include <unicode.hpp>

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
    void SetDataPtr(void** data) override {\
        if (!constant) {\
            uint32_t length = unicode_length(*((const uint8_t**)data), unitype);\
            value = std::unique_ptr<size>(new size[length + unisize]);\
            memcpy(value.get(), *((uint8_t**)data), length + unisize);\
        }\
    }\
    void GetDataPtr(void** data) const override {\
        *((size**)data) = value.get();\
    }\
private:\
    std::unique_ptr<size> value = nullptr;\
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
StringClass(String8Value, String8, UnicodeType_8Bits, 1, uint8_t);
StringClass(String16Value, String16, UnicodeType_16Bits, 2, uint16_t);
StringClass(String32Value, String32, UnicodeType_32Bits, 4, uint32_t);
StringClass(String16lValue, String16l, UnicodeType_16BitsLittle, 2, uint16_t);
StringClass(String32lValue, String32l, UnicodeType_32BitsLittle, 4, uint32_t);
StringClass(String16bValue, String16b, UnicodeType_16BitsBig, 2, uint16_t);
StringClass(String32bValue, String32b, UnicodeType_32BitsBig, 4, uint32_t);
ValueClass(Float32Value, Float32, float);
ValueClass(Float64Value, Float64, double);
ValueClass(BooleanValue, Boolean, bool);

Value ValueBase::MakeValue(Type type) {
    if (type->IsType(None))
        return Value(new NoneValue);

    if (type->IsType(Int8))
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
    
    else if (type->IsType(Float32))
        return Value(new Float32Value);
    
    else if (type->IsType(Float64))
        return Value(new Float64Value);
    
    else if (type->IsType(Boolean))
        return Value(new BooleanValue);

    return Value(new UnknownValue);
}

Value* ValueBase::MakeValuePointer(Type type) {
    if (type->IsType(None))
        return new Value(new NoneValue);

    if (type->IsType(Int8))
        return new Value(new Int8Value);
    
    else if (type->IsType(Int16))
        return new Value(new Int16Value);
    
    else if (type->IsType(Int32))
        return new Value(new Int32Value);
    
    else if (type->IsType(UInt8))
        return new Value(new UInt8Value);
    
    else if (type->IsType(UInt16))
        return new Value(new UInt16Value);
    
    else if (type->IsType(UInt32))
        return new Value(new UInt32Value);
    
#ifdef bits_64
    else if (type->IsType(Int64))
        return new Value(new Int64Value);
    
    else if (type->IsType(UInt64))
        return new Value(new UInt64Value);
#endif

    else if (type->IsType(IntMax))
        return new Value(new IntMaxValue);
    
    else if (type->IsType(IntPtr))
        return new Value(new IntPtrValue);
    
    else if (type->IsType(UIntMax))
        return new Value(new UIntMaxValue);
    
    else if (type->IsType(UIntPtr))
        return new Value(new UIntPtrValue);
    
    else if (type->IsType(Float32))
        return new Value(new Float32Value);
    
    else if (type->IsType(Float64))
        return new Value(new Float64Value);
    
    else if (type->IsType(Boolean))
        return new Value(new BooleanValue);

    return new Value(new UnknownValue);
}