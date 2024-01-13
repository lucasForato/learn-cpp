#include <iostream>
#include <string>

using namespace std;

int main() {

  cout << "What is the language of your greeting?" << endl
       << "Options include: (EN, PT, GR, FR)" << endl;

  string lang;
  cin >> lang;

  if (lang == "EN") {
    cout << "Hello!" << endl;
    return 0;
  }

  if (lang == "PT") {
    cout << "Olá" << endl;
    return 0;
  }

  if (lang == "GR") {
    cout << "Hallo!" << endl;
    return 0;
  }

  if (lang == "FR") {
    cout << "Bonjour" << endl;
    return 0;
  }

  cerr << "Invalid language." << endl;
  return 400;
}
