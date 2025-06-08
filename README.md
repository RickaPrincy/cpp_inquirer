Project generated with [Templi](https://github.com/RickaPrincy/Templi)

#  :memo: cpp_inquirer

A lightweight, extensible C++ library that interactively collects user input through a friendly prompt system inspired by [Inquirer.js](https://github.com/SBoudrias/Inquirer.js).

![demo](./images/home.png)

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Getting Started](#getting-started)
- [Standalone input](#standalone-input)
- [Validators](#validators)
- [License](#license)

## Features

- Simple and expressive syntax for defining interactive prompts
- Supports different question types: `text`, `boolean`, `select`
- Built-in validation system (`required`, `|email`, `max_length`, etc.)
- Conditional logic using `when` callbacks
- Easy integration with any C++ project

## Installation

- Archlinux

```bash
yay -Sy cpp_inquirer 
```
For the moment, you have to build templi to use it if you use another system (not archlinux)

- Dependancies
    - CMake (Version 3.18 or later)
    - C++ Compiler with C++17 support

- Build manually

```bash
git clone -b v0.0.1 https://github.com/RickaPrincy/cpp-inquirer 

cd cpp_inquirer 

mkdir build

cd build

cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

sudo make install
```
#### :warning: If some libs are not found after building manually

Identify the installation path of the missing library. For example, let's assume the library is installed in `/usr/local/lib` (on linux it should be there).

If you are using Linux, add the following code to your `~/.zshrc` or `~/.bashrc` based on what you use (replacing `/usr/local/lib` with the actual installation path):

```bash
export LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH
```

## Getting Started
```c++
cpp_inquirer::inquirer q
```

### `text_question`

`text_question` allows you to retrieve any input from the user. 

See more in the [Validators](#validators) section how to validate the user input.


![text_question](./images/text_question.png)

```c++
#include <cpp_inquirer/cpp_inquirer.hpp>

using namespace cpp_inquirer;

auto main(int argc, char *argv[]) -> int
{
	auto question1 = text_question("project_name", "What is your projet_name");
	auto answer = question1.prompt();

	// Using builder
	auto question2 = question::builder()
						 .name("email")
						 .label("What is your email")
						 .type(question_type::text)
						 .build();
	auto answer2 = question2->prompt();

	// Prompt directly
	auto answer3 = text_question::prompt("What is your project_name");

	return 0;
}
```

### `boolean_question`
`boolean_question` allows you to ask yes/no (true/false) style questions. When the user enter a non valid input (y/n), this will prompt the user again.

You can use the builder, or prompt directly like with text_question.

![boolean_question](./images/boolean_question.png)*

```c++
#include <cpp_inquirer/cpp_inquirer.hpp>

using namespace cpp_inquirer;

auto main(int argc, char *argv[]) -> int
{
	auto question1 = boolean_question("confirm", "Are u sure");
	auto answer = question1.prompt();

	// Using builder
	auto question2 = question::builder()
						 .name("confirm")
						 .label("Are u sure")
						 .type(question_type::boolean)
						 .build();
	auto answer2 = question2->prompt();

	// Prompt directly
	auto answer3 = boolean_question::prompt("Are u sure");

	return 0;
}
```

### `select_question`
`select_question` allows you to present a list of choices to the user. 

Each choice is defined using a `pair_of_string`, which is simply an alias for `std::pair<std::string, std::string>`. The first element of the pair is the internal value (name), and the second is the display label shown to the user.

The output of a select_question is the `name` of the selected choice.

![select_question](./images/select_question.png)

```c++
#include <cpp_inquirer/cpp_inquirer.hpp>
#include <iostream>

using namespace cpp_inquirer;

auto main(int argc, char *argv[]) -> int
{
	auto question1 = select_question("number", "Pick ` number", {{"1", "One"}, {"2", "Two"}});
	auto answer1 = question1.prompt();

	// Using the builder
	auto question2 = question::builder()
						.name("license")
						.label("Choose a license")
						.type(question_type::select)
						.options({ { "mit", "MIT" }, { "gpl", "GPL" }, { "apache", "Apache 2.0" } })
						.build();
	auto answer2 = question2->prompt();

	// Prompt directly
	auto answer3 = select_question::prompt(
		"Pick a number", 
		{ { "1", "One" }, { "2", "Two" }, { "3", "Three" } });
	return 0;
}
```

### `inquirer class`
`inquirer` class allows you to group multiple questions and prompt them all at once. 

You can also make some inputs conditional based on the values of previous answers.

![inquirer_class_1](./images/inquirer_class_1.png)
![inquirer_class_2](./images/inquirer_class_2.png)

```c++
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

	auto inquirer_answers = q.prompt(); // std::map<std::string, std::string>
	for (const auto &[name, answer] : inquirer_answers)
	{
		std::cout << name << " -> " << answer << "\n";
	}

	return 0;
}
```

See more predefined `when_callback`s or how to create custom ones in the [When Callback](#when-callback) section.