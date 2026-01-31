#include <cmath>
#include <iostream>
#include <string>
#include "stack.h"
float parse_and_evaluate(std::string input){
    Stack* master = new Stack();
    Stack* numbers = new Stack();
    std::string current_number = "";
    for (int pos=input.length()-1; pos>=0;pos--){
        char cur = input.at(pos);
        if (cur == '-' && !current_number.empty()){
            current_number = cur + current_number;
            std::string* token = new std::string(current_number);
            master->add(token);
            current_number = "";
        }else if (cur == '*' || cur == '/' ||cur == '-' ||cur == '+' || cur == '^'){
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
    }
    if (!current_number.empty()) {
        std::string* token = new std::string(current_number);
        master->add(token);
    }
    while (master->len()>0){
        std::string* token = (std::string*) master->pop();
        if (*token == "*" || *token == "/" || *token == "+" || *token == "-" || *token == "^"){
            std::string* as = (std::string*) numbers->pop();
            std::string* bs = (std::string*) numbers->pop();
            float a = std::stof(*as);
            float b = std::stof(*bs);
            delete as;
            delete bs;
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
            if (*token=="^"){
                result = std::pow(b, a);
            }
            numbers->add(new std::string(std::to_string(result)));
            delete token;
        }else{
            numbers->add(token);
        }
    }
    std::string* output = (std::string*)numbers->pop();
    float output_float = std::stof(*output);
    delete output;
    delete master;
    delete numbers;
    return output_float;

}
int main(){
    while (true){
        std::string input;
        std::cout << "(enter expression) ";
        std::getline(std::cin, input);
        float result = parse_and_evaluate(input);
        std::cout << std::to_string(result) << "\n";
    }
}
