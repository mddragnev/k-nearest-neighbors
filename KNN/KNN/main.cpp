#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

/*
* For this particular exmaple this is a class which contains the turnover and success of a company
* and the characteristics of the team.
* The file with the data will be a csv file whit 3 columns: turover(int), characteristics(unsigned) and success(boolean).
*/
class Company {
public:
	Company(int turnover, string characteristics, bool success) :
		turnover(turnover), success(success), distance(-1)
	{
		this->characteristics = transformCharacteristics(characteristics);
	}

	// distance from test point
	double distance;
	int turnover;
	int characteristics;
	bool success;
private:
	/*
	* Function that transforms characteristics (Very Strong,Strong,Average,Weak) as strings to number.
	* It is geting the ASCII code as decimal number and retuning the total sum of all characters within the string.
	*/
	int transformCharacteristics(string& c) {
		unsigned sum = 0;
		for (size_t i = 0; i < c.size(); ++i) {
			if (c[i] != ' ') {
				sum += (int)c[i];
			}
		}
		return sum;
	}
};

/*
* A class that represent the reader of files with csv extensions.
*/
class CSVReader {
public:
	CSVReader(const string& fileName, const string& delimeter = ",") :
		fileName(fileName),
		delimeter(delimeter)
	{}


	/*
	* Function to fetch the data from a CSV file
	*/
	vector<vector<string>> getData() {

		ifstream file(this->fileName);
		vector<vector<string>> data;
		string line = "";

		while (getline(file, line)) {
			vector<string> tmp;
			tmp = this->split(line, ",");
			data.push_back(tmp);
		}
		file.close();
		return data;
	}

private:
	string fileName;
	string delimeter;

	/*
	* Function used to split each line by the delim
	*/
	vector<string> split(string target, string delim)
	{
		vector<string> v;
		if (!target.empty()) {
			size_t start = 0;
			do {
				size_t x = target.find(delim, start);
				// a check whether target is found
				if (x == -1)
				{
					break;
				}
				string tmp = target.substr(start, x - start);
				v.push_back(tmp);
				start += delim.size() + tmp.size();
			} while (true);

			v.push_back(target.substr(start));
		}
		return v;
	}
};

// function used to compare two companies when sorting
bool comparison(Company& lhs, Company& rhs) {
	return lhs.distance < rhs.distance;
}

double euclideanDistance(Company& lhs, Company& test) {
	return sqrt(pow((lhs.turnover - test.turnover), 2) + pow((lhs.characteristics - test.characteristics), 2));
}

// We do not need to use absolute value of characteristics because they are unsigned
double manhattanDistance(Company& lhs, Company& test) {
	return (abs(lhs.turnover - test.turnover) + abs(lhs.characteristics - test.characteristics));
}

void fillDistances(vector<Company>& data, Company& test, double(*distanceFunction)(Company&, Company&)) {
	for (size_t i = 0; i < data.size(); ++i) {
		data[i].distance = distanceFunction(data[i], test);
	}
}

bool KNN(vector<Company>& data, Company& test, int k) {
	//filling the distances between all points and test
	fillDistances(data, test, manhattanDistance);

	//sorting so that we can get the k nearest
	sort(data.begin(), data.end(), comparison);

	int countSuccesful = 0;
	int countUnsuccesful = 0;
	for (int i = 0; i < k; ++i) {
		if (data[i].success) {
			++countSuccesful;
		}
		else {
			++countUnsuccesful;
		}
	}
	if (countSuccesful == countUnsuccesful) {
		test.success = data[0].success;
	}
	else {
		test.success = countSuccesful > countUnsuccesful ? true : false;
	}
	return test.success;
}

int main() {
	const string path = "C:\\Users\\MDragnev\\Desktop\\DATA.csv";
	CSVReader reader(path);
	vector<vector<string>> rawData = reader.getData();
	vector<Company> data;
	for (vector<string> line : rawData) {
		Company comp(stoi(line[0]), line[1], line[2] == "1" ? true : false);
		data.push_back(comp);
	}
	Company test(1213, "Very Strong", false);

	string answer = KNN(data, test, 10) ? "Successful" : "Unsuccessful";
	cout << answer;

}