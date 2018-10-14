#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(write_token, determining_if_stay_alone)
{
	ExpectTokenInformations("Write", { TokenInformation(Token::WRITE, StreamString("Write", StreamPosition())) });
}

TEST(write_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" Write ", { TokenInformation(Token::WRITE, StreamString("Write", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";Write;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::WRITE, StreamString("Write", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
}

TEST(write_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"Write;",
		{ TokenInformation(Token::WRITE, StreamString("Write", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		";Write",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::WRITE, StreamString("Write", StreamPosition(1, 2))) });
}

TEST(write_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1Write1", { TokenInformation(Token::UNKNOWN, StreamString("1Write1", StreamPosition())) });
	ExpectTokenInformations(
		"1Write1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Write1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations("1.1Write1", { TokenInformation(Token::UNKNOWN, StreamString("1.1Write1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1Write1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1Write1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1_E+1Write1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1Write1", StreamPosition())) });
	ExpectTokenInformations(
		"1Write1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Write1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
}

TEST(write_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("Write")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("Write")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" Write ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" Write ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1Write1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1Write1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";Write;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";Write;")", StreamPosition())) });
}

TEST(write_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//Write", { TokenInformation(Token::LINE_COMMENT, StreamString("//Write", StreamPosition())) });
	ExpectTokenInformations(
		"// Write ", { TokenInformation(Token::LINE_COMMENT, StreamString("// Write ", StreamPosition())) });
	ExpectTokenInformations(
		"//1Write1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1Write1", StreamPosition())) });
	ExpectTokenInformations(
		"//;Write;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;Write;", StreamPosition())) });
	ExpectTokenInformations(
		"/*Write*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Write*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* Write */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Write */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Write1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Write1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Write;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Write;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*Write", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Write", StreamPosition())) });
	ExpectTokenInformations(
		"/* Write ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Write ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Write1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Write1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Write;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Write;", StreamPosition())) });
}
