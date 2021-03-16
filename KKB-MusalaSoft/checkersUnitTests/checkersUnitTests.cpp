#include "pch.h"
#include "CppUnitTest.h"
#include "../KKB-MusalaSoft/CustomDataTypes.h" 
#include "../KKB-MusalaSoft/CustomOperators.h"
#include "../KKB-MusalaSoft/DataLayerFunctions.h" 
#include "../KKB-MusalaSoft/DisplayFunctions.h" 
#include "../KKB-MusalaSoft/FilterFunctions.h"
#include "../KKB-MusalaSoft/FunctionsFromCustomDataTypes.h"
#include "../KKB-MusalaSoft/GlobalVariables.h"
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace checkersUnitTests
{
	TEST_CLASS(checkersUnitTests)
	{
	public:
		
		TEST_METHOD(checksIfStudentExist)
		{
			vector<STUDENT> studentsList;
			studentsList.push_back({ 1, "Pencho", "Velikov", "QA", "PMVelikov18@test.test", "A", 10, 5.31 });
			studentsList.push_back({ 2, "Slavi", "Gochev", "backend", "PGDqkov18@test.test", "V", 8, 5.12 });
			STUDENT student1, student2;
			student1 = { 1, "Pencho", "Velikov", "QA", "PMVelikov18@test.test", "A", 10, 5.31 };
			student2 = { 2, "Slavi", "Dimitrov", "scrumtrainer", "PDStoichev18@test.test", "B", 9, 5.26 };

			bool checker1 = checkIfStudentExist(student1, studentsList);
			bool checker2 = checkIfStudentExist(student2, studentsList);

			Assert::AreEqual(true, checker1);
			Assert::AreEqual(false, checker2);
		}

		TEST_METHOD(checksIfTeamExist)
		{
			vector<TEAM> teams;
			teams.push_back({ 1, "KKB", "Our team", "3.07.2021", "free" });
			teams.push_back({ 2, "KKG", "Their team", "2.07.2021", "confirmed" });
			TEAM team1 = { 1, "KKB", "Our team", "3.07.2021", "free" };
			TEAM team2 = { 2, "KKS", "PAST", "3.07.2021", "confirmed" };

			bool checker1 = checkIfTeamExist(team1, teams);
			bool checker2 = checkIfTeamExist(team2, teams);

			Assert::AreEqual(true, checker1);
			Assert::AreEqual(false, checker2);
		}
	};
}
