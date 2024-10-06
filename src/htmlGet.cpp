#include "../include/htmlGet.hpp"
#include <curl/curl.h>
#include <iostream>
#include <string>

HtmlGet::HtmlGet() { this->curl = curl_easy_init(); }
void HtmlGet::HtmlGetter(std::string website, std::string &htmlData) {
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlData);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed : " << curl_easy_strerror(res)
                << std::endl;
    }
  }
}

std::vector<std::string>
HtmlGet::HtmlGetter(std::vector<std::string> websites) {
  std::vector<std::string> pages;
  std::string page_content;
  std::cout << "Getting Webpages : " << std::endl;
  for (int i = 0; i < websites.size(); i++) {
    std::cout << "Getting Page " << websites[i];
    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, websites[i].c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &page_content);
      res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed : " << curl_easy_strerror(res)
                  << std::endl;
      } else {
        pages.push_back(page_content);
        page_content = "";
        std::cout << " Done" << std::endl;
      }
    }
  }
  return pages;
}
size_t HtmlGet::WriteCallback(void *contents, size_t size, size_t nmemb,
                              void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}
