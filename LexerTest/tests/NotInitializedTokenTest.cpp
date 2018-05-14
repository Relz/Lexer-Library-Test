#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(not_initialized_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		"NULL", { TokenInformation(Token::NOT_INITIALIZED, StreamString("NULL", StreamPosition())) });
}

TEST(not_initialized_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" NULL ", { TokenInformation(Token::NOT_INITIALIZED, StreamString("NULL", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";NULL;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::NOT_INITIALIZED, StreamString("NULL", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
}

TEST(not_initialized_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"NULL;",
		{ TokenInformation(Token::NOT_INITIALIZED, StreamString("NULL", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";NULL",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::NOT_INITIALIZED, StreamString("NULL", StreamPosition(1, 2))) });
}

TEST(not_initialized_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1NULL1", { TokenInformation(Token::UNKNOWN, StreamString("1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		"1NULL1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1NULL1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"1.1NULL1", { TokenInformation(Token::UNKNOWN, StreamString("1.1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1NULL1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1NULL1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"1_E+1NULL1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		"1NULL1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1NULL1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
}

TEST(not_initialized_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("NULL")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("NULL")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" NULL ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" NULL ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1NULL1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1NULL1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";NULL;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";NULL;")", StreamPosition())) });
}

TEST(not_initialized_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//NULL", { TokenInformation(Token::LINE_COMMENT, StreamString("//NULL", StreamPosition())) });
	ExpectTokenInformations(
		"// NULL ", { TokenInformation(Token::LINE_COMMENT, StreamString("// NULL ", StreamPosition())) });
	ExpectTokenInformations(
		"//1NULL1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		"//;NULL;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;NULL;", StreamPosition())) });
	ExpectTokenInformations(
		"/*NULL*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*NULL*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* NULL */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* NULL */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1NULL1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1NULL1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;NULL;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;NULL;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*NULL", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*NULL", StreamPosition())) });
	ExpectTokenInformations(
		"/* NULL ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* NULL ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1NULL1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;NULL;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;NULL;", StreamPosition())) });
}
