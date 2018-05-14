#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(do_token, determining_if_stay_alone)
{
	ExpectTokenInformations("do", { TokenInformation(Token::DO, StreamString("do", StreamPosition())) });
}

TEST(do_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" do ", { TokenInformation(Token::DO, StreamString("do", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";do;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::DO, StreamString("do", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
}

TEST(do_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"do;",
		{ TokenInformation(Token::DO, StreamString("do", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		";do",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::DO, StreamString("do", StreamPosition(1, 2))) });
}

TEST(do_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1do1", { TokenInformation(Token::UNKNOWN, StreamString("1do1", StreamPosition())) });
	ExpectTokenInformations(
		"1do1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1do1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations("1.1do1", { TokenInformation(Token::UNKNOWN, StreamString("1.1do1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1do1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1do1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"1_E+1do1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1do1", StreamPosition())) });
	ExpectTokenInformations(
		"1do1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1do1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
}

TEST(do_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("do")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("do")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" do ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" do ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1do1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1do1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";do;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";do;")", StreamPosition())) });
}

TEST(do_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("//do", { TokenInformation(Token::LINE_COMMENT, StreamString("//do", StreamPosition())) });
	ExpectTokenInformations(
		"// do ", { TokenInformation(Token::LINE_COMMENT, StreamString("// do ", StreamPosition())) });
	ExpectTokenInformations(
		"//1do1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1do1", StreamPosition())) });
	ExpectTokenInformations(
		"//;do;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;do;", StreamPosition())) });
	ExpectTokenInformations(
		"/*do*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*do*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* do */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* do */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1do1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1do1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;do;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;do;*/", StreamPosition())) });
	ExpectTokenInformations("/*do", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*do", StreamPosition())) });
	ExpectTokenInformations(
		"/* do ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* do ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1do1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1do1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;do;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;do;", StreamPosition())) });
}
