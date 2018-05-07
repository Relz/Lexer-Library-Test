#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(public_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"public", { TokenInformation(Token::PUBLIC, StreamString(L"public", StreamPosition())) });
}

TEST(public_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" public ", { TokenInformation(Token::PUBLIC, StreamString(L"public", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";public;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::PUBLIC, StreamString(L"public", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
}

TEST(public_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"public;",
		{ TokenInformation(Token::PUBLIC, StreamString(L"public", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";public",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::PUBLIC, StreamString(L"public", StreamPosition(1, 2))) });
}

TEST(public_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1public1", { TokenInformation(Token::UNKNOWN, StreamString(L"1public1", StreamPosition())) });
	ExpectTokenInformations(
		L"1public1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1public1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L"1.1public1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1public1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1public1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1public1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		L"1_E+1public1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1public1", StreamPosition())) });
	ExpectTokenInformations(
		L"1public1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1public1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 12))) });
}

TEST(public_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("public")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("public")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" public ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" public ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1public1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1public1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";public;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";public;")", StreamPosition())) });
}

TEST(public_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//public", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//public", StreamPosition())) });
	ExpectTokenInformations(
		L"// public ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// public ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1public1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1public1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;public;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;public;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*public*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*public*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* public */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* public */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1public1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1public1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;public;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;public;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*public", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*public", StreamPosition())) });
	ExpectTokenInformations(
		L"/* public ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* public ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1public1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1public1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;public;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;public;", StreamPosition())) });
}
