#include <iostream>
#include <memory>
#include <fstream>
#include <stdexcept>
using namespace std;

struct FileFinalizer {
  void operator()(std::ofstream* filePtr) {
    if (filePtr->is_open()) {
        std::cout << "Cerrando archivo..." << std::endl;
        filePtr->close();
    }
    std::cout << "Eliminando ofstream..." << std::endl;
    delete filePtr;
  }
};

using spFile = std::shared_ptr<ofstream>;
int main() {
  std::string filename = "archivo.txt";
  spFile file(new ofstream(filename), FileFinalizer()); 
  try{
    file->is_open();
    *file << "Alonso god" << std::endl;
    std::string line = "";
    if (line == "") {
        throw std::runtime_error("Linea vacia encontrada");
    }
    *file << line << std::endl;
    file->close();
  }
  catch(const std::exception& e){
    std::cout << "Excepcion capturada: " << e.what() << std::endl;
    file.reset();
  }
  return 0;
}
