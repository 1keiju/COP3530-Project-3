// include libraries, headers, etc.
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

// function prototypes
void setText(sf::Text &text, float x, float y);

// main functionality
int main() {

    // load in the font
    sf::Font font;
    font.loadFromFile("./font.ttf");

    // set the welcome screen as 800x800
    sf::RenderWindow welcomeScreen(sf::VideoMode(800, 800), "Movie Recommender");
    bool startMenu = true;

    // initialize variables for typing name functionality
    int nameLength = 0;
    string index = "|";
    string name;

    // while welcome screen is open
    while(welcomeScreen.isOpen()) {

        // main title text
        sf::Text titleText;
        titleText.setFont(font);
        titleText.setString("Movie Recommender");
        titleText.setCharacterSize(40);
        titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
        float titleTextX = ((float) 400);
        float titleTextY = ((float) 200);
        setText(titleText, titleTextX, titleTextY);

        // prompt text
        sf::Text promptText;
        promptText.setFont(font);
        promptText.setString("Enter your name to get started:");
        promptText.setCharacterSize(25);
        promptText.setStyle(sf::Text::Bold);
        float promptTextX = ((float) 400);
        float promptTextY = ((float) 275);
        setText(promptText, promptTextX, promptTextY);

        // user input text
        string usernameText = name + index;
        sf::Text userText;
        userText.setFont(font);
        userText.setString(usernameText);
        userText.setCharacterSize(25);
        userText.setFillColor(sf::Color::Cyan);
        userText.setStyle(sf::Text::Bold);
        float userTextX = ((float) 400);
        float userTextY = ((float) 370);
        setText(userText, userTextX, userTextY);

        // check for events
        sf::Event event{};
        while (welcomeScreen.pollEvent(event)) {

            // close screen if exit button pressed
            if(event.type == sf::Event::Closed) {

                // make sure next menu is not opened
                welcomeScreen.close();
                startMenu = false;

            }

            // check for proper user input
            if(event.type == sf::Event::TextEntered) {
                {

                    // if the character is a-z, A-Z
                    if(event.text.unicode < 128) {

                        char inputString = (char)event.text.unicode;
                        int isString = std::isalpha(inputString);
                        if(isString > 0 && nameLength < 15){
                            nameLength += 1;

                            // if first letter, capitalize it
                            if(nameLength == 1) {

                                int upper = std::toupper(inputString);
                                char addedString = static_cast<char>(upper);
                                name.push_back(addedString);

                            }

                            // make all other letters lower case
                            else {

                                int lower = std::tolower(inputString);
                                char addedString = static_cast<char>(lower);
                                name.push_back(addedString);

                            }
                        }
                    }
                }
            }

            // enter key functionality
            if(event.type == sf::Event::KeyPressed) {

                if(event.key.code == sf::Keyboard::Enter) {

                    if(nameLength > 0){

                        welcomeScreen.close();

                    }
                }

                if(event.key.code == sf::Keyboard::Backspace) {

                    if(nameLength != 0) {

                        nameLength -= 1;
                        name.pop_back();

                    }
                }
            }
        }

        // sets background color and draw text
        welcomeScreen.clear(sf::Color::Black);
        welcomeScreen.draw(titleText);
        welcomeScreen.draw(promptText);
        welcomeScreen.draw(userText);

        // if name is zero characters, show error
        if(nameLength == 0) {

            sf::Text errorText;
            errorText.setFont(font);
            errorText.setString("Error: No Name Entered");
            errorText.setCharacterSize(25);
            errorText.setStyle(sf::Text::Bold);
            errorText.setFillColor(sf::Color::Red);
            float errorTextX = ((float) 400);
            float errorTextY = ((float) 325);
            setText(errorText, errorTextX, errorTextY);
            welcomeScreen.draw(errorText);

        }

        // else display the press enter key text
        else {

            sf::Text errorText;
            errorText.setFont(font);
            errorText.setString("Press Enter to Continue");
            errorText.setCharacterSize(25);
            errorText.setStyle(sf::Text::Bold);
            errorText.setFillColor(sf::Color::Green);
            float errorTextX = ((float) 400);
            float errorTextY = ((float) 325);
            setText(errorText, errorTextX, errorTextY);
            welcomeScreen.draw(errorText);

        }

        welcomeScreen.display();

    }

    // if proper name and user pressed enter, start the main menu
    if(startMenu) {

        // set the menu screen as 800x800
        sf::RenderWindow menuScreen(sf::VideoMode(800, 800), "Movie Recommender");

        // while menu screen is open
        while(menuScreen.isOpen()) {

            // the four buttons on top of the screen



            // check for events
            sf::Event event{};
            while (welcomeScreen.pollEvent(event)) {

                // close screen if exit button pressed
                if (event.type == sf::Event::Closed) {

                    welcomeScreen.close();

                }
            }

            // sets background color and draw text
            menuScreen.clear(sf::Color::Black);
            menuScreen.display();

        }
    }

    return 0;

}

// function that sets text to a certain position
void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}