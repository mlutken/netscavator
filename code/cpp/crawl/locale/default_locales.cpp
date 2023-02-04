#include "default_locales.h"
#include <iostream>

// for convenience
using json = nlohmann::json;

namespace crawl {

/**
  @see https://www.fincher.org/Utilities/CountryLanguageList.shtml
  */
static const auto g_locales_jobj = R"(
{
   "at" : {
       "country_code" : "at",
       "country_code3" : "aut",
       "currency_code" : "eur",
       "language_code" : "de",
       "decimal_point" : ",",
       "thousands_sep" : "."
   }
   ,
    "au" : {
        "country_code" : "au",
        "country_code3" : "aus",
        "currency_code" : "aud",
        "language_code" : "en",
        "decimal_point" : ".",
        "thousands_sep" : ","
    }
    ,
    "be" : {
        "country_code" : "be",
        "country_code3" : "bel",
        "currency_code" : "eur",
        "language_code" : "nl",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "ca" : {
        "country_code" : "ca",
        "country_code3" : "can",
        "currency_code" : "cad",
        "language_code" : "en",
        "decimal_point" : ".",
        "thousands_sep" : ","
    }
    ,
    "ch" : {
        "country_code" : "ch",
        "country_code3" : "che",
        "currency_code" : "chf",
        "language_code" : "de",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "de" : {
        "country_code" : "de",
        "country_code3" : "deu",
        "currency_code" : "eur",
        "language_code" : "de",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "dk" : {
        "country_code" : "dk",
        "country_code3" : "dnk",
        "currency_code" : "dkk",
        "language_code" : "da",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "es" : {
        "country_code" : "es",
        "country_code3" : "esp",
        "currency_code" : "eur",
        "language_code" : "es",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "eu" : {
       "country_code" : "eu",
       "country_code3" : "",
       "currency_code" : "eur",
       "language_code" : "en",
       "decimal_point" : ",",
       "thousands_sep" : " "
    }
    ,
    "fi" : {
       "country_code" : "fi",
       "country_code3" : "fin",
       "currency_code" : "eur",
       "language_code" : "fi",
       "decimal_point" : ",",
       "thousands_sep" : "."
    }
    ,
    "fr" : {
        "country_code" : "fr",
        "country_code3" : "fra",
        "currency_code" : "eur",
        "language_code" : "fr",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "gb" : {
        "country_code" : "gb",
        "country_code3" : "gbr",
        "currency_code" : "gbp",
        "language_code" : "en",
        "decimal_point" : ".",
        "thousands_sep" : ","
    }
    ,
    "is" : {
       "country_code" : "is",
       "country_code3" : "isl",
       "currency_code" : "isk",
       "language_code" : "is",
       "decimal_point" : ",",
       "thousands_sep" : "."
    }
    ,
    "it" : {
        "country_code" : "it",
        "country_code3" : "ita",
        "currency_code" : "eur",
        "language_code" : "it",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "nl" : {
        "country_code" : "nl",
        "country_code3" : "nld",
        "currency_code" : "eur",
        "language_code" : "nl",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "no" : {
        "country_code" : "no",
        "country_code3" : "nor",
        "currency_code" : "nok",
        "language_code" : "nb",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "nz" : {
        "country_code" : "nz",
        "country_code3" : "nzl",
        "currency_code" : "nzd",
        "language_code" : "en",
        "decimal_point" : ".",
        "thousands_sep" : ","
    }
    ,
    "pt" : {
        "country_code" : "pt",
        "country_code3" : "prt",
        "currency_code" : "eur",
        "language_code" : "pt",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "se" : {
        "country_code" : "se",
        "country_code3" : "swe",
        "currency_code" : "sek",
        "language_code" : "sv",
        "decimal_point" : ",",
        "thousands_sep" : "."
    }
    ,
    "us" : {
        "country_code" : "us",
        "country_code3" : "usa",
        "currency_code" : "usd",
        "language_code" : "en",
        "decimal_point" : ".",
        "thousands_sep" : ","
    }
}
)"_json;


nlohmann::json findLocale(const std::string& country_or_currency_code)
{
    auto json_loc = localeFromCountryCode(country_or_currency_code);
    if (!json_loc.empty()){
        return json_loc;
    }
    json_loc = localeFromCountryCode3(country_or_currency_code);
    if (!json_loc.empty()){
        return json_loc;
    }
    return localeFromCurrencyCode(country_or_currency_code);
}

nlohmann::json localeFromCountryCode(const std::string& country_code)
{
    const auto it = g_locales_jobj.find(country_code);
    if ( it != g_locales_jobj.end()) {
        return *it;
    }
    return nlohmann::json{};
}

nlohmann::json localeFromCountryCode3(const std::string& country_code3)
{
    for (const auto& element : g_locales_jobj.items()) {
        if (element.value()["country_code3"] == country_code3) {
            return element.value();
        }
    }
    return nlohmann::json{};
}

nlohmann::json localeFromCurrencyCode(const std::string& currency_code)
{
    for (const auto& element : g_locales_jobj.items()) {
        if (element.value()["currency_code"] == currency_code) {
            return element.value();
        }
    }
    return nlohmann::json{};
}

std::string localeValue(const std::string& country_code, const std::string& key)
{
    return g_locales_jobj[country_code][key];
}

bool hasLocaleData(const std::string& country_code)
{
   return g_locales_jobj.find(country_code) != g_locales_jobj.end();
}

std::string countryCodeFrom3LetterCC(const std::string& country_code3)
{
    std::string country_code;
    for (const auto& [cc, value] : g_locales_jobj.items()) {
        std::cerr << cc << " : " << value << "\n";
        if (value["country_code3"] == country_code3) {
            country_code = cc;
        }
    }
    return country_code;
}




} // namespace crawl

