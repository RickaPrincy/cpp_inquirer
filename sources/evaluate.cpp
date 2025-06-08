#include <cerrno>
#include <cpp_inquirer/cpp_inquirer.hpp>
#include <cstdlib>
#include <stdexcept>
#include <string>

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

	auto as_int(const std::string &value) -> int
	{
		char *end = nullptr;
		errno = 0;
		long result = std::strtol(value.c_str(), &end, 10);

		if (errno != 0 || end != value.c_str() + value.size())
		{
			throw std::runtime_error("Expected an integer, but received: " + value);
		}

		return static_cast<int>(result);
	}

	auto as_float(const std::string &value) -> float
	{
		char *end = nullptr;
		errno = 0;
		float result = std::strtof(value.c_str(), &end);

		if (errno != 0 || end != value.c_str() + value.size())
		{
			throw std::runtime_error("Expected a float, but received: " + value);
		}

		return result;
	}
}  // namespace cpp_inquirer::evaluate
