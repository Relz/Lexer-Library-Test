#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(while_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"while", { TokenInformation(Token::WHILE, StreamString(L"while", StreamPosition())) });
}

TEST(while_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" while ", { TokenInformation(Token::WHILE, StreamString(L"while", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";while;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::WHILE, StreamString(L"while", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
}

TEST(while_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"while;",
		{ TokenInformation(Token::WHILE, StreamString(L"while", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L";while",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::WHILE, StreamString(L"while", StreamPosition(1, 2))) });
}

TEST(while_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1while1", { TokenInformation(Token::UNKNOWN, StreamString(L"1while1", StreamPosition())) });
	ExpectTokenInformations(
		L"1while1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1while1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"1.1while1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1while1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1while1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1while1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L"1_E+1while1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1while1", StreamPosition())) });
	ExpectTokenInformations(
		L"1while1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1while1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
}

TEST(while_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("while")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("while")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" while ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" while ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1while1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1while1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";while;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";while;")", StreamPosition())) });
}

TEST(while_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//while", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//while", StreamPosition())) });
	ExpectTokenInformations(
		L"// while ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// while ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1while1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1while1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;while;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;while;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*while*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*while*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* while */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* while */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1while1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1while1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;while;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;while;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*while", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*while", StreamPosition())) });
	ExpectTokenInformations(
		L"/* while ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* while ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1while1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1while1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;while;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;while;", StreamPosition())) });
}
