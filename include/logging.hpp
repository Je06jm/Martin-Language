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
        friend Formatter;
        public:
            virtual ~Logger() {}
            void Push(const std::string& msg) {
                formatter.Push(msg);
            };

            virtual void Finish() = 0;
        
        protected:
            Formatter formatter;
            std::string buffer;

        private:
            void Clear() {
                formatter.Clear();
                buffer = "";
            }
        };
        
        extern Logger* FatalLogger;
        extern Logger* ErrorLogger;
        extern Logger* WarningLogger;
        extern Logger* PrintLogger;
    }

    inline void Fatal() {
        LoggingUtil::FatalLogger->Finish();
    }

    inline void Error() {
        LoggingUtil::ErrorLogger->Finish();
    }

    inline void Warning() {
        LoggingUtil::WarningLogger->Finish();
    }

    inline void Print() {
        LoggingUtil::PrintLogger->Finish();
    }

    template <typename T, typename... Args>
    inline void Fatal(T first, Args... rest) {
        std::string msg;
        Serialize(first, msg);
        LoggingUtil::FatalLogger->Push(msg);
        Fatal(rest...);
    }

    template <typename T, typename... Args>
    inline void Error(T first, Args... rest) {
        std::string msg;
        Serialize(first, msg);
        LoggingUtil::ErrorLogger->Push(msg);
        Error(rest...);
    }

    template <typename T, typename... Args>
    inline void Warning(T first, Args... rest) {
        std::string msg;
        Serialize(first, msg);
        LoggingUtil::WarningLogger->Push(msg);
        Warning(rest...);
    }

    template <typename T, typename... Args>
    inline void Print(T first, Args... rest) {
        std::string msg;
        Serialize(first, msg);
        LoggingUtil::PrintLogger->Push(msg);
        Print(rest...);
    }

}

#endif