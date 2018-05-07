#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(extends_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"extends", { TokenInformation(Token::EXTENDS, StreamString(L"extends", StreamPosition())) });
}

TEST(extends_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" extends ", { TokenInformation(Token::EXTENDS, StreamString(L"extends", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";extends;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXTENDS, StreamString(L"extends", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });
}

TEST(extends_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"extends;",
		{ TokenInformation(Token::EXTENDS, StreamString(L"extends", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L";extends",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXTENDS, StreamString(L"extends", StreamPosition(1, 2))) });
}

TEST(extends_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1extends1", { TokenInformation(Token::UNKNOWN, StreamString(L"1extends1", StreamPosition())) });
	ExpectTokenInformations(
		L"1extends1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1extends1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L"1.1extends1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1extends1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1extends1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1extends1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		L"1_E+1extends1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1extends1", StreamPosition())) });
	ExpectTokenInformations(
		L"1extends1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1extends1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 13))) });
}

TEST(extends_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("extends")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("extends")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" extends ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" extends ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1extends1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1extends1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";extends;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";extends;")", StreamPosition())) });
}

TEST(extends_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//extends", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//extends", StreamPosition())) });
	ExpectTokenInformations(
		L"// extends ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// extends ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1extends1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1extends1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;extends;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;extends;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*extends*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*extends*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* extends */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* extends */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1extends1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1extends1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;extends;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;extends;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*extends", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*extends", StreamPosition())) });
	ExpectTokenInformations(
		L"/* extends ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* extends ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1extends1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1extends1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;extends;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;extends;", StreamPosition())) });
}
