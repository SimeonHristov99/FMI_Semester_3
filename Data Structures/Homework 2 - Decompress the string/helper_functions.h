#pragma once
#include "Stack.hpp"

enum class STATUS
{
	NO_INPUT,
	NO_OUTPUT,

	FILE_CORRUPT,

	REPEAT_ZERO_TIMES,
	NO_NUMBER,
	INCORRECT_BRAKETS,
	INCORRECT_QMARKS,
	NO_SYMBOL,

	SUCCESS
};

bool is_digit(const char c);

STATUS to_output(const char* to, Stack<char>& letters);

void generate_file_name(unsigned index, char* buffer);