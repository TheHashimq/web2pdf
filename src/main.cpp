#include "../include/htmlParser.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <filesystem>
#include <fstream>
#include <iostream>

/* [x]Get web page ->
 * [x]Parse web page ->
 * [x]Get <a> ->
 *
 * I don't think so {
 *    [ ]Make a tree ->
 *    [ ]Use depth first search to parse the tree ->
 * }
 * [ ]Convert HTML into PDF.
 *
 * */
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}
int main(int argc, char **argv) {
  HtmlParser parser;
  if (argc < 2) {
    std::cerr << "No Argument Provieded " << std::endl;
    std::cerr << "Usage: web2pdf <website link> " << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "Web2Pdf!" << std::endl;
  std::string website = argv[1];

  std::cout << website << std::endl;

  if (!std::filesystem::is_directory("./tmp/")) {
    std::filesystem::create_directory("./tmp/");
  }
  // Get web page
  CURL *curl;
  CURLcode res;
  std::string htmlData;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlData);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed : " << curl_easy_strerror(res)
                << std::endl;
    }
  }

  std::vector<char> parsedUl = parser.ulParser(htmlData);
  std::vector<std::string> parsedLi = parser.liParser(parsedUl);
  std::vector<std::string> parsedA = parser.aParser(parsedLi);
  std::vector<std::string> links = parser.validateLink(parsedA, website);
  for (int i = 0; i < links.size(); i++) {
    std::cout << links[i] << std::endl;
  }

  std::ofstream htmlfile;
  htmlfile.open("./tmp/htmlpage.html");
  htmlfile << htmlData;
  htmlfile.close();
  return EXIT_SUCCESS;
}
