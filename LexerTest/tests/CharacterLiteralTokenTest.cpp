#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(character_literal_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		"'a'", { TokenInformation(Token::CHARACTER_LITERAL, StreamString("'a'", StreamPosition())) });
	ExpectTokenInformations(
		"'_'", { TokenInformation(Token::CHARACTER_LITERAL, StreamString("'_'", StreamPosition())) });
	ExpectTokenInformations(
		"'b''c'",
		{ TokenInformation(Token::CHARACTER_LITERAL, StreamString("'b'", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'c'", StreamPosition(1, 4))) });
}

TEST(character_literal_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" '1' ", { TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";'1';",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
}

TEST(character_literal_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"'1';",
		{ TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		";'1'",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 2))) });
}

TEST(character_literal_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		R"(1'1'1)",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		R"(1'1'1.1)",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		R"(1.1'1'1)",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		R"(1.1'1'1.1)",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 4))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		R"(1_E+1'1'1)",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		R"(1'1'1_E+1)",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString("'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition(1, 5))) });
}

TEST(character_literal_token, not_determining_if_has_length_not_equal_to_one)
{
	ExpectTokenInformations("''", { TokenInformation(Token::UNKNOWN, StreamString("''", StreamPosition())) });
	ExpectTokenInformations("'11'", { TokenInformation(Token::UNKNOWN, StreamString("'11'", StreamPosition())) });
}

TEST(character_literal_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//'1'", { TokenInformation(Token::LINE_COMMENT, StreamString("//'1'", StreamPosition())) });
	ExpectTokenInformations(
		"// '1' ", { TokenInformation(Token::LINE_COMMENT, StreamString("// '1' ", StreamPosition())) });
	ExpectTokenInformations(
		"//1'1'1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1'1'1", StreamPosition())) });
	ExpectTokenInformations(
		"//;'1';", { TokenInformation(Token::LINE_COMMENT, StreamString("//;'1';", StreamPosition())) });
	ExpectTokenInformations(
		"/*'1'*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*'1'*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* '1' */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* '1' */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1'1'1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1'1'1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;'1';*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;'1';*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*'1'", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*'1'", StreamPosition())) });
	ExpectTokenInformations(
		"/* '1' ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* '1' ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1'1'1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1'1'1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;'1';", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;'1';", StreamPosition())) });
}
