#include "Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

std::unordered_map<std::string, std::unique_ptr<NLSLOG::Log>> NLSLOG::Log::s_wrapperInstances;

// Set up the pattern we use with spdlog. 
NLSLOG::Log::Log() {
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e]%^[%n][%l]: %v%$");
}

// Create and return a new instance of Log for the multiton. 
std::unique_ptr<NLSLOG::Log> NLSLOG::Log::CreateUniquePtr() {  
    std::unique_ptr<NLSLOG::Log> log(new NLSLOG::Log);
    return log;
}

// Set the log level for the requested log instance. If it doesn't exist, create it first. 
void NLSLOG::Log::SetLogLevel(const std::string &wrapperName, const NLSLOG::LogLevel &logLevel) {
    // If the user requested a log that doesn't exist, create it.
    if (s_wrapperInstances.count(wrapperName) == 0) {
        GetInstance(wrapperName);
    }

    s_wrapperInstances[wrapperName]->m_spdLogger->set_level(static_cast<spdlog::level::level_enum>(logLevel));
    s_wrapperInstances[wrapperName]->m_logLevel = logLevel;
}

// Method that handles the creation of Log instances inside the multiton.
std::unique_ptr<NLSLOG::Log> &NLSLOG::Log::GetInstance(const std::string &wrapperName) {
    if (s_wrapperInstances.count(wrapperName) == 0) {
        std::unique_ptr<Log> instance = CreateUniquePtr();

        // Here we are setting up our non-static instance variables that need to be
        // different for each specific logger instance
        instance.get()->m_instanceName = wrapperName.c_str();
        instance.get()->m_spdLogger = spdlog::stdout_color_st(wrapperName);

        // Default log level will be set to TRACE.
        instance.get()->m_spdLogger->set_level(static_cast<spdlog::level::level_enum>(LogLevel::TRACE));
        instance.get()->m_logLevel = LogLevel::TRACE;

        // Add our new logger instance to the static map object that holds all instances.
        s_wrapperInstances.emplace(wrapperName,std::move(instance));
    }

    // Return the currently requested log instance. 
    return s_wrapperInstances[wrapperName];
}