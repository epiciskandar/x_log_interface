#pragma once
#include <vector>

namespace x::log {
    /**
     * @brief Logging interface
     * @details implement must be thread-safe
     */
    class Logging {
    public:
        virtual ~Logging() = default;

        enum class LogLevel {
            Detail = -1,
            Debug = 0,
            Info,
            Warning,
            Error,
            Fatal
        };

        virtual void log(LogLevel level, std::string tags, std::string msg) = 0;

        void logDetail(std::string tags, std::string msg){ log(LogLevel::Detail, std::move(tags), std::move(msg)); }

        void logDebug(std::string tags, std::string msg) { log(LogLevel::Debug, std::move(tags), std::move(msg)); }

        void logInfo(std::string tags, std::string msg) { log(LogLevel::Info, std::move(tags), std::move(msg)); }

        void logWarning(std::string tags, std::string msg) { log(LogLevel::Warning, std::move(tags), std::move(msg)); }

        void logError(std::string tags, std::string msg) { log(LogLevel::Error, std::move(tags), std::move(msg)); }

        // logFatal not panic
        void logFatal(std::string tags, std::string msg) { log(LogLevel::Fatal, std::move(tags), std::move(msg)); }
    };

    class TaggedLogger: public Logging{
    public:
        explicit TaggedLogger(Logging& logging): logging_(logging) {}
        void pushTag(std::string_view tag) {
            if (!tagString_.empty()) {
                tagString_ += '|';
            }
            tagString_ += tag;
            tagSizes_.push_back(tag.size());
        }
        void popTag() {
            if (!tagSizes_.empty()) {
                tagString_.erase(tagString_.size() - tagSizes_.back() - 1);
                tagSizes_.pop_back();
            }
        }
        void log(LogLevel level, std::string tags, std::string msg) override {
            std::string combinedTags = tagString_;
            if (!tags.empty()) {
                combinedTags += '|';
                combinedTags += tags;
            }
            logging_.log(level, std::move(combinedTags), std::move(msg));
        }
    private:
        Logging& logging_;
        std::string tagString_;
        std::vector<size_t> tagSizes_;
    };
}

