#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(if_token, determining_if_stay_alone)
{
	ExpectTokenInformations("if", { TokenInformation(Token::IF, StreamString("if", StreamPosition())) });
}

TEST(if_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" if ", { TokenInformation(Token::IF, StreamString("if", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";if;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::IF, StreamString("if", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
}

TEST(if_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"if;",
		{ TokenInformation(Token::IF, StreamString("if", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		";if",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::IF, StreamString("if", StreamPosition(1, 2))) });
}

TEST(if_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1if1", { TokenInformation(Token::UNKNOWN, StreamString("1if1", StreamPosition())) });
	ExpectTokenInformations(
		"1if1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1if1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations("1.1if1", { TokenInformation(Token::UNKNOWN, StreamString("1.1if1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1if1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1if1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"1_E+1if1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1if1", StreamPosition())) });
	ExpectTokenInformations(
		"1if1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1if1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
}

TEST(if_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("if")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("if")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" if ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" if ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1if1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1if1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";if;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";if;")", StreamPosition())) });
}

TEST(if_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("//if", { TokenInformation(Token::LINE_COMMENT, StreamString("//if", StreamPosition())) });
	ExpectTokenInformations(
		"// if ", { TokenInformation(Token::LINE_COMMENT, StreamString("// if ", StreamPosition())) });
	ExpectTokenInformations(
		"//1if1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1if1", StreamPosition())) });
	ExpectTokenInformations(
		"//;if;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;if;", StreamPosition())) });
	ExpectTokenInformations(
		"/*if*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*if*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* if */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* if */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1if1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1if1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;if;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;if;*/", StreamPosition())) });
	ExpectTokenInformations("/*if", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*if", StreamPosition())) });
	ExpectTokenInformations(
		"/* if ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* if ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1if1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1if1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;if;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;if;", StreamPosition())) });
}
