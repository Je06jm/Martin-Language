#ifndef MARTIN_CONTEXT
#define MARTIN_CONTEXT

#include <parse.hpp>

namespace Martin {

    class VariableDefinitionBase;
    class FunctionDefinitionBase;
    class ClassDefinitionBase;
    class ObjectDefinitionBase;
    class PrimitiveDefinitionBase;
    class StructDefinitionBase;
    class UnionDefinitionBase;
    class TypeDefinitionBase;
    class ImportBase;
    class ContextBase;

    typedef std::shared_ptr<VariableDefinitionBase> VariableDefinition;
    typedef std::shared_ptr<FunctionDefinitionBase> FunctionDefinition;
    typedef std::shared_ptr<ObjectDefinitionBase> ObjectDefinition;
    typedef std::shared_ptr<ClassDefinitionBase> ClassDefinition;
    typedef std::shared_ptr<PrimitiveDefinitionBase> PrimitiveDefinition;
    typedef std::shared_ptr<UnionDefinitionBase> UnionDefinition;
    typedef std::shared_ptr<StructDefinitionBase> StructDefinition;
    typedef std::shared_ptr<TypeDefinitionBase> TypeDefinition;
    typedef std::shared_ptr<ImportBase> Import;
    typedef std::shared_ptr<ContextBase> Context;

    class VariableDefinitionBase {
    public:
        enum class Type {
            Let,
            Set,
            Const,
            Constexpr
        };

        VariableDefinitionBase(
            std::shared_ptr<uint8_t[]> name,
            const std::vector<TypeDefinition>& types,
            Type type,
            const std::string& extern_type,
            bool is_unsafe,
            Context context
            ) : name(name),
                types(types),
                type(type),
                extern_type(extern_type),
                is_unsafe(is_unsafe),
                context(context) {}

        std::shared_ptr<uint8_t[]> name;
        const std::vector<TypeDefinition> types;
        const std::string extern_type;

        const Type type;
        bool is_unsafe;
        const Context context;
    };

    class FunctionDefinitionBase {
    public:
        FunctionDefinitionBase(
            std::shared_ptr<uint8_t[]> name,
            const std::vector<VariableDefinition>& arguments,
            const std::vector<TypeDefinition>& types,
            const std::string& extern_type,
            bool is_unsafe,
            Context context
        ) : name(name),
            arguments(arguments),
            types(types),
            extern_type(extern_type),
            is_unsafe(is_unsafe),
            context(context) {}

        std::shared_ptr<uint8_t[]> name;
        const std::vector<VariableDefinition> arguments;
        const std::vector<TypeDefinition> types;
        const std::string extern_type;

        const bool is_unsafe;
        const Context context;
    };

    class ClassDefinitionBase {
    public:
        enum class Access {
            Public,
            Protected,
            Private
        };

        typedef struct {
            Access access;
            ClassDefinition class_definition;
        } InheritDefinition;

        typedef struct {
            Access access;
            ClassDefinition class_definition;
        } FriendDefinition;

        ClassDefinitionBase(
            std::shared_ptr<uint8_t[]> name,
            const std::vector<InheritDefinition>& inherits,
            const std::vector<FriendDefinition>& friends,
            const std::vector<ObjectDefinition>& public_defines,
            const std::vector<ObjectDefinition>& protected_defines,
            const std::vector<ObjectDefinition>& private_defines,
            const std::string& extern_type,
            bool is_unsafe,
            Context context
        ) : name(name),
            inherits(inherits),
            friends(friends),
            public_defines(public_defines),
            protected_defines(protected_defines),
            private_defines(private_defines),
            extern_type(extern_type),
            is_unsafe(is_unsafe),
            context(context) {}

        std::shared_ptr<uint8_t[]> name;
        std::vector<InheritDefinition> inherits;
        std::vector<FriendDefinition> friends;
        std::vector<ObjectDefinition> public_defines;
        std::vector<ObjectDefinition> protected_defines;
        std::vector<ObjectDefinition> private_defines;
        const std::string extern_type;

        const bool is_unsafe;
        const Context context;
    };

    class PrimitiveDefinitionBase {
    public:
        enum class Type {
            UInt8,
            UInt16,
            UInt32,
            UInt64,
            Int8,
            Int16,
            Int32,
            Int64,
            UIntMax,
            IntMax,
            UIntPtr,
            IntPtr,
            Float32,
            Float64,
            String8,
            String16l,
            String32l,
            String16b,
            String32b,
            True,
            False,
            None
        };

        typedef union {
            uint8_t uint8;
            uint16_t uint16;
            uint32_t uint32;
            uint64_t uint64;
            int8_t int8;
            int16_t int16;
            int32_t int32;
            int64_t int64;
            uintmax_t uintmax;
            intmax_t intmax;
            uintptr_t uintptr;
            intptr_t intptr;
            bool boolean;
            void* pointer;
        } ValueUnion;
        
        PrimitiveDefinitionBase(
            Type type,
            ValueUnion value
        ) : type(type),
            value(value) {}

        const Type type;
        const ValueUnion value;
        std::shared_ptr<uint8_t> string;
    };

    class UnionDefinitionBase {
    public:
        typedef struct {
            std::vector<std::string> names;
            TypeDefinition type;
        } MemberDefinition;

        UnionDefinitionBase(
            std::shared_ptr<uint8_t[]> name,
            const std::vector<MemberDefinition>& members
        ) : name(name),
            members(members) {}

        std::shared_ptr<uint8_t[]> name;
        std::vector<MemberDefinition> members;
    };

    class StructDefinitionBase {
    public:
        typedef struct {
            std::vector<std::string> names;
            TypeDefinition type;
        } MemberDefinition;

        StructDefinitionBase(
            std::shared_ptr<uint8_t[]> name,
            const std::vector<MemberDefinition>& members
        ) : name(name),
            members(members) {}

        std::shared_ptr<uint8_t[]> name;
        std::vector<MemberDefinition> members;
    };

    class TypeDefinitionBase {
    public:
        enum class Access {
            Value,
            Array,
            Shared,
            Reference,
            Pointer
        };

        enum class Type {
            Primitive,
            Struct,
            Union,
            Class,
            Function
        };

        TypeDefinitionBase(
            std::shared_ptr<uint8_t[]> name,
            const std::vector<Access>& access,
            Type type,
            PrimitiveDefinition primitive_definition,
            ClassDefinition class_definition,
            FunctionDefinition function_definition,
            Context context
        ) : name(name),
            access(access),
            type(type),
            primitive_definition(primitive_definition),
            class_definition(class_definition),
            function_definition(function_definition),
            context(context) {}

        std::shared_ptr<uint8_t[]> name;
        const std::vector<Access> access;
        const Type type;
        
        const PrimitiveDefinition primitive_definition;
        const StructDefinition struct_definition;
        const UnionDefinition union_definition;
        const ClassDefinition class_definition;
        const FunctionDefinition function_definition;

        const Context context;
    };

    class ObjectDefinitionBase {
    public:
        enum class Type {
            Variable,
            Function
        };

        ObjectDefinitionBase(
            bool is_static,
            bool is_override,
            bool is_virtual,
            bool is_unsafe,
            Type type,
            VariableDefinition variable_definition,
            FunctionDefinition function_definition,
            Context context
        ) : is_static(is_static),
            is_override(is_override),
            is_virtual(is_virtual),
            type(type),
            variable_definition(variable_definition),
            function_definition(function_definition),
            context(context) {}

        const bool is_static;
        const bool is_override;
        const bool is_virtual;

        const Type type;

        const VariableDefinition variable_definition;
        const FunctionDefinition function_definition;

        const Context context;
    };

    class ImportBase {
    public:
        enum class Access {
            Public,
            Private
        };

        typedef struct {
            Access access;
            std::shared_ptr<uint8_t[]> name;
        } ImportDefinition;

        ImportBase(
            std::shared_ptr<uint8_t[]> name,
            Access access,
            const std::vector<ImportDefinition>& imports
        ) : name(name),
            access(access),
            imports(imports) {}

        std::shared_ptr<uint8_t[]> name;
        const Access access;
        const std::vector<ImportDefinition> imports;

        static Import CreateFromNode(TreeNode node);
    };

    class ContextBase {
    public:
        ContextBase(
            const std::vector<Import> imports,
            const std::vector<TypeDefinition> definitions,
            Context parent
        ) : imports(imports),
            definitions(definitions),
            parent(parent) {}

        const std::vector<Import> imports;
        const std::vector<TypeDefinition> definitions;

        const Context parent;

        static Context CreateFromTree(Tree tree);
    };

}

#endif