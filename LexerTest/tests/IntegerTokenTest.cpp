#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(integer_token, determining_if_stay_alone)
{
	ExpectTokenInformations("1", { TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())) });
	ExpectTokenInformations("2_1", { TokenInformation(Token::INTEGER, StreamString("2_1", StreamPosition())) });
	ExpectTokenInformations("16_F", { TokenInformation(Token::INTEGER, StreamString("16_F", StreamPosition())) });
}

TEST(integer_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" 1 ", { TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
	ExpectTokenInformations(" 2_1 ", { TokenInformation(Token::INTEGER, StreamString("2_1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";2_1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("2_1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(" 16_F ", { TokenInformation(Token::INTEGER, StreamString("16_F", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";16_F;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("16_F", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
}

TEST(integer_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"1;",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"2_1;",
		{ TokenInformation(Token::INTEGER, StreamString("2_1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		";2_1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("2_1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"16_F;",
		{ TokenInformation(Token::INTEGER, StreamString("16_F", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";16_F",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("16_F", StreamPosition(1, 2))) });
}

TEST(integer_token, not_determining_if_not_completed)
{
	ExpectTokenInformations("2_", { TokenInformation(Token::UNKNOWN, StreamString("2_", StreamPosition())) });
	ExpectTokenInformations("16_", { TokenInformation(Token::UNKNOWN, StreamString("16_", StreamPosition())) });
}

TEST(integer_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("2_1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("2_1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 2_1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 2_1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";2_1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";2_1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("16_F")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("16_F")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 16_F ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 16_F ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";16_F;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";16_F;")", StreamPosition())) });
}

TEST(integer_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("#1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1", StreamPosition())) });
	ExpectTokenInformations(
		"# 1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1;*/", StreamPosition())) });
	ExpectTokenInformations("/*1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1 ", StreamPosition())) });
	ExpectTokenInformations("/*1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1;", StreamPosition())) });

	ExpectTokenInformations(
		"#2_1", { TokenInformation(Token::LINE_COMMENT, StreamString("#2_1", StreamPosition())) });
	ExpectTokenInformations(
		"# 2_1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 2_1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;2_1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;2_1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1;", StreamPosition())) });

	ExpectTokenInformations(
		"#16_F", { TokenInformation(Token::LINE_COMMENT, StreamString("#16_F", StreamPosition())) });
	ExpectTokenInformations(
		"# 16_F ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 16_F ", StreamPosition())) });
	ExpectTokenInformations(
		"#;16_F;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;16_F;", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F */", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F ", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F;", StreamPosition())) });
}
