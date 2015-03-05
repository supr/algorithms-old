#include <iostream> 
#include <vector> 
#include <string> 
#include <cstring> 
#include <chrono> 
#include <array> 
using namespace std; 

#define BENCHMARKING 
const int test_len = 1000; 
  
std::ostream& operator << (std::ostream& os, const std::vector<char>& v) 
{ 
    os << "["; 
    for (typename std::vector<char>::const_iterator ii = v.begin(); ii != v.end(); ++ii) 
    { 
        os << *ii; 
    } 
    os << "]"; 
    return os; 
} 
  
class BufferedWrite { 
private: 
    const unsigned int buffer_size; 
    vector<char> buffer; 
    unsigned int buffer_index; 
    
    void flush() { 
        //cout << buffer << endl; 
        buffer_index = 0; 
    } 
  
public: 
    BufferedWrite(unsigned int buffer_size_): buffer(buffer_size_, 0), 
                                              buffer_size(buffer_size_), 
                                              buffer_index(0) {} 
  
    void write(const string &str) { 
        unsigned int bytes_to_copy = str.size(); 
        unsigned int copy_index = 0; 
        
        while (bytes_to_copy > 0) { 
            unsigned int size = 0; 
            unsigned int free_space = buffer_size - buffer_index; 
            
            if (bytes_to_copy >= free_space) { 
                size = free_space; 
            } 
            else { 
                size = bytes_to_copy; 
            } 
            
            memcpy(&buffer[buffer_index], (char*)(&str[copy_index]), size); 
            
            buffer_index += size; 
            copy_index += size; 
            bytes_to_copy -= size; 
            
            if (buffer_index == buffer_size) { 
                flush(); 
            } 
        } 
    } 
}; 
  
class random_text_generator { 
public: 
    random_text_generator(const std::string& str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") 
    : m_str(str) { 
        std::srand(std::time(0)); 
    }   
    
    std::string operator ()(std::size_t min_len, std::size_t max_len) { 
        std::size_t len = min_len + rand() % (max_len - min_len); 
        std::string seq; 
        std::size_t siz = m_str.size(); 
        
        if(siz) { 
            while(len--) { 
                seq.push_back(m_str[rand() % siz]); 
            } 
        } 
        
        return seq; 
    } 
    
private:         
    std::string m_str; 
}; 
  
int main() { 
    BufferedWrite w(1024); 
    random_text_generator rtg; 
    vector<string> string_vec(test_len); 
    
    for (int i = 0; i < test_len; i++) { 
        string_vec[i] = rtg(100, 200); 
    } 
    
#ifdef BENCHMARKING 
    auto start = std::chrono::steady_clock::now(); 
#endif 
  
    for (int i = 0; i < test_len; i++) { 
        w.write(string_vec[i]); 
    } 
    
#ifdef BENCHMARKING 
    auto end = std::chrono::steady_clock::now(); 
    auto diff = end - start; 
    std::cout << "\nbenchmark: " << std::chrono::duration <double, std::milli> (diff).count() << "\n\n"; 
#endif  
  
    return 0; 
}