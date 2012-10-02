#include <QtCore/QCoreApplication>
//#include <stdio.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

void updateFile(char * fileName);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char *fileName=new char[100];
    //char* fileName="d:\\Programming\\Qt prog's\\Modify_project_files\\debug\\graphics.html";
    std::cout<<"Enter file name to update: ";
    std::cin>>fileName;
    updateFile(fileName);

    delete[] fileName;

    return a.exec();
}

void updateFile(char * fileName)
{
    QFile inputFile(fileName);
    if(!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        std::cout<<"Opening file error"<<std::endl;
        return;
    }

    QTextStream ts(&inputFile);
    QString temp=ts.readAll();
    if(temp.contains("</h1>"))
    {
        temp.insert(temp.indexOf("</h1>")+5,"\n\t\t<hr>");
    }
    if(temp.contains("</body>"))
    {
        temp.insert(temp.indexOf("</body>")-1,"\t\t<hr>\n");
    }
    inputFile.close();


    QFile outputFile(fileName);
    if(!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        std::cout<<"Opening file error"<<std::endl;
        return;
    }

    QTextStream textStream(&outputFile);
    textStream<<temp;
    textStream.flush();
    outputFile.close();

    std::cout<<"File updated"<<std::endl;
}
