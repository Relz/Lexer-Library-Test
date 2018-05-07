#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(integer_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"1", { TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())) });
	ExpectTokenInformations(L"2_1", { TokenInformation(Token::INTEGER, StreamString(L"2_1", StreamPosition())) });
	ExpectTokenInformations(L"16_F", { TokenInformation(Token::INTEGER, StreamString(L"16_F", StreamPosition())) });
}

TEST(integer_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" 1 ", { TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 3))) });
	ExpectTokenInformations(L" 2_1 ", { TokenInformation(Token::INTEGER, StreamString(L"2_1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";2_1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"2_1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
	ExpectTokenInformations(L" 16_F ", { TokenInformation(Token::INTEGER, StreamString(L"16_F", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";16_F;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"16_F", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
}

TEST(integer_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"1;",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L"2_1;",
		{ TokenInformation(Token::INTEGER, StreamString(L"2_1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L";2_1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"2_1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L"16_F;",
		{ TokenInformation(Token::INTEGER, StreamString(L"16_F", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		L";16_F",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"16_F", StreamPosition(1, 2))) });
}

TEST(integer_token, not_determining_if_not_completed)
{
	ExpectTokenInformations(L"2_", { TokenInformation(Token::UNKNOWN, StreamString(L"2_", StreamPosition())) });
	ExpectTokenInformations(L"16_", { TokenInformation(Token::UNKNOWN, StreamString(L"16_", StreamPosition())) });
}

TEST(integer_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("2_1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("2_1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 2_1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 2_1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";2_1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";2_1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("16_F")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("16_F")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 16_F ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 16_F ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";16_F;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";16_F;")", StreamPosition())) });
}

TEST(integer_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(L"//1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1;*/", StreamPosition())) });
	ExpectTokenInformations(L"/*1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1 ", StreamPosition())) });
	ExpectTokenInformations(L"/*1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//2_1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//2_1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 2_1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 2_1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;2_1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;2_1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//16_F", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//16_F", StreamPosition())) });
	ExpectTokenInformations(
		L"// 16_F ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 16_F ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;16_F;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;16_F;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F;", StreamPosition())) });
}
