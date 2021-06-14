#include "D_tree.h"
using namespace d_tree;

struct d_tree::State{
    Label symbol;
    Label condition;
};

struct d_tree::IdLabel{
    Label label;
    Label id;
    Label idlabel;
};

struct d_tree::Elem{
    State state;
    IdLabel infoLabel;
};

struct d_tree::treeNode {
    Elem infoEdge;
    Tree firstChild;
    Tree nextSibling;
};

struct Cell{
    List next;
    string s;
};


Tree d_tree::createEmpty(){
    Tree t = new treeNode;
    t->firstChild = t->nextSibling = emptyTree;
    t->infoEdge.infoLabel.idlabel = emptyLabel;

    return t;
}

//////////////////////////////////////////
// Check if idlabel is inside the Tree
//////////////////////////////////////////
bool member(const Label idlabel, const Tree& tree){

    if (tree == emptyTree)
        return false;

    // if tree idlabel is the idlabel searched
    if (tree->infoEdge.infoLabel.idlabel == idlabel)
        return true;

    // recursive call on each child of t while not return true
    Tree auxT = tree->firstChild;
    while (auxT != emptyTree) {

        if (!member(idlabel, auxT)) // not found in this subtree, go ahead searching in his siblings
            auxT = auxT->nextSibling;
        else                      // found idlabel
            return true;
    }

    return false;
}

//////////////////////////////////////////
// Check if label is inside the Tree
//////////////////////////////////////////
bool memberLabel(const Label label, const Tree& tree){

    if (tree == emptyTree)
        return false;
        
    // if tree label is the label searched
    if (tree->infoEdge.infoLabel.label == label)
        return true;

    // recursive call on each child of t while not return true
    Tree auxT = tree->firstChild;
    while (auxT != emptyTree) {

        if (!memberLabel(label, auxT)) // not found in this subtree, go ahead searching in his siblings
            auxT = auxT->nextSibling;
        else                      // found label
            return true;
    }

    return false;
}

//////////////////////////////////////////
// Return node with specific label
//////////////////////////////////////////
Tree getNode(const Label l, const Tree& t){

    if (t == emptyTree || l == emptyLabel)
        return emptyTree;

    // if tree idlabel is the idlabel searched return t
    if (t->infoEdge.infoLabel.idlabel == l){
        return t;
    }

    // recursive call on each child of t while not return emptyTree
    Tree auxT = t->firstChild;
    Tree resNode;

    while (auxT != emptyTree) {
        resNode = getNode(l, auxT);
        if (resNode == emptyTree) // not found in this subtree, go ahead searching in his siblings
            auxT = auxT->nextSibling;
        else                      // found node return it
            return resNode;
    }

    return emptyTree;
}

//////////////////////////////////////////
// Get prevSibling node with label l
//////////////////////////////////////////
Tree prevSibling(const Label l, const Tree& t){

    // if tree is empty or doesn't have childs
    if (t == emptyTree || t->firstChild == emptyTree || l == emptyLabel)
        return emptyTree;

    if (t->firstChild->infoEdge.infoLabel.idlabel == l) // if the node has as first child with the label searched doesn't have previous siblings
        return emptyTree;

    else{
        Tree prevChild = t->firstChild;             
        Tree currentChild = prevChild->nextSibling;
        Tree auxT;

        while (currentChild != emptyTree && currentChild->infoEdge.infoLabel.idlabel != l){
            prevChild = currentChild;
            currentChild = currentChild->nextSibling;
        }

        if ( currentChild != emptyTree && currentChild->infoEdge.infoLabel.idlabel == l)
            return prevChild;
        else{
            currentChild = t->firstChild;

            while (currentChild != emptyTree){
                auxT = prevSibling(l, currentChild);

                if (auxT != emptyTree)
                    return auxT;
                else
                    currentChild = currentChild->nextSibling;
            }
        }
    }

    return emptyTree;
}


//////////////////////////////////////////
// Get father node with label l
//////////////////////////////////////////
Label father(const Label l, const Tree& t){
    if (t == emptyTree) return emptyLabel;

    if (t->firstChild->infoEdge.infoLabel.idlabel != emptyLabel) return t->infoEdge.infoLabel.idlabel;

    Tree child = t->firstChild;
    Label auxL;

    while (child != emptyTree){
        auxL = father(l, child);

        if (auxL != emptyLabel)
            return auxL;
        else
            child = child->nextSibling;
    }

    return emptyLabel;
}


//////////////////////////////////////////
// Modify label (auxiliary function)
//////////////////////////////////////////
Error auxModifyElem(const Label labelToModify, const Label newLabel, const Label newCondition, const Tree& t){

    if(t == emptyTree) return FAIL;

    if(t->infoEdge.infoLabel.idlabel == labelToModify){

        t->infoEdge.infoLabel.idlabel = newLabel;
        t->infoEdge.infoLabel.id.clear();                             //clear fileds of node to modify
        t->infoEdge.infoLabel.label.clear();
        t->infoEdge.state.symbol.clear();
        t->infoEdge.state.condition.clear();
        unsigned int i = 0;

        while(i < newLabel.size()) {
            if( 
                newLabel[i] == '_' || newLabel[i] == '0'|| 
                newLabel[i] == '1' || newLabel[i] == '2'|| 
                newLabel[i] == '3' || newLabel[i] == '4'|| 
                newLabel[i] == '5' || newLabel[i] == '6'|| 
                newLabel[i] == '7' || newLabel[i] == '8'|| 
                newLabel[i] == '9'
            )
                t->infoEdge.infoLabel.id += newLabel[i];                     // id example : "_1"
            else
                t->infoEdge.infoLabel.label += newLabel[i];                 // label example : "Age"
            i++;
        }

        i = 0;
        while(i < newCondition.size()) {

            if( newCondition[i] == '<' || newCondition[i] == '>' || newCondition[i] == '='|| newCondition[i] == '!')
                t->infoEdge.state.symbol += newCondition[i];                     // symbols accepted < > = !
            else
                t->infoEdge.state.condition += newCondition[i];              //in the condition I put the condition without symbols (for example if I have> 23 as a condition here I will put only 23)
            i++;
        }
        return OK;
    }

    Tree auxT = t->firstChild;
    Error res;

    while (auxT != emptyTree) {                            //resursive search to identify the node to modify
        res = auxModifyElem(labelToModify,newLabel, newCondition, auxT);
        
        if(res == OK)
            return OK;
        else
            auxT = auxT->nextSibling;
    }

    return FAIL;

    }


//////////////////////////////////////////
// Modify label
//////////////////////////////////////////
Error d_tree::modifyElem(const Label labelToModify, const Label newLabel, const Label newCondition, const Tree& t){

    if(t->infoEdge.infoLabel.idlabel == labelToModify || member(newLabel, t) || !member(labelToModify, t) )
        return FAIL;

    return auxModifyElem(labelToModify, newLabel, newCondition, t);

}



//////////////////////////////////////////
// Add new node
//////////////////////////////////////////
Error d_tree::addElem(const Label labelOfNodeInTree, const Label labelOfNodeToAdd, const Label condition, Tree& t){

    if(t == emptyTree)
        return FAIL;

    if(member(labelOfNodeToAdd,t->firstChild))
        return FAIL;

    if( t->infoEdge.infoLabel.idlabel == emptyLabel){             //if label is empty add root

        t->infoEdge.infoLabel.idlabel = labelOfNodeToAdd;      //idlabel = label + id for example "Age_1"
        unsigned int j = 0;

        while(j < labelOfNodeToAdd.size()) {
            if( 
                labelOfNodeToAdd[j] == '_' || labelOfNodeToAdd[j] == '0'|| 
                labelOfNodeToAdd[j] == '1' || labelOfNodeToAdd[j] == '2'|| 
                labelOfNodeToAdd[j] == '3' || labelOfNodeToAdd[j] == '4'|| 
                labelOfNodeToAdd[j] == '5' || labelOfNodeToAdd[j] == '6'|| 
                labelOfNodeToAdd[j] == '7' || labelOfNodeToAdd[j] == '8'|| 
                labelOfNodeToAdd[j] == '9'
            )
                t->infoEdge.infoLabel.id += labelOfNodeToAdd[j];        //id example: "_1"
            else
                t->infoEdge.infoLabel.label += labelOfNodeToAdd[j];    //label example: "Age"
            j++;
        }
        return OK;
    }

    if(t->infoEdge.infoLabel.idlabel == labelOfNodeInTree){         //case where I don't have to insert the root but its children

        Tree s = createEmpty();
        s->infoEdge.infoLabel.idlabel = labelOfNodeToAdd;
        unsigned int i = 0;


        while(i < labelOfNodeToAdd.size()) {
            if( 
                labelOfNodeToAdd[i] == '_' || labelOfNodeToAdd[i] == '0'
                || labelOfNodeToAdd[i] == '1' || labelOfNodeToAdd[i] == '2'
                || labelOfNodeToAdd[i] == '3' || labelOfNodeToAdd[i] == '4'
                || labelOfNodeToAdd[i] == '5' || labelOfNodeToAdd[i] == '6'
                || labelOfNodeToAdd[i] == '7' || labelOfNodeToAdd[i] == '8'
                || labelOfNodeToAdd[i] == '9'
            )
                s->infoEdge.infoLabel.id += labelOfNodeToAdd[i];
            else
                s->infoEdge.infoLabel.label += labelOfNodeToAdd[i];
            i++;
        }

        i = 0;
        while(i < condition.size()) {
            if( condition[i] == '<' || condition[i] == '>' || condition[i] == '='|| condition[i] == '!')
                s->infoEdge.state.symbol += condition[i];
            else
                s->infoEdge.state.condition += condition[i];
            i++;
        }

        s->nextSibling = t->firstChild;
        t->firstChild = s;
        return OK;
    }

    Tree auxT = t->firstChild;
    Error res;
    while (auxT != emptyTree) {                            //scan tree to search where attach new node
        res = d_tree::addElem(labelOfNodeInTree,labelOfNodeToAdd, condition, auxT);

        if(res == OK)
        return res;
        else
        auxT = auxT->nextSibling;
    }

    return FAIL;
}



//////////////////////////////////////////
// Remove node
//////////////////////////////////////////
Error d_tree::deleteElem(const Label l, Tree& t){

    if(t == emptyTree)
        return FAIL;

    if(!member(l, t))
        return FAIL;

    Tree fatherTree = getNode(father(l,t), t); // get father node of node to remove

    if(fatherTree == emptyTree)
        return FAIL;

    if (fatherTree != emptyTree && fatherTree->firstChild == emptyTree) {  // can remove tree root just if it has no childs
        t = emptyTree;
        return OK;
    }

    else {

        Tree nodeToRemove = getNode(l, t);
        Tree prevSibl = prevSibling(l, t);              // get prev sibling of node to remove

        if (prevSibl == emptyTree)  // if no prev sibling, the node to remove is the first: so update firstchild of father node to remove the node
            fatherTree->firstChild = fatherTree->firstChild->nextSibling;

        else // else update nextsibling of prevsibling to remove the node
            prevSibl->nextSibling = nodeToRemove->nextSibling;

        delete nodeToRemove; // delete the node to remove
    }

    return OK;
  }


//////////////////////////////////////////
// Print tree
//////////////////////////////////////////
void d_tree::printTree(const Tree& t, int counter){

    if(t == emptyTree) return;

    if( t->infoEdge.state.symbol == emptyLabel && t->infoEdge.state.condition == emptyLabel)
        cout<< t->infoEdge.infoLabel.idlabel <<endl;
    else{

        for(int i = 0; i < counter; ++i)
            cout << "--" ;

        cout << t->infoEdge.infoLabel.idlabel << " " << t->infoEdge.state.symbol <<  t->infoEdge.state.condition << endl;
    }

    Tree auxT = t->firstChild;
    while (auxT != emptyTree) {
        d_tree::printTree(auxT, counter+1);
        auxT = auxT->nextSibling;
    }
}


//////////////////////////////////////////
// Print label
//////////////////////////////////////////
void d_tree::printLabel(const Tree& t){

    if(t == emptyTree) return;

    if(t->infoEdge.infoLabel.id == "_1" && t->infoEdge.infoLabel.label != "END")
        cout << t->infoEdge.infoLabel.label << " " << endl;

    d_tree::printLabel(t->nextSibling);
    d_tree::printLabel(t->firstChild);

}


//////////////////////////////////////////
// Symbol translation
//////////////////////////////////////////
bool d_tree::translation(const Label s, const Label conditionOfUserToroot , const Label conditionOfRoot) {

    int firstNumber = str2int(conditionOfUserToroot);
    int secondNumber = str2int(conditionOfRoot);

    switch(s[0]) {
        case '>' :
            if(s[1] == '='){
                if (firstNumber >= secondNumber) return true;
            }
            else if(firstNumber > secondNumber) return true;
            else return false;

        case '<' :
            if(s[1] == '='){
                if (firstNumber <= secondNumber) return true;
            }
            else if(firstNumber < secondNumber) return true;
            else return false;

        case '=' : return firstNumber == secondNumber;

        case '!' : return firstNumber != secondNumber;

        default : return false;
    }
}



Tree list(List& l, string str, int count,const Tree supp, const Tree& t){

    List aux, temp;
    Tree res = supp;                                                              
    int i = 1;

    aux = new Cell;
    aux->s = str;
    aux->next = l;
    l = aux;                                                                   

    if(count > 1){                                                            //if count > 1 more than one condition verified
        temp = l;
        count = rand() % count + 1;                                             // choose random condition between the verified conditions

        while(i != count){                                                       // search in the list the label of the condition chosen
            temp = temp->next;
            ++i;
        }
        res = getNode(temp->s, t);                                              // assign to res the node with that label
    }
    return res;

}


//////////////////////////////////////////
// Prediction Tree once by one
//////////////////////////////////////////
Label d_tree::predictionTree_OnceByOne(const Tree& t) {

    if(t == emptyTree) return emptyLabel;

    Label conditionOfUserToroot, conditionOfUserToNodeInTree;
    List l;
    int count = 0;
    Tree foundNode = emptyTree;
    Tree aux = t->firstChild;

    cout << "Inserisci "<< t->infoEdge.infoLabel.label<<": ";                      // ask to insert the condition
    cin >> conditionOfUserToroot;

    while(aux != emptyTree){

        if(translation(aux->infoEdge.state.symbol, conditionOfUserToroot, aux->infoEdge.state.condition)){          //if condition verified
            ++count; //count tells me how many conditions verified there are
            foundNode = list(l, aux->infoEdge.infoLabel.idlabel, count, aux, t); // save in foundNode the condition chosen if count > 1
            aux = aux->nextSibling; // go ahead in the siblings to check conditions
        }

        else
            aux = aux->nextSibling;
    }

    if(foundNode == emptyTree) return emptyLabel;  //if equal to emptyTree all conditions are false
    
    aux = foundNode;

    if(aux->firstChild->infoEdge.infoLabel.label == "END") return aux->firstChild->infoEdge.state.condition;//if label of first child is END return his condition
    else{                                                               
        cout << "Inserisci "<< aux->infoEdge.infoLabel.label<<": ";//insert condition to search in the node where condition was verified
        cin >> conditionOfUserToNodeInTree;
        cout << endl;
    }

    aux = aux->firstChild;
    while(aux != emptyTree){
        if(aux->infoEdge.state.condition == conditionOfUserToNodeInTree){// search condition
            aux = aux->firstChild;
            return aux->infoEdge.state.condition;
        }
        else
            aux = aux->nextSibling;
    }

  return emptyLabel;
}




Label d_tree::predictionTree(const Label labelOfNodeInTree, const Label conditionOfUserToNodeInTree,const Label root, const Label conditionOfUserToroot, const Tree& t) {

    if(t == emptyTree || (t->infoEdge.infoLabel.label != root) || (!memberLabel(labelOfNodeInTree, t))) return emptyLabel;

    List l;
    int count = 0;
    Tree foundNode = emptyTree;

    Tree aux = t->firstChild;
    while(aux != emptyTree){

        if(translation(aux->infoEdge.state.symbol, conditionOfUserToroot, aux->infoEdge.state.condition)){
            ++count;                                                                           //count tells me how many true conditions there are (choose at random if count> 1)
            foundNode = list(l, aux->infoEdge.infoLabel.idlabel, count, aux, t);              // save in foundNode the chosen condition if count > 1 rlde foundNode = aux
            aux = aux->nextSibling;                                                           //go ahead in the siblings to check the conditions
        }
        else
            aux = aux->nextSibling;
    }

    if(foundNode == emptyTree) return emptyLabel;                                        //if equal to emptyTree all conditions are false

    aux = foundNode;                                                                     //update aux with the node with true condition

    if(aux->firstChild->infoEdge.infoLabel.label == "END")                              //if label of first child is END return his condition
        return aux->firstChild->infoEdge.state.condition;

    aux = aux->firstChild;                                                             //else go ahead to search in the childs' conditions
    while(aux != emptyTree){

        if(aux->infoEdge.state.condition == conditionOfUserToNodeInTree){              //search condition in his childs
            aux = aux->firstChild;
            return aux->infoEdge.state.condition;
        }
        else
            aux = aux->nextSibling;
    }

    return emptyLabel;
}





Tree readFromStream(istream& str){
    Tree t = createEmpty();
    string line;
    Label rootLabel, fatherLabel, childLabel, condition;

    getline(str, line);
    istringstream instream;            // variable of type istringstream to be able to scan the pieces of each line using >>
    instream.clear();
    instream.str(line);

    instream >> rootLabel;             // the first element encountered in the file is the root label
    removeBlanksandOther(fatherLabel); // normalize the root label
    addElem(emptyLabel, rootLabel, emptyLabel, t); // insert it in the empty tree, indicating that the father is not there (first argument emptyLabel)

    getline(str, line);                // start to scan the following rows
    instream.clear();
    instream.str(line);

    while (!str.eof()){
	    instream >> fatherLabel; // in each line of the file, the first element is the parent node label and the others are the child labels
        removeBlanksandOther(fatherLabel); // normalize father label

        while(!instream.eof()){

            instream >> childLabel;               //insert child label
            removeBlanksandOther(childLabel);    // normalize child label

            instream >> condition;                //insert child condition
            removeBlanksandOther(condition);    // normalize child condition

            addElem(fatherLabel, childLabel, condition, t);    // add row to decision tree
        }

        getline(str, line);
        instream.clear();
        instream.str(line);
    }
    str.clear();
    return t;
}




Tree readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // opening a stream associated with a file, reading mode
    if (!ifs){
      cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n";
      return createEmpty();
    }
    return readFromStream(ifs);
}
