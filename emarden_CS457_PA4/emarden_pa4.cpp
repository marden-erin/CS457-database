// Erin Marden
// Pa4

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <filesystem>

using namespace std;
typedef void (*FuncType)(string);

// CreateD creates a folder by using the parameter being passed as the folder name.
// It also deletes all the contents of the user.txt folder
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

// CreateT opens the file user.txt and whatever is written there is the directory that we are using.
// If the directory is changed then it opens function.txt and reads from that file and copies it into the new file.
// CHECKING TO SEE IF THE FILEE ALREADY EXSISTS DOES NOT WORK YET--WILL OVEERRIDE OLD FILE
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

// delT deletes the file indicated by the parameter beeing passed. Using user.txt it navigates to the correct folder.
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

// delD deletes a folder by using the parameter being passed as the folder name.
// It also deletes all the contents of the user.txt folder
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
void insert(string x)
{

  string myText;
  ifstream MyReadFile("function.txt");
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
      // ofstream append("function.txt", ios::app);
      getline(MyReadFile, myText);
      ofstream table(x.c_str(), ios::app);
      cout << "1 new record inserted." << endl;
      table << "\n";
      table << myText;
      table.close();
    }
  }
}

void split(string str, char del)
{
  // declaring temp string to store the curr "word" upto del
  string temp = "";
  string split = temp + " | ";
  ofstream test("function.txt", ios::app);
  for (int i = 0; i < (int)str.size(); i++)
  {
    // If cur char is not del, then append it to the cur "word", otherwise
    // you have completed the word, print it, and start a new word.
    if (str[i] != del)
    {
      temp += str[i];
    }
    else
    {
      // cout << temp << " | ";

      test << temp << " | ";

      temp = "";
    }
  }
  test.close();

  // return split;
}

// how the select* function works: reads the directory from user.txt
// changes into that folder
// the string x being passed is the file we want access to
// opens and then prints whats in it
void select(string x)
{

  string myText;
  ifstream MyReadFile("function.txt");
  if (MyReadFile.is_open())
  {
    string test;
    ifstream ope("user.txt"); // reading a file
    getline(ope, test);

    if (chdir(test.c_str()) != 0)
    {
      cout << "uh-oh does not work" << endl;
    }

    else
    {

      ifstream table(x.c_str());
      string text;
      while (table)
      {
        getline(table, text);
        cout << text << endl;
      }
      table.close();
    }
  }
}

void selectPart()
{

  string whereChoice;
  string whereChanged;
  string op;
  string newOp;
  string t;
  ifstream outfile("where.txt");
  // cout << setChanged << endl;
  outfile >> whereChoice >> op >> whereChanged;
  outfile.close();
  ofstream file("where.txt");
  file.open("where.txt", std::ofstream::out | std::ofstream::trunc);
  if (!file.eof())
  {
    file.close();
  }

  ifstream open("select.txt");
  string first;
  string second;
  string third;
  string f, s, tt;
  char del;
  string n, pt;
  open >> n >> pt;
  open.close();
  remove("select.txt");
  string myText;
  ifstream MyReadFile("from.txt");
  if (MyReadFile.is_open())
  {
    string test;
    ifstream ope("user.txt"); // reading a file
    getline(ope, test);

    if (chdir(test.c_str()) != 0)
    {
      cout << "uh-oh does not work" << endl;
    }

    else
    {
      getline(MyReadFile, myText);
      ifstream table(myText.c_str());
      string text;
      string update;
      string toDel = "|";
      string t;
      string p, in, na, va, pr, fl;
      getline(table, t);
      istringstream is(t);
      is >> in >> del >> na >> del >> pr;
      int run_once = 0;

      while (getline(table, text))
      {
        size_t pos = text.find("|");
        if (pos != string::npos)
        {
          update = text;
        }
        istringstream iss(update);
        size_t po;
        iss >> first >> del >> second >> del >> third;
        if (op == "!=")
        {
          int f = stoi(first);
          int w = stoi(whereChanged);
          if (f != w)
          {
            string testing;
            newOp = first + " ";
            size_t po = text.find(newOp);
            if (po != string::npos)
            {
              testing = text;
            }
            istringstream iss(testing);
            iss >> f >> del >> s >> del >> tt;

            if (n == "pid," || n == "name,")
            {
              if (pt == "name")
              {
                n = "pid,";
                if (run_once == 0)
                {
                  cout << p << " " << in << " " << del << na << " " << va << endl;
                  run_once = 1;
                }

                run_once = 1;
                cout << f << " " << del << " " << s << endl;
              }
              if (pt == "price")
              {
                n = "name,";
                if (run_once == 0)
                {
                  cout << na << " " << del << " " << pr << endl;
                  run_once = 1;
                }

                run_once = 1;

                cout << s << " " << del << " " << tt << endl;
              }
            }
          }
        }
      }

      MyReadFile.close();
      table.close();
      remove("from.txt");
    }
  }
}

// as of right now the setWhere function will only change the first occurence of the where name.
// how this works is that it takes the texts set.txt and where.txt to savee what we want to change where
// from there it uses the update.txt to read what file we should be working in.
// it then finds the lines that should be replaced and then depending on if we are looking for pid, price or name
// it replaces that section accordingly.
void setWhere()
{

  //// reads and stores into variable
  string setChoice;
  string setChanged;
  string whereChoice;
  string whereChanged;
  string status = "statusint";
  string seat = "seatint";
  string first;
  string second;
  char del;
  string d;
  string t;

  ifstream infile("set.txt");
  ifstream outfile("where.txt");
  infile >> setChoice >> setChanged;
  outfile >> whereChoice >> whereChanged;

  // cout<< setChoice << " " << setChanged<<endl;
  // cout<< whereChoice<< " " <<whereChanged<<endl;

  infile.close();
  outfile.close();
  remove("set.txt");
  remove("where.txt");

  string myText;
  ifstream MyReadFile("update.txt");
  if (MyReadFile.is_open())
  {
    string test;
    ifstream ope("user.txt"); // reading a file
    getline(ope, test);

    if (chdir(test.c_str()) != 0)
    {
      cout << "uh-oh does not work" << endl;
    }

    else
    {
      getline(MyReadFile, myText);
      d = myText;
    }
    MyReadFile.close();
    remove("update.txt");
  }

  string replace;
  string update;
  ifstream read(d.c_str());
  string line;
  getline(read, line);
  while (getline(read, line))
  {
    if (line.find(whereChanged) != string::npos)
    {
      replace = line;
      update = line;
      istringstream iss(update);

      iss >> first >> del >> second;

      int index;
      string temp;

      if (setChoice == seat)
      {

        temp = first + " ";
        // cout << temp << endl;
      }
      else if (setChoice == status)
      {
        temp = second;
        // cout << temp << endl;
      }

      while ((index = update.find(temp)) != string::npos)
      {
        update.replace(index, temp.length(), setChanged);
      }

      read.close();

      ifstream open(d.c_str());
      string firstL;
      getline(open, firstL);
      string firstLine = firstL + "\n";
      // cout << firstLine <<endl;

      ofstream toDelete("temp.txt");
      string strTemp;
      toDelete << firstLine;
      while (getline(open, firstL))
      {

        while ((index = firstL.find(replace)) != string::npos)
        {
          firstL.replace(index, replace.length(), update);
        }

        toDelete << firstL << "\n";
      }

      open.close();
      toDelete.close();
      //
    }
  }
  read.close();

  ofstream orig(d.c_str());
  ifstream copy("temp.txt");
  string str;
  if (copy && orig)
  {
    while (getline(copy, str))
    {
      orig << str << endl;
    }
  }
  orig.close();
  remove("temp.txt");

  fstream modified("mod.txt");
  string l;
  int count = 1;
  if (modified.peek() == EOF)
  {
    modified << count;
    cout << "1 record modified." << endl;
  }
  else
  {
    count++;
    modified << count;
    cout << count << " records modified" << endl;
  }
  modified.close();
}

//////
// how this works is that it takes the t where.txt to save what we want to delete
// from there it uses the del.txt to read what file we should be working in.
// it then finds the lines that should be deleted and then depending on if we are looking for '=' or '>'
// it deletes that section accordingly

void deleteWhere()
{

  string whereChoice;
  string whereChanged;
  string op;
  string newOp;
  string update;
  string first;
  string second;
  float third;
  char del;
  ifstream outfile("where.txt");
  outfile >> whereChoice >> op >> whereChanged;
  // cout << whereChoice << endl;
  // cout << whereChanged << endl;
  outfile.close();
  ofstream file("where.txt");
  file.open("where.txt", std::ofstream::out | std::ofstream::trunc);
  if (!file.eof())
  {
    file.close();
  }
  string myText;
  string d;
  string toDel;
  string l = ">";
  string e = "=";

  ///////
  int count = 0;

  ifstream MyReadFile("del.txt");
  if (MyReadFile.is_open())
  {
    string test;
    ifstream ope("user.txt"); // reading a file
    getline(ope, test);

    if (chdir(test.c_str()) != 0)
    {
      cout << "uh-oh does not work" << endl;
    }

    else
    {
      getline(MyReadFile, myText);
      d = myText;
    }
    string newOp;
    ifstream read(d.c_str());
    string line;
    getline(read, line);
    string firstLine = line + "\n";
    while (getline(read, line))
    {
      string copy = line;
      istringstream iss(line);

      iss >> first >> del >> second >> del >> third;
      if (op == l)
      {
        float g = stof(whereChanged);

        if (third > g)
        {
          float f = third;
          stringstream l;
          l << f;

          newOp = l.str();
          size_t pos = line.find(newOp);
          if (pos != string::npos)
          {
            count++;
            toDel = line;
            update = line;
          }
        }
        ofstream temp;
        temp.open("temp.txt");

        ifstream r(d.c_str());
        string t;

        while (getline(r, t))
        {
          size_t k = t.find(toDel);

          if (k != string::npos)
          {
            t.replace(t.find(toDel), toDel.length(), "");
          }
          if (!t.empty())
          {
            temp << t << endl;
          }
        }

        temp.close();
        ofstream orig(d.c_str());
        ifstream copy("temp.txt");
        string str;
        if (copy && orig)
        {
          while (getline(copy, str))
          {
            orig << str << "\n";
          }
        }
        orig.close();
        remove("temp.txt");
      }
      else if (op == e)
      {
        if (second == whereChanged)
        {
          newOp = " " + second;
          size_t pos = line.find(newOp);
          if (pos != string::npos)
          {
            count++;
            // cout << line<<endl;
            toDel = line;
            update = line;
          }
        }
        ofstream temp;
        temp.open("temp.txt");

        ifstream r(d.c_str());
        string t;

        while (getline(r, t))
        {

          size_t k = t.find(toDel);

          if (k != string::npos)
          {
            t.replace(t.find(toDel), toDel.length(), "");
          }
          if (!t.empty())
          {
            temp << t << endl;
          }
        }

        temp.close();
        ofstream orig(d.c_str());
        ifstream copy("temp.txt");
        string str;
        if (copy && orig)
        {
          while (getline(copy, str))
          {
            orig << str << "\n";
          }
        }
        orig.close();
        remove("temp.txt");
        remove("del.txt");
      }
    }

    read.close();
  }

  // remove("temp.txt");
  cout << count << " records deleted." << endl;
}
// how this should work is it will read user to figure out what directory to be in
// read from from.txt to decide what tables to use
// read from tupleSelectFile to decide what variable to use
// read from where.txt to know what parameters to check for
void tupleJoin()
{
  ifstream tuple("tupleSelectFile.txt");

  string firstWord;
  tuple >> firstWord;
  string e = "E";
  string inner = "inner";

  ifstream where("where.txt");
  string firstV, param1, eq, secV, param2;
  where >> firstV >> param1 >> eq >> secV >> param2;
  string firstFile;
  string secondFile;
  ifstream MyReadFile("from.txt");
  if (MyReadFile.is_open())
  {
    string test;
    ifstream ope("user.txt"); // reading a file
    getline(ope, test);

    if (chdir(test.c_str()) != 0)
    {
      cout << "uh-oh does not work" << endl;
    }

    else
    {
      MyReadFile >> firstFile >> secondFile;
    }
  }

  // if first word in tupleSelectFile.txt is inner or e variable:
  string line;
  string fp1, sp1, sp2;
  char del;
  string fp2;
  ifstream file1(firstFile.c_str());
  ifstream file2(secondFile.c_str());
  getline(file1, line);
  getline(file2, line);

  cout << "id int | name varchar10 | employeeID int | productID int" << endl;

  if (param1 == "id" && param2 == "employeeID")
  {

    while (file1 >> fp1 >> del >> fp2)
    {

      while (file2 >> sp1 >> del >> sp2)
      {

        if (fp1 == sp1)
        {

          string print = fp1 + del + fp2 + del + sp1 + del + sp2;
          cout << print << endl;
        }
      }
      if (fp1 == sp1)
      {

        string print = fp1 + del + fp2 + del + sp1 + del + sp2;
        cout << print << endl;
      }
    }
    if (firstWord == "left")
    {
      string print = fp1 + del + fp2 + del + del;
      cout << print << endl;
    }
  }

  remove("tupleSelectFile.txt");
  remove("where.txt");
  remove("from.txt");
}

int main(int argc, char *argv[])
{
  int c;
  bool locked;
  for (int i = 0; i < argc; i++)
  {
    c = i;
  }
  string w = argv[c - 1];
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
  if (string(argv[1]) == "insert")
  {
    tmap["insert"] = insert;
  }
  if (string(argv[1]) == "select" && w == "from")
  {
    tmap["select"] = select;
  }

  // truncates the function.txt at every new run
  ofstream table;
  table.open("function.txt", std::ofstream::trunc);
  table.close();

  // creates function.txt and writes all parameters to it
  // DOES NOT WORK FOR PARANTHESIS
  // string b is the name of the new file that is going to be passed
  if (argc > 4)
  {
    // for some reason when calling select* the program thinks there are more argc than there actually are
    // to adjust for this i have the program count however many argcs there are and then save that number
    // from there that argv[count] is the file we want access to and is what is passed as string x to the select functin
    int count;
    for (int i = 0; i < argc; i++)
    {
      count = i;
    }
    string arg = argv[1];
    string set = "set";
    string where = "where";
    string from = "from";
    string inner = "inner";
    string left = "left";
    string on = "on";
    ofstream table("function.txt", ios::app);

    string select = "select";
    if (arg == "select")
    {
      if (argv[count - 1] == from)
      {
        // runs for select * from Table
        string k = argv[count];
        tmap[argv[1]](k);
        table << k;
        table.close();
      }
      else
      {
        // runs for select *
        ofstream tupleSelect("tupleSelectFile.txt");
        tupleSelect << "Check for file names--Tuple join";
        tupleSelect.close();
      }
    }
    else if (arg == set){
      ifstream myFile("locked.txt");
      string locked = "locked";
      string line;
      getline(myFile, line);
      if(line == locked){


        string a = argv[2];
        // cout << "b " << a <<endl;
        string c = argv[4];
        // cout << "c " << c <<endl;

        // tmap[argv[1]](b);
        fstream sets;
        sets.open("set.txt", ios::out);
        sets << a << " " << c;
        sets.close();
      }
      else{
        return 0;
      }
    }
    else if (arg == on)
    {
      /// TUPLE SPOT
      string a = argv[2];
      // cout << "b " << a <<endl;
      string b = argv[3];

      string c = argv[4];
      // cout << "c " << c <<endl;

      string variables = a + " " + b + " " + c;
      istringstream is(variables);
      string t;
      ofstream MyFile("where.txt");

      while (getline(is, t, '.'))
      {
        // cout << t << " ";
        MyFile << t << ' ';
      }
      MyFile.close();
      tupleJoin();
    }
    else if (arg == where)
    {
      // check if file is empty
      ifstream read("del.txt");
      ifstream sel("select.txt");
      ifstream tuple("tupleSelectFile.txt");
      int i;
      ifstream myFile("locked.txt");
      string locked = "locked";
      string line;
      getline(myFile, line);
      if(line == locked){
        if (!read && !tuple)
        {
          i = 0;
          string a = argv[2];
          // cout << "b " << a <<endl;
          string c = argv[4];
          // cout << "c " << c <<endl;

          // tmap[argv[1]](b);
          ofstream MyFile("where.txt");
          MyFile << a << " " << c;
          MyFile.close();
          //setWhere();
        }
        else if (!sel && !tuple)
        {
          string a = argv[2];
          // cout << "b " << a <<endl;
          string b = argv[3];

          string c = argv[4];
          // cout << "c " << c <<endl;

          // tmap[argv[1]](b);
          ofstream MyFile("where.txt");
          MyFile << a << " " << b << " " << c;
          MyFile.close();
          deleteWhere();
          // remove("del.txt");
        }
        else if (!sel && !read)
        {
          /// TUPLE SPOT
          string a = argv[2];
          // cout << "b " << a <<endl;
          string b = argv[3];

          string c = argv[4];
          // cout << "c " << c <<endl;

          string variables = a + " " + b + " " + c;
          istringstream is(variables);
          string t;
          ofstream MyFile("where.txt");

          while (getline(is, t, '.'))
          {
            // cout << t << " ";
            MyFile << t << ' ';
          }
          MyFile.close();
          tupleJoin();
        }
        else
        {

          string a = argv[2];
          // cout << "b " << a <<endl;
          string b = argv[3];

          string c = argv[4];
          // cout << "c " << c <<endl;

          // tmap[argv[1]](b);
          ofstream MyFile("where.txt");
          MyFile << a << " " << b << " " << c;
          MyFile.close();
          // ifstream t("function.txt")
          // string file;
          // getline(t, file);
          //selectPart();

          // remove(t);
        }
      }
      else{
        return 0;
      }
        
      
    }
    else if (arg == from)
    {
      string joinT;
      // saves the name of the files we want access to in from.txt

      // saves the variable names to tupleSelectFile.txt

      if (argv[4] == inner || argv[4] == left)
      {
        ofstream s("from.txt");
        ofstream tupleNames("tupleSelectFile.txt");

        if (argv[4] == inner)
        {
          joinT = "inner";
          string b = argv[2];
          string c = argv[6];
          s << b << " " << c;
          s.close();
          string v = argv[3];
          string v2 = argv[7];
          ofstream tupleNames("tupleSelectFile.txt");
          tupleNames << joinT << endl
                     << v << " " << v2;
        }
        else
        {
          joinT = "left";
          string b = argv[2];
          string c = argv[7];
          s << b << " " << c;
          s.close();
          string v = argv[3];
          string v2 = argv[7];
          ofstream tupleNames("tupleSelectFile.txt");
          tupleNames << joinT << endl
                     << v << " " << v2;
        }

        tupleNames.close();
      }

      else
      {
        ofstream s("from.txt");
        // saves the name of the files we want access to in from.txt
        string b = argv[2];
        string c = argv[4];
        s << b << " " << c;
        s.close();
        // saves the variable names to tupleSelectFile.txt
        string v = argv[3];
        string v2 = argv[5];
        string variables = v + v2;
        istringstream is(variables);
        string t;
        ofstream tupleNames("tupleSelectFile.txt");
        while (getline(is, t, ','))
        {
          tupleNames << t << ' ';
        }
        tupleNames.close();
      }
    }

    else
    {
      for (int i = 4; i < argc; i++)
      {
        if (i != argc - 1)
        {
          char del = ',';
          std::vector<std::string> argList(argv, argv + argc);
          // calls function that gets rid of comments and formats
          split(argList[i], del);
        }
        else
        {
          string p = argv[i];
          table << p;
          table.close();
        }
      }
      string b = argv[3];
      tmap[argv[1]](b);
    }
  }

  if (argc == 4)
  {
    string arg = argv[1];
    string sel = "select";
    // string from = "from";

    string del = "delete";
    if (arg == del)
    {
      string b = argv[3];
      ofstream MyFile("del.txt");
      MyFile << b;
      MyFile.close();
    }
    else if (arg == sel)
    {
      ofstream s("select.txt");
      string b = argv[2];
      string c = argv[3];
      s << b << " " << c;
      s.close();
    }

    else
    {
      string b = argv[3];
      // cout << b;
      tmap[argv[1]](b);
    }
  }

  // creates user.txt and writes what database we want used to the file
  // creates update.txt and writes what file we want
  if (argc == 3)
  {
    string arg = argv[1];
    string begin = "begin";
    string use = "USE";
    string update = "update";
    string from = "from";
    if (arg == use)
    {
      string b = argv[2];
      ofstream MyFile("user.txt");
      MyFile << b;
      MyFile.close();
      cout << "Using database " << b << "." << endl;
      tmap[argv[1]](b);
    }
    else if (arg == update)
    {
      // this is going to create a new file called update.txt
      //  what is writes into it is the name of the file we want to update
      // later on will be able to read from file and make sure this file is selected
      // cout << "UPDATE" << endl;
      // checks to see if locked.txt exists already and if it does prints and error message and does nothing else
      string fileName = "locked.txt";
      string b = argv[2];
      ifstream myFile("locked.txt");
      string locked = "locked";
      string line;
      getline(myFile, line);
      if (line != locked)
      {
        cout << "Error: Table " << b << " is locked!";
      }
      else
      {
        string b = argv[2];
        ofstream MyFile("update.txt");
        MyFile << b;
        MyFile.close();
      }
    }
    else if (arg == from)
    {
      ofstream s("from.txt");
      string b = argv[2];
      s << b;
      s.close();
    }
    // if locked.txt doesn't exist it will create the file
    else if (arg == begin)
    {
      string fileName = "locked.txt";
      cout << "Transaction starts." << endl;
      fstream File(fileName, ios::in);
      if (!File)
      { 
        ofstream MyFile(fileName);
        MyFile<<"locked";
        MyFile.close();
      }
      else{
        ofstream MyFile(fileName);
        MyFile<<"unlocked";
        MyFile.close();
      }


     
    }

    else
    {
      cout << "doesnt work" << endl;
    }
  }

  // EXIT
  if (argc == 2)
  {

    string b = argv[1];
    string commit = "commit";
    if (b == commit)
    {
        ifstream myFile("locked.txt");
      string locked = "locked";
      string line;
      getline(myFile, line);
      if(line == locked){ 
        setWhere();
        cout << "Transaction Commited" << endl;
        remove("locked.txt");
      }
      else
      {
        cout << "Transaction abort." << endl;
        ofstream MyFile("locked.txt");
        MyFile<<"locked";
        MyFile.close();
      }
    }
    else
    {
      remove("del.txt");
      remove("from.txt");
      remove("function.txt");
      remove("update.txt");
      remove("user.txt");
      remove("where.txt");
      cout << "All done." << endl;

      return 0;
    }
  }
  return 0;
}
