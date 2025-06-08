#include <cpp_inquirer/cpp_inquirer.hpp>
#include <iostream>

using namespace cpp_inquirer;

auto main(int argc, char *argv[]) -> int
{
	inquirer q;
	q.add(question::builder()
			  .name("project_name")
			  .label("What is the name of your project")
			  .type(question_type::text)
			  .build())
		.add(question::builder()
				.name("license")
				.label("Choose a license")
				.type(question_type::select)
				.options({ { "MIT", "MIT" }, { "GPL", "GPL" } })
				.build())
		.add(question::builder()
				.name("confirm_gpl")
				.label("Are u sure to use gpl ?")
				.type(question_type::boolean)
				.when(callback::is_none_of("license", { "GPL", "UNLICENSE" }))
				.build());

	const auto answers = q.prompt();
	for (auto &answer : answers)
	{
		std::cout << answer.first << " -> " << answer.second << "\n";
	}

	return 0;
}
