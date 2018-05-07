#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(constructor_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		L"Constructor", { TokenInformation(Token::CONSTRUCTOR, StreamString(L"Constructor", StreamPosition())) });
}

TEST(constructor_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" Constructor ", { TokenInformation(Token::CONSTRUCTOR, StreamString(L"Constructor", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";Constructor;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::CONSTRUCTOR, StreamString(L"Constructor", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 13))) });
}

TEST(constructor_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"Constructor;",
		{ TokenInformation(Token::CONSTRUCTOR, StreamString(L"Constructor", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		L";Constructor",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::CONSTRUCTOR, StreamString(L"Constructor", StreamPosition(1, 2))) });
}

TEST(constructor_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1Constructor1", { TokenInformation(Token::UNKNOWN, StreamString(L"1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Constructor1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Constructor1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 14))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 15))) });
	ExpectTokenInformations(
		L"1.1Constructor1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1Constructor1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1Constructor1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 16))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 17))) });
	ExpectTokenInformations(
		L"1_E+1Constructor1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Constructor1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Constructor1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 16))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 17))) });
}

TEST(constructor_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("Constructor")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("Constructor")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" Constructor ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" Constructor ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1Constructor1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1Constructor1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";Constructor;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";Constructor;")", StreamPosition())) });
}

TEST(constructor_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//Constructor", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//Constructor", StreamPosition())) });
	ExpectTokenInformations(
		L"// Constructor ",
		{ TokenInformation(Token::LINE_COMMENT, StreamString(L"// Constructor ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1Constructor1",
		{ TokenInformation(Token::LINE_COMMENT, StreamString(L"//1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;Constructor;",
		{ TokenInformation(Token::LINE_COMMENT, StreamString(L"//;Constructor;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Constructor*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Constructor*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Constructor */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Constructor */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Constructor1*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Constructor1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Constructor;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Constructor;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Constructor", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Constructor", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Constructor ",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Constructor ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Constructor1",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Constructor1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Constructor;",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Constructor;", StreamPosition())) });
}
