/***************************************************************************
 *   Copyright (C) 2008 by Andres Cabrera   *
 *   mantaraya36@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "highlighter.h"


Highlighter::Highlighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{
     commentStartExpression = QRegExp("/\\*");
     commentEndExpression = QRegExp("\\*/");
}


Highlighter::~Highlighter()
{
}

void Highlighter::setOpcodeNameList(QStringList list)
{
  m_list = list;
  setFirstRules();
  setLastRules();
}

void Highlighter::highlightBlock(const QString &text)
{
  foreach (HighlightingRule rule, highlightingRules) {
    QRegExp expression(rule.pattern);
    QString temp = rule.pattern.pattern();
    int index = text.indexOf(expression);
    while (index >= 0) {
      int length = expression.matchedLength();
      setFormat(index, length, rule.format);
      index = text.indexOf(expression, index + length);
    }
  }
  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
    startIndex = text.indexOf(commentStartExpression);

  while (startIndex >= 0) {
    int endIndex = text.indexOf(commentEndExpression, startIndex);
    int commentLength;
    if (endIndex == -1) {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    } else {
      commentLength = endIndex - startIndex
          + commentEndExpression.matchedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex = text.indexOf(commentStartExpression,
                              startIndex + commentLength);
  }
}

void Highlighter::setFirstRules()
{
  highlightingRules.clear();
  HighlightingRule rule;
  opcodeFormat.setForeground(QColor("blue"));
  opcodeFormat.setFontWeight(QFont::Bold);
  foreach (QString pattern, m_list) {
//     pattern = "[ \\t\\r\\n]" + pattern + "[ \\t\\r\\n]";
    pattern = "\\b" + pattern + "\\b";
//     qDebug("%s",pattern.toStdString().c_str());
    rule.pattern = QRegExp(pattern);
    rule.format = opcodeFormat;
    highlightingRules.append(rule);
  }
}

void Highlighter::setLastRules()
{
  HighlightingRule rule;

  csdtagFormat.setForeground(QColor("brown"));
//      csdtagFormat.setFontWeight(QFont::Bold);
  QStringList keywordPatterns;
  keywordPatterns << "<CsoundSynthesizer>" << "</CsoundSynthesizer>"
      << "<CsOptions>" << "</CsOptions>"
      << "<CsInstruments>" << "</CsInstruments>"
      << "<CsScore>" << "</CsScore>"
      << "<CsVersion>" << "</CsVersion>";
  foreach (QString pattern, keywordPatterns) {
    rule.pattern = QRegExp(pattern);
    rule.format = csdtagFormat;
    highlightingRules.append(rule);
  }

  QStringList instPatterns;
  instPatterns << "\\binstr\\b" << "\\bendin\\b" << "\\bopcode\\b" << "\\bendop\\b";
  csdtagFormat.setForeground(QColor("purple"));
  csdtagFormat.setFontWeight(QFont::Bold);
  foreach (QString pattern, instPatterns) {
    rule.pattern = QRegExp(pattern);
    rule.format = csdtagFormat;
    highlightingRules.append(rule);
  }

  QStringList headerPatterns;
  headerPatterns << "\\bsr\\b" << "\\bkr\\b" << "\\bksmps\\b" << "\\bnchnls\\b";
  csdtagFormat.setForeground(QColor("brown"));
  csdtagFormat.setFontWeight(QFont::Bold);
  foreach (QString pattern, headerPatterns) {
    rule.pattern = QRegExp(pattern);
    rule.format = csdtagFormat;
    highlightingRules.append(rule);
  }
  singleLineCommentFormat.setForeground(QColor("green"));
  rule.pattern = QRegExp(";[^\n]*");
  rule.format = singleLineCommentFormat;
  highlightingRules.append(rule);

  multiLineCommentFormat.setForeground(QColor("green"));

  quotationFormat.setForeground(Qt::red);
  rule.pattern = QRegExp("\".*\"");
  rule.format = quotationFormat;
  highlightingRules.append(rule);

//      classFormat.setFontWeight(QFont::Bold);
//      classFormat.setForeground(Qt::darkMagenta);
//      rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
//      rule.format = classFormat;
//      highlightingRules.append(rule);


//      functionFormat.setFontItalic(true);
//      functionFormat.setForeground(Qt::blue);
//      rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
//      rule.format = functionFormat;
//      highlightingRules.append(rule);
}