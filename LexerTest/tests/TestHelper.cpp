#include "TestHelper.h"
#include "Lexer.h"
#include "Token/TokenInformation/TokenInformation.h"
#include "gtest/gtest.h"
#include <sstream>

void ExpectTokenInformations(std::wstring const & str, std::vector<TokenInformation> const & expectedTokenInformations)
{
	std::wstringstream stringStream(str);
	Lexer lexer(stringStream);
	size_t i = 0;
	TokenInformation tokenInformation;
	while (lexer.GetNextTokenInformation(tokenInformation))
	{
		EXPECT_LT(i, expectedTokenInformations.size());
		TokenInformation expectedTokenInformation = expectedTokenInformations.at(i);
		Token expectedToken = expectedTokenInformation.GetToken();
		StreamString expectedStreamString = expectedTokenInformation.GetTokenStreamString();
		EXPECT_EQ(
			TokenExtensions::ToString(tokenInformation.GetToken()), TokenExtensions::ToString(expectedToken));
		EXPECT_EQ(
			tokenInformation.GetTokenStreamString().string, expectedStreamString.string);
		EXPECT_EQ(
			tokenInformation.GetTokenStreamString().position.GetLine(), expectedStreamString.position.GetLine());
		EXPECT_EQ(
			tokenInformation.GetTokenStreamString().position.GetColumn(), expectedStreamString.position.GetColumn());
		++i;
	}
	EXPECT_EQ(i, expectedTokenInformations.size());
}
