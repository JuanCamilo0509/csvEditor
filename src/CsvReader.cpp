#include "CsvReader.hpp"

void csvReader::setHeaders() {
  ifstream file(path);
  string line;
  if (file.is_open()) {
    if (std::getline(file, line)) {
      size_t start = 0;
      size_t end = 0;

      while ((end = line.find(",", start)) != string::npos) {
        headers.headers.push_back(line.substr(start, end - start));
        start = end + 1;
      }

      headers.headers.push_back(line.substr(start));
      headers.count = headers.headers.size();
    };
  };
};

vector<double> csvReader::getColumn(string columnName) {
  for (int i = 0; i < headers.count; i++) {
    if (headers.headers[i] == columnName)
      return columns[i].data;
  }
  throw std::invalid_argument("The column name doesn't exist");
};

Headers csvReader::getHeaders() { return headers; }

void csvReader::readCsv() {
  ifstream file(path);
  string line;
  // Saltar headers
  getline(file, line);
  while (std::getline(file, line)) {
    size_t start = 0;
    size_t end = 0;
    for (int i = 0; i < headers.count; i++) {
      end = line.find(",", start);
      string token;
      if (end == string::npos)
        token = line.substr(start);
      else
        token = line.substr(start, end - start);
      columns[i].data.push_back(stod(token));
      if (end == string::npos)
        break;
      start = end + 1;
    }
  }
};
