#ifndef _OSMAND_CORE_RESOLVED_MAP_STYLE_P_H_
#define _OSMAND_CORE_RESOLVED_MAP_STYLE_P_H_

#include "stdlib_common.h"
#include <array>

#include "QtExtensions.h"
#include "ignore_warnings_on_external_includes.h"
#include <QString>
#include <QList>
#include <QHash>
#include "restore_internal_warnings.h"

#include "OsmAndCore.h"
#include "PrivateImplementation.h"
#include "UnresolvedMapStyle.h"
#include "ResolvedMapStyle.h"

namespace OsmAnd
{
    class MapStyleValueDefinition;

    class ResolvedMapStyle;
    class ResolvedMapStyle_P Q_DECL_FINAL
    {
        Q_DISABLE_COPY_AND_MOVE(ResolvedMapStyle_P);
    public:
        typedef ResolvedMapStyle::StringId StringId;
        typedef IMapStyle::ValueDefinitionId ValueDefinitionId;
        typedef ResolvedMapStyle::Value ResolvedValue;
        typedef ResolvedMapStyle::RuleNode RuleNode;
        typedef ResolvedMapStyle::BaseRule BaseRule;
        typedef ResolvedMapStyle::Rule Rule;
        typedef ResolvedMapStyle::Attribute Attribute;
        typedef ResolvedMapStyle::Parameter Parameter;
        typedef ResolvedMapStyle::ParameterValueDefinition ParameterValueDefinition;
        
    private:
        QList<QString> _stringsForwardLUT;
        QHash<QString, StringId> _stringsBackwardLUT;
        StringId addStringToLUT(const QString& value);
        StringId resolveStringIdInLUT(const QString& value);
        bool resolveStringIdInLUT(const QString& value, StringId& outId) const;

        QList< std::shared_ptr<const MapStyleValueDefinition> > _valuesDefinitions;
        QHash< QString, ValueDefinitionId > _valuesDefinitionsIndicesByName;
        void registerBuiltinValueDefinitions();

        bool parseConstantValue(
            const QString& input,
            const MapStyleValueDataType dataType,
            const bool isComplex,
            MapStyleConstantValue& outValue) const;

        bool parseConstantValue(
            const QString& input,
            const MapStyleValueDataType dataType,
            const bool isComplex,
            MapStyleConstantValue& outValue);
        
        bool resolveConstant(const QString& name, QString& value) const;
        bool collectConstants();
        bool resolveValue(
            const QString& input,
            const MapStyleValueDataType dataType,
            const bool isComplex,
            ResolvedValue& outValue);
        std::shared_ptr<RuleNode> resolveRuleNode(
            const std::shared_ptr<const UnresolvedMapStyle::RuleNode>& unresolvedRuleNode);
        bool mergeAndResolveParameters();
        bool mergeAndResolveAttributes();
        bool mergeAndResolveRulesets();

        QString dumpRuleNode(
            const std::shared_ptr<const RuleNode>& ruleNode,
            const bool rejectSupported,
            const QString& prefix) const;
        QString dumpRuleNodeOutputValues(
            const std::shared_ptr<const RuleNode>& ruleNode,
            const QString& prefix,
            const bool allowOverride) const;
        QString dumpResolvedValue(
            const ResolvedValue& value,
            const MapStyleValueDataType dataType) const;
        QString dumpConstantValue(
            const MapStyleConstantValue& value,
            const MapStyleValueDataType dataType) const;
    protected:
        ResolvedMapStyle_P(ResolvedMapStyle* const owner);

        bool resolve();
        
        QHash<QString, QString> _constants;
        QHash<StringId, std::shared_ptr<const Parameter> > _parameters;
        QHash<StringId, std::shared_ptr<const Attribute> > _attributes;
        std::array< QHash<TagValueId, std::shared_ptr<const Rule> >, MapStyleRulesetTypesCount> _rulesets;
    public:
        virtual ~ResolvedMapStyle_P();

        ImplementationInterface<ResolvedMapStyle> owner;

        ValueDefinitionId getValueDefinitionIdByName(const QString& name) const;
        std::shared_ptr<const MapStyleValueDefinition> getValueDefinitionById(const ValueDefinitionId id) const;
        QList< std::shared_ptr<const MapStyleValueDefinition> > getValueDefinitions() const;

        bool parseConstantValue(
            const QString& input,
            const ValueDefinitionId valueDefintionId,
            MapStyleConstantValue& outParsedValue) const;
        bool parseConstantValue(
            const QString& input,
            const std::shared_ptr<const MapStyleValueDefinition>& valueDefintion,
            MapStyleConstantValue& outParsedValue) const;

        std::shared_ptr<const Parameter> getParameter(const QString& name) const;
        std::shared_ptr<const Attribute> getAttribute(const QString& name) const;
        QHash< TagValueId, std::shared_ptr<const Rule> > getRuleset(
            const MapStyleRulesetType rulesetType) const;

        QString getStringById(const StringId id) const;

        QString dump(const QString& prefix) const;

    friend class OsmAnd::ResolvedMapStyle;
    };
}

#endif // !defined(_OSMAND_CORE_RESOLVED_MAP_STYLE_P_H_)
