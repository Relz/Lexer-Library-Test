#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(minus_assignment_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"-=", { TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition())) });
}

TEST(minus_assignment_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" -= ", { TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";-=;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
}

TEST(minus_assignment_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"-=;",
		{ TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		L";-=",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 2))) });
}

TEST(minus_assignment_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1-=1",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 2))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L"1-=1.1",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 2))),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L"1.1-=1",
		{ TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L"1.1-=1.1",
		{ TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 4))),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L"1_E-1-=1",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E-1", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"1-=1_E-1",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::MINUS_ASSIGNMENT, StreamString(L"-=", StreamPosition(1, 2))),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E-1", StreamPosition(1, 4))) });
}

TEST(minus_assignment_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("-=")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("-=")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" -= ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" -= ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1-=1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1-=1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";-=;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";-=;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("-=-=-=")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("-=-=-=")", StreamPosition())) });
}

TEST(minus_assignment_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(L"//-=", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//-=", StreamPosition())) });
	ExpectTokenInformations(
		L"// -= ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// -= ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1-=1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1-=1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;-=;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;-=;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*-=*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*-=*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* -= */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* -= */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1-=1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1-=1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;-=;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;-=;*/", StreamPosition())) });
	ExpectTokenInformations(L"/*-=", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*-=", StreamPosition())) });
	ExpectTokenInformations(
		L"/* -= ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* -= ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1-=1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1-=1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;-=;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;-=;", StreamPosition())) });
}
