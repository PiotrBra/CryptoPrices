#include <string>

class Crypto {
private:
    std::string symbol;
    std::string name;
    double current_price;
    long long market_cap;
    long long total_volume;

public:
    // Konstruktor
    Crypto(const std::string& symbol, const std::string& name, double current_price, long long market_cap, long long total_volume)
        : symbol(symbol), name(name), current_price(current_price), market_cap(market_cap), total_volume(total_volume) {}

    // Metody dostêpu do pól prywatnych
    std::string getSymbol() const { return symbol; }
    std::string getName() const { return name; }
    double getCurrentPrice() const { return current_price; }
    long long getMarketCap() const { return market_cap; }
    long long getTotalVolume() const { return total_volume; }
};
