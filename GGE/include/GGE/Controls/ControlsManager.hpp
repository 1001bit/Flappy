#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>

namespace gge {

struct Control
{
    std::vector<sf::Keyboard::Key> keyboard;
    std::vector<sf::Mouse::Button> mouse;
};

class ControlsManager
{
private:
    // Singleton
    static ControlsManager* instance;
    ControlsManager() {};
    
    // Controls
    std::unordered_map<std::string, Control> controlsMap;

    // All the controls that are somehow active
    struct ControlParameters
    {
        bool held;
        bool pressedNow;
        bool stepBuffered;
    };
    struct ActiveControls {
        std::unordered_map<sf::Keyboard::Key, ControlParameters> keyboard;
        std::unordered_map<sf::Mouse::Button, ControlParameters> mouse;
    };
    ActiveControls activeControls;
    
public:
    // Methods
    // Set controls
    void setControlsMap(std::unordered_map<std::string, Control> controlsMap);
    
    // Change control
    void changeControl(const std::string& controlId, const Control& control);

    // Is control held now
    bool isHeld(const std::string& controlId);

    // Is control pressed once (set isPressed = false in physics update)
    bool isPressed(const std::string& controlId, bool checkStepBuffer = false);

    // On control single press
    void controlPress(sf::Keyboard::Key key);
    void controlPress(sf::Mouse::Button button);

    // makes everyControl.buffered = false (if not pressed right this frame)
    void clearStepBuffer();
    // update active controls
    void update();

    // On control release
    void controlRelease(sf::Keyboard::Key key);
    void controlRelease(sf::Mouse::Button button);

    // Singleton
    static ControlsManager* getInstance();
};

}