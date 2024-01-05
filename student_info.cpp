#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

struct Student {
    std::string name;
    int id;
    double assignmentScore;
    double quizScore;
    double examScore;
    double overallGrade;
    char letterGrade;
    std::string feedback;
};

// Function to get valid input within a specific range
template<typename T>
T getInputInRange(const std::string& prompt, T min, T max) {
    T input;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> input) || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a value between " << min << " and " << max << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}

// Function to calculate the overall grade based on weights
double calculateOverallGrade(double assignment, double quiz, double exam, double weightAssignment, double weightQuiz, double weightExam) {
    return (assignment * weightAssignment + quiz * weightQuiz + exam * weightExam);
}

// Function to determine letter grade based on the overall grade
char determineLetterGrade(double overallGrade) {
    if (overallGrade >= 90)
        return 'A';
    else if (overallGrade >= 80)
        return 'B';
    else if (overallGrade >= 70)
        return 'C';
    else if (overallGrade >= 60)
        return 'D';
    else
        return 'F';
}

// Function to provide feedback based on the letter grade
std::string provideFeedback(char letterGrade) {
    switch (letterGrade) {
        case 'A':
            return "Congratulations! Excellent performance!";
        case 'B':
            return "Good job! Keep up the good work.";
        case 'C':
            return "Fair performance. Room for improvement.";
        case 'D':
            return "Work harder to improve your grades.";
        default:
            return "Unfortunately, you have failed. Seek help and improve your scores.";
    }
}

int main() {
    std::vector<Student> students;
    char anotherStudent = 'y';

    while (tolower(anotherStudent) == 'y') {
        Student newStudent;
        std::cout << "Enter student name: ";
        std::getline(std::cin, newStudent.name);

        std::cout << "Enter student ID: ";
        newStudent.id = getInputInRange<int>("", 0, std::numeric_limits<int>::max());

        std::cout << "Enter assignment score (0-100): ";
        newStudent.assignmentScore = getInputInRange<double>("", 0, 100);

        std::cout << "Enter quiz score (0-100): ";
        newStudent.quizScore = getInputInRange<double>("", 0, 100);

        std::cout << "Enter exam score (0-100): ";
        newStudent.examScore = getInputInRange<double>("", 0, 100);

        double weightAssignment = getInputInRange<double>("Enter weight for assignments (0-1): ", 0.0, 1.0);
        double weightQuiz = getInputInRange<double>("Enter weight for quizzes (0-1): ", 0.0, 1.0);
        double weightExam = getInputInRange<double>("Enter weight for exams (0-1): ", 0.0, 1.0);

        newStudent.overallGrade = calculateOverallGrade(newStudent.assignmentScore, newStudent.quizScore, newStudent.examScore, weightAssignment, weightQuiz, weightExam);

        newStudent.letterGrade = determineLetterGrade(newStudent.overallGrade);

        newStudent.feedback = provideFeedback(newStudent.letterGrade);

        students.push_back(newStudent);

        std::cout << "Do you want to input data for another student? (y/n): ";
        std::cin >> anotherStudent;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\n\n-- Student Grades --\n";
    for (const auto& student : students) {
        std::cout << "\nStudent Name: " << student.name << std::endl;
        std::cout << "Student ID: " << student.id << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Overall Grade: " << student.overallGrade << std::endl;
        std::cout << "Letter Grade: " << student.letterGrade << std::endl;
        std::cout << "Feedback: " << student.feedback << std::endl;
    }

    return 0;
}
