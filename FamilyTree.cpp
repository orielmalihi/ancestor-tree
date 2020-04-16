/*
 * FamilyTree.cpp
 *
 *  Created on: 12 April 2020
 *      Author: oriel malihi
 */
#include <string>
#include <iostream>
#include "FamilyTree.hpp"
using namespace std;

namespace family
{
Tree &Tree::addMother(string target, string mother)
{
	Tree &root = *this;
	int tempSize = m_ch;

	if (m_name == target)
	{
		Tree *newMother = new Tree(mother, 'f', m_depth + 1);
		if (m_mother == NULL)
		{
			m_mother = newMother;
			m_ch++;
		}
		else
		{
			throw runtime_error("the targeted person already has a mother");
		}
	}
	else
	{
		if (m_mother != NULL)
			m_mother->addMother(target, mother, m_ch);
		if (m_father != NULL)
			m_father->addMother(target, mother, m_ch);
	}

	if (tempSize == m_ch)
	{
		throw runtime_error("could not find the target person in the tree");
	}
	return root;
}
void Tree::addMother(string target, string mother, int &size)
{
	if (m_name == target)
	{
		Tree *newMother = new Tree(mother, 'f', m_depth + 1);
		if (m_mother == NULL)
		{
			m_mother = newMother;
			size++;
		}
		else
		{
			throw runtime_error("the targeted person already has a mother");
		}
	}
	else
	{
		if (m_mother != NULL)
			m_mother->addMother(target, mother, size);
		if (m_father != NULL)
			m_father->addMother(target, mother, size);
	}
}
Tree &Tree::addFather(string target, string father)
{
	Tree &root = *this;
	int tempSize = m_ch;

	if (m_name == target)
	{
		Tree *newFather = new Tree(father, 'm', m_depth + 1);
		if (m_father == NULL)
		{
			m_father = newFather;
			m_ch++;
		}
		else
		{
			throw runtime_error("the targeted person already has a father");
		}
	}
	else
	{
		if (m_mother != NULL)
			m_mother->addFather(target, father, m_ch);
		if (m_father != NULL)
			m_father->addFather(target, father, m_ch);
	}

	if (tempSize == m_ch)
	{
		throw runtime_error("could not find the target person in the tree");
	}
	return root;
}
void Tree::addFather(string target, string father, int &size)
{
	if (m_name == target)
	{
		Tree *newFather = new Tree(father, 'm', m_depth + 1);
		if (m_father == NULL)
		{
			m_father = newFather;
			size++;
		}
		else
		{
			throw runtime_error("the targeted person already has a father");
		}
	}
	else
	{
		if (m_mother != NULL)
			m_mother->addFather(target, father, size);
		if (m_father != NULL)
			m_father->addFather(target, father, size);
	}
}
string Tree::relation(string target)
{
	string ans = relationSearch(target);
	if (ans.size() > 0)
		return ans;
	else
		return "unrelated";
}
string Tree::relationSearch(string target)
{
	if (m_name == target)
	{
		string relation = "";
		int numOfGen = m_depth - 1;
		if (numOfGen == -1)
			return "me";
		if (numOfGen == 0 && m_gender == 'f')
			return "mother";
		if (numOfGen == 0 && m_gender == 'm')
			return "father";
		if (numOfGen > 0)
		{
			if (m_gender == 'f')
				relation = "grandmother";
			else
				relation = "grandfather";
			numOfGen--;
			while (numOfGen > 0)
			{
				relation = "great-" + relation;
				numOfGen--;
			}
		}
		return relation;
	}
	string relationM = "", relationF = "";
	if (m_mother != NULL)
	{
		relationM = m_mother->relationSearch(target);
	}
	if (m_father != NULL)
	{
		relationF = m_father->relationSearch(target);
	}
	if (relationF.size() > relationM.size())
		return relationF;
	else
		return relationM;
}
string Tree::findByDepth(int depth, char gender)
{
	if (m_depth > depth)
		return "";
	if (m_depth == depth && m_gender == gender)
		return m_name;
	string nameL = "", nameR = "";
	if (m_father != NULL)
		nameL = m_father->findByDepth(depth, gender);
	if (m_mother != NULL)
		nameR = m_mother->findByDepth(depth, gender);
	if (nameL.size() > nameR.size())
		return nameL;
	else
		return nameR;
}
string Tree::find(string target)
{
	if (target == "me")
		return m_name;
	int depth = 0;
	char gender;
	while (target.size() > 11)
	{
		string temp = target.substr(0, 6);
		if (temp != "great-")
			throw runtime_error("The tree cannot handle the '" + target + "' relation\n");
		depth++;
		target = target.substr(6);
	}
	if (target.size() == 11)
	{
		string temp = target.substr(0, 5);
		if (temp != "grand")
			throw runtime_error("The tree cannot handle the '" + target + "' relation\n");
		depth++;
		target = target.substr(5);
	}
	if (target == "father")
	{
		gender = 'm';
		depth++;
	}
	else if (target == "mother")
	{
		gender = 'f';
		depth++;
	}
	else
	{
		throw runtime_error("The tree cannot handle the '" + target + "' relation\n");
	}
	string ans = findByDepth(depth, gender);
	if (ans.size() > 0)
		return ans;
	else
	{
		throw runtime_error("ERR was unable to find this tharget");
	}
}
string Tree::displayTree()
{
	string ans = "name: " + m_name;
	if (m_father != NULL)
		ans += " , father: " + m_father->m_name;
	if (m_mother != NULL)
		ans += " , mother: " + m_mother->m_name;
	ans += "\n";
	string mom_side = "", dad_side = "";
	if (m_mother != NULL)
		mom_side = m_mother->displayTree();
	if (m_father != NULL)
		dad_side = m_father->displayTree();
	return ans + mom_side + dad_side;
}
void Tree::display()
{
	string ans = "root: " + m_name;
	if (m_father != NULL)
		ans += " , father: " + m_father->m_name;
	if (m_mother != NULL)
		ans += " , mother: " + m_mother->m_name;
	ans += "\n";
	string mom_side = "", dad_side = "";
	if (m_mother != NULL)
		mom_side = m_mother->displayTree();
	if (m_father != NULL)
		dad_side = m_father->displayTree();
	cout << ans << mom_side << dad_side << endl;
}
void Tree::remove(string target)
{
	int ch = m_ch;
	removeFromTree(target, m_ch);
	if (ch == m_ch)
	{
		throw runtime_error("the targeted person is not in the tree. cant be removed.");
	}
}

void Tree::removeFromTree(string target, int &change)
{
	if (m_depth == 0 && m_name == target)
		throw runtime_error("ERR can not remove the root of the tree");
	if (m_father != NULL && m_father->m_name == target)
	{
		delete m_father;
		change++;
		m_father = NULL;
	}
	if (m_mother != NULL && m_mother->m_name == target)
	{
		delete m_mother;
		change++;
		m_mother = NULL;
	}
	if (m_father != NULL)
		m_father->removeFromTree(target, change);
	if (m_mother != NULL)
		m_mother->removeFromTree(target, change);
}
Tree::~Tree()
{
	if (m_mother != NULL)
	{
		delete m_mother;
	}
	if (m_father != NULL)
	{
		delete m_father;
	}
}
} // namespace family
