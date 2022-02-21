#include <types.hpp>

class UnknownType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Unknown";
    }

    bool IsUnknown() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::UNKNOWN;
    }
};

class NoneType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "None";
    }

    bool IsNone() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::NONE;
    }
};

class Int8Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Int8";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::INT8;
    }
};

class Int16Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Int16";
    }

    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::INT16;
    }
};

class Int32Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Int32";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::INT32;
    }
};

class UInt8Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "UInt8";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::UINT8;
    }
};

class UInt16Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "UInt16";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::UINT16;
    }
};

class UInt32Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "UInt32";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::UINT32;
    }
};

#ifdef bits_64
class Int64Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Int64";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::INT64;
    }
};

class UInt64Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "UInt64";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::UINT64;
    }
};
#endif

class IntMaxType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "IntMax";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::INTMAX;
    }
};

class IntPtrType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "";
    }

    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::INTPTR;
    }
};

class UIntMaxType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "UIntMax";
    }
    
    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::UINTMAX;
    }
};

class UIntPtrType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "UIntPtr";
    }

    bool IsInteger() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::UINTPTR;
    }
};

class IDType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "ID";
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::ID;
    }
};

class String8Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "String8";
    }
    
    bool IsString() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::STRING8;
    }
};

class String16lType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "String16l";
    }
    
    bool IsString() const override {
        return true;
    }

    bool IsBigEndianness() const override {
        return false;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::STRING16L;
    }
};

class String32lType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "String32l";
    }
    
    bool IsString() const override {
        return true;
    }

    bool IsBigEndianness() const override {
        return false;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::STRING32L;
    }
};

class String16bType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "String16b";
    }
    
    bool IsString() const override {
        return true;
    }

    bool IsBigEndianness() const override {
        return false;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::STRING16B;
    }
};

class String32bType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "String32b";
    }
    
    bool IsString() const override {
        return true;
    }

    bool IsBigEndianness() const override {
        return false;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::STRING32B;
    }
};

class Float32Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Float32";
    }
    
    bool IsFloat() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::FLOAT32;
    }
};

class Float64Type : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Float64";
    }
    
    bool IsFloat() const override {
        return true;
    }

    bool IsNativeEndianness() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::FLOAT64;
    }
};

class BooleanType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Boolean";
    }

    bool IsBoolean() const override {
        return true;
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::BOOLEAN;
    }
};

class TupleType : public TypeBase {
public:
    bool IsType(Type type) const override {
        return type == shared_from_this();
    }

    std::string GetName() const override {
        return "Tuple";
    }

    PrimitiveType GetPrimitiveType() const override {
        return PrimitiveType::TUPLE;
    }
};

Type TypeBase::MakeType(PrimitiveType type) {
    switch (type) {
        case PrimitiveType::NONE:
            return Type(new NoneType);
        
        case PrimitiveType::INT8:
            return Type(new Int8Type);
        
        case PrimitiveType::INT16:
            return Type(new Int16Type);
        
        case PrimitiveType::INT32:
            return Type(new Int32Type);
        
        case PrimitiveType::UINT8:
            return Type(new UInt8Type);
        
        case PrimitiveType::UINT16:
            return Type(new UInt16Type);
        
        case PrimitiveType::UINT32:
            return Type(new UInt32Type);
        
#ifdef bits_64
        case PrimitiveType::INT64:
            return Type(new Int64Type);
        
        case PrimitiveType::UINT64:
            return Type(new UInt64Type);
#endif

        case PrimitiveType::INTMAX:
            return Type(new IntMaxType);
        
        case PrimitiveType::INTPTR:
            return Type(new IntPtrType);
        
        case PrimitiveType::UINTMAX:
            return Type(new UIntMaxType);
        
        case PrimitiveType::UINTPTR:
            return Type(new UIntPtrType);
        
        case PrimitiveType::ID:
            return Type(new IDType);

        case PrimitiveType::STRING8:
            return Type(new String8Type);
        
        case PrimitiveType::STRING16L:
            return Type(new String16lType);
        
        case PrimitiveType::STRING32L:
            return Type(new String32lType);
        
        case PrimitiveType::STRING16B:
            return Type(new String16bType);
        
        case PrimitiveType::STRING32B:
            return Type(new String32bType);
        
        case PrimitiveType::FLOAT32:
            return Type(new Float32Type);
        
        case PrimitiveType::FLOAT64:
            return Type(new Float64Type);
        
        case PrimitiveType::BOOLEAN:
            return Type(new BooleanType);

        case PrimitiveType::TUPLE:
            return Type(new TupleType);

        default:
            return Type(new UnknownType);
    }
}

const Type None = TypeBase::MakeType(TypeBase::PrimitiveType::NONE);
const Type Unknown = TypeBase::MakeType(TypeBase::PrimitiveType::UNKNOWN);
const Type Int8 = TypeBase::MakeType(TypeBase::PrimitiveType::INT8);
const Type Int16 = TypeBase::MakeType(TypeBase::PrimitiveType::INT16);
const Type Int32 = TypeBase::MakeType(TypeBase::PrimitiveType::INT32);
const Type UInt8 = TypeBase::MakeType(TypeBase::PrimitiveType::UINT8);
const Type UInt16 = TypeBase::MakeType(TypeBase::PrimitiveType::UINT16);
const Type UInt32 = TypeBase::MakeType(TypeBase::PrimitiveType::UINT32);
#ifdef bits_64
const Type Int64 = TypeBase::MakeType(TypeBase::PrimitiveType::INT64);
const Type UInt64 = TypeBase::MakeType(TypeBase::PrimitiveType::UINT64);
#endif
const Type IntMax = TypeBase::MakeType(TypeBase::PrimitiveType::INTMAX);
const Type IntPtr = TypeBase::MakeType(TypeBase::PrimitiveType::INTPTR);
const Type UIntMax = TypeBase::MakeType(TypeBase::PrimitiveType::UINTMAX);
const Type UIntPtr = TypeBase::MakeType(TypeBase::PrimitiveType::UINTPTR);
const Type ID = TypeBase::MakeType(TypeBase::PrimitiveType::ID);
const Type String8 = TypeBase::MakeType(TypeBase::PrimitiveType::STRING8);
const Type String16l = TypeBase::MakeType(TypeBase::PrimitiveType::STRING16L);
const Type String32l = TypeBase::MakeType(TypeBase::PrimitiveType::STRING32L);
const Type String16b = TypeBase::MakeType(TypeBase::PrimitiveType::STRING16B);
const Type String32b = TypeBase::MakeType(TypeBase::PrimitiveType::STRING32B);
const Type Float32 = TypeBase::MakeType(TypeBase::PrimitiveType::FLOAT32);
const Type Float64 = TypeBase::MakeType(TypeBase::PrimitiveType::FLOAT64);
const Type Boolean = TypeBase::MakeType(TypeBase::PrimitiveType::BOOLEAN);
const Type Tuple = TypeBase::MakeType(TypeBase::PrimitiveType::TUPLE);