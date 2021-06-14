////////////////////////////////////////////////////////////////////////
// COMPILING:
// g++ -Wall *cpp
////////////////////////////////////////////////////////////////////////

#include "D_tree.h"
using namespace d_tree;

const int maxreg = 10;

int menu(){
    int choice = -1;
    while (true){
        cout << "--------------------------------------------------------------------------\n";
        cout << "                                  MENU                                    \n";
        cout << "--------------------------------------------------------------------------\n";
        cout << "1. Read the decision tree from file\n"; 
        cout << "2. Insert a node labeled labelChild attached to a father labeled labelFather\n"; 
        cout << "3. Delete a node from the tree\n"; 
        cout << "4. Modify a node in the tree\n"; 
        cout << "5. Visualize the decision tree\n";
        cout << "6. Print the variables in the decision tree\n"; 
        cout << "7. Make a prediction by entering all the values one at a time\n"; 
        cout << "8. Make prediction by entering all the values at the beginning\n"; 
        cout << "0. Exit\n"; 
        cout << "\nEnter your choice and press ENTER ---> ";  
        cin >> choice;
        cin.ignore();
        cout << "--------------------------------------------------------------------------\n";
        if(cin.fail() || choice < 0 || choice > 8) {
            cout << "\nInvalid choice\n";
            cin.clear();
            cin.ignore();
            clearerr(stdin);
            continue;
        }
        return choice;
    }
}


int main() {
    //Ciclo su choice,
    // si interrompe quando l'utente sceglie di uscire (choice==0)
    try{
        Tree v = d_tree::createEmpty();
        Label l1, l2, l, l3, l4, l5;
        int num = 0;
        unsigned int i, j;
        i = j = 0;
        string nome_file;

        int index;
        while (true){
        index=menu();
        // Visualizzazione menu e acquisizione choice

        if (index == 0)
            break;

        switch (index){
            // Lettura della mappa da tastiera (grafo)
            case 1 :
                cout<<"Insert the name of the file:";
                cin >> nome_file;
                cout<<endl;
                if (!cin) throw runtime_error("Error name file insert\n");
                v = readFromFile(nome_file);
                break;

            case 2 :
                cout<<"Insert father label: ";
                cin >> l;
                cout<<endl;
                cout<<"Insert child label: ";
                cin >> l1;
                cout<<endl;
                cout<<"Insert child condition: ";
                cin >> l2;
                cout<<endl;
                if (!cin) throw runtime_error("Error data insert\n");
                removeBlanksandOther(l1);
                removeBlanksandOther(l2);
                d_tree::addElem(l, l1, l2, v);
                break;

            case 3 :
                cout<<"Insert label of node you want to delete: ";
                cin >> l;
                cout<<endl;
                removeBlanksandOther(l);
                if (d_tree::deleteElem(l, v) == FAIL) cout << "\nNode not deleted (cause: the label is the label of the root but the root still has childs, or the label doesn't exist in this tree)\n";
                else cout << "\nNode " << l << " deleted\n";
                break;

            case 4 :
                cout<<"Insert label you want to modify: ";
                cin >> l;
                cout<<endl;
                cout<<"Insert new label: ";
                cin >> l1;
                cout<<endl;
                cout<<"Insert new condition: ";
                cin >> l2;
                cout<<endl;
                removeBlanksandOther(l);
                if (d_tree::modifyElem(l,l1,l2, v) == FAIL){
                    cout << "Node not modified cause it is the label of the root\n";
                    cout<<"or there is the same label in the tree or doesn't exists the label to modify in the tree\n";
                }
                else cout << "\nNode " << l << " modified\n";
                break;

            case 5 :
                d_tree::printTree(v, num);
                break;

            case 6 :
                d_tree::printLabel(v);
                break;

            case 7 :
                l = d_tree::predictionTree_OnceByOne(v);
                if(l == emptyLabel) cout<<"The prediction cannot take place as there is a node for which there is no viable arc"<<endl;
                else{
                    if(l == "A") cout<<"Prediction: High Risk "<<endl;
                    if(l == "B") cout<<"Prediction: Low Risk "<<endl;
                }
                break;

            case 8 :
                l.clear();
                l1.clear();
                l2.clear();
                l3.clear();
                l4.clear();
                l5.clear();
                i = j = 0;
                cout<<"Insert tuples for example (Type,Family),(Age,49): ";
                getline(cin, l);

                while(i<l.size()){
                    if((l[i] == ',' || l[i] == ' ') && l1.size() == 0){
                        l1 = l.substr(j, i);
                        j = i;
                        ++i;
                    }
                    if((l[i] == ',' || l[i] == ' ') && l1.size() != 0 && l2.size() == 0){
                        l2 = l.substr(j, i-j);
                        j = i;
                        ++i;
                    }
                    if((l[i] == ',' || l[i] == ' ') && l2.size() != 0 && l3.size() == 0){
                        l3 = l.substr(j, i-j);
                        j = i;
                        i = l.size()-1;
                    }
                    if(i == l.size()-1 && l3.size() != 0 && l4.size() == 0)
                        l4 = l.substr(j, i-j);

                    ++i;
                }
                removeBlanksandOther(l1);
                removeBlanksandOther(l2);
                removeBlanksandOther(l3);
                removeBlanksandOther(l4);
                l5 = d_tree::predictionTree(l1, l2,l3,l4, v);
                if(l5 == emptyLabel) cout<<"The prediction cannot take place as there is a node for which there is no viable arc"<<endl;
                else{
                    if(l5 == "A") cout<<"Prediction: High Risk "<<endl;
                    if(l5 == "B") cout<<"Prediction: Low Risk "<<endl;
                }
                break;

            default :
                cout << "\nInvalid option\n";
          }
        }
            return 0;
    }
        catch (runtime_error &msg)
            {cerr << "Runtime error: " << msg.what() << endl;}
        catch (...)
            {cerr << "Unrecognized exception\n";}
}
