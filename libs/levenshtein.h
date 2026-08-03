#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <cctype>

inline int calcularLevenshtein(const std::string& s1, const std::string& s2) {
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j],
                                         dp[i][j - 1],
                                         dp[i - 1][j - 1]
                                        });
            }
        }
    }
    return dp[m][n];
}

inline std::string getLevenshteinResponse(const std::string& fraseBuscada, int maxDistancia = 3) {
    std::string nombreArchivo = "contexto.txt";
    std::ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) return "";

    auto limpiarTexto = [](std::string str) {
        std::string res = "";
        for (char c : str) {
            if (std::isalnum((unsigned char)c) || std::isspace((unsigned char)c)) {
                res += std::tolower((unsigned char)c);
            }
        }
        return res;
    };

    auto tokenizar = [](const std::string& str) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (ss >> token) tokens.push_back(token);
        return tokens;
    };

    std::string fraseLimpia = limpiarTexto(fraseBuscada);
    if (fraseLimpia.empty()) return "";

    std::vector<std::string> tokensUsuario = tokenizar(fraseLimpia);

    std::string linea;
    std::string mejorRespuesta = "";
    int menorDistancia = INT_MAX;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        size_t inicio = linea.find('[');
        size_t separador = linea.find(':');
        size_t fin = linea.rfind(']');

        if (inicio != std::string::npos && separador != std::string::npos && fin != std::string::npos && separador > inicio && fin > separador) {
            std::string patronesStr = linea.substr(inicio + 1, separador - (inicio + 1));
            std::string response = linea.substr(separador + 1, fin - (separador + 1));

            if (!response.empty() && response[0] == ' ') {
                response.erase(0, 1);
            }

            std::stringstream ss(patronesStr);
            std::string patron;
            while (std::getline(ss, patron, ',')) {
                std::string patronLimpio = limpiarTexto(patron);
                if (patronLimpio.empty()) continue;

                std::vector<std::string> tokensPatron = tokenizar(patronLimpio);

                // 1. Coincidencia completa de frase
                int distFrase = calcularLevenshtein(fraseLimpia, patronLimpio);
                if (distFrase < menorDistancia) {
                    menorDistancia = distFrase;
                    mejorRespuesta = response;
                }

                // 2. Coincidencia por N-gramas o palabras sueltas
                if (patron.length() > 0) {
                    for (const auto& uWord : tokensUsuario) {
                        for (const auto& pWord : tokensPatron) {
                            int distWord = calcularLevenshtein(uWord, pWord);
                            if (distWord < menorDistancia) {
                                menorDistancia = distWord;
                                mejorRespuesta = response;
                            }
                        }
                    }
                }
            }
        }
    }
    archivo.close();

    if (menorDistancia > maxDistancia) {
        return "";
    }

    return mejorRespuesta;
}

#endif // LEVENSHTEIN_H
