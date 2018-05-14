#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(block_comment_token, determining_if_stay_alone)
{
	ExpectTokenInformations("/*", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*", StreamPosition())) });
	ExpectTokenInformations("/**/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/**/", StreamPosition())) });
}

TEST(block_comment_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" /* ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* ", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";/*;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;", StreamPosition(1, 2))) });
}

TEST(block_comment_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations("/*;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;", StreamPosition())) });
	ExpectTokenInformations(
		";/*",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*", StreamPosition(1, 2))) });
}

TEST(block_comment_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1/*1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"1/*1.1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"1.1/*1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1.1/*1.1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1_E+1/*1",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"1/*1_E+1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1_E+1", StreamPosition(1, 2))) });
}

TEST(block_comment_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("/*")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("/*")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" /* ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" /* ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1/*1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1/*1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";/*;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";/*;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("/**/")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("/**/")", StreamPosition())) });
}

TEST(block_comment_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("///*", { TokenInformation(Token::LINE_COMMENT, StreamString("///*", StreamPosition())) });
	ExpectTokenInformations(
		"// /* ", { TokenInformation(Token::LINE_COMMENT, StreamString("// /* ", StreamPosition())) });
	ExpectTokenInformations(
		"//1/*1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1/*1", StreamPosition())) });
	ExpectTokenInformations(
		"//;/*;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;/*;", StreamPosition())) });
	ExpectTokenInformations(
		"/*/**/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*/**/", StreamPosition())) });
	ExpectTokenInformations(
		"/* /* */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* /* */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1/*1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1/*1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;/*;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;/*;*/", StreamPosition())) });
	ExpectTokenInformations("/*/*", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*/*", StreamPosition())) });
	ExpectTokenInformations(
		"/* /* ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* /* ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1/*1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1/*1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;/*;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;/*;", StreamPosition())) });
}

TEST(block_comment_token, does_not_end_with_end_of_line)
{
	ExpectTokenInformations(
		"/* comment\nidentifier // long comment",
		{ TokenInformation(
			Token::BLOCK_COMMENT, StreamString("/* comment\nidentifier // long comment", StreamPosition())) });
	ExpectTokenInformations(
		"/* comment\nidentifier // long comment*/",
		{ TokenInformation(
			Token::BLOCK_COMMENT, StreamString("/* comment\nidentifier // long comment*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* comment\nidentifier // long comment\n\t*/",
		{ TokenInformation(
			Token::BLOCK_COMMENT, StreamString("/* comment\nidentifier // long comment\n\t*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*comment\nidentifier // long comment*/",
		{ TokenInformation(
			Token::BLOCK_COMMENT, StreamString("/*comment\nidentifier // long comment*/", StreamPosition())) });
}
