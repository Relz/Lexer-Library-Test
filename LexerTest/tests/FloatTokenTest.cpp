#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(float_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"1.1", { TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())) });
	ExpectTokenInformations(L"2_1.1", { TokenInformation(Token::FLOAT, StreamString(L"2_1.1", StreamPosition())) });
	ExpectTokenInformations(L"16_F.A", { TokenInformation(Token::FLOAT, StreamString(L"16_F.A", StreamPosition())) });
}

TEST(float_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" 1.1 ", { TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
	ExpectTokenInformations(L" 2_1.1 ", { TokenInformation(Token::FLOAT, StreamString(L"2_1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";2_1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"2_1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(L" 16_F.A ", { TokenInformation(Token::FLOAT, StreamString(L"16_F.A", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";16_F.A;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"16_F.A", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
}

TEST(float_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"1.1;",
		{ TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L";1.1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L" 2_1.1;",
		{ TokenInformation(Token::FLOAT, StreamString(L"2_1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";2_1.1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"2_1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L"16_F.A;",
		{ TokenInformation(Token::FLOAT, StreamString(L"16_F.A", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";16_F.A",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"16_F.A", StreamPosition(1, 2))) });
}

TEST(float_token, not_determining_if_not_completed)
{
	ExpectTokenInformations(L"1.", { TokenInformation(Token::UNKNOWN, StreamString(L"1.", StreamPosition())) });
	ExpectTokenInformations(L"2_1.", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1.", StreamPosition())) });
	ExpectTokenInformations(L"16_F.", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.", StreamPosition())) });
}

TEST(float_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("1.1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1.1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 1.1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 1.1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";1.1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";1.1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("2_1.1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("2_1.1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 2_1.1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 2_1.1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";2_1.1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";2_1.1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("16_F.A")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("16_F.A")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 16_F.A ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 16_F.A ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";16_F.A;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";16_F.A;")", StreamPosition())) });
}

TEST(float_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//1.1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 1.1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;1.1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;1.1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1.1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1.1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1.1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1.1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1.1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1.1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1.1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//2_1.1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//2_1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 2_1.1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 2_1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;2_1.1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;2_1.1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1.1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1.1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1.1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1.1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1.1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1.1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1.1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//16_F.A", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//16_F.A", StreamPosition())) });
	ExpectTokenInformations(
		L"// 16_F.A ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 16_F.A ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;16_F.A;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;16_F.A;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F.A */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F.A */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F.A;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F.A;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F.A ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F.A ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F.A;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F.A;", StreamPosition())) });
}
