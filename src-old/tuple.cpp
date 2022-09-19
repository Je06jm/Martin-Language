#include <tuple.hpp>

namespace Martin {

    Value MakeTuple(const std::vector<Value>& values) {
        Value ret = ValueBase::MakeValue(Tuple);

        auto ptr = std::make_shared<std::vector<Value>>(values);

        ret->SetDataPtr(ptr);

        return ret;
    }

}