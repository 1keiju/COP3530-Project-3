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

        // initialize variables used to determine what screen is open
        bool button1Pressed = true;
        bool button2Pressed = false;
        bool button3Pressed = false;
        bool button4Pressed = false;

        // while menu screen is open
        while(menuScreen.isOpen()) {

            // first button - Home Page
            sf::RectangleShape button1(sf::Vector2f(190, 100));
            button1.setOutlineThickness(10);
            button1.setOutlineColor(sf::Color::Blue);
            button1.setFillColor(sf::Color::White);
            sf::Text button1Text;
            button1Text.setFont(font);
            button1Text.setString("Home");
            button1Text.setCharacterSize(25);
            button1Text.setStyle(sf::Text::Bold);
            button1Text.setFillColor(sf::Color::Black);
            float button1TextX = ((float) 100);
            float button1TextY = ((float) 50);
            setText(button1Text, button1TextX, button1TextY);

            // second button - Top Movies Page
            sf::RectangleShape button2(sf::Vector2f(180, 100));
            button2.setPosition(210, 0);
            button2.setOutlineThickness(10);
            button2.setOutlineColor(sf::Color::Cyan);
            button2.setFillColor(sf::Color::White);
            sf::Text button2Text;
            button2Text.setFont(font);
            button2Text.setString("Top Movies");
            button2Text.setCharacterSize(25);
            button2Text.setStyle(sf::Text::Bold);
            button2Text.setFillColor(sf::Color::Black);
            float button2TextX = ((float) 300);
            float button2TextY = ((float) 50);
            setText(button2Text, button2TextX, button2TextY);

            // third button - Search Page
            sf::RectangleShape button3(sf::Vector2f(180, 100));
            button3.setPosition(410, 0);
            button3.setOutlineThickness(10);
            button3.setOutlineColor(sf::Color::Green);
            button3.setFillColor(sf::Color::White);
            sf::Text button3Text;
            button3Text.setFont(font);
            button3Text.setString("Sort");
            button3Text.setCharacterSize(25);
            button3Text.setStyle(sf::Text::Bold);
            button3Text.setFillColor(sf::Color::Black);
            float button3TextX = ((float) 500);
            float button3TextY = ((float) 50);
            setText(button3Text, button3TextX, button3TextY);

            // fourth button - Help Page
            sf::RectangleShape button4(sf::Vector2f(190, 100));
            button4.setPosition(610, 0);
            button4.setOutlineThickness(10);
            button4.setOutlineColor(sf::Color::Red);
            button4.setFillColor(sf::Color::White);
            sf::Text button4Text;
            button4Text.setFont(font);
            button4Text.setString("Help");
            button4Text.setCharacterSize(25);
            button4Text.setStyle(sf::Text::Bold);
            button4Text.setFillColor(sf::Color::Black);
            float button4TextX = ((float) 700);
            float button4TextY = ((float) 50);
            setText(button4Text, button4TextX, button4TextY);

            // check for events
            sf::Event event{};
            while (menuScreen.pollEvent(event)) {

                // close screen if exit button pressed
                if (event.type == sf::Event::Closed) {

                    menuScreen.close();

                }

                // handle clicking the buttons
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    sf::Vector2i position = sf::Mouse::getPosition(menuScreen);

                    // check if mouse is in button 1
                    if(position.x < 190 && position.y < 100) {

                        button1Pressed = true;
                        button2Pressed = false;
                        button3Pressed = false;
                        button4Pressed = false;

                    }

                    // check if mouse is in button 2
                    if(210 < position.x && position.x < 390) {

                        if(position.y < 100) {

                            button1Pressed = false;
                            button2Pressed = true;
                            button3Pressed = false;
                            button4Pressed = false;

                        }
                    }

                    // check if mouse is in button 3
                    if(410 < position.x && position.x < 590) {

                        if(position.y < 100) {

                            button1Pressed = false;
                            button2Pressed = false;
                            button3Pressed = true;
                            button4Pressed = false;

                        }
                    }

                    // check if mouse is in button 4
                    if(610 < position.x && position.x < 800) {

                        if(position.y < 100) {

                            button1Pressed = false;
                            button2Pressed = false;
                            button3Pressed = false;
                            button4Pressed = true;

                        }
                    }
                }
            }

            // sets background color and draw text
            menuScreen.clear(sf::Color::Black);
            menuScreen.draw(button1);
            menuScreen.draw(button1Text);
            menuScreen.draw(button2);
            menuScreen.draw(button2Text);
            menuScreen.draw(button3);
            menuScreen.draw(button3Text);
            menuScreen.draw(button4);
            menuScreen.draw(button4Text);

            // shows user which button is selected text
            sf::Text selectedText;
            selectedText.setFont(font);
            selectedText.setString("(Selected)");
            selectedText.setCharacterSize(12);
            selectedText.setStyle(sf::Text::Bold);
            selectedText.setFillColor(sf::Color::Green);

            // check conditions of which button was last pressed
            // if button 1, display home screen
            if(button1Pressed) {

                // show button is selected
                setText(selectedText, 100, 75);
                menuScreen.draw(selectedText);

                // hello name text
                sf::Text helloText;
                helloText.setFont(font);
                helloText.setString("Hello, " + name + "!");
                helloText.setCharacterSize(50);
                helloText.setStyle(sf::Text::Bold);
                helloText.setFillColor(sf::Color::White);
                float helloTextX = ((float) 400);
                float helloTextY = ((float) 325);
                setText(helloText, helloTextX, helloTextY);
                menuScreen.draw(helloText);

                // home screen text
                sf::Text homeText;
                homeText.setFont(font);
                homeText.setString("Use the buttons at the top of the screen to navigate!");
                homeText.setCharacterSize(17);
                homeText.setStyle(sf::Text::Bold);
                homeText.setFillColor(sf::Color::White);
                float homeTextX = ((float) 400);
                float homeTextY = ((float) 375);
                setText(homeText, homeTextX, homeTextY);
                menuScreen.draw(homeText);

            }

            // if button 2, display top movies screen
            if(button2Pressed) {

                // show button is selected
                setText(selectedText, 300, 75);
                menuScreen.draw(selectedText);

            }

            // if button 3, display search screen
            if(button3Pressed) {

                // show button is selected
                setText(selectedText, 500, 75);
                menuScreen.draw(selectedText);

            }

            // if button 4, display help screen
            if(button4Pressed) {

                // show button is selected
                setText(selectedText, 700, 75);
                menuScreen.draw(selectedText);

            }

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