#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(string_literal_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		R"("")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition())) });
	ExpectTokenInformations(
		R"("_")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("_")", StreamPosition())) });
	ExpectTokenInformations(
		R"("""")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		R"("_id")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("_id")", StreamPosition())) });
}

TEST(string_literal_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		R"( "" )", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		R"(;"";)",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
}

TEST(string_literal_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		R"("";)",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		R"(;"")",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 2))) });
}

TEST(string_literal_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		R"(1""1)",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		R"(1""1.1)",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		R"(1.1""1)",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		R"(1.1""1.1)",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 4))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		R"(1_E+1""1)",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		R"(1""1_E+1)",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::STRING_LITERAL, StreamString(R"("")", StreamPosition(1, 2))),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition(1, 4))) });
}

TEST(string_literal_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		R"(//"")", { TokenInformation(Token::LINE_COMMENT, StreamString(R"(//"")", StreamPosition())) });
	ExpectTokenInformations(
		R"(// "" )", { TokenInformation(Token::LINE_COMMENT, StreamString(R"(// "" )", StreamPosition())) });
	ExpectTokenInformations(
		R"(//1""1)", { TokenInformation(Token::LINE_COMMENT, StreamString(R"(//1""1)", StreamPosition())) });
	ExpectTokenInformations(
		R"(//;"";)", { TokenInformation(Token::LINE_COMMENT, StreamString(R"(//;"";)", StreamPosition())) });
	ExpectTokenInformations(
		R"(/*""*/)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/*""*/)", StreamPosition())) });
	ExpectTokenInformations(
		R"(/* "" */)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/* "" */)", StreamPosition())) });
	ExpectTokenInformations(
		R"(/*1""1*/)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/*1""1*/)", StreamPosition())) });
	ExpectTokenInformations(
		R"(/*;"";*/)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/*;"";*/)", StreamPosition())) });
	ExpectTokenInformations(
		R"(/*"")", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/*"")", StreamPosition())) });
	ExpectTokenInformations(
		R"(/* "" )", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/* "" )", StreamPosition())) });
	ExpectTokenInformations(
		R"(/*1""1)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/*1""1)", StreamPosition())) });
	ExpectTokenInformations(
		R"(/*;"";)", { TokenInformation(Token::BLOCK_COMMENT, StreamString(R"(/*;"";)", StreamPosition())) });
}
