#define _CRT_SECURE_NO_WARNINGS
#include "Score.h"

Score::Score(RenderWindow* window)
{

}

Score::~Score()
{

}

int Score::highRead()
{
	readFile();
	sort(this->userScore.begin(), this->userScore.end());
	fclose(this->fp);
	return userScore[userScore.size() - 1].first;
}

void Score::readFile()
{
	this->fp = fopen("./System/score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		this->userScore.push_back(make_pair(this->score[i], this->name[i]));
	}
}

void Score::writeFile(string name, unsigned int score)
{
	readFile();
	this->name[5] = name;
	this->score[5] = score;
	this->userScore.push_back(make_pair(this->score[5], this->name[5]));
	sort(this->userScore.begin(), this->userScore.end());
	fclose(this->fp);

	fopen("./System/score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(this->fp);

}