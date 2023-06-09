#include "header.h"

using namespace std;

void check_operation(string& number)
{
    //takes the chosen opertaion as a string
    string chosen_opperation;
    //loops through that string
    for (int i = 0; i < number.length(); i++)
    {
        //if i is a digit it is appeanded
        if (isdigit(number[i]))
        {
            chosen_opperation.push_back(number[i]);
        }
    }
    //lenght of the string is not the same anymore it means that it icnulded a letter
    if (chosen_opperation.length() != number.length())
    {
        //ask the user to enter a new chioce
        cout << "Invalid input, please try again: ";
        cin >> number;
        cin.ignore();
        //re-apply the same function
        check_operation(number);
    }
}

void open_file()
{
    cout << "Enter name of file you want to open and its extention in the same folder ex: file called \"test.txt\" \n or write the whole path and the extention: ";
    getline(cin, file_name);
    my_file.open(file_name, ios::in);
    while (my_file.fail())
    {
        cout << file_name << " It is either a wrong name or path, please enter a correct One: ";
        cin.clear();
        cin.sync();
        getline(cin, file_name);
        my_file.open(file_name, ios::in);
    }
}

void repeated_word()
{
    string text, word;
    int count = 0;
    open_file();
    cin.clear(), cin.sync();
    if (my_file.is_open())
    {
        cout << "Enter the word: ";
        cin >> word;
        for (int i = 0; i < word.length(); i++)
        {
            word[i] = tolower(word[i]);
        }

        while (my_file >> text)
        {
            for (int i = 0; i < text.length(); i++)
            {
                text[i] = tolower(text[i]);
            }

            if (text == word || text == word + '.' || text == word + ',' || text == '.' + word || text == ',' + word)
                count++;
        }

        my_file.close();
        cout <<"This word has been repeated: " << count<<" times" << endl;
    }
}

void upper_words()
{

    string line, upper_words;
    open_file();
    cin.clear(), cin.sync();
    if (my_file.is_open())
    {
        while (getline(my_file, line))
        {
            upper_words += line;
            upper_words += "\n";
        }
        my_file.close();
    }

    for (int i = 0; i < upper_words.length(); i++)
    {
        upper_words[i] = toupper(upper_words[i]);
    }

    my_file.open(file_name, ios::out);
    if (my_file.is_open()) {
        my_file << upper_words;
        my_file.close();
    }
    cout<<"DONE\n";
}

void lower_words()
{


    string line, lower_words;
    open_file();
    cin.clear(), cin.sync();
    if (my_file.is_open())
    {
        while (getline(my_file, line))
        {
            lower_words += line;
            lower_words += "\n";
        }
        my_file.close();
    }

    for (int i = 0; i < lower_words.length(); i++)
    {
        lower_words[i] = tolower(lower_words[i]);
    }

    my_file.open(file_name, ios::out);
    if (my_file.is_open())
    {
        my_file << lower_words;
        my_file.close();
    }
    cout<<"DONE\n";
}

void count_words()
{
    string text;
    int ctr = 0;
    open_file();
    while (my_file >> text)
        ctr++;
  cout <<"This file has: " << ctr <<" words" << endl;
}


void title_words()
{
    string line, lower_words;
    open_file();
    cin.clear(), cin.sync();

    if (my_file.is_open())
    {
        while (getline(my_file, line))
        {
            lower_words += line;
            lower_words += "\n";

            transform(lower_words.begin(), lower_words.end(), lower_words.begin(), ::tolower);


            for (int i = 0; i < lower_words.length() - 1; ++i)
            {
                lower_words[0] = toupper(lower_words[0]);
                if (lower_words[i] == ' ' || lower_words[i] == '\n' && lower_words[i + 1] != ' ')
                {
                    lower_words[i + 1] = toupper(lower_words[i + 1]);

                }

            }

        }
        my_file.close();
    }


    my_file.open(file_name, ios::out);
    if (my_file.is_open())
    {
        my_file << lower_words;
        my_file.close();
    }
    cout<<"DONE\n";
}

void count_char()
{
    int ctr = 0;
    char c;
    open_file();
    while (1)
    {
        c = my_file.get();
        if (isalpha(c))
            ctr++;
        if (c == EOF)
        {
            cout <<"This file has: " << ctr <<" Chars" << endl;
            break;
        }
    }
}

void count_lines()
{
    string line;
    int ctr = 0;
    open_file();
    while (getline(my_file, line))
        ctr++;
    cout <<"This file has: " << ctr <<" lines" << endl;

}

void look_for_word()
{
    string word, temp;
    open_file();
    cout << "enter the word you are looking for  ";
    cin >> word;
    while (my_file)
    {
        my_file >> temp;
        if (temp == word)
        {
            cout << "FOUND\n";
            return;
        }
    }
    cout << "NOT FOUND\n";
}

void merge_files()
{
    open_file();
    ofstream original_file;
    ifstream new_file;
    original_file.open(file_name, ios_base::app);
    cout << "Enter name of file you want to open and its extention in the same folder ex: file called \"test.txt\" \n or write the whole path and the extention: ";
    getline(cin, file_name);
    new_file.open(file_name);
    while (new_file.fail())
    {
        cout << file_name << " is not a file name, try again!  ";
        cin.clear();
        cin.sync();
        getline(cin, file_name);
        new_file.open(file_name, ios::in);
    }
    original_file << new_file.rdbuf() << endl;
    original_file.close();
    new_file.close();
}

void display_content()
{
    cout<<"\n";
    open_file();
        while(! my_file.eof())
        {
            getline(my_file, content);
            cout << content << endl;
        }
    my_file.close();
}


void delete_content()
{
    ofstream ofile;
    open_file();
    my_file.close();
    ofile.open(file_name, ofstream::out | ofstream::trunc);
    if (ofile.fail())
    {
        cout << "File open error!" << endl;
    }
    else
    {
    cout << "File opened successful.\n";
    }
    ofile.close();
    cout<<"DONE\n";
}

void add_text()
{
    ofstream ofile;
    string data;
    open_file();
    my_file.close();
    ofile.open(file_name, ios_base::app);
    cout << "Please enter the data you want to append: ";
    cin.clear();
    cin.sync();
    getline(cin, data,'\0');
    cin.sync();
    cin.clear();
    ofile << data;
    ofile.close();
}

void cipher()
{
    open_file();
    while (my_file)
    {
        char ch;
        my_file.get(ch);
        c+=1;
    }
    // cout << c << endl;
    my_file.close();
    ifstream dataFile2;
    dataFile2.open(file_name);
    int ctr = 0;
    char name[c-1], name2[c-1];
        while(! dataFile2.eof())
        {
            getline(dataFile2, content);
            content2 += content;
            content2 += '\n';
        }
        // cout << content2 << endl;
    strcpy(name, content2.c_str());
    strncpy(name2, name, c-1);
    for (int i = 0; i < (c-1)  ; i++)
    {
       name2[i] = name[i] + 1;
    }
    dataFile2.close();
    ofstream ofile;
    ofile.open(file_name, ofstream::out | ofstream::trunc);
    ofile.close();
    ofstream ofile2;
    ofile2.open(file_name, ios_base::app);
    ofile2 << name2;
    ofile2.close();
    c = 0;
    content = "";
    content2 = "";
}

void decipher()
{
    open_file();
    while (my_file)
    {
        char ch;
        my_file.get(ch);
        c+=1;
    }
    // cout << c << endl;
    my_file.close();
    ifstream dataFile2;
    dataFile2.open(file_name);
    int ctr = 0;
    char name[c-1], name2[c-1];
        while(! dataFile2.eof())
        {
            getline(dataFile2, content);
            content2 += content;
            content2 += '\n';
        }
        // cout << content2 << endl;
    strcpy(name, content2.c_str());
    strncpy(name2, name, c-1);
    for (int i = 0; i < (c-1)  ; i++)
    {
       name2[i] = name[i] - 1;
    }
    dataFile2.close();
    ofstream ofile;
    ofile.open(file_name, ofstream::out | ofstream::trunc);
    ofile.close();
    ofstream ofile2;
    ofile2.open(file_name, ios_base::app);
    ofile2 << name2;
    ofile2.close();
    c = 0;
    content = "";
    content2 = "";
}

void save_file()
{
    ifstream sfile;
    ofstream tfile;
    string source_file;
    string target_file;
    string line, lower_words;
    char ch;
    cout << "Enter name of file you want to open and its extention in the same folder ex: file called \"test.txt\" \n or write the whole path and the extention: ";
    getline(cin, source_file);
    sfile.open(source_file);
    if (sfile.fail())
    {
        cout << "Error in opening file!" << endl;

    }

    cout << "\nEnter name of the new file you want to save a copy in and its extention in the same folder ex: file called \"test.txt\" \n or write the whole path and the extention: ";
    getline(cin, target_file);
    tfile.open(target_file);
    if (tfile.fail())
    {
        cout << "Error in opening file!" << endl;
        sfile.close();

    }
    while (sfile.eof() == 0)
    {
        while (getline(sfile, line))
        {
            lower_words += line;
            lower_words += "\n";
        }
        tfile << lower_words;

    }
    cout << "File is copied/saved to another file successfully :)\n";
    sfile.close();
    tfile.close();

}
