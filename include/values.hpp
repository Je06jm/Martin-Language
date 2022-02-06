#ifndef MARTIN_NODES_VALUES
#define MARTIN_NODES_VALUES

#include <memory>

#include "types.hpp"

class ValueBase;
typedef std::unique_ptr<ValueBase> Value;

class ValueBase {
public:
    ~ValueBase() = default;

    static Value MakeValue(Type type);
    static Value* MakeValuePointer(Type type);

    virtual Type GetType() const = 0;

    virtual bool CanBeConstant() const { return true; }
    virtual bool IsConstant() const { return true; }
    virtual bool SetConstant(bool is_contant) { return false; }

    virtual void SetData(void* data) {};
    virtual void GetData(void* data) const {};

    virtual void SetDataPtr(void** data) {};
    virtual void GetDataPtr(void** data) const {};
};

#endif