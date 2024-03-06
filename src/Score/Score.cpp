#include "Score/Score.hpp"

using gge::Score;

// Structors
Score::Score(std::shared_ptr<PipesManager> pipesManager, std::shared_ptr<obj::KinematicBody> bird) :
pipesManagerWeak(pipesManager),
birdWeak(bird)
{
    score = 0;
}

Score::~Score(){}

// Methods
// init text
void Score::init(std::shared_ptr<Level> level){
    std::shared_ptr<obj::Text> text = std::make_shared<obj::Text>();
    textWeak = text;
    addChild(text);
    level->drawablesManager.newDrawable(text, true, 0);
    text->text.setString(std::to_string(score));
    text->text.setFont(level->resourceManager.getFont("Assets/Fonts/font1.ttf"));
    text->text.setCharacterSize(50);
    text->text.setFillColor(sf::Color::Black);
    text->text.setOrigin(text->text.getLocalBounds().getSize() / 2.f);
    if(auto guiView = level->guiViewWeak.lock()){
        const sf::Vector2f& guiSize = guiView->getRect().getSize();
        text->setRelativePos({guiSize.x / 2, 30});
    }
}

// check for bird-pipe collision
void Score::update(const float&){
    auto pipesManager = pipesManagerWeak.lock();
    auto bird = birdWeak.lock();
    auto text = textWeak.lock();
    if(!pipesManager || !bird || !text){
        return;
    }

    if(pipesManager->checkPointCollision(bird)){
        score += 1;
        text->text.setString(std::to_string(score));
        text->text.setOrigin(text->text.getLocalBounds().getSize() / 2.f);
    }
}