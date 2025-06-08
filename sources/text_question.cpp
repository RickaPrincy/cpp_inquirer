#include <cpp_inquirer/cpp_inquirer.hpp>

#include "utils.hpp"

namespace cpp_inquirer
{
	text_question::text_question(std::string name, std::string label, when_callback when)
		: question(std::move(name), std::move(label), question_type::text, std::move(when))
	{
	}

	auto text_question::prompt() -> std::string
	{
		cpp_inquirer::print_label(this->m_label);
		return getline();
	}

	auto text_question::prompt(std::string label) -> std::string
	{
		return text_question("QUESTION", std::move(label)).prompt();
	}

}  // namespace cpp_inquirer
