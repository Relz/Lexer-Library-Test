#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(public_token, determining_if_stay_alone)
{
	ExpectTokenInformations("public", { TokenInformation(Token::PUBLIC, StreamString("public", StreamPosition())) });
}

TEST(public_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" public ", { TokenInformation(Token::PUBLIC, StreamString("public", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";public;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::PUBLIC, StreamString("public", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
}

TEST(public_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"public;",
		{ TokenInformation(Token::PUBLIC, StreamString("public", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";public",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::PUBLIC, StreamString("public", StreamPosition(1, 2))) });
}

TEST(public_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1public1", { TokenInformation(Token::UNKNOWN, StreamString("1public1", StreamPosition())) });
	ExpectTokenInformations(
		"1public1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1public1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"1.1public1", { TokenInformation(Token::UNKNOWN, StreamString("1.1public1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1public1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1public1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		"1_E+1public1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1public1", StreamPosition())) });
	ExpectTokenInformations(
		"1public1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1public1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 12))) });
}

TEST(public_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("public")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("public")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" public ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" public ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1public1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1public1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";public;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";public;")", StreamPosition())) });
}

TEST(public_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"#public", { TokenInformation(Token::LINE_COMMENT, StreamString("#public", StreamPosition())) });
	ExpectTokenInformations(
		"# public ", { TokenInformation(Token::LINE_COMMENT, StreamString("# public ", StreamPosition())) });
	ExpectTokenInformations(
		"#1public1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1public1", StreamPosition())) });
	ExpectTokenInformations(
		"#;public;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;public;", StreamPosition())) });
	ExpectTokenInformations(
		"/*public*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*public*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* public */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* public */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1public1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1public1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;public;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;public;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*public", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*public", StreamPosition())) });
	ExpectTokenInformations(
		"/* public ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* public ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1public1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1public1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;public;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;public;", StreamPosition())) });
}
