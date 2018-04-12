#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(implements_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		"implements", { TokenInformation(Token::IMPLEMENTS, StreamString("implements", StreamPosition())) });
}

TEST(implements_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" implements ", { TokenInformation(Token::IMPLEMENTS, StreamString("implements", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";implements;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::IMPLEMENTS, StreamString("implements", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 12))) });
}

TEST(implements_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"implements;",
		{ TokenInformation(Token::IMPLEMENTS, StreamString("implements", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		";implements",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::IMPLEMENTS, StreamString("implements", StreamPosition(1, 2))) });
}

TEST(implements_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1implements1", { TokenInformation(Token::UNKNOWN, StreamString("1implements1", StreamPosition())) });
	ExpectTokenInformations(
		"1implements1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1implements1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 13))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 14))) });
	ExpectTokenInformations(
		"1.1implements1", { TokenInformation(Token::UNKNOWN, StreamString("1.1implements1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1implements1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1implements1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 15))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 16))) });
	ExpectTokenInformations(
		"1_E+1implements1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1implements1", StreamPosition())) });
	ExpectTokenInformations(
		"1implements1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1implements1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 15))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 16))) });
}

TEST(implements_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("implements")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("implements")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" implements ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" implements ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1implements1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("1implements1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";implements;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";implements;")", StreamPosition())) });
}

TEST(implements_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//implements", { TokenInformation(Token::LINE_COMMENT, StreamString("//implements", StreamPosition())) });
	ExpectTokenInformations(
		"// implements ", { TokenInformation(Token::LINE_COMMENT, StreamString("// implements ", StreamPosition())) });
	ExpectTokenInformations(
		"//1implements1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1implements1", StreamPosition())) });
	ExpectTokenInformations(
		"//;implements;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;implements;", StreamPosition())) });
	ExpectTokenInformations(
		"/*implements*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*implements*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* implements */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/* implements */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1implements1*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1implements1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;implements;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;implements;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*implements", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*implements", StreamPosition())) });
	ExpectTokenInformations(
		"/* implements ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* implements ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1implements1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1implements1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;implements;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;implements;", StreamPosition())) });
}
