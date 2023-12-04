// include libraries, headers, etc.
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Movies.h"
#include "mergesort.h"
#include "quicksort.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
typedef high_resolution_clock Clock;

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

        // initialize variables used to determine what filter is selected for top movie
        bool topMovie1Pressed = true;
        bool topMovie2Pressed = false;
        bool topMovie3Pressed = false;
        bool topMovie4Pressed = false;
        bool topMovie5Pressed = false;

        // initialize variables used to determine what filter is selected for sort
        bool filter1Pressed = true;
        bool filter2Pressed = false;
        bool filter3Pressed = false;
        bool filter4Pressed = false;

        // initialize variables used to determine if filter is pressed for the first time
        bool filter1Toggle = true;
        bool filter2Toggle = false;
        bool filter3Toggle = false;
        bool filter4Toggle = false;

        // initialize variables used to determine what type of sort is done
        bool mergePressed = true;
        bool quickPressed = false;

        // initialize variables used for first filter
        string mergePopularity;
        string mergePopularityTime;
        string quickPopularity;
        string quickPopularityTime;

        // initialize variables used for third filter
        string mergeBudget;
        string mergeBudgetTime;
        string quickBudget;
        string quickBudgetTime;

        // initialize variables used for fourth filter
        string mergeRuntime;
        string mergeRuntimeTime;
        string quickRuntime;
        string quickRuntimeTime;

        // initialize variables used for fifth filter
        string mergeAvg;
        string mergeAvgTime;
        string quickAvg;
        string quickAvgTime;

        // show the loading screen temporarily
        menuScreen.clear(sf::Color::Black);
        sf::Text loadingText;
        loadingText.setFont(font);
        loadingText.setString("Loading data...");
        loadingText.setCharacterSize(25);
        loadingText.setStyle(sf::Text::Bold);
        loadingText.setFillColor(sf::Color::White);
        float loadingTextX = ((float) 400);
        float loadingTextY = ((float) 325);
        setText(loadingText, loadingTextX, loadingTextY);
        menuScreen.draw(loadingText);
        menuScreen.display();

        // initialize movies datasets
        Movies dataset;

        // do this so first quick sort is not worst case in main functionality
        quickSortRevenue(dataset.movies, 0, 110000, true);

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
            button2.setOutlineColor(sf::Color::Blue);
            button2.setFillColor(sf::Color::White);
            sf::Text button2Text;
            button2Text.setFont(font);
            button2Text.setString("Top Movies 2023");
            button2Text.setCharacterSize(17);
            button2Text.setStyle(sf::Text::Bold);
            button2Text.setFillColor(sf::Color::Black);
            float button2TextX = ((float) 300);
            float button2TextY = ((float) 50);
            setText(button2Text, button2TextX, button2TextY);

            // third button - Search Page
            sf::RectangleShape button3(sf::Vector2f(180, 100));
            button3.setPosition(410, 0);
            button3.setOutlineThickness(10);
            button3.setOutlineColor(sf::Color::Blue);
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
            button4.setOutlineColor(sf::Color::Blue);
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

                    // if on top movies menu, check if a filter is clicked on
                    if(button2Pressed) {

                        if(20 < position.x && position.x < 270) {

                            // check if mouse is in filter 1
                            if (200 < position.y && position.y < 275) {

                                topMovie1Pressed = true;
                                topMovie2Pressed = false;
                                topMovie3Pressed = false;
                                topMovie4Pressed = false;
                                topMovie5Pressed = false;

                            }

                            // check if mouse is in filter 2
                            if (300 < position.y && position.y < 375) {

                                topMovie1Pressed = false;
                                topMovie2Pressed = true;
                                topMovie3Pressed = false;
                                topMovie4Pressed = false;
                                topMovie5Pressed = false;

                            }

                            // check if mouse is in filter 3
                            if (400 < position.y && position.y < 475) {

                                topMovie1Pressed = false;
                                topMovie2Pressed = false;
                                topMovie3Pressed = true;
                                topMovie4Pressed = false;
                                topMovie5Pressed = false;

                            }

                            // check if mouse is in filter 4
                            if (500 < position.y && position.y < 575) {

                                topMovie1Pressed = false;
                                topMovie2Pressed = false;
                                topMovie3Pressed = false;
                                topMovie4Pressed = true;
                                topMovie5Pressed = false;

                            }

                            // check if mouse is in filter 5
                            if (600 < position.y && position.y < 675) {

                                topMovie1Pressed = false;
                                topMovie2Pressed = false;
                                topMovie3Pressed = false;
                                topMovie4Pressed = false;
                                topMovie5Pressed = true;

                            }
                        }
                    }

                    // if on sort menu, check if a filter is clicked on
                    if(button3Pressed) {

                        if(20 < position.x && position.x < 270) {

                            // check if mouse is in filter 1
                            if(200 < position.y  && position.y < 275) {

                                filter1Pressed = true;
                                filter2Pressed = false;
                                filter3Pressed = false;
                                filter4Pressed = false;
                                filter1Toggle = true;
                                filter2Toggle = false;
                                filter3Toggle = false;
                                filter4Toggle = false;

                            }

                            // check if mouse is in filter 2
                            if(300 < position.y && position.y < 375) {

                                filter1Pressed = false;
                                filter2Pressed = true;
                                filter3Pressed = false;
                                filter4Pressed = false;
                                filter1Toggle = false;
                                filter2Toggle = true;
                                filter3Toggle = false;
                                filter4Toggle = false;

                            }

                            // check if mouse is in filter 3
                            if(400 < position.y && position.y < 475) {

                                filter1Pressed = false;
                                filter2Pressed = false;
                                filter3Pressed = true;
                                filter4Pressed = false;
                                filter1Toggle = false;
                                filter2Toggle = false;
                                filter3Toggle = true;
                                filter4Toggle = false;
                            }

                            // check if mouse is in filter 4
                            if(500 < position.y && position.y < 575) {

                                filter1Pressed = false;
                                filter2Pressed = false;
                                filter3Pressed = false;
                                filter4Pressed = true;
                                filter1Toggle = false;
                                filter2Toggle = false;
                                filter3Toggle = false;
                                filter4Toggle = true;

                            }

                            // check if mouse is in merge sort button
                            if(700 < position.y && position.y < 775) {

                                mergePressed = true;
                                quickPressed = false;

                            }
                        }

                        // check if quick sort button is pressed
                        if(300 < position.x && position.x < 550) {

                            if(700 < position.y && position.y < 775) {

                                mergePressed = false;
                                quickPressed = true;

                            }
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

            // shows user which filter is selected in the sort menu
            sf::Text selectedFilterText;
            selectedFilterText.setFont(font);
            selectedFilterText.setString("(Selected)");
            selectedFilterText.setCharacterSize(12);
            selectedFilterText.setStyle(sf::Text::Bold);
            selectedFilterText.setFillColor(sf::Color::Green);

            // shows user which sort algorithm is selected
            sf::Text selectedSortText;
            selectedSortText.setFont(font);
            selectedSortText.setString("(Selected)");
            selectedSortText.setCharacterSize(12);
            selectedSortText.setStyle(sf::Text::Bold);
            selectedSortText.setFillColor(sf::Color::Green);

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

                // button for imdb filter
                sf::RectangleShape filter1(sf::Vector2f(250, 75));
                filter1.setPosition(20, 200);
                filter1.setOutlineThickness(10);
                filter1.setOutlineColor(sf::Color(255, 127, 0));
                filter1.setFillColor(sf::Color::White);
                sf::Text filter1Text;
                filter1Text.setFont(font);
                filter1Text.setString("IMDb");
                filter1Text.setCharacterSize(20);
                filter1Text.setStyle(sf::Text::Bold);
                filter1Text.setFillColor(sf::Color::Black);
                float filter1TextX = ((float) 135);
                float filter1TextY = ((float) 237.5);
                setText(filter1Text, filter1TextX, filter1TextY);
                menuScreen.draw(filter1);
                menuScreen.draw(filter1Text);

                // button for rotten tomatoes filter
                sf::RectangleShape filter2(sf::Vector2f(250, 75));
                filter2.setPosition(20, 300);
                filter2.setOutlineThickness(10);
                filter2.setOutlineColor(sf::Color(255, 127, 0));
                filter2.setFillColor(sf::Color::White);
                sf::Text filter2Text;
                filter2Text.setFont(font);
                filter2Text.setString("Rotten Tomatoes");
                filter2Text.setCharacterSize(20);
                filter2Text.setStyle(sf::Text::Bold);
                filter2Text.setFillColor(sf::Color::Black);
                float filter2TextX = ((float) 135);
                float filter2TextY = ((float) 337.5);
                setText(filter2Text, filter2TextX, filter2TextY);
                menuScreen.draw(filter2);
                menuScreen.draw(filter2Text);

                // button for NY times filter
                sf::RectangleShape filter3(sf::Vector2f(250, 75));
                filter3.setPosition(20, 400);
                filter3.setOutlineThickness(10);
                filter3.setOutlineColor(sf::Color(255, 127, 0));
                filter3.setFillColor(sf::Color::White);
                sf::Text filter3Text;
                filter3Text.setFont(font);
                filter3Text.setString("NY Times");
                filter3Text.setCharacterSize(20);
                filter3Text.setStyle(sf::Text::Bold);
                filter3Text.setFillColor(sf::Color::Black);
                float filter3TextX = ((float) 135);
                float filter3TextY = ((float) 437.5);
                setText(filter3Text, filter3TextX, filter3TextY);
                menuScreen.draw(filter3);
                menuScreen.draw(filter3Text);

                // button for the new yorker filter
                sf::RectangleShape filter4(sf::Vector2f(250, 75));
                filter4.setPosition(20, 500);
                filter4.setOutlineThickness(10);
                filter4.setOutlineColor(sf::Color(255, 127, 0));
                filter4.setFillColor(sf::Color::White);
                sf::Text filter4Text;
                filter4Text.setFont(font);
                filter4Text.setString("The New Yorker");
                filter4Text.setCharacterSize(20);
                filter4Text.setStyle(sf::Text::Bold);
                filter4Text.setFillColor(sf::Color::Black);
                float filter4TextX = ((float) 135);
                float filter4TextY = ((float) 537.5);
                setText(filter4Text, filter4TextX, filter4TextY);
                menuScreen.draw(filter4);
                menuScreen.draw(filter4Text);

                // button for TIME filter
                sf::RectangleShape filter5(sf::Vector2f(250, 75));
                filter5.setPosition(20, 600);
                filter5.setOutlineThickness(10);
                filter5.setOutlineColor(sf::Color(255, 127, 0));
                filter5.setFillColor(sf::Color::White);
                sf::Text filter5Text;
                filter5Text.setFont(font);
                filter5Text.setString("TIME");
                filter5Text.setCharacterSize(20);
                filter5Text.setStyle(sf::Text::Bold);
                filter5Text.setFillColor(sf::Color::Black);
                float filter5TextX = ((float) 135);
                float filter5TextY = ((float) 637.5);
                setText(filter5Text, filter5TextX, filter5TextY);
                menuScreen.draw(filter5);
                menuScreen.draw(filter5Text);


                // check conditions for which filter is selected, then display the appropriate data
                if(topMovie1Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 262.5);
                    menuScreen.draw(selectedFilterText);

                    // display top 10 movies by IMBd
                    sf::Text IMBDText;
                    setText(IMBDText, 350, 200);
                    IMBDText.setFont(font);
                    IMBDText.setString("Top 10 Movies of 2023:\n\n1. Oppenheimer\n\n2. Past Lives\n\n3. Killers of the Flower Moon"
                                       "\n\n4. Poor Things\n\n5. Anatomy of a Fall\n\n6. Spider Man: Across the Spider-Verse"
                                       "\n\n7. The Holdovers\n\n8. Mission Impossible - Dead Reckoning"
                                       "\n\n9. About Dry Grasses\n\n10. John Wick: Chapter 4");
                    IMBDText.setCharacterSize(17);
                    IMBDText.setStyle(sf::Text::Bold);
                    IMBDText.setFillColor(sf::Color::White);
                    menuScreen.draw(IMBDText);

                }

                if(topMovie2Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 362.5);
                    menuScreen.draw(selectedFilterText);

                    // display top 10 movies by Rotten Tomatoes
                    sf::Text tomatoesText;
                    setText(tomatoesText, 350, 200);
                    tomatoesText.setFont(font);
                    tomatoesText.setString("Top 10 Movies of 2023:\n\n1. The First Slam Dunk\n\n2. Shayda\n\n"
                                           "3. Are You There God? It's Me, Margaret."
                                           "\n\n4. Fallen Leaves\n\n5. Rye Lane\n\n6. Joyland"
                                           "\n\n7. Monster\n\n8. The Beasts"
                                           "\n\n9. Full Time\n\n10. Aloners");
                    tomatoesText.setCharacterSize(17);
                    tomatoesText.setStyle(sf::Text::Bold);
                    tomatoesText.setFillColor(sf::Color::White);
                    menuScreen.draw(tomatoesText);

                }

                if(topMovie3Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 462.5);
                    menuScreen.draw(selectedFilterText);

                    // display top 10 movies by NY Times
                    sf::Text NYTimesText;
                    setText(NYTimesText, 350, 200);
                    NYTimesText.setFont(font);
                    NYTimesText.setString("Top 10 Movies of 2023:\n\n1. Killers of the Flower Moon\n\n2. Oppenheimer\n\n"
                                           "3. Menus-Plaisirs - Les Troisgros"
                                           "\n\n4. Occupied City\n\n5. A Thousand and One\n\n6. Asteroid City"
                                           "\n\n7. May December\n\n8. Showing Up"
                                           "\n\n9. Orlando: My Political Biography\n\n10. Stonewalling");
                    NYTimesText.setCharacterSize(17);
                    NYTimesText.setStyle(sf::Text::Bold);
                    NYTimesText.setFillColor(sf::Color::White);
                    menuScreen.draw(NYTimesText);

                }

                if(topMovie4Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 562.5);
                    menuScreen.draw(selectedFilterText);

                    // display top 10 movies by NY Times
                    sf::Text NYText;
                    setText(NYText, 350, 200);
                    NYText.setFont(font);
                    NYText.setString("Top 10 Movies of 2023:\n\n1. Killers of the Flower Moon\n\n2. Asteroid City\n\n"
                                          "3. Barbie\n\n4. All Dirt Roads Taste of Salt"
                                          "\n\n5. Showing Up\n\n6. Passages"
                                          "\n\n7. Civic\n\n8. A Thousand and One"
                                          "\n\n9. Earth Mama\n\n10. Pinball: The Man Who Saved the Game");
                    NYText.setCharacterSize(17);
                    NYText.setStyle(sf::Text::Bold);
                    NYText.setFillColor(sf::Color::White);
                    menuScreen.draw(NYText);

                }

                if(topMovie5Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 662.5);
                    menuScreen.draw(selectedFilterText);

                    // display top 10 movies by NY Times
                    sf::Text timesText;
                    setText(timesText, 350, 200);
                    timesText.setFont(font);
                    timesText.setString("Top 10 Movies of 2023:\n\n1. Fallen Leaves\n\n2. Maestro\n\n"
                                     "3. The Zone of Interest\n\n4. Priscilla"
                                     "\n\n5. Revoir Paris\n\n6. Past Lives"
                                     "\n\n7. Killers of the Flower Moon\n\n8. Are You There God? It's Me, Margaret."
                                     "\n\n9. Dreamin' Wild\n\n10. Passages");
                    timesText.setCharacterSize(17);
                    timesText.setStyle(sf::Text::Bold);
                    timesText.setFillColor(sf::Color::White);
                    menuScreen.draw(timesText);

                }
            }

            // if button 3, display search screen
            if(button3Pressed) {

                // show button is selected
                setText(selectedText, 500, 75);
                menuScreen.draw(selectedText);

                // button for popularity filter
                sf::RectangleShape filter1(sf::Vector2f(250, 75));
                filter1.setPosition(20, 200);
                filter1.setOutlineThickness(10);
                filter1.setOutlineColor(sf::Color(255, 127, 0));
                filter1.setFillColor(sf::Color::White);
                sf::Text filter1Text;
                filter1Text.setFont(font);
                filter1Text.setString("Popularity");
                filter1Text.setCharacterSize(20);
                filter1Text.setStyle(sf::Text::Bold);
                filter1Text.setFillColor(sf::Color::Black);
                float filter1TextX = ((float) 135);
                float filter1TextY = ((float) 237.5);
                setText(filter1Text, filter1TextX, filter1TextY);
                menuScreen.draw(filter1);
                menuScreen.draw(filter1Text);

                // button for revenue filter
                sf::RectangleShape filter2(sf::Vector2f(250, 75));
                filter2.setPosition(20, 300);
                filter2.setOutlineThickness(10);
                filter2.setOutlineColor(sf::Color(255, 127, 0));
                filter2.setFillColor(sf::Color::White);
                sf::Text filter2Text;
                filter2Text.setFont(font);
                filter2Text.setString("Runtime");
                filter2Text.setCharacterSize(20);
                filter2Text.setStyle(sf::Text::Bold);
                filter2Text.setFillColor(sf::Color::Black);
                float filter2TextX = ((float) 135);
                float filter2TextY = ((float) 337.5);
                setText(filter2Text, filter2TextX, filter2TextY);
                menuScreen.draw(filter2);
                menuScreen.draw(filter2Text);

                // button for budget filter
                sf::RectangleShape filter3(sf::Vector2f(250, 75));
                filter3.setPosition(20, 400);
                filter3.setOutlineThickness(10);
                filter3.setOutlineColor(sf::Color(255, 127, 0));
                filter3.setFillColor(sf::Color::White);
                sf::Text filter3Text;
                filter3Text.setFont(font);
                filter3Text.setString("Budget");
                filter3Text.setCharacterSize(20);
                filter3Text.setStyle(sf::Text::Bold);
                filter3Text.setFillColor(sf::Color::Black);
                float filter3TextX = ((float) 135);
                float filter3TextY = ((float) 437.5);
                setText(filter3Text, filter3TextX, filter3TextY);
                menuScreen.draw(filter3);
                menuScreen.draw(filter3Text);

                // button for runtime filter
                sf::RectangleShape filter4(sf::Vector2f(250, 75));
                filter4.setPosition(20, 500);
                filter4.setOutlineThickness(10);
                filter4.setOutlineColor(sf::Color(255, 127, 0));
                filter4.setFillColor(sf::Color::White);
                sf::Text filter4Text;
                filter4Text.setFont(font);
                filter4Text.setString("Voter Average");
                filter4Text.setCharacterSize(20);
                filter4Text.setStyle(sf::Text::Bold);
                filter4Text.setFillColor(sf::Color::Black);
                float filter4TextX = ((float) 135);
                float filter4TextY = ((float) 537.5);
                setText(filter4Text, filter4TextX, filter4TextY);
                menuScreen.draw(filter4);
                menuScreen.draw(filter4Text);

                // button for merge sort
                sf::RectangleShape merge(sf::Vector2f(250, 75));
                merge.setPosition(20, 700);
                merge.setOutlineThickness(10);
                merge.setOutlineColor(sf::Color::Blue);
                merge.setFillColor(sf::Color::White);
                sf::Text mergeText;
                mergeText.setFont(font);
                mergeText.setString("Merge Sort");
                mergeText.setCharacterSize(20);
                mergeText.setStyle(sf::Text::Bold);
                mergeText.setFillColor(sf::Color::Black);
                float mergeTextX = ((float) 135);
                float mergeTextY = ((float) 737.5);
                setText(mergeText, mergeTextX, mergeTextY);
                menuScreen.draw(merge);
                menuScreen.draw(mergeText);

                // button for quick sort
                sf::RectangleShape quick(sf::Vector2f(250, 75));
                quick.setPosition(300, 700);
                quick.setOutlineThickness(10);
                quick.setOutlineColor(sf::Color::Blue);
                quick.setFillColor(sf::Color::White);
                sf::Text quickText;
                quickText.setFont(font);
                quickText.setString("Quick Sort");
                quickText.setCharacterSize(20);
                quickText.setStyle(sf::Text::Bold);
                quickText.setFillColor(sf::Color::Black);
                float quickTextX = ((float) 425);
                float quickTextY = ((float) 737.5);
                setText(quickText, quickTextX, quickTextY);
                menuScreen.draw(quick);
                menuScreen.draw(quickText);

                // check conditions for which sort is selected
                if(mergePressed) {

                    // show button is selected
                    setText(selectedSortText, 135, 762.5);
                    menuScreen.draw(selectedSortText);

                }

                if(quickPressed) {

                    // show button is selected
                    setText(selectedSortText, 425, 762.5);
                    menuScreen.draw(selectedSortText);

                }

                // check conditions for which filter is selected, then display the appropriate data
                if(filter1Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 262.5);
                    menuScreen.draw(selectedFilterText);

                    // check if selecting button for first time
                    if(filter1Toggle) {

                        // show loading data text
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString("Loading data...");
                        Text.setCharacterSize(17);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);
                        menuScreen.display();

                        // get merge sorted by popularity
                        auto t1 = Clock::now();
                        mergeSort(dataset.moviesVector, 0, 110000, "popularity", true);
                        auto t2 = Clock::now();
                        mergePopularity = "Top 10 Movies:\n\n1. " + dataset.moviesVector[0].movieName + "\n\n"\
                                 "2. " + dataset.moviesVector[1].movieName + "\n\n"
                                 "3. " + dataset.moviesVector[2].movieName + "\n\n"
                                 "4. " + dataset.moviesVector[3].movieName + "\n\n"
                                 "5. " + dataset.moviesVector[4].movieName + "\n\n"
                                 "6. " + dataset.moviesVector[5].movieName + "\n\n"
                                 "7. " + dataset.moviesVector[6].movieName + "\n\n"
                                 "8. " + dataset.moviesVector[7].movieName + "\n\n"
                                 "9. " + dataset.moviesVector[8].movieName + "\n\n"
                                 "10. " + dataset.moviesVector[9].movieName + "\n\n";
                        mergePopularityTime = to_string(duration_cast<milliseconds>(t2 - t1).count());

                        // get quick sorted by popularity
                        auto t3 = Clock::now();
                        quickSortPopularity(dataset.movies, 0, 110000, true);
                        auto t4 = Clock::now();
                        quickPopularity = "Top 10 Movies:\n\n1. " + dataset.movies[0].movieName + "\n\n"\
                                 "2. " + dataset.movies[1].movieName + "\n\n"
                                 "3. " + dataset.movies[2].movieName + "\n\n"
                                 "4. " + dataset.movies[3].movieName + "\n\n"
                                 "5. " + dataset.movies[4].movieName + "\n\n"
                                 "6. " + dataset.movies[5].movieName + "\n\n"
                                 "7. " + dataset.movies[6].movieName + "\n\n"
                                 "8. " + dataset.movies[7].movieName + "\n\n"
                                 "9. " + dataset.movies[8].movieName + "\n\n"
                                 "10. " + dataset.movies[9].movieName + "\n\n";
                        quickPopularityTime = to_string(duration_cast<milliseconds>(t4 - t3).count());

                        filter1Toggle = false;

                    }

                    if(mergePressed) {

                        // display top 10 movies by popularity - merge sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(mergePopularity);
                        Text.setCharacterSize(17);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + mergePopularityTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                    else {

                        // display top 10 movies by popularity - quick sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(quickPopularity);
                        Text.setCharacterSize(17);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + quickPopularityTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                }

                if(filter2Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 362.5);
                    menuScreen.draw(selectedFilterText);

                    // check if selecting button for first time
                    if(filter2Toggle) {

                        // show loading data text
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString("Loading data...");
                        Text.setCharacterSize(17);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);
                        menuScreen.display();

                        // get merge sorted by runtime
                        auto t1 = Clock::now();
                        mergeSort(dataset.moviesVector, 0, 110000, "runtime", true);
                        auto t2 = Clock::now();
                        mergeRuntime = "Top 10 Movies:\n\n1. " + dataset.moviesVector[0].movieName + "\n\n"\
                                  "2. " + dataset.moviesVector[1].movieName + "\n\n"
                                  "3. " + dataset.moviesVector[2].movieName + "\n\n"
                                  "4. " + dataset.moviesVector[3].movieName + "\n\n"
                                  "5. " + dataset.moviesVector[4].movieName + "\n\n"
                                  "6. " + dataset.moviesVector[5].movieName + "\n\n"
                                  "6. " + dataset.moviesVector[6].movieName + "\n\n"
                                  "8. " + dataset.moviesVector[7].movieName + "\n\n"
                                  "8. " + dataset.moviesVector[8].movieName + "\n\n"
                                  "10. " + dataset.moviesVector[9].movieName + "\n\n";
                        mergeRuntimeTime = to_string(duration_cast<milliseconds>(t2 - t1).count());

                        // get quick sorted by runtime
                        auto t3 = Clock::now();
                        quickSortRuntime(dataset.movies, 0, 110000, true);
                        auto t4 = Clock::now();
                        quickRuntime = "Top 10 Movies:\n\n1. " + dataset.movies[0].movieName + "\n\n"\
                                  "2. " + dataset.movies[1].movieName + "\n\n"
                                  "3. " + dataset.movies[2].movieName + "\n\n"
                                  "4. " + dataset.movies[3].movieName + "\n\n"
                                  "5. " + dataset.movies[4].movieName + "\n\n"
                                  "6. " + dataset.movies[5].movieName + "\n\n"
                                  "6. " + dataset.movies[6].movieName + "\n\n"
                                  "8. " + dataset.movies[7].movieName + "\n\n"
                                  "8. " + dataset.movies[8].movieName + "\n\n"
                                  "10. " + dataset.movies[9].movieName + "\n\n";
                        quickRuntimeTime = to_string(duration_cast<milliseconds>(t4 - t3).count());

                        filter2Toggle = false;

                    }

                    if(mergePressed) {

                        // display top 10 movies by revenue - merge sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(mergeRuntime);
                        Text.setCharacterSize(12);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + mergeRuntimeTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                    else {

                        // display top 10 movies by revenue - quick sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(quickRuntime);
                        Text.setCharacterSize(12);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + quickRuntimeTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                }

                if(filter3Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 462.5);
                    menuScreen.draw(selectedFilterText);

                    // check if selecting button for first time
                    if(filter3Toggle) {

                        // show loading data text
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString("Loading data...");
                        Text.setCharacterSize(17);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);
                        menuScreen.display();

                        // get merge sorted by budget
                        auto t1 = Clock::now();
                        mergeSort(dataset.moviesVector, 0, 110000, "budget", true);
                        auto t2 = Clock::now();
                        mergeBudget = "Top 10 Movies:\n\n1. " + dataset.moviesVector[0].movieName + "\n\n"\
                                  "2. " + dataset.moviesVector[1].movieName + "\n\n"
                                  "3. " + dataset.moviesVector[2].movieName + "\n\n"
                                  "4. " + dataset.moviesVector[3].movieName + "\n\n"
                                  "4. " + dataset.moviesVector[4].movieName + "\n\n"
                                  "4. " + dataset.moviesVector[5].movieName + "\n\n"
                                  "4. " + dataset.moviesVector[6].movieName + "\n\n"
                                  "8. " + dataset.moviesVector[7].movieName + "\n\n"
                                  "9. " + dataset.moviesVector[8].movieName + "\n\n"
                                  "9. " + dataset.moviesVector[9].movieName + "\n\n";
                        mergeBudgetTime = to_string(duration_cast<milliseconds>(t2 - t1).count());

                        // get quick sorted by budget
                        auto t3 = Clock::now();
                        quickSortBudget(dataset.movies, 0, 110000, true);
                        auto t4 = Clock::now();
                        quickBudget = "Top 10 Movies:\n\n1. " + dataset.movies[0].movieName + "\n\n"\
                                  "2. " + dataset.movies[1].movieName + "\n\n"
                                  "3. " + dataset.movies[2].movieName + "\n\n"
                                  "4. " + dataset.movies[3].movieName + "\n\n"
                                  "4. " + dataset.movies[4].movieName + "\n\n"
                                  "4. " + dataset.movies[5].movieName + "\n\n"
                                  "4. " + dataset.movies[6].movieName + "\n\n"
                                  "8. " + dataset.movies[7].movieName + "\n\n"
                                  "9. " + dataset.movies[8].movieName + "\n\n"
                                  "9. " + dataset.movies[9].movieName + "\n\n";
                        quickBudgetTime = to_string(duration_cast<milliseconds>(t4 - t3).count());

                        filter3Toggle = false;

                    }

                    if(mergePressed) {

                        // display top 10 movies by revenue - merge sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(mergeBudget);
                        Text.setCharacterSize(14);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + mergeBudgetTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                    else {

                        // display top 10 movies by budget - quick sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(quickBudget);
                        Text.setCharacterSize(14);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + quickBudgetTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                }

                if(filter4Pressed) {

                    // show filter is selected
                    setText(selectedFilterText, 135, 562.5);
                    menuScreen.draw(selectedFilterText);

                    // check if selecting button for first time
                    if(filter4Toggle) {

                        // show loading data text
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString("Loading data...");
                        Text.setCharacterSize(17);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);
                        menuScreen.display();

                        // get merge sorted by avg score
                        auto t1 = Clock::now();
                        mergeSort(dataset.moviesVector, 0, 110000, "vote average", true);
                        auto t2 = Clock::now();
                        mergeAvg = "Top 10 Movies (All Tied for First):\n\n1. " + dataset.moviesVector[0].movieName + "\n\n"\
                                  "1. " + dataset.moviesVector[1].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[2].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[3].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[4].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[5].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[6].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[7].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[8].movieName + "\n\n"
                                  "1. " + dataset.moviesVector[9].movieName + "\n\n";
                        mergeAvgTime = to_string(duration_cast<milliseconds>(t2 - t1).count());

                        // get quick sorted by vote avg
                        auto t3 = Clock::now();
                        quickSortAvg(dataset.movies, 0, 110000, true);
                        auto t4 = Clock::now();
                        quickAvg = "Top 10 Movies (All Tied for First):\n\n1. " + dataset.movies[0].movieName + "\n\n"\
                                  "1. " + dataset.movies[1].movieName + "\n\n"
                                  "1. " + dataset.movies[2].movieName + "\n\n"
                                  "1. " + dataset.movies[3].movieName + "\n\n"
                                  "1. " + dataset.movies[4].movieName + "\n\n"
                                  "1. " + dataset.movies[5].movieName + "\n\n"
                                  "1. " + dataset.movies[6].movieName + "\n\n"
                                  "1. " + dataset.movies[7].movieName + "\n\n"
                                  "1. " + dataset.movies[8].movieName + "\n\n"
                                  "1. " + dataset.movies[9].movieName + "\n\n";
                        quickAvgTime = to_string(duration_cast<milliseconds>(t4 - t3).count());

                        filter4Toggle = false;

                    }

                    if(mergePressed) {

                        // display top 10 movies by runtime - merge sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(mergeAvg);
                        Text.setCharacterSize(12);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + mergeAvgTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                    else {

                        // display top 10 movies by runtime - quick sort
                        sf::Text Text;
                        setText(Text, 350, 200);
                        Text.setFont(font);
                        Text.setString(quickAvg);
                        Text.setCharacterSize(12);
                        Text.setStyle(sf::Text::Bold);
                        Text.setFillColor(sf::Color::White);
                        menuScreen.draw(Text);

                        // display time it took
                        sf::Text Time;
                        setText(Time, 350, 637.5);
                        Time.setFont(font);
                        Time.setString("Time taken to sort: " + quickAvgTime + " milliseconds");
                        Time.setCharacterSize(17);
                        Time.setStyle(sf::Text::Bold);
                        Time.setFillColor(sf::Color::White);
                        menuScreen.draw(Time);

                    }
                }
            }

            // if button 4, display help screen
            if(button4Pressed) {

                // show button is selected
                setText(selectedText, 700, 75);
                menuScreen.draw(selectedText);

                sf::Text helpText;
                helpText.setFont(font);
                helpText.setString("Help:\n\n Top Movies 2023: Select the source of the\n top ten movies of the year by "
                                   "clicking on\n the filters on the left side of the screen."
                                   "\n\n Sort: Select the filter that you \n want to apply, which sorts a dataset of \n"
                                   " over 100,000 movies using either quick \n sort or merge sort (selected at"
                                   " the bottom).");
                helpText.setCharacterSize(20);
                helpText.setStyle(sf::Text::Bold);
                helpText.setFillColor(sf::Color::White);
                float helpTextX = ((float) 400);
                float helpTextY = ((float) 350);
                setText(helpText, helpTextX, helpTextY);
                menuScreen.draw(helpText);

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