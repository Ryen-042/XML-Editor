#ifndef JSHIGHLIGHTER_H
#define JSHIGHLIGHTER_H


#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class JSHighlighter: public QSyntaxHighlighter
{
public:
     JSHighlighter(QTextDocument *parent = 0);
private:
     struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;
     };
     QVector<HighlightingRule> rules;


protected:
    void highlightBlock(const QString &text);
};

#endif // JSHIGHLIGHTER_H
