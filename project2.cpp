#include <iostream>
#include <string>
using namespace std;

class Chip {
    char chipType;  // Type of the chip (A: Addition, S: Subtraction, etc.)
    string id;      // Unique identifier for the chip
    Chip* input1;   // Pointer to the first input chip
    Chip* input2;   // Pointer to the second input chip (can be NULL)
    Chip* output;   // Ptr to the output chip (is NULL for output chips)
    double inputValue;  // for the input chip

    public:
    // Constructor
    Chip(char chipType, string id) {
        this->chipType = chipType;
        this->id = id;
        this->input1 = nullptr;
        this->input2 = nullptr;
        this->output = nullptr;
        this->inputValue = 0.0;
    }

    // Getters and Setters
    char getChipType() {    // Returns the chip type
        return chipType;
    }
    string getId() {    // Returns the id
        return id;
    }
    Chip* getInput1() { // Returns the first input chip
        return input1;
    }
    Chip* getInput2() { // Returns the second input chip
        return input2;
    }
    Chip* getOutput() { // Returns the output chip
        return output;
    }
    double getInputValue() {    // Returns the input value
        return inputValue;
    }
    
    void setInput1(Chip* inputChip) {   // Sets the first input chip
        this->input1 = inputChip;
    }
    void setInput2(Chip* inputChip){    // second input chip (can be NULL)
        this->input2 = inputChip;
    }
    void setOutput(Chip* outputChip) {  // Sets the output chip (can be NULL)
        output = outputChip;
    }
    void setInputValue(double inputValue) { // Sets the input value
        this->inputValue = inputValue;
    }

    
    void compute() {;   // Computes the output value of the chip

        if(input1 != nullptr) { // If input1 is not null, compute the input value
            input1->compute();  // Recursively compute the input value
        }
        if(input2 != nullptr) { // If input2 is not null, compute the input value
            input2->compute();  // Recursively compute the input value
        }
        switch (chipType) { // Switch statement to determine the chip type
            case 'A':
                inputValue = input1->inputValue + input2->inputValue;
                output->setInputValue(inputValue);
                break;
            case 'N':
                inputValue = -input1->inputValue;
                output->setInputValue(inputValue);
                break;
            case 'M':
                inputValue = input1->inputValue * input2->inputValue;
                output->setInputValue(inputValue);
                break;
            case 'D':
                inputValue = input1->inputValue / input2->inputValue;
                output->setInputValue(inputValue);
                break;
            case 'S':
                inputValue = input1->inputValue - input2->inputValue;
                output->setInputValue(inputValue);
                break;
            case 'O':
                break;
        }
    }

    void display() {  // Displays the chip's information
        //example: I6, Output = S600 --- for the input Chip
        //example: O50, Input 1 = S600 --- for the output Chip
        //example: A100, Input 1 = I1, Input 2 = I2, Output = M300
        //string getId() const; // Returns the chip ID
        switch(chipType) {  // Switch statement to determine the chip type
            case 'I':
                cout << chipType + id << ", Output = " << output->getChipType() + output->getId() << endl;
                break;
            case 'O':   
                if(id == "50") { // If the chip type is O and id is 50, set o50Chip to this
                    return; 
                }
            case 'A':
                cout << chipType + id << ", Input 1 = " << input1->getChipType() + input1->getId()  << ", Input 2 = " << input2->getChipType() + input2->getId() << ", Output = " << output->getChipType() + output->getId() << endl;
                break;
            case 'N':
                cout << chipType + id << ", Input 1 = " << input1->getChipType() + input1->getId() << ", Input 2 = None, Output = " << output->getChipType() + output->getId() << endl;
                break;
            case 'M':
                cout << chipType + id << ", Input 1 = " << input1->getChipType() + input1->getId() << ", Input 2 = " << input2->getChipType() + input2->getId() << ", Output = " << output->getChipType() + output->getId() << endl;
                break;
            case 'D':
                cout << chipType + id << ", Input 1 = " << input1->getChipType() + input1->getId() << ", Input 2 = " << input2->getChipType() + input2->getId() << ", Output = " << output->getChipType() + output->getId() << endl;
                break;
            case 'S':
                cout << chipType + id << ", Input 1 = " << input1->getChipType() + input1->getId() << ", Input 2 = " << input2->getChipType() + input2->getId() << ", Output = " << output->getChipType() + output->getId() << endl;
                break;
        }
    }

};

int main() {    // Main function
    int numChip;
    Chip** allChip;
    Chip* o50Chip;  // Pointer to the output chip with id = 50
    int numCommands;
    int index;  // Index of the output chip with id = 50

    cin >> numChip; // Read the number of chips
    //create and array Chip objects pointers
    allChip = new Chip*[numChip];

    // each array location is a pointer to a Chip object
    for(int i = 0; i < numChip; i++) {
        //read the chip ID based on the first letter to determine its type
        //create the chip object and initialize it appropriately
        //store the chip object in the allChips array
        string input;
        cin >> input;
        allChip[i] = new Chip(input[0], input.substr(1));

    }

    cin >> numCommands; // Read the number of commands
    for(int i = 0; i < numCommands; i++) {
        // read from input the links and make the appropriate
        //connections. You may need to search the array allChips
        //to find the chip that is referred and connect.
        // If the first letter is an O, then execute the compute method
        // on the object referred
        string cType, inp, out;     // Command type, input, output
        double numVal;  // Number value

        cin >> cType;   // Read the command type
        if(cType == "I") {  // I should only have one input
            cin >> inp >> numVal;   // Read the input and number value
            for(int j = 0; j < numChip; j++) {
                if(allChip[j]->getChipType() + allChip[j]->getId() == inp) {    // If the chip type and id are equal to the input, set the input value
                    allChip[j]->setInputValue(numVal);
                }
            }
        } 
        else if(cType == "A") { // A should have two inputs
            cin >> inp >> out;  // Read the input and output
            for(int j = 0; j < numChip; j++) {
                
                if(allChip[j]-> getChipType() + allChip[j]->getId() == inp) {   // If the chip type and id are equal to the input, set the first input
                    
                    for(int k = 0; k < numChip; k++) {

                        if(allChip[k]->getChipType() + allChip[k]->getId() == out) {    // If the chip type and id are equal to the output, set the output

                            if(allChip[k]->getInput1() == nullptr) {    // If the first input is null, set the first input
                                allChip[j]->setOutput(allChip[k]);      // Set the output chip
                                allChip[k]->setInput1(allChip[j]);      // Set the first input
                            }
                            else {
                                allChip[j]->setOutput(allChip[k]);  // If the first input is not null, set the second input
                                allChip[k]->setInput2(allChip[j]);  // Set the second input
                            }

                            for(int l = 0; l < numChip; l++) {  // Set the output chip
                                if(allChip[l]->getChipType() + allChip[l]->getId() == out) {
                                    allChip[l]->setOutput(allChip[k]);
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(cType == "O") {     // O should only have one input
            cin >> inp;
            for(int j = 0; j < numChip; j++) {
                allChip[j]->compute();
                if(allChip[j]->getChipType() + allChip[j]->getId() == inp) {   // If the chip type and id are equal to the input, set the output
                    allChip[j]->setOutput(allChip[j]);
                }
            }
        }
    }

    cout << "Computation Starts" << endl;
    for(int i = 0; i < numChip; i++) {  // Compute the output value
        allChip[i]->compute();
        if(allChip[i]->getChipType() == 'O' && allChip[i]->getId() == "50") {   // If the chip type is O and id is 50, set the index
            index = i;
        }
    }
    
    cout << "The output value from this circuit is " << allChip[index]->getInputValue() << endl;    // Display the output value
    cout << "***** Showing the connections that were established" << endl;
    for(int i = 0; i < numChip; i++) {  // Display the connections
        if(allChip[i]->getChipType() == 'O' && allChip[i]->getId() == "50") {   // If the chip type is O and id is 50, set o50Chip to this  
            o50Chip = allChip[i];
        }
        else {  // Display the connections
            allChip[i]->display(); 
        }
    }
    if(o50Chip != nullptr) {    // If o50Chip is not null, display the connections
        o50Chip->display();
        cout << o50Chip->getChipType() + o50Chip->getId() << ", Input 1 = " << o50Chip->getInput1()->getChipType() + o50Chip->getInput1()->getId() << endl;
    }

    return 0;
}

/* LLM and GitHub Copilot Usage Documentation

    Prompt: "How can I implement a recursion function in the compute method of the Chip class?"
    Rationale: My classmates explained to me that the professor recommended using recursion to compute the output value of the chip. 
    I was unsure what needed to be recursed, so I needed implementations to it in the compute method of the Chip class. 
    Incremental Development: I used the recursive implementation to compute the output value of the chip. This ensures that the input value are all 
    computed before the output value is computed, enabling accurate5 output values for the chips individually before the output chip is computed.


    Prompt: "Generate a loop statement that will output the O50 Chip regardless of where it is inputted into the array in the display method?"
    Rationale: The reason why I needed this implementation is because I needed to output the O50 chip at the end of the display, regardless
    where it was inputted into the array. This was a major concern I had with my output initally, where the O50 chip display would be outputted where it was first inputted into the array.
    Incremental Development: I used the loop statement to essentially go through the allChips array and ensure that if the O50 Chip is found anywhere in the array,
    it would be stored into an object and displayed at the end of the display method. This ensures that the O50 chip is displayed at the end of the display method, regardless of where it was inputted into the array.
 
 */

 /* Specific Testings/Debugging

    Compute() Method Testings, Debugging, and Results:
    I tested the compute() method breakpoints through each input txt.files to ensure that the input values were being computed correctly.
    Specifically with input2-1.txt file, I tested the compute() method to find out that the input values were being computed incorrectly, outputting -25 instead of -85.
    I found out that the input values were being computed incorrectly because the input values were not being computed recursively, which may have caused the output values to be incorrect.
    I fixed this issue by implementing the recursive implementation in the compute() method to ensure that the input values were computed correctly before the recursive output values were computed.
    After implementing the recursive implementation, I tested the compute() method breakpoints through each input txt.files again and verified the correct output values for the chips.

    Display() Method Testings, Debugging, and Results:
    I tested the display() method breakpoints through each input txt.files to ensure that the output values were being displayed correctly.
    Problem occured amongst the display for the input3-1.txt file, where the output value was not being displayed correctly.
    I found that the output value was not being displayed correctly because the O50 chip was being displayed where it was first inputted into the array.
    I fixed this problem by implementing the loop statement to go through the allChips array and ensure that if the O50 Chip is found anywhere in the array,
    it would be stored into an object and displayed at the end of the display method.
    After implementing the loop statement, I tested the display() method breakpoints through each input txt.files again and verified the correct output values for the chips.
 */