#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(return_token, determining_if_stay_alone)
{
	ExpectTokenInformations("return", { TokenInformation(Token::RETURN, StreamString("return", StreamPosition())) });
}

TEST(return_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" return ", { TokenInformation(Token::RETURN, StreamString("return", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";return;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::RETURN, StreamString("return", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
}

TEST(return_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"return;",
		{ TokenInformation(Token::RETURN, StreamString("return", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";return",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::RETURN, StreamString("return", StreamPosition(1, 2))) });
}

TEST(return_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1return1", { TokenInformation(Token::UNKNOWN, StreamString("1return1", StreamPosition())) });
	ExpectTokenInformations(
		"1return1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1return1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"1.1return1", { TokenInformation(Token::UNKNOWN, StreamString("1.1return1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1return1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1return1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		"1_E+1return1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1return1", StreamPosition())) });
	ExpectTokenInformations(
		"1return1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1return1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 12))) });
}

TEST(return_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("return")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("return")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" return ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" return ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1return1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1return1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";return;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";return;")", StreamPosition())) });
}

TEST(return_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//return", { TokenInformation(Token::LINE_COMMENT, StreamString("//return", StreamPosition())) });
	ExpectTokenInformations(
		"// return ", { TokenInformation(Token::LINE_COMMENT, StreamString("// return ", StreamPosition())) });
	ExpectTokenInformations(
		"//1return1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1return1", StreamPosition())) });
	ExpectTokenInformations(
		"//;return;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;return;", StreamPosition())) });
	ExpectTokenInformations(
		"/*return*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*return*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* return */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* return */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1return1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1return1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;return;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;return;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*return", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*return", StreamPosition())) });
	ExpectTokenInformations(
		"/* return ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* return ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1return1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1return1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;return;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;return;", StreamPosition())) });
}
