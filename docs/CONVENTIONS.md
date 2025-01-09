<style>
/*Highlight text*/
hl 
{
    color: #00CCA2;
    font-weight: bold;
}

/*Hightlight case type*/
case-type
{
    color: #8888FF;
    font-weight: bold;
}

</style>
## Naming conventions and style guide
### General
- <hl>**Local variables**</hl>: <case-type>***camelCase***</case-type>
```c++
int32_t localVariable { 10 };
```

- <hl>**Functions**</hl>: <case-type>***PascalCase***</case-type>
- <hl>**Function parameters**</hl>: <case-type>***camelCase***</case-type>
```c++
void Function(int32_t funcParam)
{

}
```

### File names and extensions
* <hl>**Folder names**</hl>: <case-type>snake_case</case-type>
* <hl>**File names**</hl>: <case-type>PascalCase<case-type>
* Try to use only one word for folder names
* Use the **.c** extension for **C** files
* Use the **.h** extension for **C header** files
* Use the **.hpp** extension for **C++ header** files
* Use the **.cpp** extension for **C++** files
* Use the **.inl** extension for **C++ template implementation include** files


### Structs and classes
- <hl>**Class and struct**</hl>: <case-type>***PascalCase***</case-type>
- <hl>**Methods**</hl>: <case-type>***PascalCase***</case-type>
- <hl>**Method parameters**</hl>: <case-type>***camelCase***</case-type>
- <hl>**Members**</hl>: <case-type>***camelCase***</case-type>
- <hl>**Static members**</hl>: <case-type>***PascalCase***</case-type>
- **Protected and private member names** also use the **m_** prefix
- Use class access modifiers to separate between methods and members (even if it means repeating the modifier)
- Try to declare the **public**, **protected** and **private** interface in that order
- Try to declare **constructors**, **assigment operators** and **destructors** first, then **instance methods** and finally **static methods**.
- Aliases and static constants may be declared at the top of the class
- Nested structs and classes may be declared before methods and members

```c++
class Class
{
public:
    using Alias1 = int32_t;
    using Alias2 = int64_t;
    inline static constexpr StaticConstant { 10 };

    //Nested struct
    struct Nested
    {

    };

    //Constructors, assigment operators and destructors
    Class()                          = default;
    Class(const Class& c)            = default;
    Class(Class&& c)                 = default;
    Class& operator=(const Class& c) = default;
    Class& operator=(Class&& c)      = default;
    ~ClassName()                     = default;

    //Instance methods
    void InstanceMethod1(int32_t methodParam);
    virtual constexpr void InstanceMethod2() const noexcept override final;

    //Static methods
    static constexpr void StaticMethod1();
    static constexpr void StaticMethod2();
public:
    //Public static members
    inline static int32_t PublicStaticMember { 1 }; 

    //Public members
    int32_t publicMember1;
    int32_t publicMember2;
private:
    //Private static members
    inline static constexpr int32_t m_PrivateStaticMember { 1 };

    //Private members
    int32_t m_privateMember1;
    int32_t m_privateMember2;
};

```

### Namespaces
- <hl>**Namespaces**</hl>: <case-type>***camelCase***</case-type>
- Try to use only one word to describe the namespace
- Offer a 3-4 letter alias for every namespace
- Dont indent code inside of the namespace
- Simplify nested namespace definitions using ::
```c++
namespace example
{

struct Struct { };

} //namespace example

//Nested namespace
namespace example::nested 
{

} //namespace example::nested

//Shortened alias
namespace exp = example; 
```

### Enumerations
- <hl>**Enumerations**</hl>: <case-type>***PascalCase***</case-type>
- <hl>**Enumeration values**</hl>: <case-type>***PascalCase***</case-type>
- Prefer using enum class over plain enums
- Only use plain enums inside classes or namespaces

```c++
enum class EnumExample
{
    FirstValue,
    SecondValue
}
```

### Macros
- <hl>**Macros**</hl>: <case-type>***CONST_CASE***</case-type>

```c++
#define PI_2 6.28
```

