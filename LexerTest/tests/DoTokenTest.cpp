#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(do_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"do", { TokenInformation(Token::DO, StreamString(L"do", StreamPosition())) });
}

TEST(do_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" do ", { TokenInformation(Token::DO, StreamString(L"do", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";do;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::DO, StreamString(L"do", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
}

TEST(do_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"do;",
		{ TokenInformation(Token::DO, StreamString(L"do", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		L";do",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::DO, StreamString(L"do", StreamPosition(1, 2))) });
}

TEST(do_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1do1", { TokenInformation(Token::UNKNOWN, StreamString(L"1do1", StreamPosition())) });
	ExpectTokenInformations(
		L"1do1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1do1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(L"1.1do1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1do1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1do1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1do1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"1_E+1do1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1do1", StreamPosition())) });
	ExpectTokenInformations(
		L"1do1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1do1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
}

TEST(do_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("do")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("do")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" do ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" do ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1do1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1do1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";do;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";do;")", StreamPosition())) });
}

TEST(do_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(L"//do", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//do", StreamPosition())) });
	ExpectTokenInformations(
		L"// do ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// do ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1do1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1do1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;do;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;do;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*do*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*do*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* do */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* do */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1do1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1do1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;do;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;do;*/", StreamPosition())) });
	ExpectTokenInformations(L"/*do", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*do", StreamPosition())) });
	ExpectTokenInformations(
		L"/* do ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* do ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1do1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1do1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;do;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;do;", StreamPosition())) });
}
