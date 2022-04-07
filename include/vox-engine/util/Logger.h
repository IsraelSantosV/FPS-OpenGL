//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_LOGGER_H
#define VOXENGINE_LOGGER_H

#include <iostream>
#include <sstream>

class Logger {
public:
    enum Type {
        DEFINITION = 0,
        INFO = 34,
        WARNING = 33,
        ERROR = 31,
        CONFIRM = 32
    };

    struct LogLevel {
        std::string name;
    };

    struct LevelCore : public LogLevel {
        std::string name = "Core";
    };

    struct LevelApplication : public LogLevel {
        std::string name = "Application";
    };

    template<typename ... args>
    static void log(args ... to_print) {
        _printStart(DEFINITION, to_print...);
    }

    template<typename ... args>
    static void logln(args ... to_print) {
        _printStart(DEFINITION, to_print...);
        std::cout << "\n";
    }

    template<typename ... args>
    static void info(args ... to_print) {
        _printStart(INFO, to_print...);
    }

    template<typename ... args>
    static void infoln(args ... to_print) {
        _printStart(INFO, to_print...);
        std::cout << "\n";
    }

    template<typename ... args>
    static void confirm(args ... to_print) {
        _printStart(CONFIRM, to_print...);
    }

    template<typename ... args>
    static void confirmln(args ... to_print) {
        _printStart(CONFIRM, to_print...);
        std::cout << "\n";
    }

    template<typename ... args>
    static void warn(args ... to_print) {
        _printStart(WARNING, to_print...);
    }

    template<typename ... args>
    static void warnln(args ... to_print) {
        _printStart(WARNING, to_print...);
        std::cout << "\n";
    }

    template<typename ... args>
    static void error(args ... to_print) {
        _printStart(ERROR, to_print...);
    }

    template<typename ... args>
    static void errorln(args ... to_print) {
        _printStart(ERROR, to_print...);
        std::cerr << "\n";
    }

    static void hr() {
        std::cout << "---------------------------------------------------\n";
    }

    static void br() {
        std::cout << "\n";
    }


private:
    // Start
    template<typename ... args>
    static void _printStart(Type type, args ... to_print) {
        std::string time_str;

#ifdef PB_LOG_TO_FILE
        std::time_t time = std::time(nullptr);
        time_str = std::ctime(&time);
        time_str.pop_back();

        time_str = "[" + time_str + "] ";
#endif

        if (type == ERROR){
            std::cerr << "\x1B[" << std::to_string(type) << "m" << time_str << "ERROR: ";
        }
        else {
            std::cout << "\x1B[" << std::to_string(type) << "m" << time_str;
        }

        _print(type, to_print...);
    }


    // Mid
    template<typename T, typename ... args>
    static void _print(Type type, T current, args... next) {
        if (type == ERROR){
            std::cerr << current << " ";
        }
        else {
            std::cout << current << " ";
        }

        _print(type, next...);
    }


    // End
    template<typename T>
    static void _print(Type type, T last) {
        if (type == ERROR) {
            std::cerr << last << "\033[0m";
        }
        else {
            std::cout << last << "\033[0m";
        }
    }
};


#endif //VOXENGINE_LOGGER_H
