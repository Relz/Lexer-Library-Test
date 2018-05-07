#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(else_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"else", { TokenInformation(Token::ELSE, StreamString(L"else", StreamPosition())) });
}

TEST(else_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" else ", { TokenInformation(Token::ELSE, StreamString(L"else", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";else;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::ELSE, StreamString(L"else", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
}

TEST(else_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"else;",
		{ TokenInformation(Token::ELSE, StreamString(L"else", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		L";else",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::ELSE, StreamString(L"else", StreamPosition(1, 2))) });
}

TEST(else_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1else1", { TokenInformation(Token::UNKNOWN, StreamString(L"1else1", StreamPosition())) });
	ExpectTokenInformations(
		L"1else1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1else1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"1.1else1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1else1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1else1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1else1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L"1_E+1else1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1else1", StreamPosition())) });
	ExpectTokenInformations(
		L"1else1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1else1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
}

TEST(else_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("else")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("else")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" else ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" else ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1else1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1else1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";else;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";else;")", StreamPosition())) });
}

TEST(else_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//else", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//else", StreamPosition())) });
	ExpectTokenInformations(
		L"// else ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// else ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1else1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1else1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;else;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;else;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*else*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*else*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* else */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* else */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1else1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1else1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;else;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;else;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*else", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*else", StreamPosition())) });
	ExpectTokenInformations(
		L"/* else ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* else ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1else1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1else1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;else;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;else;", StreamPosition())) });
}
