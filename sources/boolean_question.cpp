#include <cpp_inquirer/cpp_inquirer.hpp>

#include "utils.hpp"

namespace cpp_inquirer
{
	boolean_question::boolean_question(std::string name, std::string label, when_callback when)
		: question(std::move(name), std::move(label), question_type::text, std::move(when))
	{
	}

	auto boolean_question::prompt() -> std::string
	{
		while (true)
		{
			cpp_inquirer::print_label(this->m_label + " (y/n)");
			auto input = getline();
			if (input == "y" || input == "Y")
			{
				return "true";
			}
			else if (input == "n" || input == "N")
			{
				return "false";
			}
		}
	}

	auto boolean_question::prompt(std::string label) -> std::string
	{
		return boolean_question("QUESTION", std::move(label)).prompt();
	}

}  // namespace cpp_inquirer
