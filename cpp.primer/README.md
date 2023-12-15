# C++ Primer, Fifth Edition

## Chapter 1. Getting Started
## Part I: The Basics
## Part II: The C++ Library
## Part III: Tools for Class Authors
### Chapter 16. Templates and Generic Programming
#### 16.1 Defining a Template
##### 16.1.1. Function Templates
- Defining a Function Template
- Instantiating a Function Template
- Template Type Parameters
- Nontype Template Parameters
- `inline` and `constexpr` Function Templates
- Writing Type-Independent Code
- Template Compilation
- Compilation Errors Are Mostly Reported during Instantiation

examples:
- [function template demo1](./template_and_generic_programming/func_template_demo1.cpp)

##### 16.1.2. Class Templates
- Defining a Class Template
- Instantiating a Class Template
- References to a Template Type in the Scope of the Template
- Member Functions of Class Templates
- Instantiation of Class-Template Member Functions
- Simplifying Use of a Template Class Name inside Class Code
- Using a Class Template Name outside the Class Template Body
- Class Templates and Friends
    - One-to-One Friendship
    - General and Specific Template Friendship
    - Befriending the Template’s Own Type Parameter
- [Template Type Aliases](./template_and_generic_programming/template_type_aliases.cpp)
- [`static` Members of Class Templates](./template_and_generic_programming/static_member_of_class_template.cpp)

examples:
- [Blob](./template_and_generic_programming/blob.h)
- [test_blob](./template_and_generic_programming/test_blob.cpp)
- [BlobPtr](./template_and_generic_programming/blob_ptr.h)
- [test_blob_ptr](./template_and_generic_programming/test_blob_ptr.cpp)

##### 16.1.3. Template Parameters
- Template Parameters and Scope
- Template Declarations
- Using Class Members That Are Types
- [Default Template Arguments](./template_and_generic_programming/default_template_args.cpp)
- [Template Default Arguments and Class Templates](./template_and_generic_programming/class_templates_default_args.cpp)

##### 16.1.4. Member Templates
- [Member Templates of Ordianary (Nontemplate) Classes](./template_and_generic_programming/member_templates_of_nontemplate_classes.cpp)
- Member Templates of Class Templates
- [Instantiation and Member Templates](./template_and_generic_programming/test_blob_2.cpp)

##### 16.1.5. Controlling Instantiations

In large systems, the overhead of instantiating the same template in multiple files
can become significant. Under the new standard (i.e., c++11), we can avoid this overhead through
an explicit instantiation. **This can reduce compilation time**.

- Instantiation Definitions Instantiate All Members

examples:
- [explicit instantiation demo](./template_and_generic_programming/explicit_instantiation_demo/)

##### 16.1.6. Efficiency and Flexibility

> The library smart pointer types (i.e., `shared_ptr` and `unique_ptr`) offer a good illustration of design choices faced by designers of templates. The obvious difference between `shared_ptr` and `unique_ptr` is the strategy they use in managing the pointer they hold—one class gives us shared ownership; the other owns the pointer that it holds. This difference is essential to what these classes do. These classes also differ in how they let users override their default deleter. We can easily override the deleter of a `shared_ptr` by passing a callable object when we create or reset the pointer. In contrast, the type of the deleter is part of the type of a `unique_ptr` object. Users must supply that type as an explicit template argument when they define a `unique_ptr`. As a result, it is more complicated for users of `unique_ptr` to provide their own deleter.

- `shared_ptr` Binding the Deleter at Run Time
- `unique_ptr` Binding the Deleter at Compile Time

#### 16.2. Template Argument Deduction
##### 16.2.1. Conversions and Template Type Parameters
> `const` conversions and array or function to pointer are the only automatic conversions for arguments to parameters with template types.

> Normal conversions are applied to arguments whose type is not a template parameter.
- Function Parameters That Use the Same Template Parameter Type
- Normal Conversions Apply for Ordinary Arguments

examples:
- [example code](./template_and_generic_programming/conversions_and_temp_type_params.cpp)

##### 16.2.2. Function-Template Explicit Arguments
> In some situations, it is not possible for the compiler to deduce the types of the template arguments. In others, we want to allow the user to control the template instantiation. Both cases arise most often when a function return type differs from any of those used in the parameter list.
- Specifying an Explicit Template Argument
- Normal Conversions Apply for Explicitly Specified Arguments

examples:
- [example code](./template_and_generic_programming/func-template_explicit_args.cpp)

##### 16.2.3. Trailing Return Types and Type Transformation
> Using an explicit template argument to represent a template function’s return type works well when we want to let the user determine the return type. In other cases, requiring an explicit template argument imposes a burden on the user with no compensating advantage.

- [The Type Transformation Library Template Classes](./template_and_generic_programming/type_transformation.cpp)

examples:
- [example code](./template_and_generic_programming/trailing_return_types.cpp)

##### 16.2.4. Function Pointers and Argument Deduction
> When we initialize or assign a function pointer from a function template, the compiler uses the type of the pointer to deduce the template argument(s).

examples:
- [example code](./template_and_generic_programming/func_pointers_and_args_deduction.cpp)

## Part IV: Advanced Topics