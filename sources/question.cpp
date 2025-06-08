#include <cpp_inquirer/cpp_inquirer.hpp>

#include "utils.hpp"

namespace cpp_inquirer
{
	auto question::builder() -> question_builder
	{
		return question_builder{};
	}

	question::question(std::string name, std::string label, question_type type, when_callback when)
		: m_name(std::move(name)),
		  m_label(std::move(label)),
		  m_type(type),
		  m_when(std::move(when))
	{
	}

	question::question(std::string name,
		std::string label,
		question_type type,
		map_options options,
		when_callback when)
		: m_name(std::move(name)),
		  m_label(std::move(label)),
		  m_options(std::move(options)),
		  m_type(type),
		  m_when(std::move(when))
	{
	}

	question::question(std::string name,
		std::string label,
		question_type type,
		pair_options options,
		when_callback when)
		: m_name(std::move(name)),
		  m_label(std::move(label)),
		  m_type(type),
		  m_when(std::move(when))
	{
		this->m_options = convert_pair_options_to_map_options(options);
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

	auto question::get_options() const -> const map_options&
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
