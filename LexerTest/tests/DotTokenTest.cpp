#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(dot_token, determining_if_stay_alone)
{
	ExpectTokenInformations(".", { TokenInformation(Token::DOT, StreamString(".", StreamPosition())) });
}

TEST(dot_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" . ", { TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";.;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
}

TEST(dot_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		".;",
		{ TokenInformation(Token::DOT, StreamString(".", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";.",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 2))) });
}

TEST(dot_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1.1", { TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())) });
	ExpectTokenInformations("1.1.1", { TokenInformation(Token::UNKNOWN, StreamString("1.1.1", StreamPosition())) });
	ExpectTokenInformations(
		"1_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1", StreamPosition())) });
}

TEST(dot_token, not_determining_if_in_character_literal)
{
	ExpectTokenInformations(
		"'.'", { TokenInformation(Token::CHARACTER_LITERAL, StreamString("'.'", StreamPosition())) });
}

TEST(dot_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"(".")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(".")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" . ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" . ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1.1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1.1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";.;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";.;")", StreamPosition())) });
}

TEST(dot_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("//.", { TokenInformation(Token::LINE_COMMENT, StreamString("//.", StreamPosition())) });
	ExpectTokenInformations(
		"// . ", { TokenInformation(Token::LINE_COMMENT, StreamString("// . ", StreamPosition())) });
	ExpectTokenInformations(
		"//1.1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1.1", StreamPosition())) });
	ExpectTokenInformations(
		"//;.;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;.;", StreamPosition())) });
	ExpectTokenInformations(
		"/*.*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*.*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* . */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* . */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;.;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;.;*/", StreamPosition())) });
	ExpectTokenInformations("/*.", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*.", StreamPosition())) });
	ExpectTokenInformations(
		"/* . ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* . ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;.;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;.;", StreamPosition())) });
}
