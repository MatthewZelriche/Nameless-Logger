#ifndef NLSLOG_LOG_H
#define NLSLOG_LOG_H

#include <memory>
#include <map>

#include <spdlog/spdlog.h>

namespace NLSLOG {

// The log levels our wrapper currently supports. 
enum LogLevel {
    TRACE       = spdlog::level::trace,
    INFO        = spdlog::level::info,
    WARN        = spdlog::level::warn,
    ERROR       = spdlog::level::err,     
};

// Our log multiton. This is not thread-safe.
class Log {
public:
    static std::unique_ptr<Log> &GetInstance(const std::string &wrapperName);
    static std::unique_ptr<Log> CreateUniquePtr();
    static void SetLogLevel(const std::string &wrapperName, const LogLevel &logLevel);

    inline std::shared_ptr<spdlog::logger> GetSPDLogger() { return m_spdLogger; }
private:
    // Prevent unintended creation of copies of the Log class. 
    Log();
    Log(Log const&);
    Log& operator=(Log const&);

    static std::unordered_map<std::string, std::unique_ptr<Log>> s_wrapperInstances;

    const char *m_instanceName {""};
    std::shared_ptr<spdlog::logger> m_spdLogger {nullptr};
    LogLevel m_logLevel {LogLevel::TRACE};
};

// Variadic Templates for each log level. 

template<typename... VariadicArgs>
void Trace(const char *name, VariadicArgs... logMessage) {
    #ifndef NDEBUG
        NLSLOG::Log::GetInstance(name)->GetSPDLogger()->trace(logMessage...);
    #endif 
}

template<typename... VariadicArgs>
void Info(const char *name, VariadicArgs... logMessage) {
    #ifndef NDEBUG
        NLSLOG::Log::GetInstance(name)->GetSPDLogger()->info(logMessage...);
    #endif 
}

template<typename... VariadicArgs>
void Warn(const char *name, VariadicArgs... logMessage) {
    #ifndef NDEBUG
        NLSLOG::Log::GetInstance(name)->GetSPDLogger()->warn(logMessage...);
    #endif 
}

template<typename... VariadicArgs>
void Error(const char *name, VariadicArgs... logMessage) {
    #ifndef NDEBUG
        NLSLOG::Log::GetInstance(name)->GetSPDLogger()->error(logMessage...);
    #endif 
}

}

#endif /* NLSLOG_LOG_H */