#ifndef SCORE_H
#define SCORE_H

class Score
{
private:
	int m_score = 0;
	sf::Text m_text;

public:
	Score(sf::Font& font, sf::Vector2f pos);
	sf::Text GetScore();
	void IncrementScore();
	void Update();
};

#endif // !SCORE_H
