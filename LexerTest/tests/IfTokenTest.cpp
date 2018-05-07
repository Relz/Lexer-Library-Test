#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(if_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"if", { TokenInformation(Token::IF, StreamString(L"if", StreamPosition())) });
}

TEST(if_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" if ", { TokenInformation(Token::IF, StreamString(L"if", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";if;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::IF, StreamString(L"if", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
}

TEST(if_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"if;",
		{ TokenInformation(Token::IF, StreamString(L"if", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		L";if",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::IF, StreamString(L"if", StreamPosition(1, 2))) });
}

TEST(if_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1if1", { TokenInformation(Token::UNKNOWN, StreamString(L"1if1", StreamPosition())) });
	ExpectTokenInformations(
		L"1if1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1if1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(L"1.1if1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1if1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1if1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1if1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"1_E+1if1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1if1", StreamPosition())) });
	ExpectTokenInformations(
		L"1if1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1if1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
}

TEST(if_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("if")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("if")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" if ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" if ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1if1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1if1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";if;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";if;")", StreamPosition())) });
}

TEST(if_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(L"//if", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//if", StreamPosition())) });
	ExpectTokenInformations(
		L"// if ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// if ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1if1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1if1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;if;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;if;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*if*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*if*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* if */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* if */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1if1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1if1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;if;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;if;*/", StreamPosition())) });
	ExpectTokenInformations(L"/*if", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*if", StreamPosition())) });
	ExpectTokenInformations(
		L"/* if ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* if ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1if1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1if1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;if;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;if;", StreamPosition())) });
}
