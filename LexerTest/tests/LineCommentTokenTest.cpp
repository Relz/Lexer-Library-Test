#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(line_comment_token, determining_if_stay_alone)
{
	ExpectTokenInformations("//", { TokenInformation(Token::LINE_COMMENT, StreamString("//", StreamPosition())) });
}

TEST(line_comment_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" // ", { TokenInformation(Token::LINE_COMMENT, StreamString("// ", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";//;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//;", StreamPosition(1, 2))) });
}

TEST(line_comment_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"//;",
		{ TokenInformation(Token::LINE_COMMENT, StreamString("//;", StreamPosition())) });
	ExpectTokenInformations(
		";//",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//", StreamPosition(1, 2))) });
}

TEST(line_comment_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1//1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"1//1.1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"1.1//1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1.1//1.1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//1.1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1_E+1//1",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"1//1_E+1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::LINE_COMMENT, StreamString("//1_E+1", StreamPosition(1, 2))) });
}

TEST(line_comment_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("//")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("//")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" // ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" // ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1//1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1//1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";//;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";//;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("////")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("////")", StreamPosition())) });
}

TEST(line_comment_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"////", { TokenInformation(Token::LINE_COMMENT, StreamString("////", StreamPosition())) });
	ExpectTokenInformations(
		"// // ", { TokenInformation(Token::LINE_COMMENT, StreamString("// // ", StreamPosition())) });
	ExpectTokenInformations(
		"//1//1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1//1", StreamPosition())) });
	ExpectTokenInformations(
		"//;//;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;//;", StreamPosition())) });
	ExpectTokenInformations(
		"/*//*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*//*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* // */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* // */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1//1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1//1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;//;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;//;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*//", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*//", StreamPosition())) });
	ExpectTokenInformations(
		"/* // ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* // ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1//1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1//1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;//;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;//;", StreamPosition())) });
}

TEST(line_comment_token, ends_with_end_of_line)
{
	ExpectTokenInformations(
		"// comment\nidentifier // long comment",
		{ TokenInformation(Token::LINE_COMMENT, StreamString("// comment", StreamPosition())),
		TokenInformation(Token::IDENTIFIER, StreamString("identifier", StreamPosition(2, 1))),
		TokenInformation(Token::LINE_COMMENT, StreamString("// long comment", StreamPosition(2, 12))) });
}
