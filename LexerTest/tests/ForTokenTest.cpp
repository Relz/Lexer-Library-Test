#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(for_token, determining_if_stay_alone)
{
	ExpectTokenInformations("for", { TokenInformation(Token::FOR, StreamString("for", StreamPosition())) });
}

TEST(for_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" for ", { TokenInformation(Token::FOR, StreamString("for", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";for;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FOR, StreamString("for", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
}

TEST(for_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"for;",
		{ TokenInformation(Token::FOR, StreamString("for", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		";for",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FOR, StreamString("for", StreamPosition(1, 2))) });
}

TEST(for_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1for1", { TokenInformation(Token::UNKNOWN, StreamString("1for1", StreamPosition())) });
	ExpectTokenInformations(
		"1for1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1for1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations("1.1for1", { TokenInformation(Token::UNKNOWN, StreamString("1.1for1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1for1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1for1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"1_E+1for1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1for1", StreamPosition())) });
	ExpectTokenInformations(
		"1for1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1for1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
}

TEST(for_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("for")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("for")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" for ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" for ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1for1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1for1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";for;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";for;")", StreamPosition())) });
}

TEST(for_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"#for", { TokenInformation(Token::LINE_COMMENT, StreamString("#for", StreamPosition())) });
	ExpectTokenInformations(
		"# for ", { TokenInformation(Token::LINE_COMMENT, StreamString("# for ", StreamPosition())) });
	ExpectTokenInformations(
		"#1for1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1for1", StreamPosition())) });
	ExpectTokenInformations(
		"#;for;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;for;", StreamPosition())) });
	ExpectTokenInformations(
		"/*for*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*for*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* for */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* for */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1for1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1for1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;for;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;for;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*for", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*for", StreamPosition())) });
	ExpectTokenInformations(
		"/* for ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* for ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1for1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1for1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;for;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;for;", StreamPosition())) });
}
