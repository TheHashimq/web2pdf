#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>

/* [ ]Get web page ->
 * [ ]Parse webpage ->
 * [ ]Get <a> ->
 * [ ]Make a tree ->
 * [ ]Use dfs to parse the tree ->
 * [ ]Convert html into pdf.
 *
 * */
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}
int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "No Argument Provieded " << std::endl;
    std::cerr << "Usage: web2pdf <website link> " << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "Web2Pdf!" << std::endl;
  std::string website = argv[1];

  std::cout << website << std::endl;

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
  std::ofstream htmlfile;
  htmlfile.open("./tmp/htmlpage.html");
  htmlfile << htmlData;
  htmlfile.close();
  return EXIT_SUCCESS;
}
