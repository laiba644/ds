#include "CombinationModule.h"
CombinationModule::CombinationModule() {
	studentCount = 0;
	studentCapacity = 10;
	students = new string[studentCapacity];
}
CombinationModule::~CombinationModule() {
	delete[] students;
}
void CombinationModule::resizeStudents() {
	studentCapacity *= 2;
	string* temp = new string[studentCapacity];

	for (int i = 0; i < studentCount; i++) {
		temp[i] = students[i];
	}

	delete[] students;
	students = temp;
}
long long CombinationModule::factorial(int n) {
	if (n <= 1) return 1;
	long long result = 1;
	for (int i = 2; i <= n; i++) {
		result *= i;
	}
	return result;
}
long long CombinationModule::nCr(int n, int r) {
	if (r > n || r < 0) return 0;
	if (r == 0 || r == n) return 1;

	// Optimize: C(n,r) = C(n, n-r)
	if (r > n - r) {
		r = n - r;
	}

	long long result = 1;
	for (int i = 0; i < r; i++) {
		result *= (n - i);
		result /= (i + 1);
	}

	return result;
}
void CombinationModule::generateProjectGroupsIterative(int groupSize)
{
	cout << "\n========================================";
	cout << "\n    PROJECT GROUPS (Size: " << groupSize << ")";
	cout << "\n========================================\n";

	if (groupSize <= 0 || groupSize > studentCount) {
		cout << "Invalid group size.\n";
		return;
	}

	long long totalGroups = nCr(studentCount, groupSize);
	cout << "Total possible groups: " << totalGroups << "\n\n";

	// Create an array to store the current combination indexes
	int* combo = new int[groupSize];

	// Step 1: start with smallest combination: [0,1,2,...,groupSize-1]
	for (int i = 0; i < groupSize; i++) {
		combo[i] = i;
	}

	long long count = 0;

	while (true)
	{
		// Print current combination
		cout << "Group " << (count + 1) << ": ";
		for (int i = 0; i < groupSize; i++) {
			cout << students[combo[i]];
			if (i < groupSize - 1) cout << ", ";
		}
		cout << "\n";

		count++;

		// Step 2: Find the right-most index that can be incremented
		int i;
		for (i = groupSize - 1; i >= 0; i--) {
			if (combo[i] != i + studentCount - groupSize) {
				break;
			}
		}

		// If i < 0, no more combinations
		if (i < 0) break;

		// Step 3: Increase this element
		combo[i]++;//[0,1,2] becomes [0,1,3]

		// Step 4: Reset all elements after it
		for (int j = i + 1; j < groupSize; j++) {
			combo[j] = combo[j - 1] + 1;
		}
	}

	delete[] combo;

	cout << "\n" << count << " groups generated successfully.\n";
}


// ======================== ADD STUDENT ========================
void CombinationModule::addStudent(const string& name) {
	// Resize if needed
	if (studentCount >= studentCapacity) {
		resizeStudents();
	}

	students[studentCount++] = name;
}

// ======================== LOAD STUDENTS FROM USER ========================
void CombinationModule::loadStudents() {
	cout << "\n========================================";
	cout << "\n         ADD STUDENTS";
	cout << "\n========================================\n";

	cout << "How many students to add? ";
	int n;
	cin >> n;

	if (n <= 0) {
		cout << "Invalid number of students.\n";
		return;
	}

	cout << "\nEnter student names:\n";
	for (int i = 0; i < n; i++) {
		string name;
		cout << (i + 1) << ". ";
		cin >> name;
		addStudent(name);
	}

	cout << "\n " << studentCount << " students added successfully.\n";
}

// ======================== DISPLAY ALL STUDENTS ========================
void CombinationModule::displayStudents() {
	cout << "\n========================================";
	cout << "\n         ALL STUDENTS";
	cout << "\n========================================\n";

	if (studentCount == 0) {
		cout << "No students added yet.\n";
		return;
	}

	for (int i = 0; i < studentCount; i++) {
		cout << (i + 1) << ". " << students[i] << "\n";
	}

	cout << "\nTotal Students: " << studentCount << "\n";
}

// ======================== GENERATE PROJECT GROUPS ========================
// ======================== GENERATE PROJECT GROUPS (FIXED) ========================
void CombinationModule::generateProjectGroups(int groupSize) {

	generateProjectGroupsIterative(groupSize);
}

// ======================== ASSIGN LAB SESSIONS ========================
void CombinationModule::assignLabSessions(int studentsPerLab) {
	cout << "\n========================================";
	cout << "\n      LAB SESSION ASSIGNMENT";
	cout << "\n========================================\n";

	if (studentsPerLab <= 0) {
		cout << " Error: Students per lab must be positive.\n";
		return;
	}

	if (studentCount == 0) {
		cout << " Error: No students available.\n";
		return;
	}

	// Calculate number of labs needed (ceiling division)
	int numLabs = (studentCount + studentsPerLab - 1) / studentsPerLab;

	cout << "Students per lab: " << studentsPerLab << "\n";
	cout << "Total labs needed: " << numLabs << "\n\n";

	// Assign students to labs
	for (int lab = 0; lab < numLabs; lab++) {
		cout << "--- Lab Session " << (lab + 1) << " ---\n";

		int start = lab * studentsPerLab;
		int end = start + studentsPerLab;
		if (end > studentCount) {
			end = studentCount;
		}

		for (int i = start; i < end; i++) {
			cout << "  " << (i - start + 1) << ". " << students[i] << "\n";
		}

		cout << "  Total: " << (end - start) << " students\n\n";
	}

	cout << " Lab sessions assigned successfully.\n";
}

// ======================== DISPLAY COMBINATION STATISTICS ========================
void CombinationModule::displayCombinationStats() {
	cout << "\n========================================";
	cout << "\n    COMBINATION STATISTICS";
	cout << "\n========================================\n";

	if (studentCount == 0) {
		cout << "No students available.\n";
		return;
	}

	cout << "Total Students: " << studentCount << "\n\n";
	cout << "Possible combinations:\n";
	cout << "--------------------------------\n";

	for (int r = 1; r <= studentCount && r <= 10; r++) {
		cout << "C(" << studentCount << "," << r << ") = " << nCr(studentCount, r);

		// Add description
		if (r == 1) cout << "  (Individual students)";
		else if (r == 2) cout << "  (Pairs)";
		else if (r == 3) cout << "  (Triplets)";
		else cout << "  (Groups of " << r << ")";

		cout << "\n";
	}

	if (studentCount > 10) {
		cout << "... (showing first 10 only)\n";
	}
}

// ======================== GETTER: STUDENT COUNT ========================
int CombinationModule::getStudentCount() const {
	return studentCount;
}