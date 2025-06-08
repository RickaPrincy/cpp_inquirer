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
				.options({ { "mit", "MIT" }, { "gpl", "GPL" }, {"unlicense", "UNLICENSE"} })
				.build())
		.add(question::builder()
				.name("confirm_gpl")
				.label("Are u sure to use gpl")
				.type(question_type::boolean)
				.when(callback::is_one_of("license", { "gpl", "unlicense" }))
				.build());

	auto inquirer_answers = q.prompt();
	for (const auto &[name, answer] : inquirer_answers)
	{
		std::cout << name << " -> " << answer << "\n";
	}

	return 0;
}
