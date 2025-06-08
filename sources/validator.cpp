#include <cpp_inquirer/cpp_inquirer.hpp>
#include <regex>
#include <string>

namespace cpp_inquirer
{
	validator::validator(std::string pattern,
		std::string message,
		bool skip_next_validators_if_match)
		: m_pattern(std::move(pattern)),
		  m_message(std::move(message)),
		  m_skip_next_validators_if_match(skip_next_validators_if_match)
	{
	}

	auto validator::match(const std::string &input) -> bool
	{
		return std::regex_match(input, std::regex(input));
	}

	auto validator::get_message() -> std::string
	{
		return this->m_message;
	}

	auto validator::get_pattern() -> std::string
	{
		return this->m_pattern;
	}

	auto validator::skip_next_validators_if_match() -> bool
	{
		return this->m_skip_next_validators_if_match;
	}
}  // namespace cpp_inquirer
