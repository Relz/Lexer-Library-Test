#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(assignment_token, determining_if_stay_alone)
{
	ExpectTokenInformations("=", { TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition())) });
}

TEST(assignment_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" = ", { TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";=;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
}

TEST(assignment_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"=;",
		{ TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";=",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 2))) });
}

TEST(assignment_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1=1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 2))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		"1=1.1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 2))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		"1.1=1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		"1.1=1.1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 4))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		"1_E+1=1",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		"1=1_E+1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 2))),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition(1, 3))) });
}

TEST(assignment_token, not_determining_if_part_of_plus_assignment)
{
	ExpectTokenInformations("+=", { TokenInformation(Token::PLUS_ASSIGNMENT, StreamString("+=", StreamPosition())) });
	ExpectTokenInformations(
		"=+=",
		{ TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition())),
		  TokenInformation(Token::PLUS_ASSIGNMENT, StreamString("+=", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"+==",
		{ TokenInformation(Token::PLUS_ASSIGNMENT, StreamString("+=", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 3))) });
}

TEST(assignment_token, not_determining_if_part_of_equivalence)
{
	ExpectTokenInformations("==", { TokenInformation(Token::EQUIVALENCE, StreamString("==", StreamPosition())) });
	ExpectTokenInformations(
		"===",
		{ TokenInformation(Token::EQUIVALENCE, StreamString("==", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 3))) });
}

TEST(assignment_token, not_determining_if_part_of_minus_assignment)
{
	ExpectTokenInformations("-=", { TokenInformation(Token::MINUS_ASSIGNMENT, StreamString("-=", StreamPosition())) });
	ExpectTokenInformations(
		"=-=",
		{ TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString("-=", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"-==",
		{ TokenInformation(Token::MINUS_ASSIGNMENT, StreamString("-=", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 3))) });
}

TEST(assignment_token, not_determining_if_part_of_multiply_assignment)
{
	ExpectTokenInformations(
		"*=", { TokenInformation(Token::MULTIPLY_ASSIGNMENT, StreamString("*=", StreamPosition())) });
	ExpectTokenInformations(
		"=*=",
		{ TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition())),
		  TokenInformation(Token::MULTIPLY_ASSIGNMENT, StreamString("*=", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"*==",
		{ TokenInformation(Token::MULTIPLY_ASSIGNMENT, StreamString("*=", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 3))) });
}

TEST(assignment_token, not_determining_if_part_of_division_assignment)
{
	ExpectTokenInformations(
		"/=", { TokenInformation(Token::DIVISION_ASSIGNMENT, StreamString("/=", StreamPosition())) });
	ExpectTokenInformations(
		"=/=",
		{ TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition())),
		  TokenInformation(Token::DIVISION_ASSIGNMENT, StreamString("/=", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"/==",
		{ TokenInformation(Token::DIVISION_ASSIGNMENT, StreamString("/=", StreamPosition())),
		  TokenInformation(Token::ASSIGNMENT, StreamString("=", StreamPosition(1, 3))) });
}

TEST(assignment_token, not_determining_if_in_character_literal)
{
	ExpectTokenInformations(
		"'='", { TokenInformation(Token::CHARACTER_LITERAL, StreamString("'='", StreamPosition())) });
}

TEST(assignment_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("=")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("=")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" = ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" = ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1=1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1=1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";=;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";=;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("===")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("===")", StreamPosition())) });
}

TEST(assignment_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("//=", { TokenInformation(Token::LINE_COMMENT, StreamString("//=", StreamPosition())) });
	ExpectTokenInformations(
		"// = ", { TokenInformation(Token::LINE_COMMENT, StreamString("// = ", StreamPosition())) });
	ExpectTokenInformations(
		"//1=1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1=1", StreamPosition())) });
	ExpectTokenInformations(
		"//;=;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;=;", StreamPosition())) });
	ExpectTokenInformations("//=", { TokenInformation(Token::LINE_COMMENT, StreamString("//=", StreamPosition())) });
	ExpectTokenInformations(
		"/*=*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*=*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* = */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* = */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1=1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1=1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;=;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;=;*/", StreamPosition())) });
	ExpectTokenInformations("/*=", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*=", StreamPosition())) });
	ExpectTokenInformations(
		"/* = ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* = ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1=1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1=1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;=;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;=;", StreamPosition())) });
}
