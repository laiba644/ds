#include "SetOperations.h"

SetOperations::Set::Set() {
    name = "";
    size = 0;
    capacity = 10;
    elements = new string[capacity];
}

SetOperations::Set::Set(const string& setName) {
    name = setName;
    size = 0;
    capacity = 10;
    elements = new string[capacity];
}

SetOperations::Set::~Set() {
    delete[] elements;
}

void SetOperations::Set::addElement(const string& element) {
    if (contains(element)) return;
    if (size >= capacity) {
        capacity *= 2;
        string* temp = new string[capacity];
        for (int i = 0; i < size; i++) temp[i] = elements[i];
        delete[] elements;
        elements = temp;
    }
    elements[size++] = element;
}

bool SetOperations::Set::contains(const string& element) const {
    for (int i = 0; i < size; i++) {
        if (elements[i] == element) return true;
    }
    return false;
}

void SetOperations::Set::display() const {
    cout << name << " = {";
    for (int i = 0; i < size; i++) {
        cout << elements[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "}\n";
    cout << "Cardinality: |" << name << "| = " << size << "\n";
}

void SetOperations::Set::clear() {
    size = 0;
}

SetOperations::SetOperations() {
    setCount = 0;
    setCapacity = 10;
    sets = new Set * [setCapacity];
}

SetOperations::~SetOperations() {
    for (int i = 0; i < setCount; i++) delete sets[i];
    delete[] sets;
}

void SetOperations::resizeSets() {
    setCapacity *= 2;
    Set** temp = new Set * [setCapacity];
    for (int i = 0; i < setCount; i++) temp[i] = sets[i];
    delete[] sets;
    sets = temp;
}

int SetOperations::findSetIndex(const string& setName) const {
    for (int i = 0; i < setCount; i++) {
        if (sets[i]->name == setName) return i;
    }
    return -1;
}

void SetOperations::removeElement(string* arr, int& size, int index) {
    for (int i = index; i < size - 1; i++) arr[i] = arr[i + 1];
    size--;
}

void SetOperations::createSet(const string& setName) {
    if (findSetIndex(setName) != -1) {
        cout << "Set '" << setName << "' already exists.\n";
        return;
    }
    if (setCount >= setCapacity) resizeSets();
    sets[setCount++] = new Set(setName);
    cout << "Set '" << setName << "' created.\n";
}

void SetOperations::addElementToSet(const string& setName, const string& element) {
    int index = findSetIndex(setName);
    if (index == -1) {
        cout << "Set '" << setName << "' not found.\n";
        return;
    }
    sets[index]->addElement(element);
}

void SetOperations::displaySet(const string& setName) const {
    int index = findSetIndex(setName);
    if (index == -1) {
        cout << "Set '" << setName << "' not found.\n";
        return;
    }
    sets[index]->display();
}

void SetOperations::displayAllSets() const {
    cout << "\nALL SETS\n\n";
    if (setCount == 0) {
        cout << "No sets created yet.\n";
        return;
    }
    for (int i = 0; i < setCount; i++) {
        sets[i]->display();
        cout << "\n";
    }
}

SetOperations::Set* SetOperations::getSet(const string& setName) const {
    int index = findSetIndex(setName);
    if (index == -1) return nullptr;
    return sets[index];
}

SetOperations::Set* SetOperations::unionSets(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }
    Set* result = new Set(setA + "_UNION_" + setB);
    for (int i = 0; i < a->size; i++) result->addElement(a->elements[i]);
    for (int i = 0; i < b->size; i++) result->addElement(b->elements[i]);
    cout << "\nUNION OPERATION\n\n";
    cout << a->name << " U " << b->name << " = ";
    result->display();
    return result;
}

SetOperations::Set* SetOperations::intersectionSets(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }
    Set* result = new Set(setA + "_INTERSECTION_" + setB);
    for (int i = 0; i < a->size; i++) {
        if (b->contains(a->elements[i])) result->addElement(a->elements[i]);
    }
    cout << "\nINTERSECTION OPERATION\n\n";
    cout << a->name << " INTERSECT " << b->name << " = ";
    result->display();
    return result;
}

SetOperations::Set* SetOperations::differenceSets(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }
    Set* result = new Set(setA + "_MINUS_" + setB);
    for (int i = 0; i < a->size; i++) {
        if (!b->contains(a->elements[i])) result->addElement(a->elements[i]);
    }
    cout << "\nDIFFERENCE OPERATION\n\n";
    cout << a->name << " - " << b->name << " = ";
    result->display();
    return result;
}

bool SetOperations::isSubset(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return false;
    }
    for (int i = 0; i < a->size; i++) {
        if (!b->contains(a->elements[i])) return false;
    }
    return true;
}

bool SetOperations::isSuperset(const string& setA, const string& setB) const {
    return isSubset(setB, setA);
}

bool SetOperations::isProperSubset(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) return false;
    return isSubset(setA, setB) && (a->size < b->size);
}

bool SetOperations::areDisjoint(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) return false;
    for (int i = 0; i < a->size; i++) {
        if (b->contains(a->elements[i])) return false;
    }
    return true;
}

bool SetOperations::areEqual(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) return false;
    if (a->size != b->size) return false;
    return isSubset(setA, setB);
}

int SetOperations::cardinality(const string& setName) const {
    Set* s = getSet(setName);
    if (!s) return -1;
    return s->size;
}

void SetOperations::generatePowerSet(const string& setName) {
    Set* s = getSet(setName);
    if (!s) {
        cout << "Set not found.\n";
        return;
    }
    cout << "\nPOWER SET GENERATION\n\nPower set of ";
    s->display();
    cout << "\n";
    int powerSetSize = 1;
    for (int i = 0; i < s->size; i++) powerSetSize *= 2;
    cout << "Total subsets: " << powerSetSize << "\n\n";
    for (int i = 0; i < powerSetSize; i++) {
        cout << "Subset " << (i + 1) << ": {";
        bool first = true;
        for (int j = 0; j < s->size; j++) {
            if (i & (1 << j)) {
                if (!first) cout << ", ";
                cout << s->elements[j];
                first = false;
            }
        }
        cout << "}\n";
    }
}

void SetOperations::cartesianProduct(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return;
    }
    cout << "\nCARTESIAN PRODUCT\n\n";
    cout << a->name << " x " << b->name << " = {\n";
    int count = 0;
    for (int i = 0; i < a->size; i++) {
        for (int j = 0; j < b->size; j++) {
            cout << "  (" << a->elements[i] << ", " << b->elements[j] << ")";
            count++;
            if (count < a->size * b->size) cout << ",";
            cout << "\n";
        }
    }
    cout << "}\n";
    cout << "Cardinality: |" << a->name << " x " << b->name << "| = " << a->size << " x " << b->size << " = " << (a->size * b->size) << "\n";
}

SetOperations::Set* SetOperations::complement(const string& setName, const string& universalSetName) {
    Set* s = getSet(setName);
    Set* u = getSet(universalSetName);
    if (!s || !u) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }
    Set* result = new Set(setName + "_COMPLEMENT");
    for (int i = 0; i < u->size; i++) {
        if (!s->contains(u->elements[i])) result->addElement(u->elements[i]);
    }
    cout << "\nCOMPLEMENT OPERATION\n\n";
    cout << setName << "' (complement with respect to " << universalSetName << ") = ";
    result->display();
    return result;
}

void SetOperations::findStudentsInBothCourses(const string& course1, const string& course2) {
    cout << "\nFIND STUDENTS IN BOTH COURSES\n\n";
    Set* result = intersectionSets(course1, course2);
    if (result && result->size > 0) {
        cout << "\nStudents enrolled in both " << course1 << " and " << course2 << ":\n";
        for (int i = 0; i < result->size; i++) cout << "  " << (i + 1) << ". " << result->elements[i] << "\n";
        cout << "\nTotal: " << result->size << " students\n";
    }
    else cout << "No students found in both courses.\n";
    if (result) delete result;
}

void SetOperations::findStudentsInEitherCourse(const string& course1, const string& course2) {
    cout << "\nFIND STUDENTS IN EITHER COURSE\n\n";
    Set* result = unionSets(course1, course2);
    if (result && result->size > 0) {
        cout << "\nStudents enrolled in either " << course1 << " or " << course2 << ":\n";
        for (int i = 0; i < result->size; i++) cout << "  " << (i + 1) << ". " << result->elements[i] << "\n";
        cout << "\nTotal: " << result->size << " students\n";
    }
    else cout << "No students found.\n";
    if (result) delete result;
}

void SetOperations::findStudentsOnlyInOneCourse(const string& course1, const string& course2) {
    cout << "\nFIND STUDENTS ONLY IN ONE COURSE\n\n";
    Set* a = getSet(course1);
    Set* b = getSet(course2);
    if (!a || !b) {
        cout << "One or both courses not found.\n";
        return;
    }
    Set* result = new Set(course1 + "_ONLY_ONE_" + course2);
    for (int i = 0; i < a->size; i++) {
        if (!b->contains(a->elements[i])) result->addElement(a->elements[i]);
    }
    for (int i = 0; i < b->size; i++) {
        if (!a->contains(b->elements[i])) result->addElement(b->elements[i]);
    }
    if (result->size > 0) {
        cout << "\nStudents enrolled in only one of " << course1 << " or " << course2 << ":\n";
        for (int i = 0; i < result->size; i++) cout << "  " << (i + 1) << ". " << result->elements[i] << "\n";
        cout << "\nTotal: " << result->size << " students\n";
    }
    else cout << "No students found.\n";
    delete result;
}

void SetOperations::findCommonFaculties(const string& dept1, const string& dept2) {
    cout << "\nFIND COMMON FACULTIES\n\n";
    Set* result = intersectionSets(dept1, dept2);
    if (result && result->size > 0) {
        cout << "\nFaculties teaching in both " << dept1 << " and " << dept2 << ":\n";
        for (int i = 0; i < result->size; i++) cout << "  " << (i + 1) << ". " << result->elements[i] << "\n";
        cout << "\nTotal: " << result->size << " faculties\n";
    }
    else cout << "No common faculties found.\n";
    if (result) delete result;
}

void SetOperations::demonstrateSetOperations() {
    cout << "\nSET OPERATIONS DEMONSTRATION\n\n";
    cout << "[PART 1: CREATING SETS]\n\n";
    createSet("A");
    addElementToSet("A", "1");
    addElementToSet("A", "2");
    addElementToSet("A", "3");
    createSet("B");
    addElementToSet("B", "2");
    addElementToSet("B", "3");
    addElementToSet("B", "4");
    createSet("C");
    addElementToSet("C", "1");
    addElementToSet("C", "2");
    displayAllSets();
    cout << "\n[PART 2: UNION]\n";
    Set* unionResult = unionSets("A", "B");
    if (unionResult) delete unionResult;
    cout << "\n[PART 3: INTERSECTION]\n";
    Set* intersectResult = intersectionSets("A", "B");
    if (intersectResult) delete intersectResult;
    cout << "\n[PART 4: DIFFERENCE]\n";
    Set* diffResult = differenceSets("A", "B");
    if (diffResult) delete diffResult;
    cout << "\n[PART 5: SUBSET RELATIONS]\n";
    cout << "\nIs C subset of A? " << (isSubset("C", "A") ? "Yes" : "No") << "\n";
    cout << "Is A subset of B? " << (isSubset("A", "B") ? "Yes" : "No") << "\n";
    cout << "Is C proper subset of A? " << (isProperSubset("C", "A") ? "Yes" : "No") << "\n";
    cout << "\n[PART 6: DISJOINT CHECK]\n";
    cout << "Are A and B disjoint? " << (areDisjoint("A", "B") ? "Yes" : "No") << "\n";
    cout << "\n[PART 7: POWER SET]\n";
    generatePowerSet("C");
    cout << "\n[PART 8: CARTESIAN PRODUCT]\n";
    cartesianProduct("C", "C");
    cout << "\nDEMONSTRATION COMPLETED\n\n";
}

void SetOperations::testUniversityScenario() {
    cout << "\nUNIVERSITY SCENARIO TEST\n\n";
    cout << "[SCENARIO: STUDENT ENROLLMENT]\n\n";
    createSet("CS101");
    addElementToSet("CS101", "Alice");
    addElementToSet("CS101", "Bob");
    addElementToSet("CS101", "Charlie");
    addElementToSet("CS101", "David");
    createSet("MATH101");
    addElementToSet("MATH101", "Bob");
    addElementToSet("MATH101", "Charlie");
    addElementToSet("MATH101", "Eve");
    createSet("PHY101");
    addElementToSet("PHY101", "Alice");
    addElementToSet("PHY101", "Eve");
    addElementToSet("PHY101", "Frank");
    displayAllSets();
    findStudentsInBothCourses("CS101", "MATH101");
    findStudentsInEitherCourse("CS101", "MATH101");
    findStudentsOnlyInOneCourse("CS101", "MATH101");
    cout << "\n[SCENARIO: FACULTY DEPARTMENTS]\n\n";
    createSet("CS_Dept");
    addElementToSet("CS_Dept", "Prof_Ahmed");
    addElementToSet("CS_Dept", "Prof_Sara");
    addElementToSet("CS_Dept", "Prof_Khan");
    createSet("Math_Dept");
    addElementToSet("Math_Dept", "Prof_Sara");
    addElementToSet("Math_Dept", "Prof_Ali");
    displaySet("CS_Dept");
    displaySet("Math_Dept");
    findCommonFaculties("CS_Dept", "Math_Dept");
    cout << "\nUNIVERSITY SCENARIO TEST COMPLETED\n\n";
}
