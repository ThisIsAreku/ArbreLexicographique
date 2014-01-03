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

#include "apc.h"

#define DEBUG true

using std::cin;
using std::cout;
using std::endl;
using std::string;

APC::APC(){
	this->root = createNode(' ');
}

APC::~APC(){
	destroy(this->root);
}

void APC::destroy(Node* n){
	if(n == NULL)
		return;

	destroy(n->brother);
	destroy(n->child);
	delete n;
}

void APC::subprint(Node* x){
	if(x == NULL)
		return;
	Node* n = x;
	while(n != NULL){
		if(n->data == '\0')
			cout << "END ";
		else
			cout << n->data << " ";
		n = n->brother;
	}
	cout << endl;
}

void APC::print(){
	subprint(this->root->child);
}

bool APC::insertWord(string s){
	Node* p = this->root;
	bool wordExists = true;
	bool fullWorldExists = true;
	for(unsigned int i = 0; i < s.length(); ++i){
		p = tryInsertChar(s[i], p, wordExists);
		fullWorldExists &= wordExists;
	}
	tryInsertChar('\0', p, wordExists); // insertion du '\0'
	fullWorldExists &= wordExists;
	return !fullWorldExists;
}

APC::Node* APC::tryInsertChar(char c, Node* p, bool& existing){
	existing = false;
	if(p == NULL) // sécurité
		return NULL;
	if(p->child == NULL){ // c'est le premier fils, on l'insert directement
		p->child = createNode(c);
		return p->child;
	}else{
		Node *n = p->child, *prev = NULL;
		while(n != NULL){
			if(n->data == c){ // si le caractère est le meme
				existing = true;
				return n;
			}
			else if(c < n->data){ // tri alphabétique
				break;
			}
			prev = n;
			n = n->brother; // on avance et on stock le précédent
		}
		// a optimiser
		Node* tmp;
		if(prev != NULL){ // si c'est pas le premier fils
			tmp = n;
			prev->brother = createNode(c);
			prev->brother->brother = tmp;
			tmp = prev->brother;
		}else{ // sinon
			tmp = p->child;
			p->child = createNode(c);
			p->child->brother = tmp;
			tmp = p->child;
		}
		return tmp;
	}
}

APC::Node* APC::createNode(char c){
	Node* n = new Node;
	n->data = c;
	n->child = n->brother = NULL;
	return n;
}

bool APC::contains(string s){
	Node* n = this->root->child;
	unsigned int charIndex = 0;
	while(n != NULL)
	{
		if(n->data == s[charIndex]){
			charIndex++;
			n = n->child; // on descend à la lettre suivante
			if(n == NULL) // si il n'y en a pas (pas de \0 p.ex)
				break;
			if(n->data == '\0' && charIndex >= s.length()){ // si \0 et fin de la chaine
				return true; // alors trouvé
			}
		}else{
			n = n->brother;
		}
	}
	return false;
}