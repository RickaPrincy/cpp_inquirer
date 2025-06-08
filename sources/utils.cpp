#include "utils.hpp"

#include <cpp_inquirer/color.hpp>
#include <iostream>
#include <stdexcept>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace cpp_inquirer
{
	auto get_key() -> key
	{
#ifdef _WIN32
		int ch = _getch();
		if (ch == 224)
		{
			switch (_getch())
			{
				case 72: return key::up;
				case 80: return key::down;
				default: return key::unknown;
			}
		}
		else if (ch == 13)
		{
			return key::enter;
		}
		return key::unknown;
#else
		struct termios oldt, newt;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

		char ch1 = getchar();
		key result = key::unknown;

		if (ch1 == '\033')
		{
			char ch2 = getchar();
			char ch3 = getchar();
			if (ch2 == '[')
			{
				if (ch3 == 'A')
					result = key::up;
				else if (ch3 == 'B')
					result = key::down;
			}
		}
		else if (ch1 == '\n')
		{
			result = key::enter;
		}

		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		return result;
#endif
	}

	auto print_label(const std::string &label) -> void
	{
		std::cout << cpp_inquirer::color::b_white << label << ": " << cpp_inquirer::color::reset;
	}

	auto getline() -> std::string
	{
		std::string input;

		if (!std::getline(std::cin, input))
		{
			throw std::runtime_error("Failed to read input.");
		}

		return input;
	}

	auto handle_input_error(question *question, const std::string &input) -> std::string
	{
		auto validator = question->match(input);

		if (validator == nullptr)
		{
			return input;
		}

		std::cout << color::red << validator->get_message() << "\n" << color::reset;
		return question->prompt();
	}
}  // namespace cpp_inquirer
