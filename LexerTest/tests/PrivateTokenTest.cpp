#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(private_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"private", { TokenInformation(Token::PRIVATE, StreamString(L"private", StreamPosition())) });
}

TEST(private_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" private ", { TokenInformation(Token::PRIVATE, StreamString(L"private", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";private;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::PRIVATE, StreamString(L"private", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });
}

TEST(private_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"private;",
		{ TokenInformation(Token::PRIVATE, StreamString(L"private", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L";private",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::PRIVATE, StreamString(L"private", StreamPosition(1, 2))) });
}

TEST(private_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1private1", { TokenInformation(Token::UNKNOWN, StreamString(L"1private1", StreamPosition())) });
	ExpectTokenInformations(
		L"1private1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1private1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L"1.1private1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1private1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1private1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1private1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		L"1_E+1private1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1private1", StreamPosition())) });
	ExpectTokenInformations(
		L"1private1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1private1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 13))) });
}

TEST(private_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("private")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("private")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" private ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" private ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1private1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1private1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";private;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";private;")", StreamPosition())) });
}

TEST(private_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//private", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//private", StreamPosition())) });
	ExpectTokenInformations(
		L"// private ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// private ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1private1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1private1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;private;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;private;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*private*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*private*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* private */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* private */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1private1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1private1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;private;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;private;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*private", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*private", StreamPosition())) });
	ExpectTokenInformations(
		L"/* private ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* private ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1private1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1private1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;private;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;private;", StreamPosition())) });
}
