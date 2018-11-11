#include "TestHelper.h"
#include "TokenLibrary/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"

using namespace std;

TEST(exponential_token, determining_if_stay_alone)
{
	ExpectTokenInformations("1_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())) });
	ExpectTokenInformations("1_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString("1_E-1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E-1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E-1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1.0_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1.0_E-1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E-1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.0A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.0A_E-1", StreamPosition())) });

	ExpectTokenInformations(
		"1_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		"1_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("1_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		"1.1_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1.0_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1.0_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.0A_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.0A_E-1.1", StreamPosition())) });
}

TEST(exponential_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		" 1_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";1_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		" 2_1_E+3 ", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E+3", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";2_1_E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E+3", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		" 16_F_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";16_F_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("16_F_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 10))) });

	ExpectTokenInformations(
		" 1.1_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";1.1_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		" 2_1.1_E+3 ", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1.1_E+3", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";2_1.1_E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("2_1.1_E+3", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		" 16_F.A_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";16_F.A_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 12))) });

	ExpectTokenInformations(
		" 1.1_E+1.1 ", { TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";1.1_E+1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		" 2_1.1_E+3.1 ", { TokenInformation(Token::EXPONENTIAL, StreamString("2_1.1_E+3.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";2_1.1_E+3.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("2_1.1_E+3.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		" 16_F.A_E+1.1 ", { TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		";16_F.A_E+1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 14))) });
}

TEST(exponential_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		"1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		";1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		" 2_1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		";2_1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("2_1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"16_F_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("16_F_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		";16_F_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("16_F_E+1", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		"1.1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		";1.1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("1.1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		" 2_1.1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("2_1.1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		";2_1.1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("2_1.1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		"16_F.A_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		";16_F.A_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString("16_F.A_E+1", StreamPosition(1, 2))) });
}

TEST(exponential_token, not_determining_if_no_underscore_before_exponent_character)
{
	ExpectTokenInformations(
		"1E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 3))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString("-", StreamPosition(1, 3))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		"1.1E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"1.1E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString("-", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"2_1E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"2_1E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString("-", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		"2_1.0E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1.0E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"2_1.0E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1.0E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString("-", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		"16_F.AE+1",
		{ TokenInformation(Token::FLOAT, StreamString("16_F.AE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"16_F.AE-1",
		{ TokenInformation(Token::FLOAT, StreamString("16_F.AE", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString("-", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"16_F.0AE+1",
		{ TokenInformation(Token::FLOAT, StreamString("16_F.0AE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		"16_F.0AE-1",
		{ TokenInformation(Token::FLOAT, StreamString("16_F.0AE", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString("-", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });

	ExpectTokenInformations(
		" 1E+1 ",
		{ TokenInformation(Token::UNKNOWN, StreamString("1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";1E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 5))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		" 2_1E+3 ",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("3", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";2_1E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("3", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		" 16_FE+1 ",
		{ TokenInformation(Token::INTEGER, StreamString("16_FE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		";16_FE+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("16_FE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 9))) });

	ExpectTokenInformations(
		" 1.1E+1 ",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";1.1E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		" 2_1.1E+3 ",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("3", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		";2_1.1E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("3", StreamPosition(1, 9))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		" 16_F.AE+1 ",
		{ TokenInformation(Token::FLOAT, StreamString("16_F.AE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		";16_F.AE+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("16_F.AE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 11))) });

	ExpectTokenInformations(
		"1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString("1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 3))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 4))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		";1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		" 2_1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		";2_1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		"16_FE+1;",
		{ TokenInformation(Token::INTEGER, StreamString("16_FE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		";16_FE+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString("16_FE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 8))) });

	ExpectTokenInformations(
		"1.1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString("1.1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 6))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		";1.1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		" 2_1.1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString("2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		";2_1.1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString("2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		"16_F.AE+1;",
		{ TokenInformation(Token::FLOAT, StreamString("16_F.AE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 9))),
		  TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		";16_F.AE+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString("16_F.AE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString("+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString("1", StreamPosition(1, 10))) });
}

TEST(exponential_token, not_determining_if_not_completed)
{
	ExpectTokenInformations("1_E+", { TokenInformation(Token::UNKNOWN, StreamString("1_E+", StreamPosition())) });
	ExpectTokenInformations("1_E-", { TokenInformation(Token::UNKNOWN, StreamString("1_E-", StreamPosition())) });
	ExpectTokenInformations("1.1_E+", { TokenInformation(Token::UNKNOWN, StreamString("1.1_E+", StreamPosition())) });
	ExpectTokenInformations("1.1_E-", { TokenInformation(Token::UNKNOWN, StreamString("1.1_E-", StreamPosition())) });
	ExpectTokenInformations("2_1_E+", { TokenInformation(Token::UNKNOWN, StreamString("2_1_E+", StreamPosition())) });
	ExpectTokenInformations("2_1_E-", { TokenInformation(Token::UNKNOWN, StreamString("2_1_E-", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E+", { TokenInformation(Token::UNKNOWN, StreamString("2_1.0_E+", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E-", { TokenInformation(Token::UNKNOWN, StreamString("2_1.0_E-", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E+", { TokenInformation(Token::UNKNOWN, StreamString("16_F.A_E+", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E-", { TokenInformation(Token::UNKNOWN, StreamString("16_F.A_E-", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E+", { TokenInformation(Token::UNKNOWN, StreamString("16_F.0A_E+", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E-", { TokenInformation(Token::UNKNOWN, StreamString("16_F.0A_E-", StreamPosition())) });

	ExpectTokenInformations("1_E", { TokenInformation(Token::UNKNOWN, StreamString("1_E", StreamPosition())) });
	ExpectTokenInformations("1.1_E", { TokenInformation(Token::UNKNOWN, StreamString("1.1_E", StreamPosition())) });
	ExpectTokenInformations("2_1_E", { TokenInformation(Token::UNKNOWN, StreamString("2_1_E", StreamPosition())) });
	ExpectTokenInformations("2_1.0_E", { TokenInformation(Token::UNKNOWN, StreamString("2_1.0_E", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E", { TokenInformation(Token::UNKNOWN, StreamString("16_F.A_E", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E", { TokenInformation(Token::UNKNOWN, StreamString("16_F.0A_E", StreamPosition())) });

	ExpectTokenInformations("1_", { TokenInformation(Token::UNKNOWN, StreamString("1_", StreamPosition())) });
	ExpectTokenInformations("1.1_", { TokenInformation(Token::UNKNOWN, StreamString("1.1_", StreamPosition())) });
	ExpectTokenInformations("2_1_", { TokenInformation(Token::UNKNOWN, StreamString("2_1_", StreamPosition())) });
	ExpectTokenInformations("2_1.0_", { TokenInformation(Token::UNKNOWN, StreamString("2_1.0_", StreamPosition())) });
	ExpectTokenInformations("16_F.A_", { TokenInformation(Token::UNKNOWN, StreamString("16_F.A_", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_", { TokenInformation(Token::UNKNOWN, StreamString("16_F.0A_", StreamPosition())) });

	ExpectTokenInformations("1_E+1.", { TokenInformation(Token::UNKNOWN, StreamString("1_E+1.", StreamPosition())) });
	ExpectTokenInformations("1_E-1.", { TokenInformation(Token::UNKNOWN, StreamString("1_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		"1.1_E+1.", { TokenInformation(Token::UNKNOWN, StreamString("1.1_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		"1.1_E-1.", { TokenInformation(Token::UNKNOWN, StreamString("1.1_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		"2_1_E+1.", { TokenInformation(Token::UNKNOWN, StreamString("2_1_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		"2_1_E-1.", { TokenInformation(Token::UNKNOWN, StreamString("2_1_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E+1.", { TokenInformation(Token::UNKNOWN, StreamString("2_1.0_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		"2_1.0_E-1.", { TokenInformation(Token::UNKNOWN, StreamString("2_1.0_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E+1.", { TokenInformation(Token::UNKNOWN, StreamString("16_F.A_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.A_E-1.", { TokenInformation(Token::UNKNOWN, StreamString("16_F.A_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E+1.", { TokenInformation(Token::UNKNOWN, StreamString("16_F.0A_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		"16_F.0A_E-1.", { TokenInformation(Token::UNKNOWN, StreamString("16_F.0A_E-1.", StreamPosition())) });
}

TEST(exponential_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		R"("1_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 1_E+1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";1_E+1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"(";1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("2_1_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("2_1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 2_1_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 2_1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";2_1_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";2_1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("16_F_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("16_F_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 16_F_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 16_F_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";16_F_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";16_F_E+1;")", StreamPosition())) });

	ExpectTokenInformations(
		R"("1.1_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(R"("1.1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 1.1_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 1.1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";1.1_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";1.1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("2_1.1_E+1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("2_1.1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 2_1.1_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 2_1.1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";2_1.1_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";2_1.1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		R"("16_F.A_E+1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"("16_F.A_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		R"(" 16_F.A_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(" 16_F.A_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		R"(";16_F.A_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(R"(";16_F.A_E+1;")", StreamPosition())) });
}

TEST(exponential_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		"#1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"# 1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		"#2_1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString("#2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"# 2_1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 2_1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;2_1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;2_1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		"#16_F_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString("#16_F_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"# 16_F_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 16_F_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;16_F_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;16_F_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		"#1.1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString("#1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"# 1.1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;1.1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;1.1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1.1_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1.1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1.1_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1.1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 1.1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;1.1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;1.1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		"#2_1.1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString("#2_1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"# 2_1.1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 2_1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;2_1.1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;2_1.1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1.1_E+1 */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1.1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1.1_E+1;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1.1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 2_1.1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 2_1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*2_1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*2_1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;2_1.1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;2_1.1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		"#16_F.A_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString("#16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"# 16_F.A_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString("# 16_F.A_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"#;16_F.A_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString("#;16_F.A_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F.A_E+1 */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F.A_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F.A_E+1;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F.A_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/* 16_F.A_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/* 16_F.A_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		"/*16_F.A_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		"/*;16_F.A_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString("/*;16_F.A_E+1;", StreamPosition())) });
}
