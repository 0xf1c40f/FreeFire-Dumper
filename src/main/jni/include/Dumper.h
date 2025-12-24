#include "xdl.h"
#include "Utils.h"
#include "il2cpp-struct.h"
#include "il2cpp-tabledefs.h"
#include "MonoString.h"

Il2CppDomain *(*il2cpp_domain_get)();
Il2CppAssembly **(*il2cpp_domain_get_assemblies)(Il2CppDomain*, size_t*);
Il2CppImage *(*il2cpp_assembly_get_image)(Il2CppAssembly*);
size_t (*il2cpp_image_get_class_count)(Il2CppImage*);
Il2CppClass *(*il2cpp_image_get_class)(Il2CppImage*, size_t);
const char *(*il2cpp_class_get_name)(Il2CppClass*);
const char *(*il2cpp_class_get_namespace)(Il2CppClass*);
Il2CppType *(*il2cpp_class_get_type)(Il2CppClass*);
int (*il2cpp_class_get_flags)(Il2CppClass*);
bool (*il2cpp_class_is_valuetype)(Il2CppClass*);
bool (*il2cpp_class_is_enum)(Il2CppClass*);
Il2CppClass *(*il2cpp_class_get_parent)(Il2CppClass*);
FieldInfo *(*il2cpp_class_get_fields)(Il2CppClass*, void**);
int (*il2cpp_field_get_flags)(FieldInfo*);
Il2CppType *(*il2cpp_field_get_type)(FieldInfo*);
const char *(*il2cpp_field_get_name)(FieldInfo*);
void (*il2cpp_field_static_get_value)(FieldInfo*, void*);
size_t (*il2cpp_field_get_offset)(FieldInfo*);
Il2CppClass *(*il2cpp_class_from_type)(Il2CppType*);
MethodInfo *(*il2cpp_class_get_methods)(Il2CppClass*, void**);
int (*il2cpp_method_get_flags)(MethodInfo*, int*);
Il2CppType *(*il2cpp_method_get_return_type)(MethodInfo*);
int (*il2cpp_method_get_param_count)(MethodInfo*);
Il2CppType *(*il2cpp_method_get_param)(MethodInfo*, int);
bool (*il2cpp_type_is_byref)(Il2CppType*);
const char *(*il2cpp_method_get_param_name)(MethodInfo*, int);
const char *(*il2cpp_method_get_name)(MethodInfo*);

void HookInit() {
    void *handle = xdl_open("libil2cpp.so", XDL_DEFAULT);
    
    il2cpp_domain_get = (Il2CppDomain *(*)()) xdl_sym(handle, "il2cpp_domain_get", nullptr);
    il2cpp_domain_get_assemblies = (Il2CppAssembly **(*)(Il2CppDomain*, size_t*)) xdl_sym(handle, "il2cpp_domain_get_assemblies", nullptr);
    il2cpp_assembly_get_image = (Il2CppImage *(*)(Il2CppAssembly*)) xdl_sym(handle, "il2cpp_assembly_get_image", nullptr);
    il2cpp_image_get_class_count = (size_t (*)(Il2CppImage*)) xdl_sym(handle, "il2cpp_image_get_class_count", nullptr);
    il2cpp_image_get_class = (Il2CppClass *(*)(Il2CppImage*, size_t)) xdl_sym(handle, "il2cpp_image_get_class", nullptr);
    il2cpp_class_get_name = (const char *(*)(Il2CppClass*)) xdl_sym(handle, "il2cpp_class_get_name", nullptr);
    il2cpp_class_get_namespace = (const char *(*)(Il2CppClass*)) xdl_sym(handle, "il2cpp_class_get_namespace", nullptr);
    il2cpp_class_get_type = (Il2CppType *(*)(Il2CppClass*)) xdl_sym(handle, "il2cpp_class_get_type", nullptr);
    il2cpp_class_get_flags = (int (*)(Il2CppClass*)) xdl_sym(handle, "il2cpp_class_get_flags", nullptr);
    il2cpp_class_is_valuetype = (bool (*)(Il2CppClass*)) xdl_sym(handle, "il2cpp_class_is_valuetype", nullptr);
    il2cpp_class_is_enum = (bool (*)(Il2CppClass*)) xdl_sym(handle, "il2cpp_class_is_enum", nullptr);
    il2cpp_class_get_parent = (Il2CppClass *(*)(Il2CppClass*)) xdl_sym(handle, "il2cpp_class_get_parent", nullptr);
    il2cpp_class_get_fields = (FieldInfo *(*)(Il2CppClass*, void**)) xdl_sym(handle, "il2cpp_class_get_fields", nullptr);
    il2cpp_field_get_flags = (int (*)(FieldInfo*)) xdl_sym(handle, "il2cpp_field_get_flags", nullptr);
    il2cpp_field_get_type = (Il2CppType *(*)(FieldInfo*)) xdl_sym(handle, "il2cpp_field_get_type", nullptr);
    il2cpp_field_get_name = (const char *(*)(FieldInfo*)) xdl_sym(handle, "il2cpp_field_get_name", nullptr);
    il2cpp_field_static_get_value = (void (*)(FieldInfo*, void*)) xdl_sym(handle, "il2cpp_field_static_get_value", nullptr);
    il2cpp_field_get_offset = (size_t (*)(FieldInfo*)) xdl_sym(handle, "il2cpp_field_get_offset", nullptr);
    il2cpp_class_from_type = (Il2CppClass *(*)(Il2CppType*)) xdl_sym(handle, "il2cpp_class_from_type", nullptr);
    il2cpp_class_get_methods = (MethodInfo *(*)(Il2CppClass*, void**)) xdl_sym(handle, "il2cpp_class_get_methods", nullptr);
    il2cpp_method_get_flags = (int (*)(MethodInfo*, int*)) xdl_sym(handle, "il2cpp_method_get_flags", nullptr);
    il2cpp_method_get_return_type = (Il2CppType *(*)(MethodInfo*)) xdl_sym(handle, "il2cpp_method_get_return_type", nullptr);
    il2cpp_method_get_param_count = (int (*)(MethodInfo*)) xdl_sym(handle, "il2cpp_method_get_param_count", nullptr);
    il2cpp_method_get_param = (Il2CppType *(*)(MethodInfo*, int)) xdl_sym(handle, "il2cpp_method_get_param", nullptr);
    il2cpp_type_is_byref = (bool (*)(Il2CppType*)) xdl_sym(handle, "il2cpp_type_is_byref", nullptr);
    il2cpp_method_get_param_name = (const char *(*)(MethodInfo*, int)) xdl_sym(handle, "il2cpp_method_get_param_name", nullptr);
    il2cpp_method_get_name = (const char *(*)(MethodInfo*)) xdl_sym(handle, "il2cpp_method_get_name", nullptr);
}

string FixGenericType(Il2CppType *type) {
    string text;
    Il2CppClass *klass = il2cpp_class_from_type(type);
    Il2CppGenericClass *generic_class = klass->generic_class;
    if (generic_class) {
        string namef = string(il2cpp_class_get_name(klass));
        int pointF = namef.find('`');
        text = namef.substr(0, pointF);
        text += "<";
        Il2CppGenericContext context = generic_class->context;
        const Il2CppGenericInst *inst = context.class_inst;
        int type_argc = inst->type_argc;
        for (int v = 0; v < type_argc; ++v) {
            Il2CppClass *klass2 = il2cpp_class_from_type(inst->type_argv[v]);
            if (klass2->generic_class) {
                text += FixGenericType(inst->type_argv[v]);
            } else {
                text += string(il2cpp_class_get_name(klass2));
            }
            if (type_argc != (v + 1)) {
                text += ", ";
            }
        }
        text += ">";
    } else {
        text = string(il2cpp_class_get_name(klass));
    }
    return text;
}

bool _il2cpp_type_is_byref(Il2CppType *type) {
    auto byref = type->byref;
    if (il2cpp_type_is_byref) {
        byref = il2cpp_type_is_byref(type);
    }
    return byref;
}

void Dumper() {
    Il2CppDomain *domain = il2cpp_domain_get();
    size_t count_ass;
    Il2CppAssembly **assems = il2cpp_domain_get_assemblies(domain, &count_ass);
    for (int i = 0; i < count_ass; ++i) {
        Il2CppAssembly *assem = assems[i];
        Il2CppImage *img = il2cpp_assembly_get_image(assem);
        string image_name = "// " + to_string(i + 1) + ". " + string(img->name);
        DumpFile(image_name);
    }
    DumpFile();
    for (int i = 0; i < count_ass; ++i) {
        Il2CppAssembly *assem = assems[i];
        Il2CppImage *img = il2cpp_assembly_get_image(assem);
        
        size_t class_count = il2cpp_image_get_class_count(img);
        for (int n = 0; n < class_count; ++n) {
            Il2CppClass *klass = il2cpp_image_get_class(img, n);
            Il2CppType *klass_type = il2cpp_class_get_type(klass);
            
            const char *class_name = il2cpp_class_get_name(klass);
            const char *namespace_name = il2cpp_class_get_namespace(klass);
            const char *image_name = img->name;
            
            if (strcmp(namespace_name, "") != 0) {
                string pre_name = "// Image: " + string(image_name) + "\n// Namespace: " + string(namespace_name);
                DumpFile(pre_name);
            } else {
                string pre_name = "// Image: " + string(image_name);
                DumpFile(pre_name);
            }
            int flags = il2cpp_class_get_flags(klass);
            bool is_valuetype = il2cpp_class_is_valuetype(klass);
            bool is_enum = il2cpp_class_is_enum(klass);
            
            if (flags & TYPE_ATTRIBUTE_SERIALIZABLE) {
                DumpFile("[Serializable]");
            }
            auto visibility = flags & TYPE_ATTRIBUTE_VISIBILITY_MASK;
            
            string pre_klass;
            switch (visibility) {
                case TYPE_ATTRIBUTE_PUBLIC:
                case TYPE_ATTRIBUTE_NESTED_PUBLIC:
                    pre_klass += "public ";
                    break;
                case TYPE_ATTRIBUTE_NOT_PUBLIC:
                case TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM:
                case TYPE_ATTRIBUTE_NESTED_ASSEMBLY:
                    pre_klass += "internal ";
                    break;
                case TYPE_ATTRIBUTE_NESTED_PRIVATE:
                    pre_klass += "private ";
                    break;
                case TYPE_ATTRIBUTE_NESTED_FAMILY:
                    pre_klass += "protected ";
                    break;
                case TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM:
                    pre_klass += "protected internal ";
                    break;
            }
            if (flags & TYPE_ATTRIBUTE_ABSTRACT && flags & TYPE_ATTRIBUTE_SEALED) {
                pre_klass += "static ";
            } else if (!(flags & TYPE_ATTRIBUTE_INTERFACE) && flags & TYPE_ATTRIBUTE_ABSTRACT) {
                pre_klass += "abstract ";
            } else if (!is_valuetype && !is_enum && flags & TYPE_ATTRIBUTE_SEALED) {
                pre_klass += "sealed ";
            }
            if (flags & TYPE_ATTRIBUTE_INTERFACE) {
                pre_klass += "interface ";
            } else if (is_enum) {
                pre_klass += "enum ";
            } else if (is_valuetype) {
                pre_klass += "struct ";
            } else {
                pre_klass += "class ";
            }
            pre_klass += string(class_name);
            
            vector<string> extends;
            Il2CppClass *class_parent = il2cpp_class_get_parent(klass);
            if (!is_valuetype && !is_enum && class_parent) {
                Il2CppType *parent_type = il2cpp_class_get_type(class_parent);
                if (parent_type->type != IL2CPP_TYPE_OBJECT) {
                    extends.emplace_back(FixGenericType(parent_type));
                }
            }
            if (!extends.empty()) {
                pre_klass += " : " + extends[0];
                for (int i = 1; i < extends.size(); ++i) {
                    pre_klass += ", " + extends[i];
                }
            }
            pre_klass += " {";
            DumpFile(pre_klass);
            
            //Fields
            void *field_iter = NULL;
            bool field_pre = true;
            while (FieldInfo *field = il2cpp_class_get_fields(klass, &field_iter)) {
                string full_fields;
                if (field_pre) {
                    full_fields += "// Fields:\n";
                    field_pre = false;
                }
                full_fields += "\t";
                int attrs = il2cpp_field_get_flags(field);
                
                auto access = attrs & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK;
                switch (access) {
                    case FIELD_ATTRIBUTE_PRIVATE:
                        full_fields += "private ";
                        break;
                    case FIELD_ATTRIBUTE_PUBLIC:
                        full_fields += "public ";
                        break;
                    case FIELD_ATTRIBUTE_FAMILY:
                        full_fields += "protected ";
                        break;
                    case FIELD_ATTRIBUTE_ASSEMBLY:
                    case FIELD_ATTRIBUTE_FAM_AND_ASSEM:
                        full_fields += "internal ";
                        break;
                    case FIELD_ATTRIBUTE_FAM_OR_ASSEM:
                        full_fields += "protected internal ";
                        break;
                }
                if (attrs & FIELD_ATTRIBUTE_LITERAL) {
                    full_fields += "const ";
                } else {
                    if (attrs & FIELD_ATTRIBUTE_STATIC) {
                        full_fields += "static ";
                    }
                    if (attrs & FIELD_ATTRIBUTE_INIT_ONLY) {
                        full_fields += "readonly ";
                    }
                }
                Il2CppType *field_type = il2cpp_field_get_type(field);
                Il2CppClass *field_class = il2cpp_class_from_type(field_type);
                
                const char *fieild_name = il2cpp_field_get_name(field);
                const char *return_field_name = il2cpp_class_get_name(field_class);
                
                full_fields += FixGenericType(field_type) + " " + string(fieild_name);
                
                if (attrs & FIELD_ATTRIBUTE_LITERAL && is_enum) {
                    uint64_t val = 0;
                    il2cpp_field_static_get_value(field, &val);
                    stringstream convert_1;
                    convert_1 << " = " << dec << val << ";";
                    full_fields += convert_1.str();
                } else {
                    stringstream convert_2;
                    convert_2 << "; // 0x" << hex << il2cpp_field_get_offset(field);
                    full_fields += convert_2.str();
                }
                if (attrs & FIELD_ATTRIBUTE_LITERAL && !is_enum) {
                    uint64_t val = 0;
                    il2cpp_field_static_get_value(field, &val);
                    if (FixGenericType(field_type) == "String") {
                        MonoString *val1 = (MonoString*)val;
                        full_fields += " = " + val1->toString() + ";";
                    }
                    if (FixGenericType(field_type) == "Int32") {
                        stringstream convert_1;
                        convert_1 << " = " << dec << val << ";";
                        full_fields += convert_1.str();
                    }
                    if (FixGenericType(field_type) == "Single") {
                        stringstream convert_1;
                        float fval = *reinterpret_cast<float*>(&val);
                        convert_1 << " = " << dec << fval << ";";
                        full_fields += convert_1.str();
                    }
                    if (FixGenericType(field_type) == "Boolean") {
                        stringstream convert_1;
                        bool fval = *reinterpret_cast<bool*>(&val);
                        convert_1 << " = " << dec << fval << ";";
                        full_fields += convert_1.str();
                    }
                }
                DumpFile(full_fields);
            }
            if (!field_pre) {
                DumpFile();
            }
            //Methods
            void *method_iter = NULL;
            bool method_pre = true;
            while (MethodInfo *method = il2cpp_class_get_methods(klass, &method_iter)) {
                string full_methodss;
                if (method_pre) {
                    full_methodss += "// Methods:\n";
                    method_pre = false;
                }
                full_methodss += "\t";
                int iflags = 0;
                int flags = il2cpp_method_get_flags(method, &iflags);
                
                auto access = flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;
                switch (access) {
                    case METHOD_ATTRIBUTE_PRIVATE:
                        full_methodss += "private ";
                        break;
                    case METHOD_ATTRIBUTE_PUBLIC:
                        full_methodss += "public ";
                        break;
                    case METHOD_ATTRIBUTE_FAMILY:
                        full_methodss += "protected ";
                        break;
                    case METHOD_ATTRIBUTE_ASSEM:
                    case METHOD_ATTRIBUTE_FAM_AND_ASSEM:
                        full_methodss += "internal ";
                        break;
                    case METHOD_ATTRIBUTE_FAM_OR_ASSEM:
                        full_methodss += "protected internal ";
                        break;
                }
                if (flags & METHOD_ATTRIBUTE_STATIC) {
                    full_methodss += "static ";
                }
                if (flags & METHOD_ATTRIBUTE_ABSTRACT) {
                    full_methodss += "abstract ";
                    if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
                        full_methodss += "override ";
                    }
                } else if (flags & METHOD_ATTRIBUTE_FINAL) {
                    if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
                        full_methodss += "sealed override ";
                    }
                } else if (flags & METHOD_ATTRIBUTE_VIRTUAL) {
                    if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_NEW_SLOT) {
                        full_methodss += "virtual ";
                    } else {
                        full_methodss += "override ";
                    }
                }
                if (flags & METHOD_ATTRIBUTE_PINVOKE_IMPL) {
                    full_methodss += "extern ";
                }
                Il2CppType *return_type_m = il2cpp_method_get_return_type(method);
                if (_il2cpp_type_is_byref(return_type_m)) {
                    full_methodss += "ref ";
                }
                Il2CppClass *return_class = il2cpp_class_from_type(return_type_m);
                
                const char *name_return_m = il2cpp_class_get_name(return_class);
                const char *name_method = il2cpp_method_get_name(method);
                
                full_methodss += FixGenericType(return_type_m) + " " + string(name_method) + "(";
                
                int param_count_m = il2cpp_method_get_param_count(method);
                for (int m = 0; m < param_count_m; ++m) {
                    Il2CppType *param = il2cpp_method_get_param(method, m);
                    auto attrs = param->attrs;
                    if (_il2cpp_type_is_byref(param)) {
                        if (attrs & PARAM_ATTRIBUTE_OUT && !(attrs & PARAM_ATTRIBUTE_IN)) {
                            full_methodss += "out ";
                        } else if (attrs & PARAM_ATTRIBUTE_IN && !(attrs & PARAM_ATTRIBUTE_OUT)) {
                            full_methodss += "in ";
                        } else {
                            full_methodss += "ref ";
                        }
                    } else {
                        if (attrs & PARAM_ATTRIBUTE_IN) {
                            full_methodss += "[In] ";
                        }
                        if (attrs & PARAM_ATTRIBUTE_OUT) {
                            full_methodss += "[Out] ";
                        }
                    }
                    Il2CppClass *parameter_class = il2cpp_class_from_type(param);
                    const char *param_type_name = il2cpp_class_get_name(parameter_class);
                    const char *param_name = il2cpp_method_get_param_name(method, m);
                    
                    full_methodss += FixGenericType(param) + " " + string(param_name);
                    if (param_count_m != (m + 1)) {
                        full_methodss += ", ";
                    }
                }
                full_methodss += ") { }";
                
                if (method->methodPointer) {
                    full_methodss += " // Offset: 0x";
                    stringstream convert_3;
                    convert_3 << hex << (uintptr_t)method->methodPointer - libBaseAddress;
                    full_methodss += convert_3.str();
                } else {
                    full_methodss += " // Offset: 0x0";
                }
                DumpFile(full_methodss);
            }
            DumpFile("}\n");
        }
    }
}