#ifndef HTMLGET_H
#define HTMLGET_H

#include <curl/curl.h>
#include <curl/header.h>
#include <string>
#include <vector>
class HtmlGet {
public:
  CURL *curl;
  CURLcode res;
  HtmlGet();
  void HtmlGetter(std::string website, std::string &htmlData);
  std::vector<std::string> HtmlGetter(std::vector<std::string> websites);
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              void *userp);
};
#endif // HTMLGET_H
