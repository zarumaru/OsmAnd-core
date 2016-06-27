#ifndef _OSMAND_CORE_ADDRESSES_BY_NAME_SEARCH_H_
#define _OSMAND_CORE_ADDRESSES_BY_NAME_SEARCH_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>
#include <OsmAndCore/ignore_warnings_on_external_includes.h>
#include <QString>
#include <QHash>
#include <QList>
#include <OsmAndCore/restore_internal_warnings.h>

#include <OsmAndCore.h>
#include <OsmAndCore/PointsAndAreas.h>
#include <OsmAndCore/Nullable.h>

#include <OsmAndCore/IObfsCollection.h>
#include <OsmAndCore/Search/BaseSearch.h>

namespace OsmAnd
{
    class Address;
    class Building;

    class OSMAND_CORE_API AddressesByNameSearch Q_DECL_FINAL : public BaseSearch
    {
        Q_DISABLE_COPY_AND_MOVE(AddressesByNameSearch);
    public:
        struct OSMAND_CORE_API Criteria : public BaseSearch::Criteria
        {
            Criteria();
            virtual ~Criteria();

            Nullable<AreaI> bbox31;
            Nullable<AreaI> obfInfoAreaFilter;
            QString name;
            ObfAddressStreetGroupTypesMask streetGroupTypesMask;
            bool includeStreets;
            QString postcode;
            QList<std::shared_ptr<const Address>> addressFilter;
        };

        struct OSMAND_CORE_API ResultEntry : public IResultEntry
        {
            ResultEntry();
            virtual ~ResultEntry();

            std::shared_ptr<const Address> address;
            std::shared_ptr<const Building> building;
        };

    private:
    protected:
    public:
        AddressesByNameSearch(const std::shared_ptr<const IObfsCollection>& obfsCollection);
        virtual ~AddressesByNameSearch();

        virtual void performSearch(
            const ISearch::Criteria& criteria,
            const NewResultEntryCallback newResultEntryCallback,
            const std::shared_ptr<const IQueryController>& queryController = nullptr) const;
    };
}

#endif // !defined(_OSMAND_CORE_ADDRESSES_BY_NAME_SEARCH_H_)
