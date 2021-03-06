#pragma once

#include "Hypodermic/IRegistration.h"
#include "Hypodermic/ProvidedInstanceRegistrationActivator.h"
#include "Hypodermic/TypeInfo.h"


namespace Hypodermic
{

    template <class T>
    class ProvidedInstanceRegistration : public IRegistration
    {
    public:
        ProvidedInstanceRegistration(const std::shared_ptr< T >& instance,
                                     const TypeAliases& typeAliases)
            : m_activator(*this, instance)
            , m_instanceType(Utils::getMetaTypeInfo< T >())
            , m_typeAliases(typeAliases)
        {
        }
    
        const TypeInfo& instanceType() const override
        {
            return m_instanceType;
        }

        const TypeAliases& typeAliases() const override
        {
            return m_typeAliases;
        }

        DependencyFactory getDependencyFactory(const TypeInfo&) const override
        {
            return nullptr;
        }

        IRegistrationActivator& activator() const override
        {
            return m_activator;
        }

        InstanceLifetimes::InstanceLifetime instanceLifetime() const override
        {
            return InstanceLifetimes::Persistent;
        }

    private:
        mutable ProvidedInstanceRegistrationActivator< T > m_activator;
        TypeInfo m_instanceType;
        TypeAliases m_typeAliases;
    };

} // namespace Hypodermic