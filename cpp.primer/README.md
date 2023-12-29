# C++ Primer, Fifth Edition

## Chapter 1. Getting Started
## Part I: The Basics
### Chapter 2. Variables and Basic Types
#### 2.1. Primitive Built-in Types
#### 2.2. Variables
#### 2.3. Compound Types
#### 2.4. const Qualifier
- Initialization and `const`
- By Default, `const` Objects Are Local to a File
##### 2.4.1. References to `const`
##### 2.4.2. Pointers and `const`
##### 2.4.3. Top-Level const
##### 2.4.4. `constexpr` and Constant Expressions
> A constant expression is an expression **whose value cannot change** and that **can be evaluated at compile time**. A *literal* is a constant expression. A *const object that is initialized from a constant expression* is also a constant expression.
- `constexpr` Variables
- Literal Types
- Pointers and `constexpr`

examples:
- [demo](./variables_and_basic_types/const_expr_demo.cpp)

#### 2.5. Dealing with Types
#### 2.6. Defining Our Own Data Structures

### Chapter 7. Classes
#### 7.1. Defining Abstract Data Types
##### 7.1.1. Designing the Sales_data Class
examples:
- [`SalesData` class](./classes/sales_data/)
##### 7.1.2. Defining the Revised Sales_data Class
- Defining Member Functions
- Introducing `this`
- Introducing `const` Member Functions
- Class Scope and Member Functions
- Defining a Member Function outside the Class
- Defining a Function to Return “This” Object
##### 7.1.3. Defining Nonmember Class-Related Functions
- Defining the `read` and `print` Functions
- Defining the `add` Function
##### 7.1.4. Constructors
- The Synthesized Default Constructor
- Some Classes Cannot Rely on the Synthesized Default Constructor
- Defining the `Sales_data` Constructors
- What `= default` Means
- Constructor Initializer List
- Defining a Constructor outside the Class Body
##### 7.1.5. Copy, Assignment, and Destruction

#### 7.2. Access Control and Encapsulation
> In C++ we use access specifiers to enforce encapsulation:
>   • Members defined after a public specifier are accessible to all parts of the program. The public members define the interface to the class.
>   • Members defined after a private specifier are accessible to the member functions of the class but are not accessible to code that uses the class. The private sections encapsulate (i.e., hide) the implementation.
- Using the `class` or `struct` Keyword
##### 7.2.1. Friends
> A class can allow another class or function to access its nonpublic members by making that class or function a friend. 
- Declarations for Friends

## Part II: The C++ Library
## Part III: Tools for Class Authors
### Chapter 13. Copy Control
#### 13.1. Copy, Assign, and Destroy
##### 13.1.1. The Copy Constructor
- The Synthesized Copy Constructor
- Copy Initialization
- Parameters and Return Values
- Constraints on Copy Initialization
- The Compiler Can Bypass the Copy Constructor

examples:
- [copy constructor demo1](./copy_control/copy_constructor_demo.cpp)
- [copy constructor demo2](./copy_control/copy_constructor_demo2.cpp)

##### 13.1.2. The Copy-Assignment Operator
- Introducing Overloaded Assignment
- The Synthesized Copy-Assignment Operator

##### 13.1.3. The Destructor
- What a Destructor Does
- When a Destructor Is Called
- The Synthesized Destructor

##### 13.1.4. The Rule of Three/Five
- Classes That Need Destructors Need Copy and Assignment
- Classes That Need Copy Need Assignment, and Vice Versa

##### 13.1.5. Using `= default`

##### 13.1.6. Preventing Copies
- Defining a Function as Deleted
- The Destructor Should Not be a Deleted Member
- The Copy-Control Members May Be Synthesized as Deleted
- `private` Copy Control

examples:
- [demo](./copy_control/preventing_copies.cpp)

#### 13.2. Copy Control and Resource Management
##### 13.2.1. Classes That Act Like Values
examples:
- [`HasPtr` acts like a value](./copy_control/has_ptr_demo1.cpp)
##### 13.2.2. Defining Classes That Act Like Pointers
examples:
- [`HasPtr` acts like a pointer](./copy_control/has_ptr_demo2.cpp)

#### 13.3. Swap
- Writing Our Own swap Function
- `swap` Functions Should Call `swap`, Not `std::swap`
- Using `swap` in Assignment Operators

examples:
- [swap demo](./copy_control/swap_demo.cpp)

#### 13.4. A Copy-Control Example
examples:
- [message handling (from CPP Primer 4th Edition)](./copy_control/message_handling)

#### 13.5. Classes That Manage Dynamic Memory
examples:
- [StrVec](./copy_control/str_vec/)

#### 13.6. Moving Objects
##### 13.6.1. Rvalue References
examples:
- [demo](./copy_control/r-value_ref_demo.cpp)
##### 13.6.2. Move Constructor and Move Assignment
##### 13.6.3. Rvalue References and Member Functions
- Rvalue and Lvalue Reference Member Functions
- Overloading and Reference Functions

examples:
- [demo1: reference member functions](./copy_control/lvalue_and_rvalue_ref_member_funcs.cpp)
- [demo2: overloading and reference functions](./copy_control/overloading_and_ref_funcs.cpp)

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

##### 16.2.5. Template Argument Deduction and References
- Type Deduction from Lvalue Reference Function Parameters
- Type Deduction from Rvalue Reference Function Parameters
- Reference Collapsing and Rvalue Reference Parameters
- Writing Template Functions with Rvalue Reference Parameters

examples:
- [demo1](./template_and_generic_programming/template_type_deduction_and_references.cpp)
- [demo2](./template_and_generic_programming/template_functions_with_rvalue_ref_params.cpp)

##### 16.2.6. Understanding `std::move`
- How `std::move` Is Defined
- How `std::move` Works
- `static_cast` from an Lvalue to an Rvalue Reference Is Permitted

examples:
- [demo1](./template_and_generic_programming/understand_move.cpp)

##### 16.2.7. Forwarding
> Some functions need to forward one or more of their arguments with their types unchanged to another, forwarded-to, function. In such cases, we need to preserve everything about the forwarded arguments, including whether or not the argument type is const, and whether the argument is an lvalue or an rvalue.

- Defining Function Parameters That Retain Type Information
- Using `std::forward` to Preserve Type Information in a Call

examples:
- [demo1](./template_and_generic_programming/forwarding.cpp)

#### 16.3. Overloading and Templates
- Writing Overloaded Templates
- Multiple Viable Templates
- Nontemplate and Template Overloads
- Missing Declarations Can Cause the Program to Misbehave

examples:
- [demo1](./template_and_generic_programming/overloading_and_template_demo1.cpp)
- [demo2](./template_and_generic_programming/overloading_and_template_demo2.cpp)
- [demo3](./template_and_generic_programming/overloading_and_template_demo3.cpp)

#### 16.4. Variadic Templates
> A variadic template is a template function or class that can take a varying number of parameters. The varying parameters are known as a parameter pack. There are two kinds of parameter packs: A template parameter pack represents zero or more template parameters, and a function parameter pack represents zero or more function parameters.
> We use an ellipsis to indicate that a template or function parameter represents a pack. In a template parameter list, class... or typename... indicates that the following parameter represents a list of zero or more types; the name of a type followed by an ellipsis represents a list of zero or more nontype parameters of the given type. In the function parameter list, a parameter whose type is a template parameter pack is a function parameter pack.

examples:
- [demo1](./template_and_generic_programming/variadic_templates_demo1.cpp)

##### 16.4.1. Writing a Variadic Function Template
##### 16.4.2. Pack Expansion

examples:
- [variadic print](./template_and_generic_programming/variadic_print.cpp)

##### 16.4.3. Forwarding Parameter Packs
examples:
- [`emplace_back` of `StrVec`](./copy_control/str_vec/str_vec.h)

#### 16.5. Template Specializations
- Defining a Function Template Specialization
- Function Overloading versus Template Specializations
- Class Template Specializations
- Class-Template Partial Specializations
- Specializing Members but Not the Class

examples:
- [function template specialization](./template_and_generic_programming/func_template_specialization.cpp)
- [class template specialization](./template_and_generic_programming/class_template_specialization_demo/)
- [class template partial specialization](./template_and_generic_programming/class_template_specialization_demo/partial_specialization_demo.cpp)
- [specializing members of the class template](./template_and_generic_programming/class_template_specialization_demo/specializing_the_member_demo.cpp)

## Part IV: Advanced Topics

### Chapter 17. Specialized Library Facilities
#### 17.1. The tuple Type
examples:
- [demo1](./specialized_library_facilities/tuple_demos/tuple_demo1.cpp)
- [demo2](./specialized_library_facilities/tuple_demos/tuple_demo2/)
##### 17.1.1. Defining and Initializing `tuple`s
##### 17.1.2. Using a `tuple` to Return Multiple Values

#### 17.2. The `bitset` Type
examples:
- [demo1](./specialized_library_facilities/bitset_demos/bitset_demo1.cpp)
##### 17.2.1. Defining and Initializing `bitset`s
##### 17.2.2. Operations on `bitset`s

#### 17.3. Regular Expressions
##### 17.3.1. Using the Regular Expression Library
- Specifying Options for a `regex` Object
- Errors in Specifying or Using a Regular Expression
- Regular Expression Classes and the Input Sequence Type

examples:
- [demo1](./specialized_library_facilities/regex_demos/regex_demo1.cpp)
- [demo2: specifying options](./specialized_library_facilities/regex_demos/regex_demo2.cpp)
- [demo3: catching errors](./specialized_library_facilities/regex_demos/regex_demo3.cpp)
- [demo4](./specialized_library_facilities/regex_demos/regex_demo4.cpp)

##### 17.3.2. The Match and Regex Iterator Types
- Using an `sregex_iterator`
- Using the Match Data

examples:
- [demo1](./specialized_library_facilities/regex_demos/regex_iter_demo1.cpp)
- [demo2](./specialized_library_facilities/regex_demos/regex_iter_demo2.cpp)

##### 17.3.3. Using Subexpressions
> A pattern in a regular expression often contains one or more subexpressions. A subexpression is a part of the pattern that itself has meaning. Regular-expression grammars typically use parentheses to denote subexpressions.
- Subexpressions for Data Validation
- Using the Submatch Operations

examples:
- [demo1](./specialized_library_facilities/regex_demos/subexpression_demo1.cpp)
- [demo2: check phonenumber](./specialized_library_facilities/regex_demos/check_phone_number.cpp)

##### 17.3.4. Using regex_replace
- Replacing Only Part of the Input Sequence
- Flags to Control Matches and Formatting
- Using Format Flags

examples:
- [demo1](./specialized_library_facilities/regex_demos/regex_replace_demo1.cpp)
- [demo2: reformat phonenumbers](./specialized_library_facilities/regex_demos/reformat_phonenumber.cpp)
- [demo3: reformat phonenumbers (with specifical `match_flag_type`)](./specialized_library_facilities/regex_demos/reformat_phonenumber2.cpp)

#### 17.4. Random Numbers
> Programs often need a source of random numbers. Prior to the new standard, both C and C++ relied on a simple C library function named `rand`. That function produces pseudorandom integers that are uniformly distributed in the range from 0 to a system-dependent maximum value that is at least 32767.
> However, the `rand` function has several problems. The random-number library, defined in the `random` header, solves these problems through a set of cooperating classes: **random-number engines** and **random-number distribution classes**.  An engine generates a sequence of unsigned random numbers. A distribution uses an engine to generate random numbers of a specified type, in a given range, distributed according to a particular probability distribution.

##### 17.4.1. Random-Number Engines and Distribution
- Distribution Types and Engines
- Comparing Random Engines and the rand Function
- Engines Generate a Sequence of Numbers
- Seeding a Generator

examples:
- [demo1: random engine (generator)](./specialized_library_facilities/random_number/rand_number_demo1.cpp)
- [demo2: distribution types adn engines](./specialized_library_facilities/random_number/rand_number_demo2.cpp)
- [demo3: seeding a generator](./specialized_library_facilities/random_number/rand_number_demo3.cpp)

##### 17.4.2. Other Kinds of Distributions
- Generating Random Real Numbers
- Using the Distribution’s Default Result Type
- Generating Numbers That Are Not Uniformly Distributed
- The `bernoulli_distribution` Class

examples:
- [demo1: uniform distributions](./specialized_library_facilities/random_number/uniform_distribution.cpp)
- [demo2: normal distribution](./specialized_library_facilities/random_number/normal_distribution.cpp)
- [demo3: bernoulli distribution](./specialized_library_facilities/random_number/bernoulli_distribution_demo2.cpp)

#### 17.5. The IO Library Revisited
##### 17.5.1. Formatted Input and Output
- Many Manipulators Change the Format State
- Controlling the Format of Boolean Values
- Specifying the Base for Integral Values
- Indicating Base on the Output
- Controlling the Format of Floating-Point Values
- Specifying How Much Precision to Print
- Specifying the Notation of Floating-Point Numbers
- Printing the Decimal Point
- Controlling Input Formatting

examples:
- [demo1: format ostream](./specialized_library_facilities/io_lib/formated_ostream_demo.cpp)
- [demo2: format istream](./specialized_library_facilities/io_lib/formated_istream_demo.cpp)

##### 17.5.2. Unformatted Input/Output Operations
> So far, our programs have used only formatted IO operations. The input and output operators (`<<` and `>>`) format the data they read or write according to the type being handled. The library also provides a set of low-level operations that support unformatted IO. These operations let us deal with a stream as **a sequence of uninterpreted bytes**.
- Single-Byte Operations
- Putting Back onto an Input Stream
- `int` Return Values from Input Operations
- Multi-Byte Operations
- Determining How Many Characters Were Read

examples:
- [demo1: `get`](./specialized_library_facilities/io_lib/get_demo.cpp)
- [demo2: `put`](./specialized_library_facilities/io_lib/put_demo.cpp)
- [demo3: `peek`](./specialized_library_facilities/io_lib/peek_demo.cpp)
- [demo4: `unget`](./specialized_library_facilities/io_lib/unget_demo.cpp)
- [demo5: `putback`](./specialized_library_facilities/io_lib/putback_demo.cpp)

##### 17.5.3. Random Access to a Stream
- Seek and Tell Functions
- There Is Only One Marker
- Repositioning the Marker
- Accessing the Marker
- Reading and Writing to the Same File

examples:
- [demo1](./specialized_library_facilities/io_lib/random_access_demo1.cpp)

### Chapter 18. Tools for Large Programs
#### 18.1. Exception Handling
> **Exception handling** allows independently developed parts of a program to communicate about and handle problems that arise at run time. Exceptions let us separate problem detection from problem resolution. One part of the program can detect a problem and can pass the job of resolving that problem to another part of the program. The detecting part need not know anything about the handling part, and vice versa.

##### 18.1.1. Throwing an Exception
- Stack Unwinding
- Objects Are Automatically Destroyed during Stack Unwinding
- Destructors and Exceptions
- The Exception Object

##### 18.1.2. Catching an Exception
- Finding a Matching Handler
- Rethrow
- The Catch-All Handler

##### 18.1.3. Function `try` Blocks and Constructors

##### 18.1.4. The `noexcept` Exception Specification
- Violating the Exception Specification
- Arguments to the noexcept Specification
- Exception Specifications and Pointers, Virtuals, and Copy Control

 examples:
 - [demo1](./tools_for_large_programs/exception_handling/noexcept_demo1.cpp)

##### 18.1.5. Exception Class Hierarchies
- Exception Classes for a Bookstore Application
- Using Our Own Exception Types

examples:
- [demo1: defining custom exception types for `SalesData`](./tools_for_large_programs/exception_handling/custom_exception_demo/)

#### 18.2. Namespaces
> Namespaces provide a much more controlled mechanism for preventing name collisions. Namespaces partition the global namespace. A namespace is a scope. By defining a library’s names inside a namespace, library authors (and users) can avoid the limitations inherent in global names.

##### 18.2.1. Namespace Definitions
- Each Namespace Is a Scope
- Namespaces Can Be Discontiguous
- Defining the Primer Namespace
- Defining Namespace Members
- Template Specializations
- The Global Namespace
- Nested Namespaces
- Inline Namespaces 
- Unnamed Namespaces

examples:
- [demo1](./tools_for_large_programs/namespace/sales_data/)

##### 18.2.2. Using Namespace Members
- Namespace Aliases
- `using` Declarations: A Recap
- `using` Directives
- `using` Directives and Scopes
- `using` Directives Example
- Headers and `using` Declarations or Directives

> Caution: Avoid `using` Directives
> Tip: One place where using directives are useful is in the implementation files of the namespace itself.

examples:
- [demo1: namespace aliases](./tools_for_large_programs/namespace/namespace_aliases/)
- [demo2: `using` declarations](./tools_for_large_programs/namespace/using_declarations/)
- [demo3: `using` directives](./tools_for_large_programs/namespace/using_directives/)

##### 18.2.3. Classes, Namespaces, and Scope
- Argument-Dependent Lookup and Parameters of Class Type
- Lookup and `std::move` and `std::forward`
- Friend Declarations and Argument-Dependent Lookup

examples:
- [demo1: name lookup for names used inside a namespace](./tools_for_large_programs/namespace/classes_namespace_and_scope/demo1.cpp)
- [demo2: name lookup, classes and namespaces](./tools_for_large_programs/namespace/classes_namespace_and_scope/demo2.cpp)
- [demo3: argument-dependent lookup and paramaters of class type](./tools_for_large_programs/namespace/classes_namespace_and_scope/demo3.cpp)
- [demo4: friend declarations and argument-dependent lookup](./tools_for_large_programs/namespace/classes_namespace_and_scope/demo4.cpp)

##### 18.2.4. Overloading and Namespaces
- Argument-Dependent Lookup and Overloading
- Overloading and `using` Declarations
- Overloading and `using` Directives
- Overloading across Multiple `using` Directives

examples:
- [demo1: argument-dependent lookup and overloading](./tools_for_large_programs/namespace/overloading_and_namespaces/demo1.cpp)
- [demo2: overloading and `using` declarations](./tools_for_large_programs/namespace/overloading_and_namespaces/demo2.cpp)
- [demo3: overloading and `using` directives](./tools_for_large_programs/namespace/overloading_and_namespaces/demo3.cpp)
- [demo4: overloading across multiple `using` directives](./tools_for_large_programs/namespace/overloading_and_namespaces/demo4.cpp)

#### 18.3. Multiple and Virtual Inheritance
##### 18.3.1. Multiple Inheritance
> The derivation list in a derived class can contain more than one base class and each base class has an optional access specifier. As with single inheritance, the derivation list may include only classes that have been defined and that were not defined as `final`. There is no language-imposed limit on the number of base classes from which a class can be derived. A base class may appear only once in a given derivation list.
- Multiply Derived Classes Inherit State from Each Base Class
- Derived Constructors Initialize All Base Classes
- Inherited Constructors and Multiple Inheritance
- Destructors and Multiple Inheritance
- Copy and Move Operations for Multiply Derived Classes

examples:
- [demo1: ZooAnimal](./tools_for_large_programs/multiple_and_virtual_inheritance/animal/)

##### 18.3.2. Conversions and Multiple Base Classes
- Lookup Based on Type of Pointer or Reference
examples:
- [demo1](./tools_for_large_programs/multiple_and_virtual_inheritance/conversions_and_multiple_base_calsses_demo1.cpp)

##### 18.3.3. Class Scope under Multiple Inheritance
> Under multiple inheritance, this same lookup happens simultaneously among all the direct base classes. If a name is found through more than one base class, then use of that name is ambiguous.

##### 18.3.4. Virtual Inheritance
> Virtual inheritance lets a class specify that it is willing to share its base class. The shared base-class subobject is called a virtual base class. Regardless of how often the same virtual base appears in an inheritance hierarchy, the derived object contains only one, shared subobject for that virtual base class.
- A Different `Panda` Class
- Using a Virtual Base Class
- Normal Conversions to Base Are Supported
- Visibility of Virtual Base-Class Members

examples:
- [demo1: a different ZooAnimal](./tools_for_large_programs/multiple_and_virtual_inheritance/animal2/)

##### 18.3.5. Constructors and Virtual Inheritance
> In a virtual derivation, the virtual base is initialized by the most derived constructor.
- How a Virtually Inherited Object Is Constructed
- Constructor and Destructor Order
