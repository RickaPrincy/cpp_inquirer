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
			  .validators({ { "[a-z]{4}", "must be a lowercase" } })
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

	for (const auto &[name, answer] : q.prompt())
	{
		std::cout << name << " -> " << answer << "\n";
	}

	return 0;
}
