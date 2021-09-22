#include <SFML/Graphics.hpp>
#include "Score.h"

Score::Score(sf::Font& font, sf::Vector2f pos)
{
	m_text.setPosition(pos.x, pos.y);
	m_text.setFont(font);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::White);
	m_text.setStyle(sf::Text::Bold);
}

sf::Text Score::GetScore()
{
	return m_text;
}

void Score::IncrementScore()
{
	m_score++;
}

void Score::Update()
{
	m_text.setString(std::to_string(m_score));
}