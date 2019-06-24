#pragma once
#include <vector>
#include <QString>
struct times
{
    QString target;
    QString show_format;
    int font_color_R;
    int font_color_G;
    int  font_color_B;
    int  font_color_A;
    int  font_size;
    bool visible;
};
struct cfg
{
    int window_size_height;
    int window_size_width;
    int window_pos_X;
    int window_pos_Y;
    std::vector<times> labels;
    times label;
};

class Config
{
public:
    static Config* instance();
    ~Config();
public:
     cfg* get() { return m_config; }
    int load_config(const QString &path);
    QString getText(times t);
private:
    cfg *m_config;
    Config();
    static Config* m_pInstance;

};
