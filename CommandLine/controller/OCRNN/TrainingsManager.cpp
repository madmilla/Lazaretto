/* Created By Stefan Hulspas
 * Using some of the code from Simon Voordouw
 * 04-13-2014 version 0.21
 * Cleaned up code
 * Added Comments
 * Added Functionallity for final product
 */

#include "TrainingsManager.h"


TrainingsManager::TrainingsManager(TrainData& td) : trainData(td), net(trainData.getTopology()), passes(1000), targetSuccesRate(0.9), mistakes(trainData.getNumOutputs(), std::vector<unsigned int>(trainData.getNumOutputs(), 0))
{
}

TrainingsManager::TrainingsManager(TrainData& td, std::string import) : trainData(td), net(import), isTrained(false), passes(1000), targetSuccesRate(0.9), mistakes(trainData.getNumOutputs(), std::vector<unsigned int>(trainData.getNumOutputs(), 0))
{
}

void TrainingsManager::run(bool print) {
	double succes = 0;
	unsigned int i = 0;
	std::cout << "One session consists off: " << passes << " iterations" << std::endl;
	//train
	if (!isTrained) {
		std::cout << "Starting the training" << std::endl;
		while (true) {
			i++;
			runPasses();
			succes = (double)correctAnswers / (double)passes;
			if (print)std::cout << "Session " << i << " had a succesrate of: " << succes << '%' << std::endl;
			else std::cout << ".";
			if (succes > targetSuccesRate) break;
		}
	}
	std::cout << std::endl;
	if (print) {
		//show off
		std::cout << "Running 10 additional runs with output to show off the results" << std::endl;
		passes = 10;
		runPasses(true);
	}
	else {
		std::cout << "Training took " << i << " session of " << passes << " passes" << std::endl;
		std::cout << "Final result rate was: " << succes << std::endl;
	}
}

void TrainingsManager::runPasses(bool print) {
	correctAnswers = 0;
	resetMistakes();
	for (unsigned int pass = 0; pass < passes; pass++) {
		unsigned int testDataID = (rand() * (int)(trainData.testDataSize() - 1) / RAND_MAX);

		net.feedForward(trainData.getInput(testDataID));

		auto results = net.getOutput();

		auto targets = trainData.getTargetOutput(testDataID);

		unsigned int highestR = 0;
		unsigned int highestT = 0;

		for (unsigned int i = 1; i < results.size(); i++) {
			if (results[i] > results[highestR]) highestR = i;
			if (targets[i] > targets[highestT]) highestT = i;
		}

		if (highestR == highestT) correctAnswers++;
		else {
			mistakes[highestT][highestR]++;
		}

		net.backPropagate(targets);

		if (print) {
			trainData.print(testDataID, results, highestR, targets, highestT);
		}
	}
}

void TrainingsManager::setPasses(unsigned int newPasses) {
	passes = newPasses;
}

void TrainingsManager::setTargetSuccesRate(double newTargetSuccesRate) {
	targetSuccesRate = newTargetSuccesRate;
}

unsigned int TrainingsManager::getRecentSucces() {
	return (correctAnswers * 100) / passes;
}

std::vector<std::vector<unsigned int>> TrainingsManager::getRecentMistakes() {
	return mistakes;
}

void TrainingsManager::resetMistakes() {
	for (unsigned int r = 0; r < mistakes.size(); r++) {
		for (unsigned int t = 0; t < mistakes[r].size(); t++) {
			mistakes[r][t] = 0;
		}
	}
}

unsigned int TrainingsManager::applyInputToNN(std::vector<double> input) {
	net.feedForward(input);
	auto results = net.getOutput();
	unsigned int highestR;
	for (unsigned int i = 1; i < results.size(); i++) {
		if (results[i] > results[highestR]) highestR = i;
	}
	return highestR;
}

void TrainingsManager::saveWeights(std::string fileName) {
	net.exportNetwork(fileName);
}

TrainingsManager::~TrainingsManager()
{
}