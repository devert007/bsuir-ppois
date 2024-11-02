#pragma once
#include <string>
#include <iostream>
using namespace std;
class Comment {
private:
	int count_of_stars;
	string info_comment;
public:
	Comment() {}
	Comment(int user_stars,string comment) {
		this->count_of_stars = user_stars;
		this->info_comment = comment;
	}
	int getCommentStars() {
		return this->count_of_stars;
	}
	string getCommentInfo() {
		return this->info_comment;
	}
	void editComment(int user_stars, string comment) {
		this->count_of_stars = user_stars;
		this->info_comment = comment;
	}
};