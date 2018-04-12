#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(type_token, determining_if_stay_alone)
{
	ExpectTokenInformations("Integer", { TokenInformation(Token::TYPE, StreamString("Integer", StreamPosition())) });
	ExpectTokenInformations("Float", { TokenInformation(Token::TYPE, StreamString("Float", StreamPosition())) });
	ExpectTokenInformations("String", { TokenInformation(Token::TYPE, StreamString("String", StreamPosition())) });
	ExpectTokenInformations("Void", { TokenInformation(Token::TYPE, StreamString("Void", StreamPosition())) });
	ExpectTokenInformations("Array", { TokenInformation(Token::TYPE, StreamString("Array", StreamPosition())) });
}

TEST(type_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" Integer ", { TokenInformation(Token::TYPE, StreamString("Integer", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";Integer;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Integer", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });

	ExpectTokenInformations(" Float ", { TokenInformation(Token::TYPE, StreamString("Float", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";Float;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Float", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });

	ExpectTokenInformations(
		" String ", { TokenInformation(Token::TYPE, StreamString("String", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";String;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("String", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });

	ExpectTokenInformations(" Void ", { TokenInformation(Token::TYPE, StreamString("Void", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";Void;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Void", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });

	ExpectTokenInformations(" Array ", { TokenInformation(Token::TYPE, StreamString("Array", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";Array;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Array", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
}

TEST(type_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"Integer;",
		{ TokenInformation(Token::TYPE, StreamString("Integer", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		";Integer",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Integer", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		"Float;",
		{ TokenInformation(Token::TYPE, StreamString("Float", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		";Float",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Float", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		"String;",
		{ TokenInformation(Token::TYPE, StreamString("String", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";String",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("String", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		"Void;",
		{ TokenInformation(Token::TYPE, StreamString("Void", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";Void",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Void", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		"Array;",
		{ TokenInformation(Token::TYPE, StreamString("Array", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		";Array",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::TYPE, StreamString("Array", StreamPosition(1, 2))) });
}

TEST(type_token, not_determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1Integer1", { TokenInformation(Token::UNKNOWN, StreamString("1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		"1Integer1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Integer1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1.1Integer1", { TokenInformation(Token::UNKNOWN, StreamString("1.1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1Integer1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1Integer1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		"1_E+1Integer1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		"1Integer1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Integer1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 12))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 13))) });

	ExpectTokenInformations("1Float1", { TokenInformation(Token::UNKNOWN, StreamString("1Float1", StreamPosition())) });
	ExpectTokenInformations(
		"1Float1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Float1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"1.1Float1", { TokenInformation(Token::UNKNOWN, StreamString("1.1Float1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1Float1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1Float1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1_E+1Float1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1Float1", StreamPosition())) });
	ExpectTokenInformations(
		"1Float1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Float1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });

	ExpectTokenInformations(
		"1String1", { TokenInformation(Token::UNKNOWN, StreamString("1String1", StreamPosition())) });
	ExpectTokenInformations(
		"1String1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1String1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"1.1String1", { TokenInformation(Token::UNKNOWN, StreamString("1.1String1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1String1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1String1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 12))) });
	ExpectTokenInformations(
		"1_E+1String1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1String1", StreamPosition())) });
	ExpectTokenInformations(
		"1String1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1String1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 11))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 12))) });

	ExpectTokenInformations("1Void1", { TokenInformation(Token::UNKNOWN, StreamString("1Void1", StreamPosition())) });
	ExpectTokenInformations(
		"1Void1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Void1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"1.1Void1", { TokenInformation(Token::UNKNOWN, StreamString("1.1Void1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1Void1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1Void1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"1_E+1Void1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1Void1", StreamPosition())) });
	ExpectTokenInformations(
		"1Void1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Void1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });

	ExpectTokenInformations("1Array1", { TokenInformation(Token::UNKNOWN, StreamString("1Array1", StreamPosition())) });
	ExpectTokenInformations(
		"1Array1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Array1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"1.1Array1", { TokenInformation(Token::UNKNOWN, StreamString("1.1Array1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1Array1.1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1Array1", StreamPosition())),
		  TokenInformation(Token::DOT, StreamString(".", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		"1_E+1Array1", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1Array1", StreamPosition())) });
	ExpectTokenInformations(
		"1Array1_E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1Array1_E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 10))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 11))) });
}

TEST(type_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("Integer")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("Integer")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" Integer ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" Integer ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1Integer1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("1Integer1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";Integer;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";Integer;")", StreamPosition())) });

	ExpectTokenInformations(
		R"("Float")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("Float")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" Float ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" Float ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1Float1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1Float1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";Float;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";Float;")", StreamPosition())) });

	ExpectTokenInformations(
		R"("String")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("String")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" String ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" String ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1String1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1String1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";String;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";String;")", StreamPosition())) });

	ExpectTokenInformations(
		R"("Void")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("Void")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" Void ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" Void ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1Void1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1Void1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";Void;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";Void;")", StreamPosition())) });

	ExpectTokenInformations(
		R"("Array")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("Array")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" Array ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" Array ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1Array1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1Array1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";Array;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";Array;")", StreamPosition())) });
}

TEST(type_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"//Integer", { TokenInformation(Token::LINE_COMMENT, StreamString("//Integer", StreamPosition())) });
	ExpectTokenInformations(
		"// Integer ", { TokenInformation(Token::LINE_COMMENT, StreamString("// Integer ", StreamPosition())) });
	ExpectTokenInformations(
		"//1Integer1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		"//;Integer;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;Integer;", StreamPosition())) });
	ExpectTokenInformations(
		"/*Integer*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Integer*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* Integer */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Integer */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Integer1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Integer1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Integer;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Integer;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*Integer", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Integer", StreamPosition())) });
	ExpectTokenInformations(
		"/* Integer ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Integer ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Integer1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Integer1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Integer;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Integer;", StreamPosition())) });

	ExpectTokenInformations(
		"//Integer", { TokenInformation(Token::LINE_COMMENT, StreamString("//Integer", StreamPosition())) });
	ExpectTokenInformations(
		"// Float ", { TokenInformation(Token::LINE_COMMENT, StreamString("// Float ", StreamPosition())) });
	ExpectTokenInformations(
		"//1Float1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1Float1", StreamPosition())) });
	ExpectTokenInformations(
		"//;Float;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;Float;", StreamPosition())) });
	ExpectTokenInformations(
		"/*Float*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Float*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* Float */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Float */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Float1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Float1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Float;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Float;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*Float", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Float", StreamPosition())) });
	ExpectTokenInformations(
		"/* Float ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Float ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Float1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Float1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Float;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Float;", StreamPosition())) });

	ExpectTokenInformations(
		"//String", { TokenInformation(Token::LINE_COMMENT, StreamString("//String", StreamPosition())) });
	ExpectTokenInformations(
		"// String ", { TokenInformation(Token::LINE_COMMENT, StreamString("// String ", StreamPosition())) });
	ExpectTokenInformations(
		"//1String1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1String1", StreamPosition())) });
	ExpectTokenInformations(
		"//;String;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;String;", StreamPosition())) });
	ExpectTokenInformations(
		"/*String*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*String*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* String */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* String */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1String1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1String1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;String;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;String;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*String", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*String", StreamPosition())) });
	ExpectTokenInformations(
		"/* String ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* String ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1String1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1String1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;String;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;String;", StreamPosition())) });

	ExpectTokenInformations(
		"//Void", { TokenInformation(Token::LINE_COMMENT, StreamString("//Void", StreamPosition())) });
	ExpectTokenInformations(
		"// Void ", { TokenInformation(Token::LINE_COMMENT, StreamString("// Void ", StreamPosition())) });
	ExpectTokenInformations(
		"//1Void1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1Void1", StreamPosition())) });
	ExpectTokenInformations(
		"//;Void;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;Void;", StreamPosition())) });
	ExpectTokenInformations(
		"/*Void*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Void*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* Void */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Void */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Void1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Void1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Void;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Void;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*Void", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Void", StreamPosition())) });
	ExpectTokenInformations(
		"/* Void ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Void ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Void1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Void1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Void;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Void;", StreamPosition())) });

	ExpectTokenInformations(
		"//Array", { TokenInformation(Token::LINE_COMMENT, StreamString("//Array", StreamPosition())) });
	ExpectTokenInformations(
		"// Array ", { TokenInformation(Token::LINE_COMMENT, StreamString("// Array ", StreamPosition())) });
	ExpectTokenInformations(
		"//1Array1", { TokenInformation(Token::LINE_COMMENT, StreamString("//1Array1", StreamPosition())) });
	ExpectTokenInformations(
		"//;Array;", { TokenInformation(Token::LINE_COMMENT, StreamString("//;Array;", StreamPosition())) });
	ExpectTokenInformations(
		"/*Array*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Array*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* Array */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Array */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Array1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Array1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Array;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Array;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*Array", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*Array", StreamPosition())) });
	ExpectTokenInformations(
		"/* Array ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* Array ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1Array1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1Array1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;Array;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;Array;", StreamPosition())) });
}
