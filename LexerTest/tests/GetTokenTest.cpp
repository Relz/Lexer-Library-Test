#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(get_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"get", { TokenInformation(Token::GET, StreamString(L"get", StreamPosition())) });
}

TEST(get_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" get ", { TokenInformation(Token::GET, StreamString(L"get", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";get;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::GET, StreamString(L"get", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
}

TEST(get_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"get;",
		{ TokenInformation(Token::GET, StreamString(L"get", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L";get",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::GET, StreamString(L"get", StreamPosition(1, 2))) });
}

TEST(get_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1get1", { TokenInformation(Token::UNKNOWN, StreamString(L"1get1", StreamPosition())) });
	ExpectTokenInformations(
		L"1get1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1get1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))) });
	ExpectTokenInformations(L"1.1get1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1get1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1get1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1get1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"1_E+1get1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1get1", StreamPosition())) });
	ExpectTokenInformations(
		L"1get1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1get1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
}

TEST(get_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("get")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("get")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" get ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" get ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1get1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1get1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";get;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";get;")", StreamPosition())) });
}

TEST(get_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//get", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//get", StreamPosition())) });
	ExpectTokenInformations(
		L"// get ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// get ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1get1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1get1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;get;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;get;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*get*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*get*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* get */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* get */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1get1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1get1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;get;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;get;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*get", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*get", StreamPosition())) });
	ExpectTokenInformations(
		L"/* get ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* get ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1get1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1get1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;get;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;get;", StreamPosition())) });
}
