/* Created By Stefan Hulspas
 * Using some of the code from Simon Voordouw
 * 04-13-2014 version 0.21
 * Cleaned up code
 * Added Comments
 * Added Functionallity for final product
 */

#pragma once
#include "NeuralNetwork.h"
#include "TrainData.h"

class TrainingsManager
{
private:
	//Traindata set currently default is set to OCR trainData set
	TrainData trainData;
	//The NN which will be used
	NeuralNetwork net;
	//Boolean to keep track of if the network is trained at the start or not
	//Currently this is always set to true when an import file is presented
	//isTrained should be set to false if import file could not be found
	bool isTrained = false;
	//Int to keep track of the correct answers in the last pass
	unsigned int correctAnswers;
	//Total passes from which the succes rate will be calculated
	unsigned int passes;
	//The target Succes Rate for which the training will go
	//Default is set to 0.9
	double targetSuccesRate;
	//A vector to record the mistakes in the last pass
	std::vector<std::vector<unsigned int>> mistakes;
	//run the total passes 
	//Boolean is ussually set to false
	//When its true debug data will be printed
	void runPasses(bool print = false);
	//Private method to reset the mistakes
	void resetMistakes();
public:
	//Constructor taking a TrainData object from which to train the NN
	TrainingsManager(TrainData& td);
	//Constructor taking a TrainData object from which to train the NN, and the import file
	TrainingsManager(TrainData& td, std::string import);
	//Method to change to total number of passes
	void setPasses(unsigned int newPasses);
	//Method to change the target succes rate
	//so the accuracy of the NN can be changed
	void setTargetSuccesRate(double newTargetSuccesRate);
	//Method to return the recent succes
	//Might not be needed in end product
	unsigned int getRecentSucces();
	//Method to return the recent mistakes
	//For debug purposes, it shows where it goes wrong
	std::vector<std::vector<unsigned int>> getRecentMistakes();
	//Method to manually input data and get a result
	unsigned int applyInputToNN(std::vector<double> input);
	//The trainings run 
	//Boolean is ussually set to false
	//When its false each session will print a '.'
	//And how many sessions it took to train
	//When its true each session and its succesrate will be printed
	//Along with 10 additional runs with debug data
	void run(bool print = false);
	//Method to save the current configuration of the neural net
	void saveWeights(std::string fileName);
	~TrainingsManager();
};

