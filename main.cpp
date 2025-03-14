#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
namespace helpers {

std::vector<int> ReadVector(std::ifstream& stream);
std::map<std::string, int> ReadMap(std::ifstream& stream);

void SyncContainers(std::vector<int>& vec, std::map<std::string, int>& mp);
}  // namespace helpers

std::ostream& operator<<(std::ostream& stream, const std::vector<int>& vec) {
  for (int value : vec) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
  return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const std::map<std::string, int>& mp) {
  for (auto& [k, v] : mp) {
    std::cout << k << " " << v << " ";
  }
  std::cout << std::endl;
  return stream;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 0;
  }

  std::ifstream stream{argv[1]};
  if (!stream) {
    std::cout << "Can't open file" << std::endl;
    return 0;
  }

  std::vector<int> vec = helpers::ReadVector(stream);
  std::map<std::string, int> mp = helpers::ReadMap(stream);
  helpers::SyncContainers(vec, mp);

  std::cout << vec << mp;

  return 0;
}

namespace helpers {

std::vector<int> ReadVector(std::ifstream& stream) {
  size_t vector_size{0};
  stream >> vector_size;
  std::vector<int> vec(vector_size);
  for (size_t i = 0; i < vector_size; i++) {
    stream >> vec[i];
  }
  return vec;
}

std::map<std::string, int> ReadMap(std::ifstream& stream) {
  size_t map_size{0};
  stream >> map_size;
  std::map<std::string, int> mp;
  for (size_t i = 0; i < map_size; i++) {
    std::string key{""};
    int value{};
    stream >> key >> value;
    mp[key] = value;
  }
  return mp;
};

void SyncContainers(std::vector<int>& vec, std::map<std::string, int>& mp) {
  std::bitset<16> vec_values{};
  std::bitset<16> mp_values{};
  for (int value : vec) {
    vec_values.set(value);
  }

  for (auto it = mp.begin(); it != mp.end();) {
    if (!vec_values.test(it->second)) {
      it = mp.erase(it);
    } else {
      mp_values.set(it->second);
      it++;
    }
  }

  vec.erase(std::remove_if(
                vec.begin(), vec.end(),
                [&mp_values](int value) { return !(mp_values.test(value)); }),
            vec.end());
}

}  // namespace helpers