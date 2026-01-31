#include <cmath>
#include <iostream>
#include <string>
#include "stack.h"

float a = 0;
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
std::string preprocessor(std::string input){
    std::size_t index = 0;
    std::string answer_string = std::to_string(a);
    while (true) {
         index = input.find("a", index);
         if (index == std::string::npos) break;
         input.replace(index, 1, answer_string);
         index += 1;
    }
    return input;
}
Stack* command(std::string input){
    if (input.empty() || input.at(0) != ':'){
        return new Stack();
    }
    Stack* master = new Stack();
    std::string current_token = "";
    for (int i = input.length()-1;i>=0;i--){
        if (input.at(i)==':'){
            current_token.insert(current_token.begin(), input[i]);
            master->add(new std::string(current_token));
            current_token.clear();
        }else{
            current_token.insert(current_token.begin(), input[i]);
        }
    }
    if (current_token.length()>0)
        master->add(new std::string(current_token));
    return master;
}
std::string process_command(std::string* command_string, Stack* body){
    std::string result = "";
    if (*command_string == ":help"){
        result = "\t1. Use the postfix notation, like <a> <b> <operator>. e.g. 5 5 * 10 - will be equivalent to 5*5 - 10, the operations always execute with the two numbers to the left if awailable.\n\t2. type :help to see this message\n use * / + - ^ for multiplication, division, addition, subtraction and power.\n\t3. type 'a' in your expression to eccess your previous output";
    }
    command_string->clear();
    while (body->len()>0){
        delete body->pop();
    }
    return result;
}
std::string execute(Stack* commands){
    Stack* body = new Stack();
    std::string command_string = "";
    std::string result = "";
    while (commands->len() > 0){
        std::string* component = (std::string*)commands->pop();
        if ((*component)[0] == ':' && command_string.empty()){
            command_string = *component;
        }
        else if ((*component)[0] == ':' && !command_string.empty()){
            result += process_command(&command_string, body);
            command_string=*component;
        }else if ((*component)[0] != ':'){
            body->add(new std::string(*component));
        }
        delete component;
    }
    result += process_command(&command_string, body);
    delete body;
    return result;
}
int main(){
    std::cout << "Welcome to postfixc, an elegant calculator built for simplicity and awailability." << "\n";
    std::cout << "type :help to recieve help" << "\n";
    while (true){
        std::string input;
        std::cout << "\x1b[32m" << "calculator $ " << "\x1b[0m";
        std::getline(std::cin, input);
        Stack* commands = command(input);
        if (commands->len()>0){
            std::string commands_result = execute(commands);
            std::cout << commands_result << "\n";
            continue;
        }
        input = preprocessor(input);
        float result = parse_and_evaluate(input);
        a = result;
        std::cout << "\x1b[31m" << ">>>  " << std::to_string(result) << "\x1b[0m" << "\n";
    }
}
