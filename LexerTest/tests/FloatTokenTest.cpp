#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(float_token, determining_if_stay_alone)
{
	ExpectTokenInformations("1.1", { TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())) });
	ExpectTokenInformations("2_1.1", { TokenInformation(Token::FLOAT, StreamString("2_1.1", StreamPosition())) });
	ExpectTokenInformations("16_F.A", { TokenInformation(Token::FLOAT, StreamString("16_F.A", StreamPosition())) });
}

TEST(float_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" 1.1 ", { TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(" 2_1.1 ", { TokenInformation(Token::FLOAT, StreamString("2_1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";2_1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("2_1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		" 16_F.A ", { TokenInformation(Token::FLOAT, StreamString("16_F.A", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";16_F.A;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("16_F.A", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
}

TEST(float_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"1.1;",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		";1.1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		" 2_1.1;",
		{ TokenInformation(Token::FLOAT, StreamString("2_1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";2_1.1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("2_1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"16_F.A;",
		{ TokenInformation(Token::FLOAT, StreamString("16_F.A", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";16_F.A",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("16_F.A", StreamPosition(1, 2))) });
}

TEST(float_token, not_determining_if_not_completed)
{
	ExpectTokenInformations("1.", { TokenInformation(Token::UNKNOWN, StreamString("1.", StreamPosition())) });
	ExpectTokenInformations("2_1.", { TokenInformation(Token::UNKNOWN, StreamString("2_1.", StreamPosition())) });
	ExpectTokenInformations("16_F.", { TokenInformation(Token::UNKNOWN, StreamString("16_F.", StreamPosition())) });
}

TEST(float_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("1.1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1.1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 1.1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 1.1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";1.1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";1.1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("2_1.1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("2_1.1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 2_1.1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 2_1.1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";2_1.1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";2_1.1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("16_F.A")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("16_F.A")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 16_F.A ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 16_F.A ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";16_F.A;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";16_F.A;")", StreamPosition())) });
}

TEST(float_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//1.1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1.1", StreamPosition())) });
	ExpectTokenInformations(
		"// 1.1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("// 1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		"//;1.1;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;1.1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1.1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1.1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1.1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1.1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1.1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1.1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1.1;", StreamPosition())) });

	ExpectTokenInformations(
		"//2_1.1", { TokenInformation(Token::LINE_COMMENT, StreamString("//2_1.1", StreamPosition())) });
	ExpectTokenInformations(
		"// 2_1.1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("// 2_1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		"//;2_1.1;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;2_1.1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1.1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1.1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1.1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1.1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1.1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1.1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1.1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1.1;", StreamPosition())) });

	ExpectTokenInformations(
		"//16_F.A", { TokenInformation(Token::LINE_COMMENT, StreamString("//16_F.A", StreamPosition())) });
	ExpectTokenInformations(
		"// 16_F.A ", { TokenInformation(Token::LINE_COMMENT, StreamString("// 16_F.A ", StreamPosition())) });
	ExpectTokenInformations(
		"//;16_F.A;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;16_F.A;", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F.A */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F.A */", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F.A;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F.A;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F.A ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F.A ", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F.A;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F.A;", StreamPosition())) });
}
