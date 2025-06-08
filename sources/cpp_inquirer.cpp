#include <cpp_inquirer/cpp_inquirer.hpp>

namespace cpp_inquirer
{
	inquirer::inquirer(std::initializer_list<std::shared_ptr<question>> questions)
		: m_questions(questions)
	{
	}

	inquirer::inquirer(std::vector<std::shared_ptr<question>> questions)
		: m_questions(std::move(questions))
	{
	}

	auto inquirer::add(std::shared_ptr<question> q) -> inquirer&
	{
		this->m_questions.push_back(std::move(q));
		return *this;
	}

	auto inquirer::prompt() -> answers
	{
		answers answers;
		for (const auto& q : this->m_questions)
		{
			if (q->is_visible(answers))
			{
				auto answer = q->prompt();
				answers[q->get_name()] = std::move(answer);
			}
		}
		return answers;
	}
}  // namespace cpp_inquirer
