#pragma once

#include <cpp_inquirer/cpp_inquirer.hpp>
#include <cstdint>

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
	auto convert_pair_options_to_map_options(const pair_options& options) -> map_options;
}  // namespace cpp_inquirer
