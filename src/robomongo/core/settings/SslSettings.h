#pragma once

#include <QString>
#include <QVariant>
#include <QVariantMap>

namespace Robomongo
{
    class SslSettings
    {
    public:
        SslSettings();

        /**
         * Clones credential settings.
         */
        SslSettings *clone() const;

        /**
         * Converts to QVariantMap
         */
        QVariant toVariant() const;
        void fromVariant(const QVariantMap &map);


        // todo: getters
        std::string pemKeyFile() const { return _pemKeyFile; }
        std::string caFile() const { return _caFile; }
        std::string pemPassPhrase() const { return _pemPassPhrase; }

        // todo: setters 
        void setPemKeyFile(const std::string &path) { _pemKeyFile = path; }
        void setCaFile(const std::string &path) { _caFile = path; }
        void setPemPassPhrase(const std::string &pemPassPhrase) { _pemPassPhrase = pemPassPhrase; }

        /**
         * Flag, indicating whether we should use
         * this SSL settings or not.
         */
        bool enabled() const { return _enabled; }
        bool sslEnabled() const { return _enabled; }
        void enableSSL(bool enabled) { _enabled = enabled; }

    private:
        std::string _caFile;
        std::string _pemKeyFile;
        std::string _pemPassPhrase;
        /**
         * Flag, indicating whether we should use
         * this SSL settings or not.
         */
        bool _enabled;
    };
}