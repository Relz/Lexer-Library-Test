#include "Token/TokenInformation/TokenInformation.h"
#include "TestHelper.h"
#include "gtest/gtest.h"

using namespace std;

TEST(exponential_token, determining_if_stay_alone)
{
	ExpectTokenInformations(L"1_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition())) });
	ExpectTokenInformations(L"1_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E-1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E-1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E-1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.0_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.0_E-1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E-1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E+1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.0A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E-1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.0A_E-1", StreamPosition())) });

	ExpectTokenInformations(
		L"1_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"1_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.0_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.0_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E-1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E+1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.0A_E+1.1", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E-1.1", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.0A_E-1.1", StreamPosition())) });
}

TEST(exponential_token, determining_if_stay_between_delimiters)
{
	ExpectTokenInformations(
		L" 1_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";1_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L" 2_1_E+3 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E+3", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";2_1_E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E+3", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L" 16_F_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";16_F_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 10))) });

	ExpectTokenInformations(
		L" 1.1_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";1.1_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L" 2_1.1_E+3 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.1_E+3", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";2_1.1_E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.1_E+3", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L" 16_F.A_E+1 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";16_F.A_E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 12))) });

	ExpectTokenInformations(
		L" 1.1_E+1.1 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";1.1_E+1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L" 2_1.1_E+3.1 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.1_E+3.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";2_1.1_E+3.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.1_E+3.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 13))) });
	ExpectTokenInformations(
		L" 16_F.A_E+1.1 ", { TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1.1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L";16_F.A_E+1.1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1.1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 14))) });
}

TEST(exponential_token, determining_if_stay_near_delimiter)
{
	ExpectTokenInformations(
		L"1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L";1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L" 2_1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L";2_1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L"16_F_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L";16_F_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F_E+1", StreamPosition(1, 2))) });

	ExpectTokenInformations(
		L"1.1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L";1.1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"1.1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L" 2_1.1_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.1_E+1", StreamPosition(1, 2))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L";2_1.1_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"2_1.1_E+1", StreamPosition(1, 2))) });
	ExpectTokenInformations(
		L"16_F.A_E+1;",
		{ TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1", StreamPosition())),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 11))) });
	ExpectTokenInformations(
		L";16_F.A_E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::EXPONENTIAL, StreamString(L"16_F.A_E+1", StreamPosition(1, 2))) });
}

TEST(exponential_token, not_determining_if_no_underscore_before_exponent_character)
{
	ExpectTokenInformations(
		L"1E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 3))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L"1E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString(L"-", StreamPosition(1, 3))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 4))) });
	ExpectTokenInformations(
		L"1.1E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L"1.1E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString(L"-", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L"2_1E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L"2_1E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString(L"-", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L"2_1.0E+1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"2_1.0E-1",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0E", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString(L"-", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L"16_F.AE+1",
		{ TokenInformation(Token::FLOAT, StreamString(L"16_F.AE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"16_F.AE-1",
		{ TokenInformation(Token::FLOAT, StreamString(L"16_F.AE", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString(L"-", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"16_F.0AE+1",
		{ TokenInformation(Token::FLOAT, StreamString(L"16_F.0AE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L"16_F.0AE-1",
		{ TokenInformation(Token::FLOAT, StreamString(L"16_F.0AE", StreamPosition())),
		  TokenInformation(Token::MINUS, StreamString(L"-", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });

	ExpectTokenInformations(
		L" 1E+1 ",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		L";1E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 5))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 6))) });
	ExpectTokenInformations(
		L" 2_1E+3 ",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"3", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";2_1E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"3", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L" 16_FE+1 ",
		{ TokenInformation(Token::INTEGER, StreamString(L"16_FE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L";16_FE+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"16_FE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 9))) });

	ExpectTokenInformations(
		L" 1.1E+1 ",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";1.1E+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L" 2_1.1E+3 ",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"3", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L";2_1.1E+3;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"3", StreamPosition(1, 9))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L" 16_F.AE+1 ",
		{ TokenInformation(Token::FLOAT, StreamString(L"16_F.AE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L";16_F.AE+1;",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"16_F.AE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 11))) });

	ExpectTokenInformations(
		L"1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 3))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 4))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		L";1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 4))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 5))) });
	ExpectTokenInformations(
		L" 2_1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L";2_1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"2_1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L"16_FE+1;",
		{ TokenInformation(Token::INTEGER, StreamString(L"16_FE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 8))) });
	ExpectTokenInformations(
		L";16_FE+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::INTEGER, StreamString(L"16_FE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 7))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 8))) });

	ExpectTokenInformations(
		L"1.1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"1.1E", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 5))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 6))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L";1.1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 6))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 7))) });
	ExpectTokenInformations(
		L" 2_1.1E+1;",
		{ TokenInformation(Token::UNKNOWN, StreamString(L"2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L";2_1.1E+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::UNKNOWN, StreamString(L"2_1.1E", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))) });
	ExpectTokenInformations(
		L"16_F.AE+1;",
		{ TokenInformation(Token::FLOAT, StreamString(L"16_F.AE", StreamPosition())),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 8))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 9))),
		  TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition(1, 10))) });
	ExpectTokenInformations(
		L";16_F.AE+1",
		{ TokenInformation(Token::SEMICOLON, StreamString(L";", StreamPosition())),
		  TokenInformation(Token::FLOAT, StreamString(L"16_F.AE", StreamPosition(1, 2))),
		  TokenInformation(Token::PLUS, StreamString(L"+", StreamPosition(1, 9))),
		  TokenInformation(Token::INTEGER, StreamString(L"1", StreamPosition(1, 10))) });
}

TEST(exponential_token, not_determining_if_not_completed)
{
	ExpectTokenInformations(L"1_E+", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+", StreamPosition())) });
	ExpectTokenInformations(L"1_E-", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E-", StreamPosition())) });
	ExpectTokenInformations(L"1.1_E+", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1_E+", StreamPosition())) });
	ExpectTokenInformations(L"1.1_E-", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1_E-", StreamPosition())) });
	ExpectTokenInformations(L"2_1_E+", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1_E+", StreamPosition())) });
	ExpectTokenInformations(L"2_1_E-", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1_E-", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E+", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0_E+", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E-", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0_E-", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E+", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.A_E+", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E-", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.A_E-", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E+", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.0A_E+", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E-", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.0A_E-", StreamPosition())) });

	ExpectTokenInformations(L"1_E", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E", StreamPosition())) });
	ExpectTokenInformations(L"1.1_E", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1_E", StreamPosition())) });
	ExpectTokenInformations(L"2_1_E", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1_E", StreamPosition())) });
	ExpectTokenInformations(L"2_1.0_E", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0_E", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.A_E", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.0A_E", StreamPosition())) });

	ExpectTokenInformations(L"1_", { TokenInformation(Token::UNKNOWN, StreamString(L"1_", StreamPosition())) });
	ExpectTokenInformations(L"1.1_", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1_", StreamPosition())) });
	ExpectTokenInformations(L"2_1_", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1_", StreamPosition())) });
	ExpectTokenInformations(L"2_1.0_", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0_", StreamPosition())) });
	ExpectTokenInformations(L"16_F.A_", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.A_", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.0A_", StreamPosition())) });

	ExpectTokenInformations(L"1_E+1.", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E+1.", StreamPosition())) });
	ExpectTokenInformations(L"1_E-1.", { TokenInformation(Token::UNKNOWN, StreamString(L"1_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1_E+1.", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		L"1.1_E-1.", { TokenInformation(Token::UNKNOWN, StreamString(L"1.1_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1_E+1.", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1_E-1.", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E+1.", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		L"2_1.0_E-1.", { TokenInformation(Token::UNKNOWN, StreamString(L"2_1.0_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E+1.", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.A_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.A_E-1.", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.A_E-1.", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E+1.", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.0A_E+1.", StreamPosition())) });
	ExpectTokenInformations(
		L"16_F.0A_E-1.", { TokenInformation(Token::UNKNOWN, StreamString(L"16_F.0A_E-1.", StreamPosition())) });
}

TEST(exponential_token, not_determining_if_part_of_string_literal)
{
	ExpectTokenInformations(
		LR"("1_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 1_E+1 ")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";1_E+1;")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("2_1_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("2_1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 2_1_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 2_1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";2_1_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";2_1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("16_F_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("16_F_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 16_F_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 16_F_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";16_F_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";16_F_E+1;")", StreamPosition())) });

	ExpectTokenInformations(
		LR"("1.1_E+1")", { TokenInformation(Token::STRING_LITERAL, StreamString(LR"("1.1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 1.1_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 1.1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";1.1_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";1.1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("2_1.1_E+1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("2_1.1_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 2_1.1_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 2_1.1_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";2_1.1_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";2_1.1_E+1;")", StreamPosition())) });
	ExpectTokenInformations(
		LR"("16_F.A_E+1")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"("16_F.A_E+1")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(" 16_F.A_E+1 ")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(" 16_F.A_E+1 ")", StreamPosition())) });
	ExpectTokenInformations(
		LR"(";16_F.A_E+1;")",
		{ TokenInformation(Token::STRING_LITERAL, StreamString(LR"(";16_F.A_E+1;")", StreamPosition())) });
}

TEST(exponential_token, not_determining_if_part_of_comment)
{
	ExpectTokenInformations(
		L"//1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//2_1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 2_1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 2_1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;2_1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;2_1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//16_F_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//16_F_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 16_F_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 16_F_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;16_F_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;16_F_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//1.1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 1.1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;1.1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;1.1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1.1_E+1 */", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1.1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1.1_E+1;*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1.1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 1.1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;1.1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;1.1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//2_1.1_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//2_1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 2_1.1_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 2_1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;2_1.1_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;2_1.1_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1.1_E+1 */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1.1_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1.1_E+1;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1.1_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 2_1.1_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 2_1.1_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*2_1.1_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*2_1.1_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;2_1.1_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;2_1.1_E+1;", StreamPosition())) });

	ExpectTokenInformations(
		L"//16_F.A_E+1", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"// 16_F.A_E+1 ", { TokenInformation(Token::LINE_COMMENT, StreamString(L"// 16_F.A_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"//;16_F.A_E+1;", { TokenInformation(Token::LINE_COMMENT, StreamString(L"//;16_F.A_E+1;", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F.A_E+1 */",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F.A_E+1 */", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A_E+1*/", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A_E+1*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F.A_E+1;*/",
		{ TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F.A_E+1;*/", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/* 16_F.A_E+1 ", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/* 16_F.A_E+1 ", StreamPosition())) });
	ExpectTokenInformations(
		L"/*16_F.A_E+1", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*16_F.A_E+1", StreamPosition())) });
	ExpectTokenInformations(
		L"/*;16_F.A_E+1;", { TokenInformation(Token::BLOCK_COMMENT, StreamString(L"/*;16_F.A_E+1;", StreamPosition())) });
}
