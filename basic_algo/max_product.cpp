#include <iostream> 
#include <vector> 
#include <string>
#include <limits> 
using namespace std;

auto find_max_product_subarray(std::vector<int> &vec) { 
    int start = 0; 
    int tmp = 0; 
    int end = 0; 
    int currProd = 0; 
    int maxProd = std::numeric_limits<int>::min(); 
    
    for (int i = 0; i < vec.size(); i++) { 
        currProd *= vec[i]; 
        
        if (currProd == 0) { 
            currProd = 1; 
            tmp = i+1; 
        } 
        else if (currProd > maxProd) { 
            maxProd = currProd; 
            start = tmp; 
            end = i; 
        } 
    } 
    
    currProd = 1; 
    tmp = vec.size() - 1; 
    
    for (int i = vec.size() - 1; i >= 0; i--) { 
        currProd *= vec[i]; 
        
        if (currProd == 0) { 
            currProd = 1; 
            tmp = i-1; 
        } 
        else if (currProd > maxProd) { 
            maxProd = currProd; 
            start = i; 
            end = tmp; 
        } 
    } 
    
    return std::make_pair(start, end); 
} 

int main() {

  vector<int> vec1 = {6, -3, -10, 0, 2};
  auto p1 = find_max_product_subarray(vec1); 
  cout << "start: " << p1.first << ", end: " << p1.second << std::endl; 

  vector<int> vec2 = {-1, -3, -10, 0, 60};
  auto p2 = find_max_product_subarray(vec2); 
  cout << "start: " << p2.first << ", end: " << p2.second << std::endl; 

  vector<int> vec3 = {-2, -3, 0, -2, -40};
  auto p3 = find_max_product_subarray(vec3); 
  cout << "start: " << p3.first << ", end: " << p3.second << std::endl; 

  vector<int> vec4 = {1, -2, -3, 0, 7, -8, -2};
  auto p4 = find_max_product_subarray(vec4); 
  cout << "start: " << p4.first << ", end: " << p4.second << std::endl; 

  vector<int> vec5 = {2, 2, -3, 0, 1, 5, 10, 2, -3, 0};
  auto p5 = find_max_product_subarray(vec5); 
  cout << "start: " << p5.first << ", end: " << p5.second << std::endl; 

  vector<int> vec6 = {-1, -3, -10, 0, 60};
  auto p6 = find_max_product_subarray(vec6); 
  cout << "start: " << p6.first << ", end: " << p6.second << std::endl; 

  vector<int> vec7 = {6, -3, 0, -10, 3, -60, -40, 2};
  auto p7 = find_max_product_subarray(vec7); 
  cout << "start: " << p7.first << ", end: " << p7.second << std::endl; 

  vector<int> vec8 = {6, 0, -5, 1, -10, 3, -6, 4, -4};
  auto p8 = find_max_product_subarray(vec8); 
  cout << "start: " << p8.first << ", end: " << p8.second << std::endl; 

  vector<int> vec9 = {2,1}; 
  auto p9 = find_max_product_subarray(vec9); 
  cout << "start: " << p9.first << ", end: " << p9.second << std::endl; 
  
  vector<int> vec10 = {1,0,-2,-2,-3}; 
  auto p10 = find_max_product_subarray(vec10); 
  cout << "start: " << p10.first << ", end: " << p10.second << std::endl; 

  return 0;
}