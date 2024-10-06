#ifndef HTMLCONVERT_H
#define HTMLCONVERT_H

#include <string>
#include <vector>
class HtmlConvert {
public:
  int status;
  HtmlConvert();
  int htmlToPdf(std::vector<std::string> webpages);
};

#endif // HTMLCONVERT_H
