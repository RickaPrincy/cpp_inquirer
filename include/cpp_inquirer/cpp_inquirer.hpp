#pragma once

#include <cstdint>
#include <functional>
#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace cpp_inquirer
{
	using answers = std::map<std::string /* name */, std::string /* value */>;
	using pair_options =
		std::initializer_list<std::pair<std::string /* name */, std::string /* label */>>;
	using map_options = std::map<std::string /* name */, std::string /* label */>;
	using when_callback = std::function<bool(const answers &)>;

	enum class question_type : std::uint8_t
	{
		text,
		select,
		boolean
	};

	class question_builder;

	class question
	{
	protected:
		std::string m_name{}, m_label{};
		map_options m_options{};
		when_callback m_when{};
		question_type m_type{ question_type::text };

	public:
		question() = default;
		question(std::string name, std::string label, question_type type, when_callback when = {});
		question(std::string name,
			std::string label,
			question_type type,
			map_options options = {},
			when_callback when = {});
		question(std::string name,
			std::string label,
			question_type type,
			pair_options options = {},
			when_callback when = {});

		[[nodiscard]] auto get_name() const -> const std::string &;
		[[nodiscard]] auto get_label() const -> const std::string &;
		[[nodiscard]] auto get_type() const -> question_type;
		[[nodiscard]] auto get_options() const -> const map_options &;
		[[nodiscard]] auto is_visible(const answers &answers) const -> bool;

		virtual auto prompt() -> std::string = 0;
		virtual ~question() = default;

		static auto builder() -> question_builder;
		friend class question_builder;
	};

	class text_question : public question
	{
	public:
		text_question(std::string name, std::string label, when_callback when = {});
		auto prompt() -> std::string override;

		static auto prompt(std::string label) -> std::string;
	};

	class boolean_question : public question
	{
	public:
		boolean_question(std::string name, std::string label, when_callback when = {});

		auto prompt() -> std::string override;
		static auto prompt(std::string label) -> std::string;
	};

	class select_question : public question
	{
	public:
		select_question(std::string name,
			std::string label,
			map_options options,
			when_callback when = {});
		select_question(std::string name,
			std::string label,
			pair_options options,
			when_callback when = {});

		auto prompt() -> std::string override;
		static auto prompt(std::string label, pair_options options) -> std::string;
		static auto prompt(std::string label, map_options options) -> std::string;
	};

	class question_factory
	{
	private:
		question_factory() = default;

	public:
		static auto make_question(std::string name,
			std::string label,
			question_type type,
			map_options options,
			when_callback when) -> std::shared_ptr<question>;
	};

	class question_builder
	{
	private:
		std::shared_ptr<question> m_question;

	public:
		question_builder();

		auto name(std::string name) -> question_builder &;
		auto label(std::string label) -> question_builder &;
		auto options(pair_options options) -> question_builder &;
		auto options(map_options options) -> question_builder &;
		auto type(question_type type) -> question_builder &;
		auto when(std::function<bool(const answers &)> condition) -> question_builder &;
		auto build() -> std::shared_ptr<question>;
	};

	class inquirer
	{
	private:
		std::vector<std::shared_ptr<question>> m_questions;

	public:
		inquirer() = default;
		inquirer(std::initializer_list<std::shared_ptr<question>> questions);
		inquirer(std::vector<std::shared_ptr<question>> questions);

		auto add(std::shared_ptr<question> q) -> inquirer &;
		auto prompt() -> std::map<std::string, std::string>;
	};

	namespace evaluate
	{
		auto as_boolean(const std::string &value) -> bool;
	}  // namespace evaluate

	namespace callback
	{
		auto is_true(std::string name) -> when_callback;
		auto is_false(std::string name) -> when_callback;

		auto is_empty(std::string name) -> when_callback;
		auto is_not_empty(std::string name) -> when_callback;

		auto is_equal(std::string name, std::string value) -> when_callback;
		auto is_not_equal(std::string name, std::string value) -> when_callback;

		auto is_one_of(std::string name, std::vector<std::string> values) -> when_callback;
		auto is_one_of(std::string name, std::initializer_list<std::string> values)
			-> when_callback;

		auto is_none_of(std::string name, std::vector<std::string> values) -> when_callback;
		auto is_none_of(std::string name, std::initializer_list<std::string> values)
			-> when_callback;
	}  // namespace callback
}  // namespace cpp_inquirer
