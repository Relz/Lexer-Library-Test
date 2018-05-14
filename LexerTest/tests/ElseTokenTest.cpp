#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(else_token, determining_if_stay_alone)
{
	ExpectTokenInformations("else", { TokenInformation(Token::ELSE, StreamString("else", StreamPosition())) });
}

TEST(else_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" else ", { TokenInformation(Token::ELSE, StreamString("else", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";else;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::ELSE, StreamString("else", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
}

TEST(else_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"else;",
		{ TokenInformation(Token::ELSE, StreamString("else", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";else",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::ELSE, StreamString("else", StreamPosition(1, 2))) });
}

TEST(else_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1else1", { TokenInformation(Token::UNKNOWN, StreamString("1else1", StreamPosition())) });
	ExpectTokenInformations(
		"1else1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1else1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"1.1else1", { TokenInformation(Token::UNKNOWN, StreamString("1.1else1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1else1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1else1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"1_E+1else1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1else1", StreamPosition())) });
	ExpectTokenInformations(
		"1else1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1else1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
}

TEST(else_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("else")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("else")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" else ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" else ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1else1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1else1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";else;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";else;")", StreamPosition())) });
}

TEST(else_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//else", { TokenInformation(Token::LINE_COMMENT, StreamString("//else", StreamPosition())) });
	ExpectTokenInformations(
		"// else ", { TokenInformation(Token::LINE_COMMENT, StreamString("// else ", StreamPosition())) });
	ExpectTokenInformations(
		"//1else1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1else1", StreamPosition())) });
	ExpectTokenInformations(
		"//;else;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;else;", StreamPosition())) });
	ExpectTokenInformations(
		"/*else*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*else*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* else */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* else */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1else1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1else1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;else;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;else;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*else", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*else", StreamPosition())) });
	ExpectTokenInformations(
		"/* else ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* else ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1else1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1else1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;else;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;else;", StreamPosition())) });
}
