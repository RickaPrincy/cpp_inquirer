#include <cpp_inquirer/cpp_inquirer.hpp>
#include <regex>

namespace cpp_inquirer
{
	auto question::match(const std::string& input) const -> std::shared_ptr<validator>
	{
		for (const auto& validator : this->m_validators)
		{
			if (!std::regex_match(input, std::regex(validator->get_pattern())))
			{
				if (validator->skip_next_validators_if_match())
				{
					continue;
				}

				return validator;
			}

			if (validator->skip_next_validators_if_match())
			{
				return nullptr;
			}
		}

		return nullptr;
	}

	auto question::builder() -> question_builder
	{
		return question_builder{};
	}

	auto question::get_name() const -> const std::string&
	{
		return this->m_name;
	}

	auto question::get_label() const -> const std::string&
	{
		return this->m_label;
	}

	auto question::get_type() const -> question_type
	{
		return this->m_type;
	}

	auto question::get_options() const -> const std::vector<pair_of_string>&
	{
		return this->m_options;
	}

	auto question::is_visible(const answers& answers) const -> bool
	{
		if (this->m_when)
		{
			return this->m_when(answers);
		}
		return true;
	}
}  // namespace cpp_inquirer
