/*
 * FamilyTree.hpp
 *
 *  Created on: 12 April 2020
 *      Author: oriel malihi
 */

#ifndef FamilyTree_HPP_
#define FamilyTree_HPP_

#include <string>
using namespace std;

namespace family
{
class Tree
{
private:
    int treeSize;
    int m_depth;
    char m_gender;
    string m_name;
    Tree *m_father;
    Tree *m_mother;
    Tree(string name, char gender, int depth) : m_name(name),
                                                m_gender(gender),
                                                m_depth(depth),
                                                treeSize(0),
                                                m_father(NULL),
                                                m_mother(NULL) {}
    void addMother(string target, string mother, int& size);
    void addFather(string target, string father, int& size);
    string displayTree();
    string relationSearch(string target);
    string findByDepth(int depth, char gender);

public:
    Tree(string name) : m_name(name),
                        m_gender(' '),
                        m_depth(0),
                        treeSize(1),
                        m_father(NULL),
                        m_mother(NULL) {}
    Tree &addMother(string target, string mother);
    Tree &addFather(string target, string father);
    string relation(string target);
    string find(string target);
    void display();
    void remove(string target);
    ~Tree();
};
} // namespace family

#endif /* FamilyTree_HPP_ */
