#pragma once

#include "yandex/contest/config/Error.hpp"
#include "yandex/contest/config/TypeTraits.hpp"

#include <type_traits>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

namespace yandex{namespace contest{namespace config
{
    template <typename Ptree>
    class InputArchive: private boost::noncopyable
    {
    public:
        typedef std::integral_constant<bool, true> is_loading;
        typedef std::integral_constant<bool, false> is_saving;

        inline unsigned int get_library_version() { return 0; }

    public:
        explicit InputArchive(const Ptree &ptree): ptree_(&ptree) {}

        template <typename T>
        InputArchive &operator&(T &obj)
        {
            return *this >> obj;
        }

        template <typename T>
        InputArchive &operator>>(T &obj)
        {
            load(obj);
            return *this;
        }

        template <typename T>
        InputArchive &operator>>(const boost::serialization::nvp<T> &nvp)
        {
            boost::optional<const Ptree &> ptree = ptree_->get_child_optional(nvp.name());
            if (ptree)
            {
                loadFromPtree(nvp.value(), ptree.get());
            }
            else
            {
                reset(nvp.value());
            }
            return *this;
        }

        template <typename T>
        static void loadFromPtree(T &obj, const Ptree &ptree)
        {
            InputArchive<Ptree> ia(ptree);
            ia >> obj;
        }

    private:
        template <typename T>
        void reset(T &value)
        {
            value = T();
        }

        /// For complex types.
        template <typename T>
        typename std::enable_if<!traits::directAssign<T>::value, void>::type
        load(T &obj)
        {
            obj.serialize(*this, boost::serialization::version<T>::value);
            //FIXME boost::serialization::serialize_adl(*this, obj, boost::serialization::version<T>::value);
        }

        /*!
         * \brief Helper for integral types to load them from std::istream
         * instances using oct and hex prefixes.
         */
        template <typename T>
        class Integral
        {
        public:
            constexpr Integral()=default;
            constexpr Integral(const T value): value_(value) {}
            constexpr operator T() const { return value_; }

        public:
            friend std::istream &operator>>(std::istream &in, Integral &integral)
            {
                std::ios_base::fmtflags flags = in.flags();
                in.unsetf(std::ios_base::basefield);
                in >> integral.value_;
                in.setf(flags);
                return in;
            }

        private:
            T value_ = 0;
        };

        /// For integral primitive types.
        template <typename T>
        typename std::enable_if<std::is_integral<T>::value, void>::type
        loadPrimitive(T &obj)
        {
            obj = ptree_->template get_value<Integral<T>>();
        }

        /// For non-integral primitive types.
        template <typename T>
        typename std::enable_if<!std::is_integral<T>::value, void>::type
        loadPrimitive(T &obj)
        {
            obj = ptree_->template get_value<T>();
        }

        /// For primitive types.
        template <typename T>
        typename std::enable_if<traits::directAssign<T>::value, void>::type
        load(T &obj)
        {
            loadPrimitive(obj);
        }

        /// For boost::optional.
        template <typename T>
        void load(boost::optional<T> &obj)
        {
            T value;
            load(value);
            obj = value;
        }

        /// For boost::filesystem::path.
        void load(boost::filesystem::path &obj)
        {
            obj = ptree_->template get_value<std::string>();
        }

        /// For std::unordered_map.
        template <typename Key, typename Tp, typename Hash, typename Pred, typename Alloc>
        void load(std::unordered_map<Key, Tp, Hash, Pred, Alloc> &obj)
        {
            obj.clear();
            for (const typename Ptree::value_type &keyValue: *ptree_)
            {
                const Key key = boost::lexical_cast<Key>(keyValue.first);
                Tp value;
                loadFromPtree(value, keyValue.second);
                obj.emplace(key, value);
            }
        }

        /// For std::unordered_set.
        template <typename Value, typename Hash, typename Pred, typename Alloc>
        void load(std::unordered_set<Value, Hash, Pred, Alloc> &obj)
        {
            obj.clear();
            for (const typename Ptree::value_type &keyValue: *ptree_)
            {
                Value value;
                loadFromPtree(value, keyValue.second);
                obj.insert(value);
            }
        }

        /// For std::vector.
        template <typename Tp, typename Alloc>
        void load(std::vector<Tp, Alloc> &obj)
        {
            obj.resize(ptree_->size());
            auto objIter = obj.begin();
            auto ptreeIter = ptree_->begin();
            for (; objIter != obj.end(); ++objIter, ++ptreeIter)
                loadFromPtree(*objIter, ptreeIter->second);
        }

        /// For boost::variant.
        template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
        void load(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> &obj);

    private:
        const Ptree *const ptree_;
    };

    namespace input_archive_detail
    {
        /// Base declaration.
        template <typename ... Args>
        struct LoadVariant;

        /// Implementation.
        template <typename Arg, typename ... Args>
        struct LoadVariant<Arg, Args...>
        {
            /*!
             * \brief Key is unknown.
             *
             * \note This overload is needed
             * for boost::variant implementation
             * that uses boost::detail::variant::void_.
             */
            template <typename Archive, typename Variant>
            static typename std::enable_if<!traits::typeKey<Variant, Arg>::value, void>::type
            load(const std::string &name, Archive &, Variant &)
            {
                BOOST_THROW_EXCEPTION(
                    VariantLoadInvalidKeyError() <<
                    VariantLoadKeyError::key(name) <<
                    Error::message("Unknown type."));
            }

            /// Check Arg's key.
            template <typename Archive, typename Variant>
            static typename std::enable_if<static_cast<bool>(traits::typeKey<Variant, Arg>::value), void>::type
            load(const std::string &name, Archive &ar, Variant &obj)
            {
                if (name == traits::typeKey<Variant, Arg>::value)
                {
                    Arg arg;
                    ar >> arg;
                    obj = arg;
                }
                else
                {
                    LoadVariant<Args...>::load(name, ar, obj);
                }
            }
        };

        /// There is no types left.
        template <>
        struct LoadVariant<>
        {
            template <typename Archive, typename Variant>
            void load(const std::string &name, Archive &, Variant &)
            {
                BOOST_THROW_EXCEPTION(
                    VariantLoadInvalidKeyError() <<
                    VariantLoadKeyError::key(name) <<
                    Error::message("There is no types left for variant."));
            }
        };
    }

    template <typename Ptree>
    template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
    void InputArchive<Ptree>::load(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> &obj)
    {
        if (ptree_->empty())
            BOOST_THROW_EXCEPTION(VariantLoadNoKeyError());
        if (ptree_->size() > 1)
            BOOST_THROW_EXCEPTION(VariantLoadMultipleKeysError());
        const std::string typeName = ptree_->front().first;
        InputArchive<Ptree> ar(ptree_->front().second);
        input_archive_detail::LoadVariant<BOOST_VARIANT_ENUM_PARAMS(T)>::load(typeName, ar, obj);
    }
}}}
