#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <set>
#include <algorithm> 

// Definindo uma cartela
struct Cartela {
    int tabuleiro[5][5]; 
    bool marcado[5][5];  
};

// Fun��o para gerar um n�mero aleat�rio em um intervalo
int gerarNumero(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Fun��o para garantir que as cartelas n�o sejam duplicadas
Cartela gerarCartela(std::set<int>& numerosUsados) {
    Cartela cartela;
    
    // Vetor de n�meros para cada coluna
    std::vector<int> colunas[5]; 
    
    // Coluna B
    for (int i = 1; i <= 15; ++i) colunas[0].push_back(i);
    
    // I
    for (int i = 16; i <= 30; ++i) colunas[1].push_back(i);
    
    // N
    for (int i = 31; i <= 45; ++i) colunas[2].push_back(i);
    
    // G
    for (int i = 46; i <= 60; ++i) colunas[3].push_back(i);
    
    // O
    for (int i = 61; i <= 75; ++i) colunas[4].push_back(i);

    
    std::random_device rd;
    std::mt19937 g(rd()); // Essa parte � para gerar n�meros aleat�rios
    
    // Embaralhar os n�meros de cada coluna
    for (int i = 0; i < 5; ++i) {
        std::shuffle(colunas[i].begin(), colunas[i].end(), g);
    }
    
    // Preencher a cartela com n�meros �nicos
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == 2 && j == 2) {
                cartela.tabuleiro[i][j] = 0; // aqui � para o FREE na tela
            } else {
                // Garantir que o n�mero seja �nico
                int numero;
                do {
                    numero = colunas[i].back();
                    colunas[i].pop_back();
                } while (numerosUsados.find(numero) != numerosUsados.end()); // Verifica se o n�mero j� foi marcado
                cartela.tabuleiro[i][j] = numero;
                numerosUsados.insert(numero); 
            }
            cartela.marcado[i][j] = false; 
        }
    }
    
    return cartela;
}

// Fun��o para imprimir a cartela e iindicando se existem n�meros marcados
void imprimirCartela(const Cartela &cartela) {
    std::cout << "B   I   N   G   O" << std::endl;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (cartela.tabuleiro[i][j] == 0) {
                std::cout << "FREE ";
            } else {
                // Se o n�mero estiver marcado, mostrar com asterisco
                if (cartela.marcado[i][j]) {
                    std::cout << "*" << cartela.tabuleiro[i][j] << "  ";
                } else {
                    std::cout << cartela.tabuleiro[i][j] << "   ";
                }
            }
        }
        std::cout << std::endl;
    }
}

// Fun��o para marcar um n�mero na cartela
void marcarNumero(Cartela &cartela, int numero) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (cartela.tabuleiro[i][j] == numero) {
                cartela.marcado[i][j] = true;
            }
        }
    }
}

// Fun��o para verificar a cartela e exibir o progresso
std::string verificarCartela(const Cartela &cartela) {
    for (int i = 0; i < 5; ++i) {
        bool linhaCompleta = true;
        for (int j = 0; j < 5; ++j) {
            if (!cartela.marcado[i][j]) {
                linhaCompleta = false;
                break;
            }
        }
        if (linhaCompleta) {
            return "LINHA";
        }
    }

    // Verificar por coluna
    for (int j = 0; j < 5; ++j) {
        bool colunaCompleta = true;
        for (int i = 0; i < 5; ++i) {
            if (!cartela.marcado[i][j]) {
                colunaCompleta = false;
                break;
            }
        }
        if (colunaCompleta) {
            return "COLUNA";
        }
    }

    // Verificar Bingo completo
    bool bingoCompleto = true;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // "FREE" no centro � ignorado na visualiza��o
            if (cartela.tabuleiro[i][j] != 0 && !cartela.marcado[i][j]) {
                bingoCompleto = false;
                break;
            }
        }
        if (!bingoCompleto) break;
    }
    if (bingoCompleto) return "BINGO";

    // Verificar "Olha a boa!" 
    int numerosMarcados = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (cartela.marcado[i][j]) {
                ++numerosMarcados;
            }
        }
    }
    if (numerosMarcados == 24) return "Olha a boa!";

    return "Nenhuma vitoria";
}

int main() {
    srand(time(0));  // Inicializa o gerador de n�meros aleat�rios
    int opcao, numeroChamado;
    std::vector<Cartela> cartelas;
    std::vector<int> numerosChamados;
    std::set<int> numerosUsados; // Conjunto para armazenar n�meros usados e garantir unicidade

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Criar cartela\n";
        std::cout << "2. Marcar n�mero\n";      // Cria��o de Menu
        std::cout << "3. Verificar cartela\n";
        std::cout << "4. Visualizar cartelas\n";
        std::cout << "5. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        if (opcao == 1) {
            // Criar cartela
            int qtdCartelas;
            std::cout << "Quantas cartelas deseja criar? ";
            std::cin >> qtdCartelas;
            for (int i = 0; i < qtdCartelas; ++i) {
                Cartela cartela = gerarCartela(numerosUsados);  
                cartelas.push_back(cartela);
                std::cout << "Cartela " << i + 1 << " criada!" << std::endl;
                imprimirCartela(cartela);
            }
        }
        else if (opcao == 2) {
            // Marcar n�mero
            std::cout << "Digite o numero chamado: ";
            std::cin >> numeroChamado;
            if (numeroChamado < 1 || numeroChamado > 75) {
                std::cout << "Numero invalido! Digite um n�mero entre 1 e 75." << std::endl;
            } else {
                numerosChamados.push_back(numeroChamado);
                for (auto &cartela : cartelas) {
                    marcarNumero(cartela, numeroChamado);
                }
            }
        }
        else if (opcao == 3) {
            // Verificar cartela
            for (int i = 0; i < cartelas.size(); ++i) {
                std::cout << "\nCartela " << i + 1 << std::endl;
                imprimirCartela(cartelas[i]);
                std::string resultado = verificarCartela(cartelas[i]);
                std::cout << "Status: " << resultado << std::endl;

                // Verifica se a cartela j� completou alguma linha, coluna ou Bingo
                if (resultado == "BINGO") {
                    std::cout << "Parabens! Voc� completou um BINGO!" << std::endl;
                }
                else if (resultado == "Olha a boa!") {
                    std::cout << "Olha a boa! Falta apenas 1 numero!" << std::endl;
                }
            }
        }
        else if (opcao == 4) {
            // Visualizar cartelas
            for (int i = 0; i < cartelas.size(); ++i) {
                std::cout << "\nCartela " << i + 1 << std::endl;
                imprimirCartela(cartelas[i]);
            }
        }
        else if (opcao == 5) {
            break;
        }
        else {
            std::cout << "Op��o invalida! Tente novamente." << std::endl;
        }
    }

    return 0;
}

// Observa��es: N�o consegui realizar a quest�o 7

