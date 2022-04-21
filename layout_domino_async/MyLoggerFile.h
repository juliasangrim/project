#ifndef LAYOUT_DOMINO_MYLOGGERFILE_H
#define LAYOUT_DOMINO_MYLOGGERFILE_H


#include <iostream>
#include <chrono>
#include <fstream>

namespace LoggingLib {

    class Logger {
    public:
        Logger() : start(std::chrono::system_clock::now()) {}
        virtual ~Logger() = default;

        std::string time() {
            const auto end = std::chrono::system_clock::now();
            auto duration = end - start;
            const auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
            duration -= hours;
            const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
            duration -= minutes;
            const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
            duration -= seconds;
            const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
            duration -= milliseconds;
            const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
            duration -= microseconds;
            const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
            const std::string time_message = std::to_string(hours.count()) + "h:"
                                             + std::to_string(minutes.count()) + "m:"
                                             + std::to_string(seconds.count()) + "s:"
                                             + std::to_string(milliseconds.count()) + "ms:"
                                             + std::to_string(microseconds.count()) + "µs:"
                                             + std::to_string(nanoseconds.count()) + "ns\n";
            return time_message;
        }

    protected:
        template <typename... Args>
        void write(std::ostream& stream, Args&&... args) {
            (stream << ... << args) << '\n' << '\n';
        }

        void write_prefix(std::ostream& stream) {
            stream << "[ LOG ] Time since started:: " << time() << "\t";
        }

        void write_error_prefix(std::ostream& stream) {
            stream << "[ERROR] Time since started:: " << time() << "An error occurred::\n\t";
        }

    private:
        const std::chrono::time_point<std::chrono::system_clock> start;
    }; // class Logger


    class FileLogger : public Logger {
    public:
        explicit FileLogger(const std::string& filename) {
            try {
                filestream.open(filename, std::fstream::out);
                if (!filestream.is_open()) {
                    std::cerr <<"open() failed for file " << filename << std::endl;
                    return;
                }
            }
            catch (std::exception& exception) {
                std::cerr << "open() failed for file " << filename << exception.what() << std::endl;
            }
        }

        ~FileLogger() override {
            filestream.close();
        }

        template <typename... Rest>
        void log(const Rest&... rest) {
            write_prefix(filestream);
            write(filestream, rest...);
        }

        template <typename... Rest>
        void log_error(const Rest&... rest) {
            write_error_prefix(filestream);
            write(filestream, rest...);
        }

        template<typename T>
        friend FileLogger& operator<<(FileLogger& logger, const T& Arg) {
            logger.filestream << Arg;
            return logger;
        }

    private:
        std::ofstream filestream;
    }; // class FileLogger




}
#endif //LAYOUT_DOMINO_MYLOGGERFILE_H
