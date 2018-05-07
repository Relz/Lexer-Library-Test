#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(implements_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		L"implements", { TokenInformation(Token::IMPLEMENTS, StreamString(L"implements", StreamPosition())) });
}

TEST(implements_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" implements ", { TokenInformation(Token::IMPLEMENTS, StreamString(L"implements", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";implements;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::IMPLEMENTS, StreamString(L"implements", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 12))) });
}

TEST(implements_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"implements;",
		{ TokenInformation(Token::IMPLEMENTS, StreamString(L"implements", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L";implements",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::IMPLEMENTS, StreamString(L"implements", StreamPosition(1, 2))) });
}

TEST(implements_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1implements1", { TokenInformation(Token::UNKNOWN, StreamString(L"1implements1", StreamPosition())) });
	ExpectTokenInformations(
		L"1implements1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1implements1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 13))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 14))) });
	ExpectTokenInformations(
		L"1.1implements1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1implements1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1implements1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1implements1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 15))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 16))) });
	ExpectTokenInformations(
		L"1_E+1implements1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1implements1", StreamPosition())) });
	ExpectTokenInformations(
		L"1implements1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1implements1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 15))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 16))) });
}

TEST(implements_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("implements")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("implements")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" implements ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" implements ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1implements1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1implements1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";implements;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";implements;")", StreamPosition())) });
}

TEST(implements_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//implements", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//implements", StreamPosition())) });
	ExpectTokenInformations(
		L"// implements ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// implements ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1implements1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1implements1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;implements;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;implements;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*implements*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*implements*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* implements */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* implements */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1implements1*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1implements1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;implements;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;implements;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*implements", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*implements", StreamPosition())) });
	ExpectTokenInformations(
		L"/* implements ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* implements ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1implements1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1implements1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;implements;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;implements;", StreamPosition())) });
}
