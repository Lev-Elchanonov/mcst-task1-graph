#pragma once
#include <string>
#include <utility>

class Output_msg{
    private:
        bool result_;
        std::string msg_;
    public:
        Output_msg(const bool res, std::string msg) : result_(res), msg_(std::move(msg)) {}
        [[nodiscard]] const std::string& get_msg() const noexcept { return msg_; }
        [[nodiscard]] const bool& get_result() const noexcept { return result_; }
};
