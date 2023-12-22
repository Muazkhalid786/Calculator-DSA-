#include <iostream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

class node {
public:
    int value;
    char opt;
    node* address = NULL;
    node* left = NULL;
    node* right = NULL;
    node(char ch) {
        opt = ch;
    }

    node(int num) {
        value = num;
    }
    node(node* add) {
        address = add;
    }
};

class StackForBST {
public:
    node* head = NULL;

    void PUSH(node* value) {
        if (head == NULL)
            head = new node(value);
        else {
            node* temp = new node(value);
            temp->left = head;
            head = temp;
        }
    }

    node* POP() {
        node* ch = head;
        if (head != NULL)
            head = head->left;
        return ch;
    }
};

class StackForPostFix {
public:
    stack<char> s;

    void push(char num) {
        s.push(num);
    }

    void pop() {
        if (!s.empty()) {
            s.pop();
        }
    }

    char getvalue() {
        if (!s.empty()) {
            return s.top();
        }
        return -1; 
    }

    void print() {
        stack<char> temp = s;
        while (!temp.empty()) {
            cout << temp.top() << endl;
            temp.pop();
        }
    }

    bool empty() {
        return s.empty();
    }
};

bool isoperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')');
}

bool pre(char chindex, char chstack) {
    int stack = 0;
    int eq = 0;
    if (chstack == '+' || chstack == '-') {
        stack = 1;
    }
    else if (chstack == '(') {
        stack = 0;
    }
    else {
        stack = 2;
    }
    if (chindex == '*' || chindex == '/')
        eq = 2;
    else
        eq = 1;
    return (stack < eq);
}

bool isopenbracket(char ch) {
    return (ch == '(');
}

bool isclosebracket(char ch) {
    return (ch == ')');
}

class BST {
public:
    int ans;
    node* root = NULL;

    void inserteq(string eq) {
        StackForBST ST;
        int index = 0;
        while (index < eq.size()) {
            int ch = eq[index];
            if (isoperator(ch)) {
                node* temp = new node((char)ch); 
                temp->left = ST.POP()->address;
                temp->right = ST.POP()->address;
                ST.PUSH(temp);
            }
            else if (!isspace(ch)) {

                int num = 0;
                while (index < eq.size() && isdigit(eq[index])) {
                    num = num * 10 + (eq[index] - '0');
                    index++;
                }
                index--;
                node* temp = new node(num);
                ST.PUSH(temp);
            }
            index++;
        }
        root = ST.POP()->address;
    }

    void printinorder(node* Root) {
        if (Root == NULL) {
            return;
        }
        else {
            printinorder(Root->left);
            cout << Root->value << endl;
            printinorder(Root->right);
        }
    }
    int solve(int a, int b, char c) {
        if (c == '+')
            return a + b;
        if (c == '*')
            return a * b;
        if (c == '-')
            return b - a;
        if (c == '/')
            return static_cast<int>(static_cast<float>(b) / static_cast<float>(a));
    }

    int simplify(node* root) {
        int ans1, ans2, ans;
        if (root->value == 0) {
            ans1 = simplify(root->left);
        }
        else {
            return root->value;
        }
        char opt = root->opt;
        ans2 = simplify(root->right);
        ans = solve(ans1, ans2, opt);
        return ans;



    }
};
string InfixtoPostfix(string eq, StackForPostFix obj) {
    string temp;
    for (int index = 0; index < eq.size(); ++index) {
        char ch = eq[index];
        if (isoperator(ch)) {
            char chstack = obj.getvalue();
            if (obj.empty() || pre(ch, chstack) || isopenbracket(ch)) {
                obj.push(ch);
            }
            else if (isclosebracket(ch)) {
                while (obj.getvalue() != '(' && !obj.empty()) {
                    char value = obj.getvalue();
                    obj.pop();
                    temp += value;
                }
                obj.pop();
            }
            else {
                chstack = obj.getvalue();
                obj.pop();
                temp += chstack;
                obj.push(ch);
            }
        }
        else if (isdigit(ch)) {

            int num = 0;
            while (index < eq.size() && isdigit(eq[index])) {
                num = num * 10 + (eq[index] - '0');
                temp += eq[index];
                ++index;
            }
            --index;
            temp += ' ';
        }
        else {
            temp += ch;
        }
    }

    while (!obj.empty()) {
        temp += obj.getvalue();
        obj.pop();
    }

    return temp;
}

int main() {
    BST tree;
    int ans;
    StackForPostFix obj;
    string eq;
    cout << "Enter Equation" << endl;
    cin >> eq;
l2:
    string temp = InfixtoPostfix(eq, obj);
    //cout << temp;

    tree.inserteq(temp);
    //    tree.printinorder(tree.root);
    ans = tree.simplify(tree.root);
    cout << "Ans: " << ans;
    cin >> eq;
    eq = (to_string(ans)) + eq;
    goto l2;

    return 0;
}
