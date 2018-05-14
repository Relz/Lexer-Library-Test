#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(while_token, determining_if_stay_alone)
{
	ExpectTokenInformations("while", { TokenInformation(Token::WHILE, StreamString("while", StreamPosition())) });
}

TEST(while_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" while ", { TokenInformation(Token::WHILE, StreamString("while", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";while;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::WHILE, StreamString("while", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
}

TEST(while_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"while;",
		{ TokenInformation(Token::WHILE, StreamString("while", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		";while",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::WHILE, StreamString("while", StreamPosition(1, 2))) });
}

TEST(while_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1while1", { TokenInformation(Token::UNKNOWN, StreamString("1while1", StreamPosition())) });
	ExpectTokenInformations(
		"1while1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1while1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"1.1while1", { TokenInformation(Token::UNKNOWN, StreamString("1.1while1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1while1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1while1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1_E+1while1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1while1", StreamPosition())) });
	ExpectTokenInformations(
		"1while1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1while1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
}

TEST(while_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("while")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("while")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" while ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" while ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1while1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1while1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";while;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";while;")", StreamPosition())) });
}

TEST(while_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//while", { TokenInformation(Token::LINE_COMMENT, StreamString("//while", StreamPosition())) });
	ExpectTokenInformations(
		"// while ", { TokenInformation(Token::LINE_COMMENT, StreamString("// while ", StreamPosition())) });
	ExpectTokenInformations(
		"//1while1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1while1", StreamPosition())) });
	ExpectTokenInformations(
		"//;while;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;while;", StreamPosition())) });
	ExpectTokenInformations(
		"/*while*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*while*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* while */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* while */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1while1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1while1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;while;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;while;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*while", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*while", StreamPosition())) });
	ExpectTokenInformations(
		"/* while ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* while ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1while1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1while1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;while;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;while;", StreamPosition())) });
}
