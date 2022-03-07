#include <logging.hpp>

#include <iostream>
#include <time.h>
#include <stdlib.h>

namespace Martin::LoggingUtil {
    bool Formatter::GetFormatted(std::string& arg) {
        if (buffer.size() == 0) 
            return false;

        size_t index = 1;
        size_t arg_pos;

        std::string format = buffer[0];

        arg_pos = format.find("$");
        while (arg_pos != std::string::npos) {
            if ((arg_pos < format.size()) && (format[arg_pos+1] == '$')) {
                arg_pos += 2;
            } else {
                if (index >= buffer.size()) {
                    Error("Not enough arguments for formatted string: $\n", format);
                    return false;

                } else {
                    format = format.replace(arg_pos, 1, buffer[index]);
                    arg_pos += buffer[index++].size();
                }
            }
            arg_pos = format.find("$", arg_pos+1);
        }

        arg = format;

        if (index < buffer.size()) {
            size_t size = buffer.size();
            Warning("String has $ unused arguments: $\n", size - index, format);
            return false;
        }

        buffer.clear();

        return true;
    }

    class FatalLoggingClass : public Logger {
    public:
        void Out(std::string msg) override {
            std::string buffer;
            Setup(buffer);
            ReplaceNewlines(msg);
            std::cerr << buffer << msg << "\033[0m";
            exit(EXIT_FAILURE);
        }

    private:
        void Setup(std::string& buffer) {
            buffer = "\033[0;41m";
        }

        void ReplaceNewlines(std::string& msg) {
            size_t index = msg.find("\n");
            while (index != std::string::npos) {
                msg = msg.replace(index, 1, "\033[0m\n\033[41m");
                index += 10;
                index = msg.find("\n", index);
            }
        }
    };

    class ErrorLoggingClass : public Logger {
    public:
        void Out(std::string msg) override {
            std::string buffer;
            Setup(buffer);
            ReplaceNewlines(msg);
            std::cerr << buffer << msg << "\033[0m";
        }

    private:
        void Setup(std::string& buffer) {
            buffer = "\033[0;31m";
        }

        void ReplaceNewlines(std::string& msg) {
            size_t index = msg.find("\n");
            while (index != std::string::npos) {
                msg = msg.replace(index, 1, "\033[0m\n\033[31m");
                index += 10;
                index = msg.find("\n", index);
            }
        }
    };

    class WarningLoggingClass : public Logger {
    public:
        void Out(std::string msg) override {
            std::string buffer;
            Setup(buffer);
            ReplaceNewlines(msg);
            std::cout << buffer << msg << "\033[0m";
        }

    private:
        void Setup(std::string& buffer) {
            buffer = "\033[0;33m";
        }

        void ReplaceNewlines(std::string& msg) {
            size_t index = msg.find("\n");
            while (index != std::string::npos) {
                msg = msg.replace(index, 1, "\033[0m\n\033[33m");
                index += 10;
                index = msg.find("\n", index);
            }
        }
    };

    class PrintLoggingClass : public Logger {
    public:
        void Out(std::string msg) override {
            std::string buffer;
            Setup(buffer);
            ReplaceNewlines(msg);
            std::cout << buffer << msg << "\033[0m";
        }
    
    private:
        void Setup(std::string& buffer) {
            buffer = "\033[0;37m";
        }

        void ReplaceNewlines(std::string& msg) {
            size_t index = msg.find("\n");
            while (index != std::string::npos) {
                msg = msg.replace(index, 1, "\033[0m\n\033[37m");
                index += 10;
                index = msg.find("\n", index);
            }
        }
    };

    Logger* FatalLogger = new FatalLoggingClass;
    Logger* ErrorLogger = new ErrorLoggingClass;
    Logger* WarningLogger = new WarningLoggingClass;
    Logger* PrintLogger = new PrintLoggingClass;
    Formatter* FormatFormatter = new Formatter;

}