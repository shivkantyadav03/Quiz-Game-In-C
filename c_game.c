#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUESTIONS 15
#define MAX_OPTIONS 4
#define MAX_STACK_SIZE 100
#define MAX_NAME_LENGTH 100

// Function declarations
void initStack(int stack[], int *top);
int isFullStack(int top);
int isEmptyStack(int top);
void push(int stack[], int *top, int score);
int pop(int stack[], int *top);
void playQuiz(char questions[][256], char options[][MAX_OPTIONS][100], int correctOptions[], char playerName[]);
void shuffleOptions(char options[][MAX_OPTIONS][100], int correctOptions[]);

int main() {
    srand(time(NULL)); // Seed for random number generation

    // Player information
    printf("                                                       WELCOME TO THE QUIZ GAME\n");
    printf("\n \n \n");
    char playerName[MAX_NAME_LENGTH];
    printf("Enter your name: ");
    scanf("%s", playerName);

    // Array of questions and options
    char questions[MAX_QUESTIONS][256] = {
        "What is the value of x if 2x + 3 = 15?",
        "Solve for x: 3(x - 8) = -12",
        "What is the area of a triangle with base 10 and height 5?",
        "What is the value of sin(30 degrees)?",
        "What is the value of 5 factorial (5!)?",
        "What is the derivative of sin(x)?",
        "If a triangle has sides 5, 12, and 13, is it a right triangle?",
        "What is the area of a circle with radius 7?",
        "What is the value of log10(100)?",
        "What is the sum of the interior angles of a triangle?",
        "What is the molar mass of carbon dioxide (CO2)?",
        "What is the chemical formula for sulfuric acid?",
        "What is the primary function of ribosomes in a cell?",
        "What is the universal gas constant (R) in J/(mol·K)?",
        "What is the main component of Earth's atmosphere?"
    };

    char options[MAX_QUESTIONS][MAX_OPTIONS][100] = {
        {"6", "8", "10", "7"}, // Q1
        {"x = 8", "x = 4", "x = 12", "x = 2"}, // Q2
        {"25", "50", "15", "30"}, // Q3
        {"0.33", "0.50", "1", "0.25"}, // Q4
        {"120", "60", "30", "24"}, // Q5
        {"cos(x)", "1", "sin(x)", "tan(x)"}, // Q6
        {"Yes", "No", "It depends", "Only if angle is right"}, // Q7
        {"154", "153.94", "148", "153"}, // Q8
        {"2", "10", "3", "1"}, // Q9
        {"180 degrees", "360 degrees", "90 degrees", "120 degrees"}, // Q10
        {"34 g/mol", "32 g/mol", "28 g/mol", "44 g/mol"}, // Q11
        {"H2SO4", "HCl", "NaOH", "CO2"}, // Q12
        {"Protein synthesis", "Energy production", "Cell division", "DNA replication"}, // Q13
        {"8.314", "0.0821", "1.987", "3.14159"}, // Q14 (corrected R value)
        {"Nitrogen", "Oxygen", "Carbon Dioxide", "Hydrogen"} // Q15
    };

    // Updated correct options
    int correctOptions[MAX_QUESTIONS] = {0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 3, 0, 0, 0, 1};

    printf("Welcome to the Quiz Game, %s!\n", playerName);
    playQuiz(questions, options, correctOptions, playerName); // Start the quiz

    return 0;
}

// Function to initialize the score stack
void initStack(int stack[], int *top) {
    *top = -1;
}

// Function to check if the stack is full
int isFullStack(int top) {
    return top == MAX_STACK_SIZE - 1;
}

// Function to check if the stack is empty
int isEmptyStack(int top) {
    return top == -1;
}

// Function to push a score onto the stack
void push(int stack[], int *top, int score) {
    if (!isFullStack(*top)) {
        stack[++(*top)] = score;
    }
}

// Function to pop a score from the stack
int pop(int stack[], int *top) {
    if (!isEmptyStack(*top)) {
        return stack[(*top)--];
    }
    return 0; // Default return if empty
}

// Function to shuffle options and update correct answers accordingly
void shuffleOptions(char options[][MAX_OPTIONS][100], int correctOptions[]) {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        for (int j = MAX_OPTIONS - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            // Swap options
            for (int l = 0; l < 100; l++) {
                char temp = options[i][j][l];
                options[i][j][l] = options[i][k][l];
                options[i][k][l] = temp;
            }
            // Update correct option index if it was swapped
            if (correctOptions[i] == j) {
                correctOptions[i] = k;
            } else if (correctOptions[i] == k) {
                correctOptions[i] = j;
            }
        }
    }
}

// Function to play the quiz
void playQuiz(char questions[][256], char options[][MAX_OPTIONS][100], int correctOptions[], char playerName[]) {
    int scoreStack[MAX_STACK_SIZE];
    int top = -1;
    int score = 0;
    int answer, questionIndex;

    // Shuffle questions and options
    for (int i = MAX_QUESTIONS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap questions
        char tempQ[256];
        char tempO[MAX_OPTIONS][100];
        int tempC;

        // Swap questions
        for (int k = 0; k < 256; k++) {
            tempQ[k] = questions[i][k];
            questions[i][k] = questions[j][k];
            questions[j][k] = tempQ[k];
        }

        // Swap options
        for (int k = 0; k < MAX_OPTIONS; k++) {
            for (int l = 0; l < 100; l++) {
                tempO[k][l] = options[i][k][l];
                options[i][k][l] = options[j][k][l];
                options[j][k][l] = tempO[k][l];
            }
        }

        // Swap correct options
        tempC = correctOptions[i];
        correctOptions[i] = correctOptions[j];
        correctOptions[j] = tempC;
    }

    // Shuffle options
    shuffleOptions(options, correctOptions);

    // Play the quiz
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        questionIndex = i; // Use shuffled index
        printf("\nQuestion %d: %s\n", i + 1, questions[questionIndex]);
        for (int j = 0; j < MAX_OPTIONS; j++) {
            char optionChar = 'a' + j; // Convert index to lowercase letter (a, b, c, d)
            printf("%c. %s\n", optionChar, options[questionIndex][j]);
        }

        // Include the exit option
        printf("Enter your answer (a-%c) or 'e' to exit: ", 'a' + MAX_OPTIONS - 1);
        char input;
        scanf(" %c", &input); // Read a character input

        if (input == 'e') {
            printf("You chose to exit the quiz early.\n");
            printf("Your scores for each question:\n");
            while (!isEmptyStack(top)) {
                int poppedScore = pop(scoreStack, &top);
                printf("Question %d score: %d\n", top + 1, poppedScore); // Display score with question number
            }
            printf("Your current score is: %d\n", score);
            return; // Exit the quiz
        }

        // Convert input character to index
        answer = input - 'a';

        // Check answer and calculate score
        if (answer >= 0 && answer < MAX_OPTIONS) {
            if (answer == correctOptions[questionIndex]) {
                printf("Correct!\n");
                score += 10; // +10 for correct answer
                push(scoreStack, &top, 10); // Store +10 score in stack
            } else {
                printf("Wrong! The correct answer was: %s\n", options[questionIndex][correctOptions[questionIndex]]);
                score -= 5; // -5 for incorrect answer
                push(scoreStack, &top, -5); // Store -5 score in stack
            }
        } else {
            printf("Invalid input. Please try again.\n");
            i--; // Decrement i to repeat the question
        }
    }

    printf("\nYour final score is: %d\n", score);
    printf("Scores during the game:\n");
    int total = 0;
    while (!isEmptyStack(top)) {
        int poppedScore = pop(scoreStack, &top);
        printf("Question %d score: %d\n", top + 1, poppedScore); // Display score with question number
        total += poppedScore; // Calculate total score from stack
    }
    printf("Total score from stack: %d\n", total);
}
