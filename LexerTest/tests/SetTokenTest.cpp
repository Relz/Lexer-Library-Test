#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(set_token, determining_if_stay_alone)
{
	ExpectTokenInformations("set", { TokenInformation(Token::SET, StreamString("set", StreamPosition())) });
}

TEST(set_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" set ", { TokenInformation(Token::SET, StreamString("set", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";set;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::SET, StreamString("set", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
}

TEST(set_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"set;",
		{ TokenInformation(Token::SET, StreamString("set", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		";set",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::SET, StreamString("set", StreamPosition(1, 2))) });
}

TEST(set_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1set1", { TokenInformation(Token::UNKNOWN, StreamString("1set1", StreamPosition())) });
	ExpectTokenInformations(
		"1set1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1set1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations("1.1set1", { TokenInformation(Token::UNKNOWN, StreamString("1.1set1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1set1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1set1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"1_E+1set1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1set1", StreamPosition())) });
	ExpectTokenInformations(
		"1set1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1set1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
}

TEST(set_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("set")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("set")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" set ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" set ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1set1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1set1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";set;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";set;")", StreamPosition())) });
}

TEST(set_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"#set", { TokenInformation(Token::LINE_COMMENT, StreamString("#set", StreamPosition())) });
	ExpectTokenInformations(
		"# set ", { TokenInformation(Token::LINE_COMMENT, StreamString("# set ", StreamPosition())) });
	ExpectTokenInformations(
		"#1set1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1set1", StreamPosition())) });
	ExpectTokenInformations(
		"#;set;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;set;", StreamPosition())) });
	ExpectTokenInformations(
		"/*set*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*set*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* set */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* set */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1set1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1set1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;set;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;set;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*set", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*set", StreamPosition())) });
	ExpectTokenInformations(
		"/* set ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* set ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1set1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1set1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;set;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;set;", StreamPosition())) });
}
