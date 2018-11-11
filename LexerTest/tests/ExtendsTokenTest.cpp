#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(extends_token, determining_if_stay_alone)
{
	ExpectTokenInformations("extends", { TokenInformation(Token::EXTENDS, StreamString("extends", StreamPosition())) });
}

TEST(extends_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" extends ", { TokenInformation(Token::EXTENDS, StreamString("extends", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";extends;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXTENDS, StreamString("extends", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });
}

TEST(extends_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"extends;",
		{ TokenInformation(Token::EXTENDS, StreamString("extends", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		";extends",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXTENDS, StreamString("extends", StreamPosition(1, 2))) });
}

TEST(extends_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1extends1", { TokenInformation(Token::UNKNOWN, StreamString("1extends1", StreamPosition())) });
	ExpectTokenInformations(
		"1extends1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1extends1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1.1extends1", { TokenInformation(Token::UNKNOWN, StreamString("1.1extends1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1extends1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1extends1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		"1_E+1extends1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1extends1", StreamPosition())) });
	ExpectTokenInformations(
		"1extends1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1extends1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 13))) });
}

TEST(extends_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("extends")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("extends")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" extends ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" extends ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1extends1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("1extends1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";extends;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";extends;")", StreamPosition())) });
}

TEST(extends_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"#extends", { TokenInformation(Token::LINE_COMMENT, StreamString("#extends", StreamPosition())) });
	ExpectTokenInformations(
		"# extends ", { TokenInformation(Token::LINE_COMMENT, StreamString("# extends ", StreamPosition())) });
	ExpectTokenInformations(
		"#1extends1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1extends1", StreamPosition())) });
	ExpectTokenInformations(
		"#;extends;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;extends;", StreamPosition())) });
	ExpectTokenInformations(
		"/*extends*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*extends*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* extends */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* extends */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1extends1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1extends1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;extends;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;extends;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*extends", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*extends", StreamPosition())) });
	ExpectTokenInformations(
		"/* extends ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* extends ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1extends1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1extends1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;extends;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;extends;", StreamPosition())) });
}
