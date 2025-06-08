#include <cpp_inquirer/color.hpp>
#include <cpp_inquirer/cpp_inquirer.hpp>
#include <iostream>

#include "utils.hpp"

namespace cpp_inquirer
{
	auto clear_lines(int count) -> void;

	select_question::select_question(std::string name,
		std::string label,
		std::vector<pair_of_string> options,
		when_callback when)
	{
		this->m_name = std::move(name);
		this->m_label = std::move(label);
		this->m_when = std::move(when);
		this->m_options = std::move(options);
	}

	auto select_question::prompt() -> std::string
	{
		std::vector<std::string> keys;
		keys.reserve(this->m_options.size());

		for (const auto& [key, _] : this->m_options)
		{
			keys.push_back(key);
		}

		int current = 0;
		int option_count = static_cast<int>(this->m_options.size());

		while (true)
		{
			print_label(this->m_label);
			std::cout << "\n";

			int i = 0;
			for (const auto& [key, val] : this->m_options)
			{
				if (i == current)
					std::cout << color::b_green << "> " << color::blue << val << color::reset
							  << "\n";
				else
					std::cout << "  " << val << "\n";
				++i;
			}

			key key = get_key();
			clear_lines(option_count + 1);

			switch (key)
			{
				case key::up: current = (current - 1 + option_count) % option_count; break;
				case key::down: current = (current + 1) % option_count; break;
				case key::enter: return keys[current];
				default: break;
			}
		}
	}

	auto select_question::prompt(std::string label, std::vector<pair_of_string> options)
		-> std::string
	{
		return select_question("QUESTION", std::move(label), std::move(options)).prompt();
	}

	auto clear_lines(int count) -> void
	{
		for (int i = 0; i < count; ++i)
		{
			std::cout << "\33[2K\r\033[1A";
		}
	}
}  // namespace cpp_inquirer
