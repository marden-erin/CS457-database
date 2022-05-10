#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
typedef void (*FuncType)(string);

//CreateD creates a folder by using the parameter being passed as the folder name.
//It also deletes all the contents of the user.txt folder
void createD(string x)
{
  ofstream myFile("user.txt");
  myFile.open("user.txt", std::ofstream::out | std::ofstream::trunc);
  if (!myFile.eof())
  {
    myFile.close();
  }

  if (mkdir(x.c_str(), 0777) == -1)
  {
    cout << "!Failed to create " << x << " because it already exists" << endl;
  }
  else
  {
    cout << "Database " << x << " created." << endl;
  }
}

//CreateT opens the file user.txt and whatever is written there is the directory that we are using.
//If the directory is changed then it opens function.txt and reads from that file and copies it into the new file.
//CHECKING TO SEE IF THE FILEE ALREADY EXSISTS DOES NOT WORK YET--WILL OVEERRIDE OLD FILE
void createT(string x)
{
  string myText;
  ifstream MyReadFile("function.txt");
  // reading a file
  if (MyReadFile.is_open())
  {
    string test;
    ifstream ope("user.txt"); // reading a file
    getline(ope, test);

    if (chdir(test.c_str()) != 0)
    {
      cout << "!Failed to create table " << x << " because it already exists." << endl;
    }

    else
    {
      cout << "Table " << x << " created." << endl;
      getline(MyReadFile, myText);
      ofstream table(x.c_str());
      table << myText;
      table.close();
    }
  }
  else
  {
    cout << "Unable to open file";
  }
  MyReadFile.close();
}
void access(string x)
{
  // empty
}

//delT deletes the file indicated by the parameter beeing passed. Using user.txt it navigates to the correct folder. 
void delT(string x)
{
  string myText;
  ifstream MyReadFile("user.txt"); // reading a file
  if (MyReadFile.is_open())
  {
    while (!MyReadFile.eof())
    {
      getline(MyReadFile, myText);
      if (chdir(myText.c_str()) != 0)
      {
        cout << "!Failed to delete " << x << " because it does not exist." << endl;
      }
      else
      {
        fstream f;
        f.open(x.c_str());
        f.close();
        if (remove(x.c_str()) == 0)
        {
          cout << "Table " << x << " deleted." << endl;
        }
        else
        {
          cout << "Unable to delete the file" << endl;
        }
      }
    }
  }
  else
  {
    cout << "Unable to open file";
  }
  MyReadFile.close();
}

//delD deletes a folder by using the parameter being passed as the folder name.
//It also deletes all the contents of the user.txt folder
void delD(string x)
{
  ofstream myFile("user.txt");
  myFile.open("user.txt", std::ofstream::out | std::ofstream::trunc);
  if (!myFile.eof())
  {
    myFile.close();
  }
  if (remove(x.c_str()))
  {
    cout << "!Failed to delete " << x << " because it does not exist" << endl;
  }
  else
  {
    cout << "Database " << x << " deleted" << endl;
  }
}

int main(int argc, char *argv[])
{

  //map to decide what functions to use
  map<string, FuncType> tmap;
  if (string(argv[1]) == "CREATE" && string(argv[2]) == "DATABASE")
  {
    tmap["CREATE"] = createD;
  }
  if (string(argv[1]) == "CREATE" && string(argv[2]) == "TABLE")
  {
    tmap["CREATE"] = createT;
  }

  tmap["USE"] = access;

  if (string(argv[1]) == "DROP" && string(argv[2]) == "DATABASE")
  {
    tmap["DROP"] = delD;
  }
  if (string(argv[1]) == "DROP" && string(argv[2]) == "TABLE")
  {
    tmap["DROP"] = delT;
  }

  //creates function.txt and writes all parameters to it
  //DOES NOT WORK FOR PARANTHESIS
  //string b is the name of the new file that is going to be passed
  if (argc > 4)
  {
    ofstream table("function.txt");
    for (int i = 4; i < argc; i++)
    {
      string p = argv[i];
      table << p << " ";
    }
    table.close();
    string b = argv[3];
    tmap[argv[1]](b);
  }

  //string b is the name of the file being passed
  if (argc == 4)
  {
    string b = argv[3];
   // cout << b;
    tmap[argv[1]](b);
  }

  //creates user.txt and writes what databasee we want used to the file
  if (argc == 3)
  {
    string b = argv[2];
    ofstream MyFile("user.txt");
    MyFile << b;
    MyFile.close();
    cout << "Using database " << b << "." << endl;
    tmap[argv[1]](b);
  }

  //EXIT
  if (argc == 2)
  {
    string b = argv[1];
    cout << "All done." << endl;

    return 0;
  }

  return 0;
}
