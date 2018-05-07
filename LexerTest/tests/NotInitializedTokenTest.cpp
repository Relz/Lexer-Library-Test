#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(not_initialized_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		L"NULL", { TokenInformation(Token::NOT_INITIALIZED, StreamString(L"NULL", StreamPosition())) });
}

TEST(not_initialized_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" NULL ", { TokenInformation(Token::NOT_INITIALIZED, StreamString(L"NULL", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";NULL;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::NOT_INITIALIZED, StreamString(L"NULL", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
}

TEST(not_initialized_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"NULL;",
		{ TokenInformation(Token::NOT_INITIALIZED, StreamString(L"NULL", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		L";NULL",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::NOT_INITIALIZED, StreamString(L"NULL", StreamPosition(1, 2))) });
}

TEST(not_initialized_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1NULL1", { TokenInformation(Token::UNKNOWN, StreamString(L"1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		L"1NULL1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1NULL1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"1.1NULL1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1NULL1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1NULL1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L"1_E+1NULL1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		L"1NULL1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1NULL1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
}

TEST(not_initialized_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("NULL")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("NULL")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" NULL ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" NULL ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1NULL1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1NULL1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";NULL;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";NULL;")", StreamPosition())) });
}

TEST(not_initialized_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//NULL", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//NULL", StreamPosition())) });
	ExpectTokenInformations(
		L"// NULL ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// NULL ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1NULL1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;NULL;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;NULL;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*NULL*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*NULL*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* NULL */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* NULL */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1NULL1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1NULL1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;NULL;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;NULL;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*NULL", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*NULL", StreamPosition())) });
	ExpectTokenInformations(
		L"/* NULL ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* NULL ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1NULL1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1NULL1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;NULL;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;NULL;", StreamPosition())) });
}
