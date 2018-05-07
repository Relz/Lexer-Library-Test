#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(type_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"Integer", { TokenInformation(Token::TYPE, StreamString(L"Integer", StreamPosition())) });
	ExpectTokenInformations(L"Float", { TokenInformation(Token::TYPE, StreamString(L"Float", StreamPosition())) });
	ExpectTokenInformations(L"String", { TokenInformation(Token::TYPE, StreamString(L"String", StreamPosition())) });
	ExpectTokenInformations(L"Void", { TokenInformation(Token::TYPE, StreamString(L"Void", StreamPosition())) });
	ExpectTokenInformations(L"Array", { TokenInformation(Token::TYPE, StreamString(L"Array", StreamPosition())) });
}

TEST(type_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" Integer ", { TokenInformation(Token::TYPE, StreamString(L"Integer", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";Integer;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Integer", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });

	ExpectTokenInformations(L" Float ", { TokenInformation(Token::TYPE, StreamString(L"Float", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";Float;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Float", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });

	ExpectTokenInformations(
		L" String ", { TokenInformation(Token::TYPE, StreamString(L"String", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";String;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"String", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });

	ExpectTokenInformations(L" Void ", { TokenInformation(Token::TYPE, StreamString(L"Void", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";Void;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Void", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });

	ExpectTokenInformations(L" Array ", { TokenInformation(Token::TYPE, StreamString(L"Array", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";Array;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Array", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
}

TEST(type_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"Integer;",
		{ TokenInformation(Token::TYPE, StreamString(L"Integer", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L";Integer",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Integer", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		L"Float;",
		{ TokenInformation(Token::TYPE, StreamString(L"Float", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L";Float",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Float", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		L"String;",
		{ TokenInformation(Token::TYPE, StreamString(L"String", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";String",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"String", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		L"Void;",
		{ TokenInformation(Token::TYPE, StreamString(L"Void", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		L";Void",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Void", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		L"Array;",
		{ TokenInformation(Token::TYPE, StreamString(L"Array", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L";Array",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString(L"Array", StreamPosition(1, 2))) });
}

TEST(type_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		L"1Integer1", { TokenInformation(Token::UNKNOWN, StreamString(L"1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Integer1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Integer1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L"1.1Integer1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1Integer1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1Integer1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		L"1_E+1Integer1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Integer1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Integer1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 13))) });

	ExpectTokenInformations(L"1Float1", { TokenInformation(Token::UNKNOWN, StreamString(L"1Float1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Float1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Float1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"1.1Float1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1Float1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1Float1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1Float1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L"1_E+1Float1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1Float1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Float1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Float1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });

	ExpectTokenInformations(
		L"1String1", { TokenInformation(Token::UNKNOWN, StreamString(L"1String1", StreamPosition())) });
	ExpectTokenInformations(
		L"1String1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1String1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L"1.1String1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1String1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1String1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1String1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		L"1_E+1String1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1String1", StreamPosition())) });
	ExpectTokenInformations(
		L"1String1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1String1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 12))) });

	ExpectTokenInformations(L"1Void1", { TokenInformation(Token::UNKNOWN, StreamString(L"1Void1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Void1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Void1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"1.1Void1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1Void1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1Void1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1Void1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L"1_E+1Void1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1Void1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Void1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Void1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });

	ExpectTokenInformations(L"1Array1", { TokenInformation(Token::UNKNOWN, StreamString(L"1Array1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Array1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Array1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"1.1Array1", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1Array1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1Array1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1Array1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(L".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L"1_E+1Array1", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1Array1", StreamPosition())) });
	ExpectTokenInformations(
		L"1Array1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1Array1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 11))) });
}

TEST(type_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("Integer")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("Integer")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" Integer ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" Integer ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1Integer1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1Integer1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";Integer;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";Integer;")", StreamPosition())) });

	ExpectTokenInformations(
		LR"("Float")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("Float")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" Float ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" Float ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1Float1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1Float1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";Float;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";Float;")", StreamPosition())) });

	ExpectTokenInformations(
		LR"("String")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("String")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" String ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" String ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1String1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1String1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";String;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";String;")", StreamPosition())) });

	ExpectTokenInformations(
		LR"("Void")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("Void")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" Void ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" Void ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1Void1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1Void1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";Void;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";Void;")", StreamPosition())) });

	ExpectTokenInformations(
		LR"("Array")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("Array")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" Array ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" Array ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("1Array1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1Array1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";Array;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";Array;")", StreamPosition())) });
}

TEST(type_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//Integer", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//Integer", StreamPosition())) });
	ExpectTokenInformations(
		L"// Integer ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// Integer ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1Integer1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;Integer;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;Integer;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Integer*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Integer*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Integer */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Integer */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Integer1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Integer1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Integer;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Integer;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Integer", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Integer", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Integer ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Integer ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Integer1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Integer;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Integer;", StreamPosition())) });

	ExpectTokenInformations(
		L"//Integer", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//Integer", StreamPosition())) });
	ExpectTokenInformations(
		L"// Float ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// Float ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1Float1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1Float1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;Float;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;Float;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Float*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Float*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Float */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Float */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Float1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Float1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Float;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Float;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Float", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Float", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Float ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Float ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Float1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Float1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Float;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Float;", StreamPosition())) });

	ExpectTokenInformations(
		L"//String", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//String", StreamPosition())) });
	ExpectTokenInformations(
		L"// String ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// String ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1String1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1String1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;String;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;String;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*String*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*String*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* String */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* String */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1String1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1String1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;String;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;String;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*String", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*String", StreamPosition())) });
	ExpectTokenInformations(
		L"/* String ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* String ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1String1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1String1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;String;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;String;", StreamPosition())) });

	ExpectTokenInformations(
		L"//Void", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//Void", StreamPosition())) });
	ExpectTokenInformations(
		L"// Void ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// Void ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1Void1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1Void1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;Void;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;Void;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Void*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Void*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Void */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Void */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Void1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Void1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Void;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Void;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Void", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Void", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Void ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Void ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Void1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Void1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Void;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Void;", StreamPosition())) });

	ExpectTokenInformations(
		L"//Array", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//Array", StreamPosition())) });
	ExpectTokenInformations(
		L"// Array ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// Array ", StreamPosition())) });
	ExpectTokenInformations(
		L"//1Array1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1Array1", StreamPosition())) });
	ExpectTokenInformations(
		L"//;Array;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;Array;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Array*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Array*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Array */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Array */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Array1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Array1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Array;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Array;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*Array", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*Array", StreamPosition())) });
	ExpectTokenInformations(
		L"/* Array ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* Array ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1Array1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1Array1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;Array;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;Array;", StreamPosition())) });
}
