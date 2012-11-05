#include <QtCore/QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>

void updateFile(char * ,char *);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc < 3)
    {
        std::cout<<"Please enter parameters.";
        getchar();
        return 0;
    }
    char *inputFileName;
    char *outputFileName;
    inputFileName=argv[1];
    outputFileName=argv[2];
    std::cout<<inputFileName<<" -> "<<outputFileName<<std::endl;
    updateFile(inputFileName,outputFileName);

    delete[] inputFileName;
    delete[] outputFileName;
    return 0;
}

void updateFile(char * inFileName,char * outFileName)
{
    QFile inputFile(inFileName);
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


    QFile outputFile(outFileName);
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
