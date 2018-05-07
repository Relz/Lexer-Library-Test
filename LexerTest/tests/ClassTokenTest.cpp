#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(class_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"class", { TokenInformation(Token::CLASS, StreamString(L"class", StreamPosition())) });
}

TEST(class_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(L" class ", { TokenInformation(Token::CLASS, StreamString(L"class", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";class;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::CLASS, StreamString(L"class", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
}

TEST(class_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"class;",
		{ TokenInformation(Token::CLASS, StreamString(L"class", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L";class",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::CLASS, StreamString(L"class", StreamPosition(1, 2))) });
}

TEST(class_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(L"1class1", { TokenInformation(Token::UNKNOWN, StreamString(L"1class1", StreamPosition())) });
	ExpectTokenInformations(
		L"1class1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1class1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"1.1class1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1class1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1class1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1class1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L"1_E+1class1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1class1", StreamPosition())) });
	ExpectTokenInformations(
		L"1class1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1class1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
}

TEST(class_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("class")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("class")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" class ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" class ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1class1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1class1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";class;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";class;")", StreamPosition())) });
}

TEST(class_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//class", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//class", StreamPosition())) });
	ExpectTokenInformations(
		L"// class ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// class ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1class1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1class1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;class;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;class;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*class*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*class*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* class */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* class */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1class1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1class1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;class;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;class;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*class", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*class", StreamPosition())) });
	ExpectTokenInformations(
		L"/* class ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* class ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1class1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1class1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;class;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;class;", StreamPosition())) });
}
