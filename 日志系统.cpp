/********************/日志系统/************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
};

class Logger {
public:
        Logger(const std::string& filename) : filename_(filename) {}

        void log(LogLevel level, const std::string& message) {
                std::string logLevelStr;
                switch (level) {
                case LogLevel::DEBUG:
                        logLevelStr = "DEBUG";
                        break;
                case LogLevel::INFO:
                        logLevelStr = "INFO";
                        break;
                case LogLevel::WARNING:
                        logLevelStr = "WARNING";
                        break;
                case LogLevel::ERROR:
                        logLevelStr = "ERROR";
                        break;
                }

                std::time_t now = std::time(nullptr);
                std::string timeStr = std::ctime(&now);
                timeStr.pop_back(); // remove trailing newline

                std::string formattedMessage = "[" + timeStr + "][" + logLevelStr + "] " + message;

                writeToConsole(formattedMessage);
                writeToFile(formattedMessage);
        }

private:
        std::string filename_;

        void writeToConsole(const std::string& message) {
                std::cout << message << std::endl;
        }

        void writeToFile(const std::string& message) {
                std::ofstream outFile(filename_, std::ios_base::app);
                if (outFile.is_open()) {
                        outFile << message << std::endl;
                        outFile.close();
                }
                else {
                        std::cerr << "Error: Unable to open file " << filename_ << " for writing." << std::endl;
                }
        }
};

int main() {
        Logger logger("log.txt");

        logger.log(LogLevel::DEBUG, "This is a debug message.");
        logger.log(LogLevel::INFO, "This is an info message.");
        logger.log(LogLevel::WARNING, "This is a warning message.");
        logger.log(LogLevel::ERROR, "This is an error message.");

        return 0;
}


在这个示例中，Logger 类用于日志记录，构造函数接受一个文件名作为参数，用于指定日志输出文件。
log() 方法用于记录日志，接受日志级别和消息作为参数，并根据日志级别格式化日志消息。然后将日志消息输出到控制台和文件中。
这个示例只是一个简单的日志系统，可以根据需要进行扩展，比如添加更多的日志级别、支持日志文件滚动、支持日志格式自定义等。

