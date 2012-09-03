#pragma once

#include <string>
#include <sstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

namespace yandex{namespace contest{namespace serialization
{
    template <typename IArchive>
    struct Reader
    {
        static_assert(IArchive::is_loading::value, "IArchive should be loading");

        template <typename IStream, typename T>
        static void readFromStream(IStream &in, T &obj)
        {
            IArchive ia(in);
            ia >> obj;
        }

        template <typename String, typename T>
        static void deserialize(const String &s, T &obj)
        {
            std::basic_istringstream<
                typename String::value_type,
                typename String::traits_type,
                typename String::allocator_type> buf(s);
            readFromStream(buf, obj);
        }

        template <typename T, typename String>
        static T deserialize(const String &s)
        {
            T obj;
            deserialize(s, obj);
            return obj;
        }
    };

    template <typename OArchive>
    struct Writer
    {
        static_assert(OArchive::is_saving::value, "OArchive should be saving");

        template <typename OStream, typename T>
        static void writeToStream(OStream &out, const T &obj)
        {
            OArchive oa(out);
            oa << obj;
        }

        template <typename String, typename T>
        static void serialize(String &s, const T &obj)
        {
            std::basic_ostringstream<
                typename String::value_type,
                typename String::traits_type,
                typename String::allocator_type> buf;
            writeToStream(buf, obj);
            s = buf.str();
        }

        template <typename String, typename T>
        static String serialize(const T &obj)
        {
            String s;
            serialize(s, obj);
            return s;
        }
    };

    typedef Writer<boost::archive::binary_oarchive> BinaryWriter;
    typedef Reader<boost::archive::binary_iarchive> BinaryReader;

    template <typename T>
    std::string serialize(const T &obj)
    {
        return BinaryWriter::serialize<std::string>(obj);
    }

    template <typename T>
    T deserialize(const std::string &s)
    {
        return BinaryReader::deserialize<T>(s);
    }
}}}
