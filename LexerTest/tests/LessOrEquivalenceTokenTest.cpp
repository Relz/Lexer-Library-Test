#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(less_or_equivalence_token, determining_if_stay_alone)
{
	ExpectTokenInformations(
		"<=", { TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition())) });
}

TEST(less_or_equivalence_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" <= ", { TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";<=;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 4))) });
}

TEST(less_or_equivalence_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"<=;",
		{ TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 3))) });
	ExpectTokenInformations(
		";<=",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 2))) });
}

TEST(less_or_equivalence_token, determining_if_stay_between_numbers)
{
	ExpectTokenInformations(
		"1<=1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 2))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1<=1.1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 2))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1.1<=1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"1.1<=1.1",
		{ TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 4))),
		  TokenInformation(Token::FLOAT, StreamString("1.1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"1_E+1<=1",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"1<=1_E+1",
		{ TokenInformation(Token::INTEGER, StreamString("1", StreamPosition())),
		  TokenInformation(Token::LESS_OR_EQUIVALENCE, StreamString("<=", StreamPosition(1, 2))),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition(1, 4))) });
}

TEST(less_or_equivalence_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("<=")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("<=")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" <= ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" <= ")", StreamPosition())) });
	ExpectTokenInformations(
		R"("1<=1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1<=1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";<=;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";<=;")", StreamPosition())) });
}

TEST(less_or_equivalence_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations("#<=", { TokenInformation(Token::LINE_COMMENT, StreamString("#<=", StreamPosition())) });
	ExpectTokenInformations(
		"# <= ", { TokenInformation(Token::LINE_COMMENT, StreamString("# <= ", StreamPosition())) });
	ExpectTokenInformations(
		"#1<=1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1<=1", StreamPosition())) });
	ExpectTokenInformations(
		"#;<=;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;<=;", StreamPosition())) });
	ExpectTokenInformations(
		"/*<=*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*<=*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* <= */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* <= */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1<=1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1<=1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;<=;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;<=;*/", StreamPosition())) });
	ExpectTokenInformations("/*<=", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*<=", StreamPosition())) });
	ExpectTokenInformations(
		"/* <= ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* <= ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1<=1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1<=1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;<=;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;<=;", StreamPosition())) });
}
