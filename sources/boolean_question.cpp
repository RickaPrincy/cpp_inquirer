#include <cpp_inquirer/color.hpp>
#include <cpp_inquirer/cpp_inquirer.hpp>
#include <iostream>

#include "utils.hpp"

namespace cpp_inquirer
{
	boolean_question::boolean_question(std::string name, std::string label, when_callback when)
	{
		this->m_name = std::move(name);
		this->m_label = std::move(label);
		this->m_when = std::move(when);
	}

	auto boolean_question::prompt() -> std::string
	{
		while (true)
		{
			cpp_inquirer::print_label(this->m_label + " (y/n)");
			std::cout << cpp_inquirer::color::blue;
			auto input = getline();
			std::cout << cpp_inquirer::color::reset;

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
