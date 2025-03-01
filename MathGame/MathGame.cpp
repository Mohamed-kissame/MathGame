#include <iostream>
#include <cstdlib>

using namespace std;

enum enLevlQuestion { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion {

	int number1 = 0;
	int number2 = 0;
	enOperationType OperationType;
	enLevlQuestion QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;

};

struct stQuizz {

	stQuestion QuestionList[100];
	short NumberOfQuestion;
	enLevlQuestion LvlQuestion;
	enOperationType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};

short ReadHowManyQuestions() {

	short numberOfQuestion;

	do {

		cout << "How Many Questions do you want To answer ? : ";
		cin >> numberOfQuestion;
	} while (numberOfQuestion < 1 || numberOfQuestion > 10);

	return numberOfQuestion;
}

enLevlQuestion AskForLevlOfQuestion() {

	short QuestionLevel = 0;

	do {

		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enLevlQuestion)QuestionLevel;
}

enOperationType ChoiceOperationType() {

	short OpType;

	do {

		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

string GetOpTypeSymbol(enOperationType opType) {

	switch (opType) {

	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}

}

string GetQuestionLevelText(enLevlQuestion QuestionLevel) {

	string arrQuestionLevel[4] = { "Easy","Med","Hard","Mix" };

	return arrQuestionLevel[QuestionLevel - 1];
}

int RandomNumber(int From, int To) {

	int randNumber = rand() % (To - From + 1) + From;
	return randNumber;
}

void SetScreenColor(bool Right) {

	if (Right)
		system("color 2F");
	else {

		system("color 4F");
		cout << "\a";
	}
}

int  SimpleCalculate(int number1, int number2, enOperationType opType) {

	switch (opType) {

	case enOperationType::Add:
		return number1 + number2;
	case enOperationType::Sub:
		return number1 - number2;
	case enOperationType::Mult:
		return number1 * number2;
	case enOperationType::Div:
		return number1 / number2;
	default:
		return number1 + number2;
	}
}

enOperationType GetRandomOperationType() {

	return (enOperationType)RandomNumber(1, 4);
}

stQuestion GenerateQuestion(enLevlQuestion QuestionLevel, enOperationType opType) {

	stQuestion Question;

	if (QuestionLevel == enLevlQuestion::Mix) {

		QuestionLevel = (enLevlQuestion)RandomNumber(1, 3);
	}

	if (opType == enOperationType::MixOp) {

		opType = (enOperationType)GetRandomOperationType();
	}

	Question.OperationType = opType;

	switch (QuestionLevel) {

	case enLevlQuestion::EasyLevel:
		Question.number1 = RandomNumber(1, 10);
		Question.number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculate(Question.number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enLevlQuestion::MedLevel:
		Question.number1 = RandomNumber(10, 50);
		Question.number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculate(Question.number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enLevlQuestion::HardLevel:
		Question.number1 = RandomNumber(50, 100);
		Question.number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculate(Question.number1, Question.number2, Question.OperationType);
		return Question;
	}

	return Question;
}

void GenerateQuizzQuestion(stQuizz& Quizz) {

	for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++) {

		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.LvlQuestion, Quizz.OpType);
	}
}

int ReadQuestionAnswer() {

	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintteQuestion(stQuizz& Quizz, short QuestionNumber) {

	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "] \n\n";

	cout << Quizz.QuestionList[QuestionNumber].number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].number2 << endl;

	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n____________" << endl;
}

void CorrectTheQuestion(stQuizz& Quizz, short QuestionNumber) {

	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {

		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-(";
		cout << "The Right Answer is : ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";

	}

	else {

		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}

	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz) {


	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++) {

		PrintteQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestion(Quizz, QuestionNumber);

	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass) {

	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz) {

	cout << "\n";
	cout << "_______________________________________\n\n";


	cout << "Final Results is " << GetFinalResultsText(Quizz.isPass);

	cout << "\n_______________________________________\n\n";

	cout << "Number of Question  : "

		<< Quizz.NumberOfQuestion << endl;

	cout << "Questions Level     : "
		<< GetQuestionLevelText(Quizz.LvlQuestion) << endl;

	cout << "OpType              : "

		<< GetOpTypeSymbol(Quizz.OpType) << endl;

	cout << "Number of Right Answer : "

		<< Quizz.NumberOfRightAnswers << endl;

	cout << "Number of Wrong Answer : "

		<< Quizz.NumberOfWrongAnswers << endl;


	cout << "_______________________________________\n\n";
}

void PlayMathGame() {

	stQuizz Quizz;

	Quizz.NumberOfQuestion = ReadHowManyQuestions();
	Quizz.LvlQuestion = AskForLevlOfQuestion();
	Quizz.OpType = ChoiceOperationType();

	GenerateQuizzQuestion(Quizz);

	AskAndCorrectQuestionListAnswer(Quizz);

	PrintQuizzResults(Quizz);
}

void RestScreen() {

	system("cls");
	system("color 0F");
}

void StartGame() {

	char PlayAgain = 'Y';

	do {

		RestScreen();
		PlayMathGame();

		cout << "Do you want play again : Y/N ?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {

	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}