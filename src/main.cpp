#include "../include/htmlConvert.hpp"
#include "../include/htmlGet.hpp"
#include "../include/htmlParser.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
/* [x]Get web page ->
 * [x]Parse web page ->
 * [x]Get <a> ->
 * [ ]Convert HTML into PDF.
 * */
int main(int argc, char **argv) {
  HtmlParser parser;
  HtmlGet gethtml = HtmlGet();
  HtmlConvert convert = HtmlConvert();
  std::string htmlData;
  std::string website = argv[1];

  if (argc < 2) {
    std::cerr << "No Argument Provieded " << std::endl;
    std::cerr << "Usage: web2pdf <website link> " << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "Web2Pdf!" << std::endl;
  // Get web page
  gethtml.HtmlGetter(website, htmlData);
  std::vector<char> parsedUl = parser.ulParser(htmlData);
  std::vector<std::string> parsedLi = parser.liParser(parsedUl);
  std::vector<std::string> parsedA = parser.aParser(parsedLi);
  std::vector<std::string> links = parser.validateLink(parsedA, website);
  std::vector<std::string> pages = gethtml.HtmlGetter(links);
  int res = convert.htmlToPdf(pages);

  if (!std::filesystem::is_directory("./tmp/")) {
    std::filesystem::create_directory("./tmp/");
  }

  std::ofstream htmlfile;
  htmlfile.open("./tmp/htmlpage.html");
  htmlfile << htmlData;
  htmlfile.close();
  return EXIT_SUCCESS;
}
