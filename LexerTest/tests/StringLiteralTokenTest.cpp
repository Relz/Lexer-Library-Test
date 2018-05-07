#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(string_literal_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		LR"("")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("_")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("_")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("""")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		LR"("_id")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("_id")", StreamPosition())) });
}

TEST(string_literal_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		LR"( "" )", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		LR"(;"";)",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
}

TEST(string_literal_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		LR"("";)",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		LR"(;"")",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 2))) });
}

TEST(string_literal_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		LR"(1""1)",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		LR"(1""1.1)",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		LR"(1.1""1)",
		{ TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		LR"(1.1""1.1)",
		{ TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 4))),
		  TokenInformation(Token::FLOAT, StreamString(L"1.1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		LR"(1_E+1""1)",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		LR"(1""1_E+1)",
		{ TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(LR"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition(1, 4))) });
}

TEST(string_literal_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		LR"(//"")", { TokenInformation(Token::LINE_COMMENT, StreamString(LR"(//"")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(// "" )", { TokenInformation(Token::LINE_COMMENT, StreamString(LR"(// "" )", StreamPosition())) });
	ExpectTokenInformations(
		LR"(//1""1)", { TokenInformation(Token::LINE_COMMENT, StreamString(LR"(//1""1)", StreamPosition())) });
	ExpectTokenInformations(
		LR"(//;"";)", { TokenInformation(Token::LINE_COMMENT, StreamString(LR"(//;"";)", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/*""*/)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/*""*/)", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/* "" */)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/* "" */)", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/*1""1*/)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/*1""1*/)", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/*;"";*/)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/*;"";*/)", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/*"")", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/*"")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/* "" )", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/* "" )", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/*1""1)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/*1""1)", StreamPosition())) });
	ExpectTokenInformations(
		LR"(/*;"";)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(LR"(/*;"";)", StreamPosition())) });
}
