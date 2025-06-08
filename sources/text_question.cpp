#include <cpp_inquirer/cpp_inquirer.hpp>

#include "utils.hpp"

namespace cpp_inquirer
{
	text_question::text_question(std::string name,
		std::string label,
		std::vector<pair_of_string> validators,
		when_callback when)
	{
		this->m_name = std::move(name);
		this->m_label = std::move(label);
		this->m_when = std::move(when);
		this->m_validators = std::move(validators);
	}

	auto text_question::prompt() -> std::string
	{
		cpp_inquirer::print_label(this->m_label);
		const auto input = getline();
		return handle_input_error(this, input);
	}

	auto text_question::prompt(std::string label, std::vector<pair_of_string> validators)
		-> std::string
	{
		return text_question("QUESTION", std::move(label), std::move(validators)).prompt();
	}

	auto text_question::prompt(std::string label, std::initializer_list<pair_of_string> validators)
		-> std::string
	{
		return text_question::prompt(std::move(label), std::vector<pair_of_string>(validators));
	}
}  // namespace cpp_inquirer
