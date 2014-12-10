/*
Given two English words of the same length, say, "HEAD" and "TAIL", come up with a 
sequence of valid English words, starting with "HEAD", and ending with "TAIL", such 
that each word is formed by changing a single letter of the previous word.
*/

#include <iostream> 
#include <string> 
#include <cctype> 
#include <vector> 
#include <iterator> 
#include <fstream> 
#include <unordered_map> 
#include <unordered_set> 
#include <cstring> 
#include <queue> 
  
  
// Erst einmal jede Menge Framework, hauptsächlich Boilerplatecode: 
// -Ein Klasse für Wörter mit fester Länge und nur aus Buchstaben bestehend. Groß-/Kleinschreibung ist egal. 
// -Eine spezialisierte Hashfunktion dafür. 
// -Ein- und Ausgabe für diese Klasse. 
template <unsigned N> class N_Letter_Word 
{ 
  char word[N]; 
  
public: 
  // Um den Graph zu bauen, brauchen wir später ein Sonderzeichen als Platzhalter: 
  void set_placeholder(unsigned index) 
  { 
    word[index] = 'Z' + 1; 
  } 
  
  char operator[] (unsigned index) const { return word[index]; } 
  
  friend bool operator==(const N_Letter_Word<N>& lhs, const N_Letter_Word<N>& rhs) 
  { 
    return !memcmp(lhs.word, rhs.word, N); 
  } 
  
  friend std::istream& operator>>(std::istream &in, N_Letter_Word<N> &w) 
  { 
    std::string word; 
    in >> word; 
    if (word.size() == N) 
      { 
        for(unsigned i = 0; i < N; ++i) 
          { 
            if(std::isalpha(word[i])) 
              { 
                w.word[i] = std::toupper(word[i]); 
              } 
            else 
              { 
                in.setstate(std::ios::failbit); 
                return in; 
              } 
          } 
      } 
    else 
      in.setstate(std::ios::failbit); 
    return in; 
  } 
  friend std::ostream& operator<<(std::ostream& out, const N_Letter_Word<N> &w) 
  { 
    return out.write(w.word, N); 
  } 
}; 
  
namespace std 
{ 
  template <unsigned N> struct hash<N_Letter_Word<N> > 
  { 
    std::size_t operator()(const N_Letter_Word<N>& word) const 
    { 
      std::size_t hash = 0; 
      std::size_t prod = 1; 
      for(unsigned i = 0; i < N; ++i) 
        { 
          hash += prod * (word[i] - 'A'); 
          prod *= 27; 
        } 
      return hash; 
    } 
  }; 
} 
  
  
// Hier geht der eigentlich relevante Code los. 
// Die Suchfunktion ist eine Klasse, damit man nicht bei jeder Suche den Graph 
// und das Wörterbuch neu aufbauen muss. 
  
template<unsigned N> class Word_Ladder_Searcher 
{ 
  std::vector<N_Letter_Word<N> > dictionary; 
  std::unordered_map<N_Letter_Word<N>, std::size_t> dictionary_index; 
  std::unordered_map<std::size_t, std::vector<std::size_t> > graph; 
public: 
  template<typename Iterator> Word_Ladder_Searcher<N>(Iterator begin, Iterator end) 
  : dictionary(begin, end) 
  { 
    // Baue den Graph auf. Zuerst werden alle Wörter die sich nur um einen Buchstaben unterscheiden 
    // gemeinsam in eine List gepackt. Dies wird erreicht, indem man eine 
    // map aufbaut, in der die Kategorien die Wörter sind, wobei jeweils ein 
    // Buchstabe durch einen Platzhalter ersetzt wurde. Wörter, die sich nur an der 
    // Stelle unterscheiden, wo der Platzhalter ist, landen so in der gleichen Kategorie. 
    // Alle Wörter in einer Kategorie sind dann durch genau eine Ersetzung verbunden 
    // (nämlich an der Stelle, wo der Platzhalter steht). 
    std::unordered_map<N_Letter_Word<N>, std::vector<std::size_t> > words; 
    for (std::size_t i = 0; i < dictionary.size(); ++i) 
      { 
        for(unsigned j = 0; j < N; ++j) 
          { 
            N_Letter_Word<N> word = dictionary[i]; 
            word.set_placeholder(j); 
            // Es werden nicht die Worte selber gespeichert. Das ganze Programm arbeitet 
            // aus Effizienzgründen nur mit der Position eines Wortes in der Wörterliste 
            words[word].push_back(i); 
          } 
        // Nebenbei noch einen Index anlegen, damit man später zu einem Wort schnell 
        // die Position im Wörterbuch finden kann, ohne das ganze Buch durchsuchen zu müssen. 
        dictionary_index[dictionary[i]] = i; 
      } 
    // Die Kategorien wurden erzeugt. Der Graph wird durch eine Adjazenzliste 
    // dargestellt. Zu jedem Vertex (also jedem Wort) gehört eine Liste benachbarter 
    // Vertices/Worte. 
    for (auto const& bucket: words) 
      { 
        const auto& wordlist = bucket.second; 
        for (auto word1 : wordlist) 
          for (auto word2 : wordlist) 
            { 
              if (word1 != word2) 
                graph[word1].push_back(word2); 
            } 
      } 
  } 
  
  // Die eigentliche Suchfunktion. Sucht von begin nach end und schreibt das 
  // Ergebnis in out. 
  template<typename Iterator> Iterator search(const N_Letter_Word<N>& begin_word, const N_Letter_Word<N>& end_word, Iterator out) 
  { 
    std::size_t begin, end; 
    { 
      // Wenn die Suchworte gar nicht existieren, sparen wir uns die Suche: 
      auto b_it = dictionary_index.find(begin_word); 
      if (b_it == dictionary_index.end()) return out; 
      auto e_it = dictionary_index.find(end_word); 
      if (e_it == dictionary_index.end()) return out; 
      
      begin = e_it->second;  // Wir suchen von hinten nach vorne, um hinterher leichter das Ergbenis ablesen zu können 
      end = b_it->second;    // und dabei die Reihenfolge zu erhalten, die der Nutzer erwartet. 
    } 
  
    // Nun wird eine Breitensuche durchgeführt. Ganz naiver Algorithmus, 
    // direkt von Wikipedia übernommen. 
  
    // Als Ergebnis merken wir uns zu jedem Wort den Vorgänger bei der Suche. 
    // Als Vorgänger des Startwortes nehmen wir den Sonderwert -1. 
    std::unordered_map<std::size_t, std::size_t> bfs_tree; 
    bfs_tree[begin] = -1; 
  
    // Gib der Warteschlange der zu besuchenden Vertices den Startvertex als Anfangswert: 
    std::queue<std::size_t> queue; 
    queue.push(begin); 
  
    while(!queue.empty())  // Solange noch Vertices zu besuchen sind... 
      { 
        auto current_vertex = queue.front();  // ...nehme den Vertex... 
        if (current_vertex == end) // Falls wir beim Ziel angekommen sind, brechen wir sofort ab 
          { 
            break; 
          } 
        for (auto adjacent_vertex : graph[current_vertex])  // ...und untersuche alle Nachbarn... 
          { 
            if(!bfs_tree.count(adjacent_vertex))   // ...teste, ob wir den Nachbar schon besucht haben... 
              { 
                bfs_tree[adjacent_vertex] = current_vertex;  // ...falls nicht, füge ihn der Ergebnisliste hinzu.... 
                                                             // ...Sein Vorgänger ist der aktuelle Vertex.... 
                queue.push(adjacent_vertex);                 // ...Füge ihn in die Liste der zu besuchenden Vertices ein. 
              } 
          } 
        queue.pop(); // Entferne den aktuellen Vertex aus der Warteschlange 
      } 
    
    if (queue.empty()) return out;  // Warteschlange leer, bedeutet wir konnten keine Verbindung finden. 
  
    // Gebe vom Ende anfangend jeweils den Vorgänger im Suchbaum aus. 
    // Konstruktionsbedingt hat jeder Vertex genau einen Vorgänger und wir werden 
    // garantiert beim Anfang (-1) ankommen. 
    for(std::size_t it = end; it != -1; it = bfs_tree[it]) 
      { 
        *(out++) = dictionary[it]; 
      } 
    return out; 
  } 
}; 
  
  
  
int main() 
{ 
  std::ifstream word_list("4_letter_words.txt"); 
  std::istream_iterator<N_Letter_Word<4>> it(word_list), end; 
  Word_Ladder_Searcher<4> wls(it, end); 
  
 std::ostream_iterator<N_Letter_Word<4>> out(std::cout, "\n"); 
  for (N_Letter_Word<4> begin, end; std::cin >> begin >> end; ) 
    {   
      wls.search(begin, end, out); 
    } 
}