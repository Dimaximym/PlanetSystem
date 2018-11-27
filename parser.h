#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QString>
#include <QPair>
#include <QTextBrowser>

class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
    
    void setString(QString string);
    void Parsing(QString string);
    bool ParsBody();
    void ParsStart();
    QPair<QPair<int,int>, bool> ParsCoords();
    bool ParsCommand();
    void ParsingCommand();

    bool error;
    bool init;
    QString string;
    QString originalString;

signals:
    void invokeCreateBody(int x, int y, int mass, int rad);
    void invokeFillLog(QString err, QString src, QString rx);
    void invokeClear();
};

#endif // PARSER_H
