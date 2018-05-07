#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(identifier_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"_", { TokenInformation(Token::IDENTIFIER, StreamString(L"_", StreamPosition())) });
	ExpectTokenInformations(L"id", { TokenInformation(Token::IDENTIFIER, StreamString(L"id", StreamPosition())) });
	ExpectTokenInformations(L"_id", { TokenInformation(Token::IDENTIFIER, StreamString(L"_id", StreamPosition())) });
	ExpectTokenInformations(L"_id_", { TokenInformation(Token::IDENTIFIER, StreamString(L"_id_", StreamPosition())) });
	ExpectTokenInformations(L"_i_d_", { TokenInformation(Token::IDENTIFIER, StreamString(L"_i_d_", StreamPosition())) });
	ExpectTokenInformations(L"1id", { TokenInformation(Token::UNKNOWN, StreamString(L"1id", StreamPosition())) });
	ExpectTokenInformations(L"i1d", { TokenInformation(Token::IDENTIFIER, StreamString(L"i1d", StreamPosition())) });
}

TEST(identifier_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" id ", { TokenInformation(Token::IDENTIFIER, StreamString(L"id", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";id;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::IDENTIFIER, StreamString(L"id", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 4))) });
}

TEST(identifier_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"id;",
		{ TokenInformation(Token::IDENTIFIER, StreamString(L"id", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		L";id",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::IDENTIFIER, StreamString(L"id", StreamPosition(1, 2))) });
}

TEST(identifier_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1id1", { TokenInformation(Token::UNKNOWN, StreamString(L"1id1", StreamPosition())) });
	ExpectTokenInformations(
		L"1id1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1id1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(L"1.1id1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1id1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1id1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1id1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"1_E+1id1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1id1", StreamPosition())) });
	ExpectTokenInformations(
		L"1id1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1id1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
}

TEST(identifier_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("id")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("id")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" id ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" id ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1id1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1id1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";id;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";id;")", StreamPosition())) });
}

TEST(identifier_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(L"//id", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//id", StreamPosition())) });
	ExpectTokenInformations(
		L"// id ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// id ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1id1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1id1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;id;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;id;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*id*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*id*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* id */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* id */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1id1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1id1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;id;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;id;*/", StreamPosition())) });
	ExpectTokenInformations(L"/*id", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*id", StreamPosition())) });
	ExpectTokenInformations(
		L"/* id ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* id ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1id1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1id1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;id;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;id;", StreamPosition())) });
}
