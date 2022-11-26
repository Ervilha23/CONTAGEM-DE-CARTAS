#include "Partida.hpp"
#include "Jogador.hpp"
#include <string>
#include <queue>
#include <algorithm>
#include <random>

Partida::Partida(Jogador* jogador, int seed){
    this->jogador=jogador;
    this->dealer = new Jogador("dealer", -1);
    this->initializeDeck(seed);
}

Partida::~Partida(){
    delete this;
}

void Partida::initializeDeck(int seed){
    for (int deckqnt = 0; deckqnt<2; deckqnt++){
        for(int i = 1; i < 14; i++){
            for(int j = 0; j < 4; j++){
                deck.push_back(Carta(i,j));
            }
        }
    }
    shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}
void Partida::startNewRound(){
    jogador->bet(baseBet);
    Carta carta = deck.front();
    deck.pop_front();
    jogador->adicionaCarta(carta);
    carta = deck.front();
    deck.pop_front();
    dealer->adicionaCarta(carta);
    carta = deck.front();
    deck.pop_front();
    jogador->adicionaCarta(carta);
    carta = deck.front();
    deck.pop_front();
    dealer->adicionaCarta(carta);
};
bool Partida::dealCard(){
    Carta carta = deck.front();
    deck.pop_front();
    return jogador->adicionaCarta(carta);
};
bool Partida::dealerTurn(){
    int dealerSum = dealer->getSum();
    int jogadorSum = jogador->getSum();
    while(dealerSum < jogadorSum){
        Carta carta = deck.front();
        deck.pop_front();
        dealer->adicionaCarta(carta);
        dealerSum = dealer->getSum();
    }
    return dealerSum > 21;
};
void Partida::printStatus(){
    jogador->imprimirStatus();
    dealer->imprimirStatus();
};
bool Partida::bet(int valor){
    return jogador->bet(valor);
}
void Partida::endRound(){
    int jogadorPontos = jogador->imprimirStatus();
    int dealerPontos = dealer->imprimirStatus();
    int gameResult = 0;
    if(jogadorPontos==dealerPontos){
        cout << "Draw!" << endl;
        gameResult = 1;
    }
    else if(jogadorPontos>dealerPontos){
        cout << "You win!" << endl;
        gameResult = 2;
    }
    else{
        cout << "Dealer wins!" << endl;
        gameResult = -1;
    }
    while(jogador->getNumCards()){
        deck.push_back(jogador->popCard());
    }
    while(dealer->getNumCards()){
        deck.push_back(dealer->popCard());
    }
    jogador->endRound(gameResult);
};
bool Partida::checkCash(){
    return jogador->checkCash();
}
/*void Partida::addJogadorCarta(string nomeJogador, int numero_pontos_carta, string naipe){
    for(int i=0; i<this->_atualSize; i++){
        if(nomeJogador.compare(this->_jogadores[i].getNomeJogador())==0){
            this->_jogadores[i].adicionaCarta(Carta(numero_pontos_carta,naipe));
            return;
        }
    }
    this->_atualSize++;
    setJogadores(_jogadores);
    this->_jogadores[_atualSize-1].setNomeJogador(nomeJogador);
    this->_jogadores[_atualSize-1].adicionaCarta(Carta(numero_pontos_carta,naipe));
    
    return;
}

int Partida::getNumJogadores(){
    return(this->_num_jogadores);
}
int Partida::getNumAtualJogadores(){
    return(this->_atualSize);
}
void Partida::setJogadores(Jogador* jogadores){
    this-> _jogadores = (Jogador*) realloc(this->_jogadores, this->_atualSize*sizeof(Jogador));
}
Jogador* Partida::getJogadores(){
    return this->_jogadores;
}
Jogador Partida::getCampeao(){
    return this->_jogadores[this->_num_jogadores-1];
}
Jogador* Partida::getJogadoresOrdenados(){
    Jogador temp;
    int a=0;
    while(1){
        for(int i=1;i<this->_atualSize;i++){
            if(this->_jogadores[i-1].calcularPontuacao()>this->_jogadores[i].calcularPontuacao()){
                temp=_jogadores[i];
                _jogadores[i]=_jogadores[i-1];
                _jogadores[i-1]=temp;
                a++;
            }
        }
        if(a==0){
            break;
        }
        a=0;
    }
    return this->_jogadores;
}
void Partida::imprimeJogadoresOrdenados(){
    Jogador* imprimir=this->getJogadoresOrdenados();
    std::cout << " " << std::endl;
    for(int i=0; i<this->_atualSize;i++){
        std::cout <<imprimir[i].getNomeJogador()<< " " << imprimir[i].calcularPontuacao()<<std::endl;
    }
    return;
}*/
