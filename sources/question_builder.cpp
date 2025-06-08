#include <cpp_inquirer/cpp_inquirer.hpp>
#include <stdexcept>

#include "utils.hpp"

namespace cpp_inquirer
{
	question_builder::question_builder() : m_question(std::make_shared<text_question>("", ""))
	{
	}

	auto question_builder::name(std::string name) -> question_builder&
	{
		this->m_question->m_name = std::move(name);
		return *this;
	}

	auto question_builder::label(std::string label) -> question_builder&
	{
		this->m_question->m_label = std::move(label);
		return *this;
	}

	auto question_builder::options(pair_options options) -> question_builder&
	{
		this->m_question->m_options = convert_pair_options_to_map_options(options);
		return *this;
	}

	auto question_builder::options(map_options options) -> question_builder&
	{
		this->m_question->m_options = std::move(options);
		return *this;
	}

	auto question_builder::type(question_type type) -> question_builder&
	{
		this->m_question->m_type = type;
		return *this;
	}

	auto question_builder::when(when_callback condition) -> question_builder&
	{
		this->m_question->m_when = std::move(condition);
		return *this;
	}

	auto question_builder::build() -> std::shared_ptr<question>
	{
		if (this->m_question->m_name.empty())
		{
			throw std::runtime_error("question must have a name");
		}
		if (this->m_question->m_label.empty())
		{
			throw std::runtime_error("question must have a label");
		}
		if (this->m_question->m_type == question_type::select &&
			this->m_question->m_options.empty())
		{
			throw std::runtime_error("select question must have at least one option");
		}

		return question_factory::make_question(this->m_question->m_name,
			this->m_question->m_label,
			this->m_question->m_type,
			this->m_question->m_options,
			this->m_question->m_when);
	}

}  // namespace cpp_inquirer
