#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(character_literal_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		L"'a'", { TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'a'", StreamPosition())) });
	ExpectTokenInformations(
		L"'_'", { TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'_'", StreamPosition())) });
	ExpectTokenInformations(
		L"'b''c'",
		{ TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'b'", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'c'", StreamPosition(1, 4))) });
}

TEST(character_literal_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" '1' ", { TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";'1';",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
}

TEST(character_literal_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"'1';",
		{ TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L";'1'",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 2))) });
}

TEST(character_literal_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		LR"(1'1'1)",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		LR"(1'1'1.1)",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		LR"(1.1'1'1)",
		{ TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		LR"(1.1'1'1.1)",
		{ TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 4))),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		LR"(1_E+1'1'1)",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		LR"(1'1'1_E+1)",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::CHARACTER_LITERAL, StreamString(L"'1'", StreamPosition(1, 2))),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition(1, 5))) });
}

TEST(character_literal_token, not_determining_if_has_length_not_equal_to_one)
{
	ExpectTokenInformations(L"''", { TokenInformation(Token::UNKNOWN, StreamString(L"''", StreamPosition())) });
	ExpectTokenInformations(L"'11'", { TokenInformation(Token::UNKNOWN, StreamString(L"'11'", StreamPosition())) });
}

TEST(character_literal_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//'1'", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//'1'", StreamPosition())) });
	ExpectTokenInformations(
		L"// '1' ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// '1' ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1'1'1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1'1'1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;'1';", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;'1';", StreamPosition())) });
	ExpectTokenInformations(
		L"/*'1'*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*'1'*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* '1' */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* '1' */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1'1'1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1'1'1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;'1';*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;'1';*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*'1'", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*'1'", StreamPosition())) });
	ExpectTokenInformations(
		L"/* '1' ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* '1' ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1'1'1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1'1'1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;'1';", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;'1';", StreamPosition())) });
}
