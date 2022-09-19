#ifndef MARTIN_NODES_VALUES
#define MARTIN_NODES_VALUES

#include <memory>

#include "types.hpp"

namespace Martin {

    class ValueBase;
    typedef std::shared_ptr<ValueBase> Value;

    class ValueBase {
    public:
        ~ValueBase() = default;

        static Value MakeValue(Type type);

        virtual Type GetType() const = 0;

        virtual bool CanBeConstant() const { return true; }
        virtual bool IsConstant() const { return true; }
        virtual bool SetConstant(bool is_contant) { return false; }

        virtual void SetData(void* data) {};
        virtual void GetData(void* data) const {};

        void SetDataPtr(const std::shared_ptr<void>& data) { data_ptr = data; };
        std::shared_ptr<void> GetDataPtr() { return data_ptr; };

        void SetLineNumber(unsigned int number) { if (lineno == 0) lineno = number; }
        unsigned int GetLineNumber() const { return lineno; }
    protected:
        std::shared_ptr<void> data_ptr;
        unsigned int lineno = 0;
    };

}

#endif