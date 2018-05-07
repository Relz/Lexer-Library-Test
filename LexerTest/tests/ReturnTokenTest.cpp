#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(return_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"return", { TokenInformation(Token::RETURN, StreamString(L"return", StreamPosition())) });
}

TEST(return_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" return ", { TokenInformation(Token::RETURN, StreamString(L"return", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";return;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::RETURN, StreamString(L"return", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
}

TEST(return_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"return;",
		{ TokenInformation(Token::RETURN, StreamString(L"return", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";return",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::RETURN, StreamString(L"return", StreamPosition(1, 2))) });
}

TEST(return_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1return1", { TokenInformation(Token::UNKNOWN, StreamString(L"1return1", StreamPosition())) });
	ExpectTokenInformations(
		L"1return1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1return1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L"1.1return1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1return1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1return1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1return1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		L"1_E+1return1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1return1", StreamPosition())) });
	ExpectTokenInformations(
		L"1return1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1return1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 12))) });
}

TEST(return_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("return")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("return")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" return ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" return ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1return1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1return1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";return;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";return;")", StreamPosition())) });
}

TEST(return_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//return", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//return", StreamPosition())) });
	ExpectTokenInformations(
		L"// return ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// return ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1return1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1return1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;return;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;return;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*return*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*return*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* return */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* return */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1return1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1return1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;return;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;return;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*return", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*return", StreamPosition())) });
	ExpectTokenInformations(
		L"/* return ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* return ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1return1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1return1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;return;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;return;", StreamPosition())) });
}
