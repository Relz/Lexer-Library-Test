#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(constructor_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		"Constructor", { TokenInformation(Token::CONSTRUCTOR, StreamString("Constructor", StreamPosition())) });
}

TEST(constructor_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" Constructor ", { TokenInformation(Token::CONSTRUCTOR, StreamString("Constructor", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";Constructor;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::CONSTRUCTOR, StreamString("Constructor", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 13))) });
}

TEST(constructor_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"Constructor;",
		{ TokenInformation(Token::CONSTRUCTOR, StreamString("Constructor", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		";Constructor",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::CONSTRUCTOR, StreamString("Constructor", StreamPosition(1, 2))) });
}

TEST(constructor_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1Constructor1", { TokenInformation(Token::UNKNOWN, StreamString("1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		"1Constructor1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Constructor1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 14))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 15))) });
	ExpectTokenInformations(
		"1.1Constructor1", { TokenInformation(Token::UNKNOWN, StreamString("1.1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1Constructor1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1Constructor1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 16))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 17))) });
	ExpectTokenInformations(
		"1_E+1Constructor1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		"1Constructor1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Constructor1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 16))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 17))) });
}

TEST(constructor_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("Constructor")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("Constructor")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" Constructor ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" Constructor ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1Constructor1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("1Constructor1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";Constructor;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";Constructor;")", StreamPosition())) });
}

TEST(constructor_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//Constructor", { TokenInformation(Token::LINE_COMMENT, StreamString("//Constructor", StreamPosition())) });
	ExpectTokenInformations(
		"// Constructor ",
		{ TokenInformation(Token::LINE_COMMENT, StreamString("// Constructor ", StreamPosition())) });
	ExpectTokenInformations(
		"//1Constructor1",
		{ TokenInformation(Token::LINE_COMMENT, StreamString("//1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		"//;Constructor;",
		{ TokenInformation(Token::LINE_COMMENT, StreamString("//;Constructor;", StreamPosition())) });
	ExpectTokenInformations(
		"/*Constructor*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Constructor*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* Constructor */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Constructor */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Constructor1*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Constructor1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Constructor;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Constructor;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*Constructor", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Constructor", StreamPosition())) });
	ExpectTokenInformations(
		"/* Constructor ",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Constructor ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Constructor1",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Constructor;",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Constructor;", StreamPosition())) });
}
