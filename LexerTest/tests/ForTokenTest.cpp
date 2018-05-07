#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(for_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"for", { TokenInformation(Token::FOR, StreamString(L"for", StreamPosition())) });
}

TEST(for_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" for ", { TokenInformation(Token::FOR, StreamString(L"for", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";for;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FOR, StreamString(L"for", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
}

TEST(for_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"for;",
		{ TokenInformation(Token::FOR, StreamString(L"for", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L";for",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FOR, StreamString(L"for", StreamPosition(1, 2))) });
}

TEST(for_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1for1", { TokenInformation(Token::UNKNOWN, StreamString(L"1for1", StreamPosition())) });
	ExpectTokenInformations(
		L"1for1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1for1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))) });
	ExpectTokenInformations(L"1.1for1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1for1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1for1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1for1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"1_E+1for1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1for1", StreamPosition())) });
	ExpectTokenInformations(
		L"1for1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1for1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
}

TEST(for_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("for")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("for")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" for ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" for ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1for1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1for1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";for;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";for;")", StreamPosition())) });
}

TEST(for_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//for", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//for", StreamPosition())) });
	ExpectTokenInformations(
		L"// for ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// for ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1for1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1for1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;for;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;for;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*for*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*for*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* for */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* for */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1for1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1for1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;for;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;for;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*for", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*for", StreamPosition())) });
	ExpectTokenInformations(
		L"/* for ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* for ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1for1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1for1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;for;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;for;", StreamPosition())) });
}
