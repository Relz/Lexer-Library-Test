#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(read_token, determining_if_stay_alone)
{
	ExpectTokenInformations("Read", { TokenInformation(Token::READ, StreamString("Read", StreamPosition())) });
}

TEST(read_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" Read ", { TokenInformation(Token::READ, StreamString("Read", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";Read;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::READ, StreamString("Read", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
}

TEST(read_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"Read;",
		{ TokenInformation(Token::READ, StreamString("Read", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";Read",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::READ, StreamString("Read", StreamPosition(1, 2))) });
}

TEST(read_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1Read1", { TokenInformation(Token::UNKNOWN, StreamString("1Read1", StreamPosition())) });
	ExpectTokenInformations(
		"1Read1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Read1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations("1.1Read1", { TokenInformation(Token::UNKNOWN, StreamString("1.1Read1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1Read1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1Read1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"1_E+1Read1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1Read1", StreamPosition())) });
	ExpectTokenInformations(
		"1Read1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Read1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
}

TEST(read_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("Read")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("Read")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" Read ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" Read ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1Read1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1Read1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";Read;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";Read;")", StreamPosition())) });
}

TEST(read_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"#Read", { TokenInformation(Token::LINE_COMMENT, StreamString("#Read", StreamPosition())) });
	ExpectTokenInformations(
		"# Read ", { TokenInformation(Token::LINE_COMMENT, StreamString("# Read ", StreamPosition())) });
	ExpectTokenInformations(
		"#1Read1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1Read1", StreamPosition())) });
	ExpectTokenInformations(
		"#;Read;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;Read;", StreamPosition())) });
	ExpectTokenInformations(
		"/*Read*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Read*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* Read */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Read */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Read1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Read1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Read;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Read;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*Read", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Read", StreamPosition())) });
	ExpectTokenInformations(
		"/* Read ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Read ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Read1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Read1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Read;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Read;", StreamPosition())) });
}
