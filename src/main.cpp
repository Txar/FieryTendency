#include "game/game.hpp"
#include "game/math/random.hpp"
#include "SFML/Network.hpp"
#include <random>

int main(){
    //socket testing

    /*int mode;
    std::cin >> mode;
    sf::UdpSocket socket;
    if (mode == 0) {
        char data[100] = "haha ale string se leci";
        sf::IpAddress recipient = "192.168.1.88";
        unsigned short port = 54000;
        if (socket.send(data, 100, recipient, port) != sf::Socket::Done) {
            std::cout << "Send FAIL" << std::endl;
        }
        else {
            std::cout << "Succesfuly sent \"" << data << "\"" << std::endl;
        }
    }
    else {
        char data[100];
        std::size_t received;
        sf::IpAddress sender;
        unsigned short port;
        if (socket.bind(54000) != sf::Socket::Done) {
            std::cout << "Bind FAIL" << std::endl;
        }

        if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done) {
            std::cout << "Receive FAIL" << std::endl;
        }
        std::cout << "Received " << received << " bytes on port " << port << std::endl;
        std::cout << "Data: " << data << std::endl;
    }*/

    game FieryTendency(true);
    return FieryTendency.main_loop();
}