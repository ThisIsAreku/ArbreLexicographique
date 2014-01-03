/*
* apc.cpp
*
* Copyright 2013 Alexandre Boucey <alexandre.boucey@alumni.univ-avignon.fr>
*
* This file is part of APC.
*
* APC is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* APC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with APC.  If not, see <http://www.gnu.org/licenses/>.
*
*
*/

#include <iostream>

class APC{
private:
	struct Node{
		Node* child;
		Node* brother;
		char data;
	};
	Node* root;
	void destroy(Node*);
	Node* tryInsertChar(char, Node*, bool&);
	Node* createNode(char);
	void subprint(Node*);
public:
	APC();
	~APC();
	bool insertWord(std::string);
	bool contains(std::string);
	void print();
};