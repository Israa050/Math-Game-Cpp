
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

//
//
//struct stGameResults
//{
//    short NumberOfQuestions = 0;
//    enQuizzLevel QuestionsLevel;
//    enOpType OpType;
//    short NumberOfRightAnswers = 0;
//    short NumberOfWrongAnswers = 0;
//};
//
//int RandomNumber(int From, int To) {
//    int random = rand() % (To - From + 1) + From;
//    return random;
//}
//
//enPassFail Winner(stGameResults GameResults) {
//    if (GameResults.NumberOfRightAnswers >= GameResults.NumberOfWrongAnswers)
//        return enPassFail::Pass;
//    else
//        return enPassFail::Fail;
//}
//
//string PassFailName(enPassFail PassFail) {
//    if (PassFail == enPassFail::Pass)
//        return "Pass :-) ";
//    else
//        return "Fail :-( ";
//}
//
//int GenerateNumberInRange(enQuizzLevel QuizzLevel) {
//    switch (QuizzLevel)
//    {
//    case enQuizzLevel::Easy: {
//        return RandomNumber(1, 10);
//    }
//    case enQuizzLevel::Medume: {
//        return RandomNumber(11, 50);
//    }
//    case enQuizzLevel::Hard: {
//        return RandomNumber(50, 100);
//    }
//    default:
//        return RandomNumber(1, 100);
//        break;
//    }
//}
//
//char GeneraterOpType(enOpType OpType) {
//
//    char arrOpType[4] = { '+','-','*','/' };
//    if (OpType == 5) {
//        short randomOP = RandomNumber(1, 4);
//        return arrOpType[randomOP - 1];
//    }
//    else
//        return arrOpType[OpType - 1];
//}
//
//int CalculateQuizzQuestion(int num1, int num2, char opType) {
//    switch (opType)
//    {
//    case '+':
//        return num1 + num2;
//    case '-':
//        return num1 - num2;
//    case '*':
//        return num1 * num2;
//    case '/':
//        return num1 / num2;
//    }
//}
//
//int GenerateQuizzQuestion(stQuizz Quizz) {
//    int num1 = GenerateNumberInRange(Quizz.QuizzLevel);
//    int num2 = GenerateNumberInRange(Quizz.QuizzLevel);
//    char opType = GeneraterOpType(Quizz.OpType);
//
//    int answer = CalculateQuizzQuestion(num1, num2, opType);
//
//    cout << "\n" << num1 << endl;
//    cout << num2 << " " << opType << endl;
//    cout << "-------------\n";
//
//    return answer;
//}
//
//int HowManyQuestions() {
//    int NumberOfQuestions = 0;
//    do {
//        cout << "How Many Questions do you wnat to answer ? ";
//        cin >> NumberOfQuestions;
//    } while (NumberOfQuestions < 0);
//
//    return NumberOfQuestions;
//}
//
//enQuizzLevel ReadQuizzLevel() {
//    short Level = 1;
//    do {
//        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
//        cin >> Level;
//    } while (Level < 1 || Level > 4);
//
//    return (enQuizzLevel)Level;
//}
//
//enOpType ReadOperationType() {
//    short OpType = 1;
//    do {
//        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
//        cin >> OpType;
//    } while (OpType < 1 || OpType > 5);
//
//    return (enOpType)OpType;
//}
//
//void ChangeScreenColor(enPassFail PassFail) {
//    if (PassFail == enPassFail::Pass) {
//        system("color 2F");
//    }
//    else {
//        system("color 4F");
//        cout << "\a";
//    }
//}
//
//enPassFail PrintResult(int userAnswer, int correctAnswer) {
//    if (userAnswer == correctAnswer) {
//        cout << "Right Answer :-) \n";
//        return enPassFail::Pass;
//    }
//    else {
//        cout << "Wrong Answer :-( \n";
//        cout << "The right answer is: " << correctAnswer << endl;
//        return enPassFail::Fail;
//    }
//}
//
//stGameResults FillGameResults(short NumberOfQuestion, int NumberOfRightAnswers, int NumberOfWrongAnswer, stQuizz Quizz) {
//    stGameResults GameResults;
//    GameResults.QuestionsLevel = Quizz.QuizzLevel;
//    GameResults.OpType = Quizz.OpType;
//    GameResults.NumberOfQuestions = NumberOfQuestion;
//    GameResults.NumberOfRightAnswers = NumberOfRightAnswers;
//    GameResults.NumberOfWrongAnswers = NumberOfWrongAnswer;
//
//    return GameResults;
//}
//
//stGameResults PlayGame(short HowManyQuestion) {
//
//    stQuizz Quizz;
//    Quizz.QuizzLevel = ReadQuizzLevel();
//    Quizz.OpType = ReadOperationType();
//    int UserAnswer = 0;
//    int CorrectAnswer = 0;
//    int NumberOfRightAnswers = 0;
//    int NumberOfWrongAnswers = 0;
//
//    for (int Question = 1; Question <= HowManyQuestion; Question++) {
//        cout << "\n\n";
//        cout << "Question  [" << Question << "/" << HowManyQuestion << "]:\n\n";
//        CorrectAnswer = GenerateQuizzQuestion(Quizz);
//        cin >> UserAnswer;
//        enPassFail PassFail = PrintResult(UserAnswer, CorrectAnswer);
//        ChangeScreenColor(PassFail);
//
//        if (PassFail == enPassFail::Pass)
//            NumberOfRightAnswers++;
//        else
//            NumberOfWrongAnswers++;
//
//    }
//
//    stGameResults GameResults;
//    return FillGameResults(HowManyQuestion, NumberOfRightAnswers, NumberOfWrongAnswers, Quizz);
//}
//
//void ResetScreen() {
//    system("cls");
//    system("color 0F");
//}
//
//string QuizzLevelName(enQuizzLevel QuizzLevel) {
//    string arrQuizzLevel[4] = { "Easy", "Medium", "Hard", "Mix" };
//    return arrQuizzLevel[QuizzLevel - 1];
//}
//
//string OpTypeName(enOpType OpType) {
//    string arrOpType[5] = { "Add","Sub","Mul","Div","Mix" };
//    return arrOpType[OpType - 1];
//}
//
//void ShowPassFailScreen(stGameResults GameResults) {
//    cout << "\n\n" << endl;
//    cout << "----------------------------------\n";
//    cout << "Final Results is " << PassFailName(Winner(GameResults)) << endl;
//    cout << "----------------------------------\n";
//
//}
//
//void ShowFinalResultsScreen(stGameResults GameResults) {
//    ShowPassFailScreen(GameResults);
//    cout << "Number of Questions: " << GameResults.NumberOfQuestions << endl;
//    cout << "Questions Level    : " << QuizzLevelName(GameResults.QuestionsLevel) << endl;
//    cout << "OpType             : " << OpTypeName(GameResults.OpType) << endl;
//    cout << "Number of Right Answers: " << GameResults.NumberOfRightAnswers << endl;
//    cout << "Number of Wrong Answers: " << GameResults.NumberOfWrongAnswers << endl;
//    cout << "----------------------------------\n";
//    ChangeScreenColor(Winner(GameResults));
//}
