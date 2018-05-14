#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(identifier_token, determining_if_stay_alone)
{
	ExpectTokenInformations("_", { TokenInformation(Token::IDENTIFIER, StreamString("_", StreamPosition())) });
	ExpectTokenInformations("id", { TokenInformation(Token::IDENTIFIER, StreamString("id", StreamPosition())) });
	ExpectTokenInformations("_id", { TokenInformation(Token::IDENTIFIER, StreamString("_id", StreamPosition())) });
	ExpectTokenInformations("_id_", { TokenInformation(Token::IDENTIFIER, StreamString("_id_", StreamPosition())) });
	ExpectTokenInformations("_i_d_", { TokenInformation(Token::IDENTIFIER, StreamString("_i_d_", StreamPosition())) });
	ExpectTokenInformations("1id", { TokenInformation(Token::UNKNOWN, StreamString("1id", StreamPosition())) });
	ExpectTokenInformations("i1d", { TokenInformation(Token::IDENTIFIER, StreamString("i1d", StreamPosition())) });
}

TEST(identifier_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" id ", { TokenInformation(Token::IDENTIFIER, StreamString("id", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";id;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::IDENTIFIER, StreamString("id", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
}

TEST(identifier_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"id;",
		{ TokenInformation(Token::IDENTIFIER, StreamString("id", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		";id",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::IDENTIFIER, StreamString("id", StreamPosition(1, 2))) });
}

TEST(identifier_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1id1", { TokenInformation(Token::UNKNOWN, StreamString("1id1", StreamPosition())) });
	ExpectTokenInformations(
		"1id1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1id1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations("1.1id1", { TokenInformation(Token::UNKNOWN, StreamString("1.1id1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1id1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1id1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"1_E+1id1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1id1", StreamPosition())) });
	ExpectTokenInformations(
		"1id1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1id1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
}

TEST(identifier_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("id")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("id")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" id ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" id ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1id1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1id1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";id;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";id;")", StreamPosition())) });
}

TEST(identifier_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("//id", { TokenInformation(Token::LINE_COMMENT, StreamString("//id", StreamPosition())) });
	ExpectTokenInformations(
		"// id ", { TokenInformation(Token::LINE_COMMENT, StreamString("// id ", StreamPosition())) });
	ExpectTokenInformations(
		"//1id1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1id1", StreamPosition())) });
	ExpectTokenInformations(
		"//;id;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;id;", StreamPosition())) });
	ExpectTokenInformations(
		"/*id*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*id*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* id */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* id */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1id1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1id1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;id;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;id;*/", StreamPosition())) });
	ExpectTokenInformations("/*id", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*id", StreamPosition())) });
	ExpectTokenInformations(
		"/* id ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* id ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1id1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1id1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;id;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;id;", StreamPosition())) });
}
