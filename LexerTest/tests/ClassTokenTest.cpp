#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(class_token, determining_if_stay_alone)
{
	ExpectTokenInformations("class", { TokenInformation(Token::CLASS, StreamString("class", StreamPosition())) });
}

TEST(class_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(" class ", { TokenInformation(Token::CLASS, StreamString("class", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";class;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::CLASS, StreamString("class", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
}

TEST(class_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"class;",
		{ TokenInformation(Token::CLASS, StreamString("class", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		";class",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::CLASS, StreamString("class", StreamPosition(1, 2))) });
}

TEST(class_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations("1class1", { TokenInformation(Token::UNKNOWN, StreamString("1class1", StreamPosition())) });
	ExpectTokenInformations(
		"1class1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1class1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"1.1class1", { TokenInformation(Token::UNKNOWN, StreamString("1.1class1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1class1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1class1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1_E+1class1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1class1", StreamPosition())) });
	ExpectTokenInformations(
		"1class1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1class1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
}

TEST(class_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("class")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("class")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" class ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" class ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1class1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1class1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";class;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";class;")", StreamPosition())) });
}

TEST(class_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//class", { TokenInformation(Token::LINE_COMMENT, StreamString("//class", StreamPosition())) });
	ExpectTokenInformations(
		"// class ", { TokenInformation(Token::LINE_COMMENT, StreamString("// class ", StreamPosition())) });
	ExpectTokenInformations(
		"//1class1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1class1", StreamPosition())) });
	ExpectTokenInformations(
		"//;class;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;class;", StreamPosition())) });
	ExpectTokenInformations(
		"/*class*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*class*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* class */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* class */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1class1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1class1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;class;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;class;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*class", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*class", StreamPosition())) });
	ExpectTokenInformations(
		"/* class ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* class ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1class1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1class1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;class;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;class;", StreamPosition())) });
}
