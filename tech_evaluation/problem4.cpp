#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
class table_generator {
    using table_t = std::vector<std::tuple<std::string, std::size_t>>;

   private:
    auto const& add_word() {
        table_.reserve(table_.size() + 1);
        auto it = hash_word(word_);
        table_.emplace_back(word_, hash_word(word_));
        return table_.back();
    }

    bool next_word() {
        return std::next_permutation(word_.begin(), word_.end());
    }

    static std::size_t hash_word(std::string const& word) {
        return std::hash<std::string>{}(word);
    }

   public:
    table_generator(std::string alphabet)
        : word_{alphabet} {}

    // Params `hash` also need to be a reference
    bool operator()(std::string& word, std::size_t& hash) {
        // Check if this is the first operation, Or we will get next word
        if (table_.empty())
            std::sort(word_.begin(), word_.end());
        else if (!next_word())
            return false;

        std::tie(word, hash) = add_word();
        return true;
    }

   private:
    table_t table_;
    std::string& word_;
};

int main() {
    table_generator proble4Input("abc");

    std::string word;
    std::size_t hash;
    while (proble4Input(word, hash))
        std::cout << word << " " << std::hex << hash << "\n";
}
