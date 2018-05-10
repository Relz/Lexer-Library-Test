#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(get_token, determining_if_stay_alone)
{
	ExpectTokenInformations("get", { TokenInformation(Token::GET, StreamString("get", StreamPosition())) });
}

TEST(get_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" get ", { TokenInformation(Token::GET, StreamString("get", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";get;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::GET, StreamString("get", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
}

TEST(get_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"get;",
		{ TokenInformation(Token::GET, StreamString("get", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		";get",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::GET, StreamString("get", StreamPosition(1, 2))) });
}

TEST(get_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1get1", { TokenInformation(Token::UNKNOWN, StreamString("1get1", StreamPosition())) });
	ExpectTokenInformations(
		"1get1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1get1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations("1.1get1", { TokenInformation(Token::UNKNOWN, StreamString("1.1get1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1get1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1get1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"1_E+1get1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1get1", StreamPosition())) });
	ExpectTokenInformations(
		"1get1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1get1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
}

TEST(get_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("get")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("get")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" get ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" get ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1get1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1get1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";get;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";get;")", StreamPosition())) });
}

TEST(get_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//get", { TokenInformation(Token::LINE_COMMENT, StreamString("//get", StreamPosition())) });
	ExpectTokenInformations(
		"// get ", { TokenInformation(Token::LINE_COMMENT, StreamString("// get ", StreamPosition())) });
	ExpectTokenInformations(
		"//1get1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1get1", StreamPosition())) });
	ExpectTokenInformations(
		"//;get;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;get;", StreamPosition())) });
	ExpectTokenInformations(
		"/*get*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*get*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* get */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* get */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1get1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1get1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;get;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;get;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*get", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*get", StreamPosition())) });
	ExpectTokenInformations(
		"/* get ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* get ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1get1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1get1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;get;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;get;", StreamPosition())) });
}
