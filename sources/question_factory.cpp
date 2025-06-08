#include <cpp_inquirer/cpp_inquirer.hpp>
#include <memory>
#include <stdexcept>

namespace cpp_inquirer
{
	auto question_factory::make(std::string name,
		std::string label,
		question_type type,
		std::vector<pair_of_string> options,
		std::vector<std::shared_ptr<validator>> validators,
		when_callback when) -> std::shared_ptr<question>
	{
		if (question_type::text == type)
		{
			return std::make_shared<text_question>(name, label, validators, when);
		}

		if (question_type::boolean == type)
		{
			return std::make_shared<boolean_question>(name, label, when);
		}

		if (question_type::select == type)
		{
			return std::make_shared<select_question>(name, label, options, when);
		}

		throw std::runtime_error("Not supported type");
	}
}  // namespace cpp_inquirer
