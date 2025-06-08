#include <cpp_inquirer/cpp_inquirer.hpp>

#include "utils.hpp"

namespace cpp_inquirer
{
	text_question::text_question(std::string name,
		std::string label,
		std::vector<std::shared_ptr<validator>> validators,
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

	auto text_question::prompt(std::string label,
		std::vector<std::shared_ptr<validator>> validators) -> std::string
	{
		return text_question("QUESTION", std::move(label), std::move(validators)).prompt();
	}
}  // namespace cpp_inquirer
