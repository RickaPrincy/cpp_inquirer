#include <cpp_inquirer/cpp_inquirer.hpp>
#include <stdexcept>

namespace cpp_inquirer::evaluate
{
	auto as_boolean(const std::string &value) -> bool
	{
		if (value == "true")
		{
			return true;
		}
		if (value == "false")
		{
			return false;
		}

		throw std::runtime_error("Expected a boolean, but received: " + value);
	}
}  // namespace cpp_inquirer::evaluate
