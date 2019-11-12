#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

int main (int, char **) {
  std::vector<int> v;
  int input;

  while (std::cin >> input)
    v.push_back (input);

  std::sort(v.begin(), v.end());

  std::copy (v.begin(), v.end(),
    std::ostream_iterator<int> (std::cout, "\n"));

  for (size_t i = 0; i < v.size(); i++)
	  std::cout << v[i] << std::endl;
	
  for (auto it = v.begin(); it != v.end(); ++it)
	std::cout << *it << std::endl;

  for (auto e : v)
	std::cout << e << std::endl;
  

  return 0;
}