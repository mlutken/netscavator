#ifndef DEFAULTLOCALES_H
#define DEFAULTLOCALES_H

#include <nlohmann/json.hpp>

namespace crawl {

/** Findlocale info from 2 or 3 letter country code or currency code */
nlohmann::json findLocale(const std::string& country_or_currency_code);

/** Get locale info from 2 letter country code */
nlohmann::json localeFromCountryCode(const std::string& country_code);

/** Get locale info from 3 letter country code */
nlohmann::json localeFromCountryCode3(const std::string& country_code3);

/** Get locale info from 3 letter currency code */
nlohmann::json localeFromCurrencyCode(const std::string& currency_code);

std::string localeValue         (const std::string& country_code, const std::string& key);
bool        hasLocaleData       (const std::string& country_code);

/** Get 2 letter country_code from 3 letter country code*/
std::string countryCodeFrom3LetterCC(const std::string& country_code3);

} // namespace crawl

#endif // DEFAULTLOCALES_H
