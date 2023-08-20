#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mp make_pair
#define pb push_back
#define vll vector<ll>
#define mod(n) n % 1000000007
#define sp << " "
#define precision(n) cout << fixed << setprecision(n);
#define startTime time_t start, end;time(&start);
#define endTime time(&end);double tt = double(end-start);cout<<"Time taken : "<<fixed<<tt<<setprecision(5);cout <<" sec"<< endl;
 
using namespace std; 

/* 	takeInput(): A function to take input */
string takeInput() {
	cout << "Enter the circuit arrangement input: ";
	string s;
	getline(cin, s);
	return s;
}

/* 	printConductance(): A function to print out the 
	result */
void printConductance(double net_conductance) {
	cout << "The Net Conductance of the System is = " << net_conductance << endl;
}

/* 	removeSpace(): A utility function to remove spaces 
	from the string if any. */
string removeSpaces(string s) {
	int len = s.length();
	for (int i = 0; i < len; i++) {
		if (s[i] == ' ') {
			s.erase(i, 1);
			i -= 1;
			len -= 1;
		}
	}
	return s;
}

/* 	parallel(): A utility fuction which calculates the
	parallel conductance of a list of conductances given. */
double parallel(vector<double> conductance) {
	int len = conductance.size();
	double net_conductance = 0.0;
	for (int i = 0; i < len; i++) {
		net_conductance += conductance[i];
	}
	return net_conductance;
}

/* 	series(): A utility fuction which calculates the
	series conductance of a list of conductances given. */
double series(vector<double> conductance) {
	int len = conductance.size();
	double net_conductance = 0.0;
	for (int i = 0; i < len; i++) {
		net_conductance += 1 / conductance[i];
	}
	return 1 / net_conductance;
}

/*	calculateConductance(): A driver function which 
	controls the string stackand drives all the 
	calculations appropriately. */
void calculateConductance(string s) {
	// Length of string
	int len = s.length();

	// A stack of circuit connections
	stack <pair <char, vector <double>> > circuit;

	// A temporary variable to store individual conductances as string
	string num;
	for (int i = 0; i < len; i++) {

		// Pushing arrangement into the stack
		if (s[i] == '(') {
			vector <double> conductances;
			circuit.push(mp(s[i - 1], conductances));
		} 

		// Separating the numerical entries
		else if (s[i] == ',') {
			if (s[i - 1] == ')') continue;
			pair <char, vector <double>> arrangement = circuit.top();
			circuit.pop();
			arrangement.second.pb(stod(num));
			circuit.push(arrangement);
			num = "";
		} 

		// Closing the calculation on the top of the stack
		else if (s[i] == ')') {
			pair <char, vector <double>> arrangement = circuit.top();
			circuit.pop();
			if (num != "") arrangement.second.pb(stod(num));
			double net_conductance = 0.0;
			if (arrangement.first == 'S') {
				net_conductance = series(arrangement.second);
			} else {
				net_conductance = parallel(arrangement.second);
			}
			if (i == len - 1) {
				printConductance(net_conductance);
				return;
			}
			arrangement = circuit.top();
			circuit.pop();
			arrangement.second.pb(net_conductance);
			circuit.push(arrangement);
			num = "";
		}

		// Formation of numerical string
		if (s[i] != '(' && s[i] != ')' && s[i] != ',' && s[i] != 'P' && s[i] != 'S') num += s[i];
	}
}

int main() { 
	string s = takeInput(); 
	s = removeSpaces(s);  
	calculateConductance(s);
	string hold;
	cout << "Enter any letter and press ENTER to exit." << endl;
	cin >> hold;
}