#include "../include/htmlParser.hpp"
#include <iostream>
#include <vector>

HtmlParser::HtmlParser() {}

std::vector<char> HtmlParser::ulParser(std::string htmlData) {
  std::vector<char> parsedUl;
  size_t ulStart = 0, ulEnd = 0;
  std::cout << "Hello from UL Parser" << std::endl;
  while ((ulStart = htmlData.find("<ul", ulStart)) != std::string::npos ||
         (ulStart = htmlData.find("<ol", ulStart)) != std::string::npos) {
    ulEnd = htmlData.find("</ul>", ulStart);
    if (ulEnd == std::string::npos) {
      ulEnd = htmlData.find("</ol>", ulStart);
    }
    if (ulEnd != std::string::npos) {
      size_t contentStart = htmlData.find('>', ulStart) + 1;
      std::string content = htmlData.substr(contentStart, ulEnd - contentStart);
      parsedUl.insert(parsedUl.end(), content.begin(), content.end());
      ulStart = ulEnd + 5;
    } else {
      break;
    }
  }
  return parsedUl;
}

std::vector<std::string> HtmlParser::liParser(std::vector<char> parsedUl) {
  std::vector<std::string> parsedLi;
  std::string ulString(parsedUl.begin(), parsedUl.end());
  std::string liString;
  size_t liStart = 0, liEnd = 0;
  std::cout << "Hello from Li parser" << std::endl;
  while ((liStart = ulString.find("<li", liStart)) != std::string::npos) {
    liEnd = ulString.find("</li>", liStart);
    if (liEnd != std::string::npos) {
      size_t contentStart = ulString.find('>', liStart) + 1;
      std::string liContent =
          ulString.substr(contentStart, liEnd - contentStart);
      parsedLi.push_back(liContent);
      liStart = liEnd + 5;
    } else {
      break;
    }
  }
  return parsedLi;
}
std::vector<std::string>
HtmlParser::aParser(std::vector<std::string> parsedLi) {
  std::vector<std::string> parsedA;
  std::string aString;
  std::vector<std::string> links;
  std::cout << "Starting aParser" << std::endl;
  for (const auto &li : parsedLi) {
    size_t pos = 0;
    while ((pos = li.find("<a", pos)) != std::string::npos) {
      size_t endPos = li.find("</a>", pos);
      if (endPos != std::string::npos) {
        aString = li.substr(pos, endPos + 4 - pos);
        parsedA.push_back(aString);
        pos = endPos + 4;
      } else {
        break;
      }
    }
  }

  std::cout << "Finished extracting links." << std::endl;
  std::cout << "Starting to extract href." << std::endl;
  std::string link;
  for (const auto &a : parsedA) {
    size_t pos = 0;
    while ((pos = a.find("href=\"", pos)) != std::string::npos) {
      pos += 6;
      size_t endPos = a.find('"', pos);
      if (endPos != std::string::npos) {
        link = a.substr(pos, endPos - pos);
        links.push_back(link);
        pos = endPos + 1;
      } else {
        break;
      }
    }
  }
  return links;
}

std::vector<std::string>
HtmlParser::validateLink(std::vector<std::string> links, std::string baseurl) {
  std::vector<std::string> newLinks;
  for (int i = 0; i < links.size(); i++) {
    if ((links[i].find("https://" || "http://"))) {
      newLinks.push_back(baseurl + links[i]);
    } else {
      newLinks.push_back(links[i]);
      continue;
    }
  }
  return newLinks;
}
