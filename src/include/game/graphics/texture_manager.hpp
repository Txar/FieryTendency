#include "SFML/Graphics.hpp"

class texture_manager {
    public:
        texture_manager() {

        };
    
        sf::Sprite get_sprite(std::string texture_name, int frame = -1, int width = -1, int height = -1) {
            sf::Sprite s;
            if (frame != -1) {
                s.setTextureRect(sf::IntRect({frame * width, 0}, {width, height}));
            }
            if (is_loaded(texture_name)) {
                s.setTexture(textures[texture_name]);
            }
            else {
                load(texture_name);
                s.setTexture(textures[texture_name]);
            }
            return s;
        }

    private:
        bool is_loaded(std::string texture_name) {
            return (textures.find(texture_name) != textures.end());
        }

        bool load(std::string texture_name) {
            sf::Texture t;
            bool success = t.loadFromFile(textures_path + "/" + texture_name + ".png");
            if (!success) {
                success = t.loadFromFile(textures_path + "/" + missing_texture_name + ".png");
            }
            textures.insert(std::pair<std::string, sf::Texture>(texture_name, t));
            return success;
        }

        std::string missing_texture_name = "missing";
        std::string textures_path = "assets";
        std::map<std::string, sf::Texture> textures;
};

texture_manager texture_mgr;