#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/sql/sql.h"
#include "../../includes/table/table.h"
#include "../../includes/table/typedefs.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_select1(bool debug = false)
{
  bool debug2 = true;
  if(debug)
  {
    vectorstr v = {"fname", "lname", "age", "major", "Salary"};
    Table t("test_select", v);
    //student 1
    v = {"Alex", "Tatoian", "19", "CS", "100"};
    t.insert_into(v);
    //student 2
    v = {"Ryan", "Tokumoto", "20", "Art", "100"};
    t.insert_into(v);
    //student 3
    v = {"Matthew", "Karvelas", "19", "Art", "200"};
    t.insert_into(v);
    //student 4
    v = {"Matthew", "Le", "19", "CS", "400"};
    t.insert_into(v);
    //student 5
    v = {"Liam", "Carson", "12", "PE", "101"};
    t.insert_into(v);
    //student 6
    v = {"Patrick", "Xuerra", "11", "Math", "101"};
    t.insert_into(v);
    //student 7
    v = {"Qnoxx", "Decker", "11", "History", "500"};
    t.insert_into(v);
    if(debug)
      cout << "\n\n" << t << endl;

    //TESTING SELECT
    v = {"fname", "lname", "major"};
    Table newTable = t.select(v, {"lname", ">", "To", "and", "major", "=", "CS", "or", "age", "<", "20", "and", "Salary", "<=", "101"});
    if(debug)
      cout <<"Searching for first lname < Tatoian:" << t.select_recnos() << endl << newTable << endl;
    // cout << "OLD TABLE:\n" << t;
  }
  return true;
}

bool test_sql(bool debug = false)
{
  bool debug2 = false;
  if(debug)
  {
    SQL sql;
    Table t;
    Table playerTable;
    Table clubsTable;
    vectorstr commands = {
      "make table players fields fname, lname, age, position, team",
      "insert into players values Julian, Marin, 17, Winger, \"18AA\"",
      "insert into players values Adam, Scott, 17, Winger, \"18AA\"",
      "insert into players values Jared, Padilla, 18, Center, \"18AA\"",
      "insert into players values Anthony, Aceves, 17, Defense, \"18AA\"",
      "insert into players values Jayden, Deguzman, 16, Defense, \"16AA\"",
      "insert into players values Aiden, Zakaria, 16, Center, \"16AA\"",
      "insert into players values Collin, \"O'Brian\", 15, Winger, \"16AA\"",
      "insert into players values Rafe, Armstrong, 16, Defense, \"16AA\"",
      "insert into players values Taiki, Schneider, 16, Winger, \"16AA\"",
      "insert into players values Garion, Barber, 16, Center, \"16AA\"",
      "insert into players values Sebastian, Benavente, 16, Winger, \"16AA\"",
      "insert into players values Liam, Carson, 11, Defense, \"12B\"",
      "insert into players values Damien, Boucher, 11, Center, \"12B\"",
      "insert into players values Bella, Gao, 11, Winger, \"12B\"",
      "insert into players values Reagan, Ludlow, 11, Winger, \"12B\"",
      "insert into players values Patrick, Guerra, 12, Defense, \"12B\"",
      "insert into players values Qnoxx, \"Decker-Knealing\", 11, Winger, \"12B\"",
      "make table clubs fields name, numTeams, championships, \"year founded\"",
      "insert into clubs values Empire, 10, 06, 2010",
      "insert into clubs values \"Jr. Kings\", 20, 45, 1996",
      "insert into clubs values Wave, 16, 25, 2002",
      "insert into clubs values \"Jr. Ducks\", 22, 40, 1998",
      "insert into clubs values Bears, 18, 17, 1999",
      "insert into clubs values \"Maple Leafs\", 08, 03, 2004",
      "insert into clubs values OC, 12, 08, 2008"
    };
    for(int i = 0; i < commands.size(); i++)
    {
      cout << ">" << commands[i] << endl;
      t = sql.command(commands[i]);
      if(i == 17)
        playerTable = t;
      // cout << "__________\n\n" << t << "________\n"; //inserts and makes work
    }
    clubsTable = t;
    cout << playerTable << "______\n\n" << clubsTable << "\n_____\n";
    vectorstr select_commands = {
      // "select lname, age, fname from players where lname > G and fname < H or age <= 16"
      "select * from clubs",
      "select name from clubs where \"year founded\" <= 2001 and \"year founded\" > 2001",//and
      "select fname from players where position = Defense or age >= 17 and fName > J",//or and
      "select fname, lname from players where fname > H and lname < K and position = Defense",//and and
      "select team, fname from players where fname > J and fname < T or team >= \"16\" and age <= 17",//and or and
      "select lname, fname, age from players where position = Winger or age >=16 and position = Defense or lname < N",//or and or
      "select * from players where age > 19 or fname > J",//empty or full solution
      "select * from players where age <= 17 or fname = Alex",//full or empty
      "select * from players where age > 19 or fname = Alex",//empty or empty
      "select * from players where age > 19 and fname > J",//empty and full
      "select lname, fname, position from players where age <= 17 and fname = Alex",//full and empty
      "select lname, fname, position from players where age > 18 and fname = Alex",//empty and empty
      "select lname, fname, position from players where (age <= 16 or fname > J and (lname > D)) and position = Defense",
      "select lname, fname, position, team from players where age >= \"16\""
    };

    for(int i = 0; i < select_commands.size(); i++)
    {
      cout << "\n_____________\n\n" << ">" << select_commands[i] << endl << sql.command(select_commands[i]);
      cout << sql.select_recnos() << "_________\n\n";
    }
    
  }
  
  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_SQL, TestSQL)
{
  EXPECT_EQ(1, test_sql(1));
}

TEST(TEST_BRUH, TestBruh)
{
  EXPECT_EQ(1, test_select1());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

