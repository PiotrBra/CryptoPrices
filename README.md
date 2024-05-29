# Crypto Prices

Projekt Crypto Prices pobiera aktualne dane o kryptowalutach z API CoinGecko, parsuje je, a następnie wyświetla informacje o wybranych kryptowalutach w konsoli.

## Uruchomienie projektu

Aby uruchomić ten projekt, wykonaj następujące kroki:


1. **Instalacja narzędzia vcpkg (Jeśli nie masz)**: Pobierz i zainstaluj narzędzie vcpkg ze strony [GitHub vcpkg](https://github.com/microsoft/vcpkg).
2. **Pobierz biblioteki niestandardowe (Jeśli nie masz)**: Pobierz bibliteki curl oraz nlohmann

3. **Instalacja bibliotek**: Otwórz terminal i przejdź do katalogu, w którym znajduje się vcpkg. Następnie użyj vcpkg do zainstalowania bibliotek curl i nlohmann/json:
   ```bash
   vcpkg install curl
   vcpkg install nlohmann-json
   ```
4. ** W pliku CMakeLists.txt zmień ścieżkę do vcpkg**
```bash set(CMAKE_TOOLCHAIN_FILE "scieżka_do_vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake") ```
5. ** Skompiluj i uruchom program**.
