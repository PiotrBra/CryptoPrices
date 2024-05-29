#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "Crypto.cpp"

using json = nlohmann::json;

// Deklaracja klasy Crypto

// Struktura do przechowywania danych pobranych przez cURL
struct DownloadedData {
    char* memory;
    size_t size;
};

// Funkcja callback do zapisywania danych pobranych przez cURL
size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct DownloadedData* mem = (struct DownloadedData*)userp;

    char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        // B³¹d alokacji pamiêci
        std::cerr << "B³¹d alokacji pamiêci!" << std::endl;
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main() {
    CURL* curl_handle;
    CURLcode res;

    struct DownloadedData chunk;
    chunk.memory = (char*)malloc(1);  // Inicjalizacja pustego bufora
    chunk.size = 0;  // Rozmiar pocz¹tkowy bufora

    curl_global_init(CURL_GLOBAL_ALL);  // Inicjalizacja cURL
    curl_handle = curl_easy_init();     // Inicjalizacja uchwytu cURL

    // Konfiguracja uchwytu cURL
    curl_easy_setopt(curl_handle, CURLOPT_URL, "https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd&order=market_cap_desc&per_page=5&page=1");
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    // Wykonanie ¿¹dania HTTP
    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK) {
        // W przypadku b³êdu wypisz informacjê o b³êdzie
        std::cerr << "B³¹d cURL: " << curl_easy_strerror(res) << std::endl;
    }
    else {
        // Jeœli pobieranie danych by³o udane, przetwórz dane JSON
        std::string json_data(chunk.memory);

        // Parsowanie danych JSON
        json parsed_json = json::parse(json_data);

        // Przechowywanie obiektów Crypto
        std::vector<Crypto> cryptocurrencies;

        // Iteracja przez dane JSON i tworzenie obiektów Crypto
        for (const auto& crypto_data : parsed_json) {
            Crypto crypto(crypto_data["symbol"], crypto_data["name"], crypto_data["current_price"], crypto_data["market_cap"], crypto_data["total_volume"]);
            cryptocurrencies.push_back(crypto);
        }

        // Wyœwietlanie informacji o kryptowalutach
        for (const auto& crypto : cryptocurrencies) {
            std::cout << "Symbol: " << crypto.getSymbol() << std::endl;
            std::cout << "Name: " << crypto.getName() << std::endl;
            std::cout << "Current Price: " << crypto.getCurrentPrice() << "$" << std::endl;
            std::cout << "Market Cap: " << crypto.getMarketCap() << "$" << std::endl;
            std::cout << "Total Volume: " << crypto.getTotalVolume() << "$" << std::endl;
            std::cout << std::endl;
        }
    }

    // Zwolnienie zasobów
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    // Zwolnienie pamiêci zaalokowanej dla danych pobranych
    free(chunk.memory);

    return 0;
}
