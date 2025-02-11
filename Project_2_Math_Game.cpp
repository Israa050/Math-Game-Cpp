
#include <iostream>
using namespace std;

enum enQuestionLevel {EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4};

enum enOperationType{Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz {
    stQuestion QuestionsList[100];
    short NumberOfQuestions  = 0;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    int NumberOfRightAnswers = 0;
    int NumberOfWrongAnswers = 0;
    bool isPass = false;
};

int RandomNumber(int From, int To) {
        int random = rand() % (To - From + 1) + From;
        return random;
}

enOperationType GetRandomOpType() {
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

short ReadHowManyQuestion() {
    short NumberOfQuestions = 1;
    do {
        cout << "How Many Questions do you wnat to answer ? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}

enQuestionLevel ReadQuestionLevel() {
    short QuestionLevel = 1;
    do {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel >4);

    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType() {
    short OpType = 1;
    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mul:
        return Number1 * Number2;
    case enOperationType::Div: 
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType) {
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::Mix) {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOpType();
    }

    Question.OpType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz) {

    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
        Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

string GetOpTypeSymbol(enOperationType OpType) {
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mul:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

void PrintTheQuestion(stQuizz &Quizz, short QuestionNumber) {
    cout << "\n";     
    cout << "Question [" << QuestionNumber + 1 << "/" 
        << Quizz.NumberOfQuestions << "] \n\n";     
    cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;    
    cout << Quizz.QuestionsList[QuestionNumber].Number2 << " ";     
    cout << GetOpTypeSymbol(Quizz.QuestionsList[QuestionNumber].OpType);    
    cout << "\n_________" << endl;
}

int ReadQuestionAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void SetScreenColor(bool Right) {
    if(Right)
        system("color 2F");
    else {
        system("color 4F");
        cout << "\a";
    }
        
}

void CorrectTheQuestionAnswer(stQuizz &Quizz, short QuestionNumber) {
    if (Quizz.QuestionsList[QuestionNumber].PlayerAnswer != Quizz.QuestionsList[QuestionNumber].CorrectAnswer) {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Worng Answer :-( \n";         
        cout << "The right answer is: ";           
        cout << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;           
        cout << "\n";
    }
    else 
    {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "Right Answer :-) \n";

    }

    cout << endl;

    SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {

        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
    //SetScreenColor(Quizz.isPass);
}

string GetFinalResultsText(bool isPass) {
    if (isPass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
    string arrQuestionLevel[4] = { "Easy","Med","Hard","Mix" };
    return arrQuestionLevel[QuestionLevel - 1];
}

void PrintQuizzResults(stQuizz Quizz) {
    cout << "\n";      cout << "______________________________\n\n";
    cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";

    SetScreenColor(Quizz.isPass);
}

void PlayMathGame() {
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestion();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {

    char PlayAgain = 'Y';

    do {
        ResetScreen();
        PlayMathGame();

        cout << "\n" << "Do you want to play again ? Y/N ?";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

}
