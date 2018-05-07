#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(set_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"set", { TokenInformation(Token::SET, StreamString(L"set", StreamPosition())) });
}

TEST(set_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" set ", { TokenInformation(Token::SET, StreamString(L"set", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";set;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::SET, StreamString(L"set", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
}

TEST(set_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"set;",
		{ TokenInformation(Token::SET, StreamString(L"set", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L";set",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::SET, StreamString(L"set", StreamPosition(1, 2))) });
}

TEST(set_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1set1", { TokenInformation(Token::UNKNOWN, StreamString(L"1set1", StreamPosition())) });
	ExpectTokenInformations(
		L"1set1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1set1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))) });
	ExpectTokenInformations(L"1.1set1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1set1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1set1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1set1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"1_E+1set1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1set1", StreamPosition())) });
	ExpectTokenInformations(
		L"1set1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1set1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
}

TEST(set_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("set")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("set")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" set ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" set ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1set1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1set1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";set;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";set;")", StreamPosition())) });
}

TEST(set_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//set", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//set", StreamPosition())) });
	ExpectTokenInformations(
		L"// set ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// set ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1set1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1set1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;set;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;set;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*set*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*set*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* set */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* set */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1set1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1set1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;set;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;set;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*set", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*set", StreamPosition())) });
	ExpectTokenInformations(
		L"/* set ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* set ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1set1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1set1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;set;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;set;", StreamPosition())) });
}
