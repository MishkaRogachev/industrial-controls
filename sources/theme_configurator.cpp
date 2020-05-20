#include "theme_configurator.h"

#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QJsonParseError>
#include <QQmlEngine>

namespace
{
constexpr char rounding[] = "rounding";
constexpr char baseSize[] = "baseSize";
constexpr char animationTime[] = "animationTime";
constexpr char underline[] = "underline";
constexpr char scrollSize[] = "scrollSize";
constexpr char shadowSize[] = "shadowSize";

constexpr char spacing[] = "spacing";
constexpr char margins[] = "margins";
constexpr char padding[] = "padding";
constexpr char iconSize[] = "iconSize";
constexpr char sliderSize[] = "sliderSize";
constexpr char switchSize[] = "switchSize";
constexpr char handleSize[] = "handleSize";
constexpr char checkmarkSize[] = "checkmarkSize";
constexpr char floatSize[] = "floatSize";
constexpr char mainFontSize[] = "mainFontSize";
constexpr char auxFontSize[] = "auxFontSize";

const double mainFontFactor = 2.0;
const double auxFontFactor = 2.5;
const double spacingFactor = 4.0;
const double marginsFactor = 4.0;
const double paddingFactor = 6.0;
const double iconFactor = 1.75;
const double sliderFactor = 8.0;
const double switchFactor = 4.0;
const double handleSizeFactor = 1.5;
const double checkmarkFactor = 1.5;
const double floatFactor = 0.75;

// Colors
constexpr char colors[] = "colors";

constexpr char background[] = "background";
constexpr char sunken[] = "sunken";
constexpr char raised[] = "raised";
constexpr char text[] = "text";
constexpr char hover[] = "hover";
constexpr char border[] = "border";

constexpr char disabled[] = "disabled";

constexpr char control[] = "control";
constexpr char controlText[] = "controlText";

constexpr char tip[] = "tip";
constexpr char tipText[] = "tipText";

constexpr char selection[] = "selection";
constexpr char selectedText[] = "selectedText";

constexpr char highlight[] = "highlight";
constexpr char highlightedText[] = "highlightedText";

constexpr char link[] = "link";
constexpr char positive[] = "positive";
constexpr char neutral[] = "neutral";
constexpr char negative[] = "negative";
constexpr char shadow[] = "shadow";

const QColor linkColor = "#51a0e7";
const QColor positiveColor = "#86c34a";
const QColor neutralColor = "#ff9800";
const QColor negativeColor = "#e53535";
const QColor shadowColor = "#80000000";

const QColor darkBackgroundColor = "#2c393f";
const QColor darkTextColor = "#ffffff";
const QColor darkSelectionColor = "#009688";
const QColor darkSelectedTextColor = "#000000";
const QColor darkHoverColor = "#16ffffff";

const QColor brightBackgroundColor = "#f4f6f7";
const QColor brightTextColor = "#273339";
const QColor brightSelectionColor = "#20b2aa";
const QColor brightSelectedTextColor = "#ffffff";
const QColor brightHoverColor = "#16000000";

const double brightRaisedFactor = 105;
const double brightSunkenFactor = 95;
const double brightDisabledFactor = 250;
const double brightControlFactor = 125;
const double brightBorderFactor = 135;

const double darkRaisedFactor = 115;
const double darkSunkenFactor = 85;
const double darkDisabledFactor = 50;
const double darkBlueDisabledFactor = 1.15; // how disabled color bluer than normal diasbled
const double darkControlFactor = 150;
const double darkBorderFactor = 150;

} // namespace

ThemeConfigurator::ThemeConfigurator(QObject* parent) : QObject(parent)
{
    m_pathToConfig = qApp->applicationDirPath() + "/" + "theme.json";
}

void ThemeConfigurator::setTheme(QObject* theme)
{
    if (m_theme == theme)
        return;

    m_theme = theme;

    if (m_theme)
    {
        m_rounding = theme->property(::rounding).toInt();
        m_baseSize = theme->property(::baseSize).toInt();
    }
}

void ThemeConfigurator::setRounding(int rounding)
{
    if (m_rounding == rounding)
        return;

    m_rounding = rounding;
}

void ThemeConfigurator::setBaseSize(int baseSize)
{
    if (m_baseSize == baseSize)
        return;

    m_baseSize = baseSize;
}

void ThemeConfigurator::setDark(bool dark)
{
    m_dark = dark;
}

void ThemeConfigurator::configureSizes()
{
    if (!m_theme)
        return;

    m_theme->setProperty(::rounding, m_rounding);
    m_theme->setProperty(::baseSize, m_baseSize);
    m_theme->setProperty(::spacing, m_baseSize / ::spacingFactor);
    m_theme->setProperty(::margins, m_baseSize / ::marginsFactor);
    m_theme->setProperty(::padding, m_baseSize / ::paddingFactor);
    m_theme->setProperty(::iconSize, m_baseSize / ::iconFactor);
    m_theme->setProperty(::sliderSize, m_baseSize / ::sliderFactor);
    m_theme->setProperty(::switchSize, m_baseSize / ::switchFactor);
    m_theme->setProperty(::handleSize, m_baseSize / ::handleSizeFactor);
    m_theme->setProperty(::checkmarkSize, m_baseSize / ::checkmarkFactor);
    m_theme->setProperty(::floatSize, m_baseSize / ::floatFactor);
    m_theme->setProperty(::mainFontSize, m_baseSize / ::mainFontFactor);
    m_theme->setProperty(::auxFontSize, m_baseSize / ::auxFontFactor);
}

void ThemeConfigurator::configureColors()
{
    if (!m_theme)
        return;

    QObject* colors = m_theme->property(::colors).value<QObject*>();
    if (!colors)
        return;

    // set theme base color
    if (m_dark)
    {
        colors->setProperty(::background, ::darkBackgroundColor);
        colors->setProperty(::text, ::darkTextColor);
        colors->setProperty(::selection, ::darkSelectionColor);
        colors->setProperty(::selectedText, ::darkSelectedTextColor);
        colors->setProperty(::hover, ::darkHoverColor);

        // make disabled color bluer
        QColor disabledColor = ::darkTextColor.lighter(::darkDisabledFactor);
        disabledColor.setBlue(disabledColor.blue() * darkBlueDisabledFactor);
        colors->setProperty(::disabled, disabledColor);
        colors->setProperty(::sunken, ::darkBackgroundColor.lighter(::darkSunkenFactor));
        colors->setProperty(::raised, ::darkBackgroundColor.lighter(::darkRaisedFactor));
        colors->setProperty(::control, ::darkBackgroundColor.lighter(::darkControlFactor));
        colors->setProperty(::border, ::darkBackgroundColor.lighter(::darkBorderFactor));
    }
    else
    {
        colors->setProperty(::background, ::brightBackgroundColor);
        colors->setProperty(::text, ::brightTextColor);
        colors->setProperty(::selection, ::brightSelectionColor);
        colors->setProperty(::selectedText, ::brightSelectedTextColor);
        colors->setProperty(::hover, ::brightHoverColor);

        colors->setProperty(::disabled, ::brightTextColor.lighter(::brightDisabledFactor));
        colors->setProperty(::sunken, ::brightBackgroundColor.lighter(::brightSunkenFactor));
        colors->setProperty(::raised, ::brightBackgroundColor.lighter(::brightRaisedFactor));
        colors->setProperty(::control, ::brightBackgroundColor.darker(::brightControlFactor));
        colors->setProperty(::border, ::brightBackgroundColor.darker(::brightBorderFactor));
    }

    // set other theme colors
    colors->setProperty(::controlText, m_dark ? darkTextColor : brightTextColor);
    colors->setProperty(::tip, m_dark ? darkSelectionColor : brightSelectionColor);
    colors->setProperty(::tipText, m_dark ? darkTextColor : brightTextColor);
    colors->setProperty(::highlight, m_dark ? darkSelectionColor : brightSelectionColor);
    colors->setProperty(::highlightedText, m_dark ? darkSelectedTextColor : brightSelectedTextColor);

    // set independent colors
    colors->setProperty(::link, ::linkColor);
    colors->setProperty(::positive, ::positiveColor);
    colors->setProperty(::neutral, ::neutralColor);
    colors->setProperty(::negative, ::negativeColor);
    colors->setProperty(::shadow, ::shadowColor);
}

void ThemeConfigurator::configureThemeFromConfig()
{
    QString val;
    QFile file;
    file.setFileName(m_pathToConfig);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "[CONFIG] ERROR: don't open config file" << m_pathToConfig;
    }
    val = file.readAll();
    QJsonParseError parseError;
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8(), &parseError);


}

void ThemeConfigurator::configureColorsFromConfig()
{
    QJsonObject root = loadJson(m_pathToConfig).object();
    if (root.isEmpty()) {
        return;
    }
    QJsonValueRef ref = root.find(m_dark ? "colors_night" : "colors_day").value();
    if (ref.isNull()) {
        return;
    }
    QJsonObject color = ref.toObject();
    qDebug() << "+++" << color;
}

void ThemeConfigurator::setPathToConfig(const QString &path)
{
    m_pathToConfig = path;
}

void ThemeConfigurator::saveThemeToJson()
{
    QJsonDocument doc;
    QJsonObject root;
    setDark(false);
    configureColors();
    root["colors_day"] = saveObjectToJson(m_theme->property(::colors).value<QObject*>());
    setDark(true);
    configureColors();
    root["colors_night"] = saveObjectToJson(m_theme->property(::colors).value<QObject*>());
    root["sizes"] = saveObjectToJson(m_theme);
    doc.setObject(root);
    saveJson(doc, m_pathToConfig);
}

QJsonDocument ThemeConfigurator::loadJson(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void ThemeConfigurator::saveJson(QJsonDocument document, QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

QJsonObject ThemeConfigurator::saveObjectToJson(QObject* obj)
{
    QJsonObject res;

    auto mo = obj->metaObject();
    std::vector<std::pair<QString, QVariant> > v;
    v.reserve(mo->propertyCount() - mo->propertyOffset());
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
      v.emplace_back(mo->property(i).name(), mo->property(i).read(obj));
    }
    std::sort(v.begin(), v.end());
    for (auto &i : v) {
        qDebug() << i.first << "=>" << i.second;
        res[i.first] = i.second.toString();
    }

    return res;
}
