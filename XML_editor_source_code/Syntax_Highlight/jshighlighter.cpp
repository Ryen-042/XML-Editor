#include "jshighlighter.h"
#include <QRegExp>
#include <QDebug>
#include <QTextCharFormat>
#include <QTextDocument>

JSHighlighter::JSHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
   HighlightingRule rule;


//   //reserved words
//   rule.pattern = QRegExp("(true|false|null)(?!\"[^\"]*\")");
//   rule.format.setForeground(Qt::darkBlue);
//   rules.append(rule);

   //key
   rule.pattern = QRegExp ("(\"[^\"]*\")");
   rule.format.setForeground(Qt::darkBlue);
   rules.append(rule);

   //value
   rule.pattern = QRegExp(":\\s*([\"](?:[^\"])*[\"])");
   rule.format.setForeground(Qt::red);
   rules.append(rule);

//  //numbers
//  rule.pattern = QRegExp("([-0-9.]+)(?!([^\"]*\"[\\s]*\\:))");
//  rule.format.setForeground(QColor(174,129,248));
//  rules.append(rule);
}

void JSHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, rules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while (index >= 0) {
            index = expression.pos(1);
            int length = expression.cap(1).length();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}
