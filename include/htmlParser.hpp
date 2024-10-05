#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <vector>
class HtmlParser {
public:
  HtmlParser();
  std::vector<char> ulParser(std::string htmlData);
  std::vector<std::string> liParser(std::vector<char> parsedUl);
  std::vector<std::string> aParser(std::vector<std::string> parsedUl);
  std::vector<std::string> validateLink(std::vector<std::string> links,
                                        std::string baseurl);

private:
  char peek(std::string htmlData);
};

#endif // HTMLPARSER_H
