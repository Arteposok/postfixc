#include <cmath>
#include <iostream>
#include <string>
#include "stack.h"
int main(){
    while (true){
    std::string input;
    std::cout << "(enter expression) ";
    std::getline(std::cin, input);
    Stack* master = new Stack();
    Stack* numbers = new Stack();
    Stack* trash = new Stack();
    std::string current_number = "";
    for (int pos=input.length()-1; pos>=0;pos--){
        char cur = input.at(pos);
        if (cur == '*' || cur == '/' ||cur == '-' ||cur == '+'){
            if (!current_number.empty()){
                std::string* token = new std::string(current_number);
                master->add(token);
                current_number = "";
            }
            master->add(new std::string(1, cur));
        }else if (cur == ' ') {
            if (!current_number.empty()){
                std::string* token = new std::string(current_number);
                master->add(token);
                current_number = "";
            }
        }else{
            current_number = cur + current_number;
        }
        if (pos==0){break;}
    }
    if (!current_number.empty()) {
        std::string* token = new std::string(current_number);
        master->add(token);
    }
    while (master->len()>0){
        std::string* token = (std::string*) master->pop();
        trash->add(token);
        if (*token == "*" || *token == "/" || *token == "+" || *token == "-"){
            std::string* as = (std::string*) numbers->pop();
            std::string* bs = (std::string*) numbers->pop();
            float a = std::stof(*as);
            float b = std::stof(*bs);
            float result=0;
            if (*token=="+"){
                result = b + a;
            }
            if (*token=="-"){
                result = b - a;
            }
            if (*token=="*"){
                result = b * a;
            }

            if (*token=="/"){
                result = b / a;
            }
            numbers->add(new std::string(std::to_string(result)));
        }else{
            numbers->add(token);
        }
    }
    std::cout << *(std::string*)numbers->pop() << std::endl;
    while (trash->len()>0){
        delete trash->pop();
    }
    delete master;
    delete numbers;
    delete trash;
    }
}
