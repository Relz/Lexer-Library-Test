#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(boolean_literal_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		"True", { TokenInformation(Token::BOOLEAN_LITERAL, StreamString("True", StreamPosition())) });
	ExpectTokenInformations(
		"False", { TokenInformation(Token::BOOLEAN_LITERAL, StreamString("False", StreamPosition())) });
	ExpectTokenInformations(
		"True False",
		{ TokenInformation(Token::BOOLEAN_LITERAL, StreamString("True", StreamPosition())),
		  TokenInformation(Token::BOOLEAN_LITERAL, StreamString("False", StreamPosition(1, 6))) });
}

TEST(boolean_literal_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" True ", { TokenInformation(Token::BOOLEAN_LITERAL, StreamString("True", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";True;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::BOOLEAN_LITERAL, StreamString("True", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
}

TEST(boolean_literal_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"True;",
		{ TokenInformation(Token::BOOLEAN_LITERAL, StreamString("True", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";True",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::BOOLEAN_LITERAL, StreamString("True", StreamPosition(1, 2))) });
}

TEST(boolean_literal_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		R"(1True1)",
		{ TokenInformation(Token::UNKNOWN, StreamString("1True1", StreamPosition())) });
	ExpectTokenInformations(
		R"(1True1.1)",
		{ TokenInformation(Token::UNKNOWN, StreamString("1True1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		R"(1.1True1)",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1True1", StreamPosition())) });
	ExpectTokenInformations(
		R"(1.1True1.1)",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1True1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		R"(1_E+1True1)",
		{ TokenInformation(Token::UNKNOWN, StreamString("1_E+1True1", StreamPosition())) });
	ExpectTokenInformations(
		R"(1True1_E+1)",
		{ TokenInformation(Token::UNKNOWN, StreamString("1True1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
}


TEST(boolean_literal_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//True", { TokenInformation(Token::LINE_COMMENT, StreamString("//True", StreamPosition())) });
	ExpectTokenInformations(
		"// True ", { TokenInformation(Token::LINE_COMMENT, StreamString("// True ", StreamPosition())) });
	ExpectTokenInformations(
		"//1True1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1True1", StreamPosition())) });
	ExpectTokenInformations(
		"//;True;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;True;", StreamPosition())) });
	ExpectTokenInformations(
		"/*True*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*True*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* True */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* True */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1True1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1True1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;True;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;True;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*True", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*True", StreamPosition())) });
	ExpectTokenInformations(
		"/* True ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* True ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1True1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1True1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;True;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;True;", StreamPosition())) });
}
