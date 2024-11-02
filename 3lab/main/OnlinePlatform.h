#pragma once
#include <string>
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Contact.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Comment.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Manager.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Operator.h"
#include <vector>
using namespace std;
class OnlinePlatform {
private:
	string name;
	string orientation;
	vector<Comment> comments;
	vector<Contact> contacts;
	Operator operatorOfCompany;
	Manager managerOfCompany;
	
public:
	OnlinePlatform(string name, string orientation) : operatorOfCompany("", ""), managerOfCompany("", "") {
		this->name = name;
		this->orientation = orientation;
		
	}
	void setComments(vector<Comment>new_comments) {
		this->comments.resize(new_comments.size());

		for (int i = 0; i < new_comments.size(); i++) {
			this->comments[i].editComment(new_comments[i].getCommentStars(),
				new_comments[i].getCommentInfo());
		}

	}
	void setContacts(vector<string> contactsArray) {
		this->contacts.resize(contactsArray.size()); 
		operatorOfCompany.changeOperatorNumber(contactsArray[0]);
		operatorOfCompany.changeOperatorEmail(contactsArray[1]);
		managerOfCompany.changeManagerNumber(contactsArray[2]);
		managerOfCompany.changeManagerEmail(contactsArray[3]);

		for (int i = 0; i < contactsArray.size(); i++) {
			this->contacts[i].setContact(contactsArray[i]);
		}
	}
	vector<Comment>getCommentsArray() {
		return this->comments;
	}
	vector<Contact>getContact() {
		return this->contacts;
	}
	string getName() {
		return this->name;
	}
	string getOrientation() {
		return this->orientation;
	}
	
};