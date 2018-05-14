#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(private_token, determining_if_stay_alone)
{
	ExpectTokenInformations("private", { TokenInformation(Token::PRIVATE, StreamString("private", StreamPosition())) });
}

TEST(private_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" private ", { TokenInformation(Token::PRIVATE, StreamString("private", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";private;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::PRIVATE, StreamString("private", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });
}

TEST(private_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"private;",
		{ TokenInformation(Token::PRIVATE, StreamString("private", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		";private",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::PRIVATE, StreamString("private", StreamPosition(1, 2))) });
}

TEST(private_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1private1", { TokenInformation(Token::UNKNOWN, StreamString("1private1", StreamPosition())) });
	ExpectTokenInformations(
		"1private1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1private1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1.1private1", { TokenInformation(Token::UNKNOWN, StreamString("1.1private1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1private1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1private1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		"1_E+1private1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1private1", StreamPosition())) });
	ExpectTokenInformations(
		"1private1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1private1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 13))) });
}

TEST(private_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("private")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("private")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" private ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" private ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1private1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("1private1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";private;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";private;")", StreamPosition())) });
}

TEST(private_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//private", { TokenInformation(Token::LINE_COMMENT, StreamString("//private", StreamPosition())) });
	ExpectTokenInformations(
		"// private ", { TokenInformation(Token::LINE_COMMENT, StreamString("// private ", StreamPosition())) });
	ExpectTokenInformations(
		"//1private1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1private1", StreamPosition())) });
	ExpectTokenInformations(
		"//;private;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;private;", StreamPosition())) });
	ExpectTokenInformations(
		"/*private*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*private*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* private */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* private */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1private1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1private1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;private;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;private;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*private", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*private", StreamPosition())) });
	ExpectTokenInformations(
		"/* private ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* private ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1private1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1private1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;private;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;private;", StreamPosition())) });
}
