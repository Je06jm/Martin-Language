#ifndef MARTIN_ERROR
#define MARTIN_ERROR

#include <string>
#include <vector>
#include <stdint.h>

#define _TO_STRING_HELPER(T)\
template <>\
inline void Serialize(const T& type, std::string& serial) {\
    serial = std::to_string(type);\
}\
template <>\
inline void Serialize(const T* type, std::string& serial) {\
    serial = std::string("*") + std::to_string(*(type));\
}

namespace Martin {

    template <typename T>
    void Serialize(const T* type, std::string& serial) {
        type->Serialize(serial);
    }

    template <typename T>
    void Serialize(const T& type, std::string& serial) {
        type.Serialize(serial);
    }

    template <>
    inline void Serialize(const std::string& type, std::string& serial) {
        serial = std::string(type);
    }

    template <>
    inline void Serialize(const int8_t& type, std::string& serial) {
        serial = std::to_string(type);
    }

    template <>
    inline void Serialize(const char* type, std::string& serial) {
        serial = std::string(type);
    }

    _TO_STRING_HELPER(uint8_t)
    _TO_STRING_HELPER(int16_t)
    _TO_STRING_HELPER(uint16_t)
    _TO_STRING_HELPER(int32_t)
    _TO_STRING_HELPER(uint32_t)
    _TO_STRING_HELPER(int64_t)
    _TO_STRING_HELPER(uint64_t)

    namespace LoggingUtil {
        class Formatter {
        public:
            inline void Push(const std::string& arg) {
                buffer.push_back(arg);
            }

            inline void Clear() {
                buffer.clear();
            }

            bool GetFormatted(std::string& msg);
        
        private:
            std::vector<std::string> buffer;
        };

        class Logger {
        public:
            virtual ~Logger() {}
            virtual void Out(std::string msg) = 0;
        };
        
        extern Logger* FatalLogger;
        extern Logger* ErrorLogger;
        extern Logger* WarningLogger;
        extern Logger* PrintLogger;

        extern Formatter* FormatFormatter;

        inline void FormatArr(std::vector<std::string>&) {}

        template <typename T, typename... Args>
        inline void FormatArr(std::vector<std::string>& arr, T first, Args... rest) {
            std::string msg;
            Serialize(first, msg);
            arr.push_back(msg);
            FormatArr(arr, rest...);
        }
    }

    template <typename T, typename... Args>
    inline std::string Format(T first, Args... rest) {
        std::vector<std::string> strs;
        LoggingUtil::FormatArr(strs, first, rest...);

        LoggingUtil::FormatFormatter->Clear();
        for (auto str : strs) {
            LoggingUtil::FormatFormatter->Push(str);
        }

        std::string result;
        if (LoggingUtil::FormatFormatter->GetFormatted(result)) {
            return result;
        }

        return "Could not format string";
    }

    template <typename T, typename... Args>
    inline void Fatal(T first, Args... rest) {
        std::string msg = Format(first, rest...);
        LoggingUtil::FatalLogger->Out(msg);
    }

    template <typename T, typename... Args>
    inline void Error(T first, Args... rest) {
        std::string msg = Format(first, rest...);
        LoggingUtil::ErrorLogger->Out(msg);
    }

    template <typename T, typename... Args>
    inline void Warning(T first, Args... rest) {
        std::string msg = Format(first, rest...);
        LoggingUtil::WarningLogger->Out(msg);
    }

    template <typename T, typename... Args>
    inline void Print(T first, Args... rest) {
        std::string msg = Format(first, rest...);
        LoggingUtil::PrintLogger->Out(msg);
    }

}

#undef _TO_STRING_HELPER

#endif