#ifndef LEXERTEST_TESTHELPER_H
#define LEXERTEST_TESTHELPER_H

#include <string>
#include <vector>

class TokenInformation;

void ExpectTokenInformations(std::string const & str, std::vector<TokenInformation> const & expectedTokenInformations);

#endif
