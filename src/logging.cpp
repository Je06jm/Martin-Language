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
            Warning("String has $ unused arguments: $\n", size - index + 2, format);
            return false;
        }

        buffer.clear();

        return true;
    }

    std::string FormatTime() {
        const char days[7][4] = {
            "Sun",
            "Mon",
            "Tue",
            "Wed",
            "Thu",
            "Fri",
            "Sat"
        };

        const char months[12][4] = {
            "Jan",
            "Feb",
            "Mar",
            "Apr",
            "May",
            "Jun",
            "Jul",
            "Aug",
            "Sep",
            "Oct",
            "Nov",
            "Dec"
        };

        time_t result = time(nullptr);
        tm* local_time = localtime(&result);

        // Format example: [Wed Jan 1, 2022 - 1:30 pm]
        std::string str_time = "[";
        str_time += std::string(days[local_time->tm_wday]) + " ";
        str_time += std::string(months[local_time->tm_mon]) + " ";
        str_time += std::to_string(local_time->tm_mday) + " ";
        str_time += std::to_string(local_time->tm_year + 1900) + ", ";
        str_time += std::to_string(local_time->tm_hour % 12) + ":";
        str_time += std::to_string(local_time->tm_min) + " ";
        str_time += std::string(local_time->tm_hour / 12 ? "pm" : "am");
        str_time += "]";

        return str_time;
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
            buffer = "\033[0m\033[1;41m[Fatal]\033[4;41m" + FormatTime() + "\033[0;41m - ";
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
            buffer = "\033[0m\033[1;31m[Error]\033[4;31m" + FormatTime() + "\033[0;31m - ";
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
            buffer = "\033[0m\033[1;33m[Warning]\033[4;33m" + FormatTime() + "\033[0;33m - ";
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
            buffer = "\033[0m\033[1;37m[Print]\033[4;37m" + FormatTime() + "\033[0;37m - ";
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