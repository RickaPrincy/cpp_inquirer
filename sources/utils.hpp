#pragma once

#include <cpp_inquirer/cpp_inquirer.hpp>
#include <cstdint>
#include <string>

namespace cpp_inquirer
{
	enum class key : std::uint8_t
	{
		up,
		down,
		enter,
		unknown
	};

	auto get_key() -> key;
	auto getline() -> std::string;
	auto print_label(const std::string& label) -> void;
	auto handle_input_error(question* question, const std::string& input) -> std::string;
}  // namespace cpp_inquirer
