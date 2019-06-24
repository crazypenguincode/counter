#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QObject>
#include <QDatetime>
#include "config.h"
Config* Config::m_pInstance = nullptr;

Config::Config()
{
    m_config = new cfg();
    m_config->window_size_height;
    m_config->window_size_height = 200;
    m_config->window_size_width = 600;

    m_config->window_pos_X = 1000;
    m_config->window_pos_Y = 1000;
    m_config->label.font_color_R = 0;
    m_config->label.font_color_G = 255;
    m_config->label.font_color_B = 0;
    m_config->label.font_color_A = 0;
    m_config->label.font_size = 15;
}

Config::~Config()
{
    delete m_config;
    if (m_pInstance != nullptr) {
        delete m_pInstance;
    }
}

Config* Config::instance() {
    if (m_pInstance == nullptr)  
        m_pInstance = new Config();
    return m_pInstance;
}
int Config::load_config(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "read json file failed";
        return 0;
    }
    QByteArray ba = file.readAll();
    qDebug() << "read contents：";
    qDebug() << ba; QJsonParseError e;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(ba, &e);
    if (e.error == QJsonParseError::NoError && !jsonDoc.isNull()) {
        qDebug() << jsonDoc;
        if (jsonDoc.isObject()) {
            QJsonObject doc = jsonDoc.object();
            m_config->window_size_height = doc.value("window_size").toObject().value("height")["value"].toInt();
            m_config->window_size_width = doc.value("window_size").toObject().value("width")["value"].toInt();
            m_config->window_pos_X = doc.value("window_pos").toObject().value("X")["value"].toInt();
            m_config->window_pos_Y = doc.value("window_pos").toObject().value("Y")["value"].toInt();
            qDebug() << "value" << doc.value("window_pos")["value"].toString() ;
            QJsonArray  lables = doc.take("times").toArray();
                for (int i = 0; i < lables.size(); i++) {
                    times label;
                    label.target = lables.at(i).toObject().value("target")["value"].toString();
                    label.show_format = lables.at(i).toObject().value("show_format")["value"].toString();
                    label.font_color_R = lables.at(i).toObject().value("font_color").toObject().value("R")["value"].toInt();
                    label.font_color_G = lables.at(i).toObject().value("font_color").toObject().value("G")["value"].toInt();
                    label.font_color_B = lables.at(i).toObject().value("font_color").toObject().value("B")["value"].toInt();
                    label.font_color_A = lables.at(i).toObject().value("font_color").toObject().value("A")["value"].toInt();
                    label.font_size = lables.at(i).toObject().value("font_size")["value"].toInt();
                    label.visible = lables.at(i).toObject().value("visible")["value"].toBool();
                    if (label.visible)
                    {
                        m_config->labels.push_back(label);
                    }
                    
                }
            
        }
       
    }
    return 0;
}
QString Config::getText(times t) {
    QDateTime current = QDateTime::currentDateTime();   //获取当前时间  
    int start = QDateTime::currentDateTime().toTime_t();                     //将当前时间转为时间戳  
    //QString endtime = t.target;
    QDateTime endt = QDateTime::fromString(t.target, "yyyy-MM-dd hh:mm:ss");
    int end = endt.toTime_t();
    int daysec = 24 * 60 * 60;
    int to = end - start;
    bool future = true;
    if (to <= 0)
    {
        future = false;
        to = start - end;
    }
    int day = to / daysec;
    int hour = (to - day * daysec) / 3600;
    int min = (to - day * daysec - hour * 3600) / 60;
    int sec = to - day * daysec - hour * 3600 - min * 60;
    // %d-%h:%m:%s 
    QString text = t.show_format.replace("%d", "%1").replace("%h", "%2").replace("%m", "%3").replace("%s", "%4");
    text = text.arg(day, 3, 10, QLatin1Char('0')).arg(hour, 2, 10, QLatin1Char('0')).arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));

    return text;
}
