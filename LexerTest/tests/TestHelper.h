#ifndef PROJECT_TESTHELPER_H
#define PROJECT_TESTHELPER_H

#include <string>
#include <vector>

class TokenInformation;

void ExpectTokenInformations(std::string const & str, std::vector<TokenInformation> const & expectedTokenInformations);

#endif //PROJECT_TESTHELPER_H
