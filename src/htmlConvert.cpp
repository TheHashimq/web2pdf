#include "../include/htmlConvert.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <wkhtmltox/pdf.h>

HtmlConvert::HtmlConvert() {
  status = wkhtmltopdf_init(0);
  if (status != 1) {
    std::cerr << "Failed to initialize wkhtmltopdf!" << std::endl;
  }
}
int HtmlConvert::htmlToPdf(std::vector<std::string> pages) {
  for (int i = 0; i < pages.size(); i++) {
    std::ofstream htmlfile;
    htmlfile.open("./tmp/htmlpage" + std::to_string(i) + ".html");
    htmlfile << pages[i];
    htmlfile.close();
  }

  std::string command = "wkhtmltopdf ./tmp/htmlpage.html ";
  for (int i = 0; i < pages.size(); i++) {
    command += "./tmp/htmlpage" + std::to_string(i) + ".html ";
  }
  command += "output.pdf";
  std::cout << command;
  int result = std::system(command.c_str());
  if (!result) {
    std::cerr << "Failed to convert" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "Converted Enjoy" << std::endl;
  return EXIT_SUCCESS;
}
