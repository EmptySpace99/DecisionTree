#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "string-utility.h"

using namespace std;

namespace d_tree{

enum Error {OK, FAIL};

typedef string Label;

const Label emptyLabel = "$#$#$";

struct State;
struct IdLabel;
struct Elem;
struct treeNode;

typedef treeNode* Tree;

const Tree emptyTree = NULL;

Error addElem(const Label, const Label, const Label, Tree&);//insert element of Tree
Tree createEmpty();//create empty Tree
Error deleteElem(const Label, Tree&);// delete Tree node
Error modifyElem(const Label , const Label , const Label , const Tree& );// modify Tree node
void printTree(const Tree&, int);// print Tree
void printLabel(const Tree& t);// print Tree labels
Label predictionTree(const Label, const Label, const Label, const Label, const Tree&);  // Tree prediction with all parameters
Label predictionTree_OnceByOne(const Tree&);// Tree prediction with the values one at a time
bool translation(const Label, const Label, const Label);// Translate and verify conditions
}

bool memberLabel(const d_tree::Label , const d_tree::Tree& );//check if exists label for example "Age"
bool member(const d_tree::Label l, const d_tree::Tree& t);// check if exists label + id for example "Age_1"
d_tree::Tree readFromFile(string);   // read Tree from file
d_tree::Tree getNode(const d_tree::Label , const d_tree::Tree& ); //get node with that label
d_tree::Tree prevSibling(const d_tree::Label , const d_tree::Tree& ); //get prev sibling node of node with that label
d_tree::Label father(const d_tree::Label , const d_tree::Tree& ); //get father node of node with that label

struct Cell;

typedef Cell* List;
