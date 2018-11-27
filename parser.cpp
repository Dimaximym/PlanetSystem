#include "parser.h"
#include <QRegExp>
#include <QDebug>

Parser::Parser() : error(false), init(true)
{

}

void Parser::Parsing(QString str)
{
    error = false;
    originalString = str;
    string = originalString;
    string = string.simplified();
    if (init)
    {
        QRegExp rx(";|(?:;\\s)");
        while(ParsBody()) {
            if (error) return;
            // Если найден символ ";" - конец инициализации и начало команд
            if (rx.indexIn(string) == 0)
            {
                int i = 1;
                if (rx.cap(0).size() == 2) i = 2;
                string.remove(0, i);
                break;
            }
        }
        if (error) return;
        init = false;
    }
    while(ParsCommand()){
        if (error) return;
    }
    if (error) return;
}

bool Parser::ParsBody()
{
    QRegExp srx("^\\s");
    if (srx.indexIn(string) == 0) string.remove(0, 1);
    QRegExp rx("(planet|star)");
    int x = 0, y = 0, mass = 0, rad = 0;
    int index = 0;

    auto lambdaBody = [&]() -> bool
    {
        string.remove(index, rx.cap(1).size() + 1);

        auto resultPC = ParsCoords();
        if (!resultPC.second)
        {
            error = true;
            return false;
        }

        x = resultPC.first.first;
        y = resultPC.first.second;

        //mass
        rx.setPattern("m(\\d+)\\b");
        if (rx.indexIn(string) == 0) {
            mass = rx.cap(1).toInt();
            string.remove(0, rx.cap(0).size() + 1);
        }
        else {
           emit invokeFillLog("Неверный формат введения массы", string, "(\\S+)");
           error = true;
           return false;
        }
        rx.setPattern("r(\\d+)\\b");
        if (rx.indexIn(string) == 0) {
            rad = rx.cap(1).toInt();
            // Не удалять символ ';', если он в конце описания тела
            QRegExp srx(";");
            int i = 1;
            if (srx.indexIn(string) == rx.cap(0).size()) i = 0;
            string.remove(0, rx.cap(0).size() + i);
        }
        else {
            //ERROR mass / radius
            emit invokeFillLog("Неверный формат введения радиуса", string, "(\\S+)");
            error = true;
            return false;
        }
        return true;
    };

    if ((index = rx.indexIn(string)) == 0) {
        if (rx.cap(1) == "planet") {
            //PLANET
            if (!lambdaBody()) return false;
        }
        else {
            //STAR
            if (!lambdaBody()) return false;
        }
        //ИСПОЛЬЗОВАНИЕ ДАННЫХ ДЛЯ СОЗДАНИЯ ТЕЛА
        //FIX ME: СДЕЛАТЬ РАЗНИЦУ МЕЖДУ ЗВЕЗДОЙ И ПЛАНЕТОЙ
        emit invokeCreateBody(x, y, mass, rad);
    }
    else {
        //ERROR planet / star
        if (string.isEmpty()) return false;
        emit invokeFillLog("В начале описания тела должно следовать planet или star.", string, "(\\S+)");
        error = true;
        return false;
    }
    return true;
}

QPair<QPair<int, int>, bool> Parser::ParsCoords()
{
    QRegExp rx("x(-?\\d+)\\sy(-?\\d+(?=\\s))");
    QPair<QPair<int, int>, bool> result;
    if (rx.indexIn(string) == 0) {
        result.first.first = rx.cap(1).toInt();
        result.first.second = rx.cap(2).toInt();
        result.second = true;
    }
    else {
        ///ERROR
        invokeFillLog("Неверный формат введения координат.", string, "(\\S+\\s\\S+)");
        result.second = false;
        return result;
    }
    string.remove(0, rx.cap(0).size() + 1);
    return result;
}

bool Parser::ParsCommand()
{
    QRegExp rx("(add|clear)");
    if (rx.indexIn(string) == 0) {
        if (rx.cap(1) == "add")
        {
            // COMMAND ADD
            string.remove(0, rx.cap(1).size() + 1);
            if (!ParsBody()) return false;
        }
        else {
            // COMMAND CLEAR
            emit invokeClear();
            return false;
        }
    }
    else
    {
        if (string.isEmpty()) return false;
        invokeFillLog("Неизвестная команда.", string, "(\\S+)");
        error = true;
        return false;
    }
    return true;
}
