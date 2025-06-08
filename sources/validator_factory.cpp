#include <cpp_inquirer/cpp_inquirer.hpp>
#include <string>

namespace cpp_inquirer
{
	auto validator_factory::make(std::string pattern,
		std::string message,
		bool skip_next_validators) -> std::shared_ptr<validator>
	{
		return std::make_shared<validator>(
			std::move(pattern), std::move(message), skip_next_validators);
	}

	auto validator_factory::required(std::string message) -> std::shared_ptr<validator>
	{
		return validator_factory::make(R"(^(?!\s*$).+)", std::move(message));
	}

	auto validator_factory::min_length(int n, std::string message) -> std::shared_ptr<validator>
	{
		if (message.empty())
		{
			message = "Minimum length is " + std::to_string(n);
		}

		return validator_factory::make("^.{" + std::to_string(n) + ",}$", std::move(message));
	}

	auto validator_factory::max_length(int n, std::string message) -> std::shared_ptr<validator>
	{
		if (message.empty())
		{
			message = "Maximum length is " + std::to_string(n);
		}
		return validator_factory::make("^.{0," + std::to_string(n) + "}$", std::move(message));
	}

	auto validator_factory::number(std::string message) -> std::shared_ptr<validator>
	{
		return validator_factory::make(R"(^-?\d+$)", std::move(message));
	}

	auto validator_factory::floating(std::string message) -> std::shared_ptr<validator>
	{
		return validator_factory::make(R"(^-?\d+(\.\d+)?$)", std::move(message));
	}

	auto validator_factory::lowercase(std::string message) -> std::shared_ptr<validator>
	{
		return validator_factory::make(R"(^[a-z]+$)", std::move(message));
	}

	auto validator_factory::uppercase(std::string message) -> std::shared_ptr<validator>
	{
		return validator_factory::make(R"(^[A-Z]+$)", std::move(message));
	}

	auto validator_factory::email(std::string message) -> std::shared_ptr<validator>
	{
		return validator_factory::make(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)", std::move(message));
	}

	auto validator_factory::optional(std::string message) -> std::shared_ptr<validator>
	{
		return validator_factory::make(R"(^\s*$)", std::move(message), true);
	}
}  // namespace cpp_inquirer
