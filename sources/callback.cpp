#include <algorithm>
#include <cpp_inquirer/cpp_inquirer.hpp>

namespace cpp_inquirer::callback
{
	inline auto get_value(const answers& ans, const std::string& name) -> const std::string*
	{
		auto it = ans.find(name);
		return it == ans.end() ? nullptr : &it->second;
	}

	auto is_true(std::string name) -> when_callback
	{
		return [name = std::move(name)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return cpp_inquirer::evaluate::as_boolean(*val);
			}
			return false;
		};
	}

	auto is_false(std::string name) -> when_callback
	{
		return [name = std::move(name)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return !cpp_inquirer::evaluate::as_boolean(*val);
			}
			return true;
		};
	}

	auto is_not_empty(std::string name) -> when_callback
	{
		return [name = std::move(name)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return !val->empty();
			}
			return false;
		};
	}

	auto is_empty(std::string name) -> when_callback
	{
		return [name = std::move(name)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return val->empty();
			}
			return true;
		};
	}

	auto is_equal(std::string name, std::string value) -> when_callback
	{
		return [name = std::move(name), value = std::move(value)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return *val == value;
			}
			return false;
		};
	}

	auto is_not_equal(std::string name, std::string value) -> when_callback
	{
		return [name = std::move(name), value = std::move(value)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return *val != value;
			}
			return true;
		};
	}

	auto is_one_of(std::string name, std::vector<std::string> values) -> when_callback
	{
		return [name = std::move(name), values = std::move(values)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return std::find(values.begin(), values.end(), *val) != values.end();
			}
			return false;
		};
	}

	auto is_none_of(std::string name, std::vector<std::string> values) -> when_callback
	{
		return [name = std::move(name), values = std::move(values)](const answers& ans)
		{
			if (auto val = get_value(ans, name))
			{
				return std::find(values.begin(), values.end(), *val) == values.end();
			}
			return true;
		};
	}
}  // namespace cpp_inquirer::callback
