## Arrays and Structures

- First, how a processor works with respect to memory: every device has a CPU. In every CPU, you have cores. In each core, you have registers. In terms of memory capacity, a register can hold 64 bits. Remember: 1 byte = 8 bits.

- You might have 1 kilobyte of memory in the CPU. Every device also has RAM; it starts at address 0x00000000 and ends at 0xFFFFFFFF (64-bit architecture). Usually, RAM has like 16 GB, i.e., billions of times more.

- A processor can make operations on the content of registers. So, if you want to operate on different parts of the RAM, you will have to store something into registers and vice-versa. So, the CPU does three things:

  1. It can do operations.
  2. It can load data from RAM.
  3. It can store data into RAM.

- Note: it takes 10000x more energy to load/store. So, your processor will spend its time waiting IF it didn't have a cache.

## Cache

- Cache usually has 3 layers. When you access the data in the RAM, instead of putting the value in the registers, the processor can place the data in the cache. The advantage is the cache can be accessed much more easily. Of course, the cache is around 32–64 MB. So, the RAM will have multiple orders of magnitude more data than the cache.

## Heading into C

- The compiler GCC takes C code and turns it into binary. You must be able to tell your compiler how to structure the data and which data should be put into memory and hence cache later on. The idea is that if your data is related (if you access one, you'll access the other MOST OF THE TIME), it should live close together. So, each time you use an array, you tell the compiler that the data put in the array should be placed continuously in RAM.

# Key Concepts

**1. Array: homogeneous**

- To declare an array: `type var_name[n];` — `type` gives the type of the elements, `var_name` is the name of the variable, `[n]` indicates that we declare an array of size n.

- We can initialize an array when we declare it: `type name[n] = {0}` (sets all elements to 0).

- To access an array: `name[idx]` — `name` gives the name of the variable, `[idx]` indicates an array access, `idx` gives the index of the accessed element.

**2. Structure: heterogeneous**

- To define a type: `struct type_name { ... };`
- To declare a structure: `struct type_name var_name;`
- To access a field: `var_name.field_name`

> **An array is used to store homogeneous elements whereas a structure is used to store heterogeneous elements.**

- In Python, all the memory things are hidden from the user. In C, it's accessible.

# Array and Function Call

- When you give an array as a parameter to a function:

```c
void f(int tab[]) {
    for (int i = 0; i < 3; i++) {
        printf("%d\n", tab[i]); // prints 1, 2, 3
    }
}
```

- When you give a function an array, you give it the address of where the array sits in memory — not a copy.

- To declare a structure, first define a new type:

```c
struct name_of_the_struct {
    type1 field_name_1;
    type2 field_name_2;
    // ...
};
```

Example:

```c
struct strange {
    char c;
    int i;
    float f;
};

int main(int argc, char* argv[]) {
    struct strange var = {'a', 3, 3.14};
    return 0;
}
```

- `c`, `i`, and `f` are called the **fields** of the structure.

- If you want to access the fields, you can use dot notation, as in any OOP language:

```c
int main(int argc, char* argv[]) {
    struct strange var;
    var.c = 'a';
    var.i = 3;
    var.f = 3.14;
    printf("%c %d %f\n", var.c, var.i, var.f); // prints: a 3 3.140000
    return 0;
}
```

### To Declare a Function Parameter with a Struct Type

```c
void print_strange(struct strange s) {
    printf("%c %d %f\n", s.c, s.i, s.f);
}
```

- If you modify a structure inside a function, you modify the **copy**, not the original. Vice-versa for an array.

- If you want to modify the content of the structure using a function, you need a pointer to it (covered in the next section). Writing `p.x = 5.6;` inside a function only modifies the local copy.

# Reminders

- A variable is just a memory location that has a name, a type, and a value.

- A function is a group of instructions that creates a macro-instruction. It allows for code reuse and takes arguments and returns a result.

- A function has a name, a list of input parameters in the form `type symbol`, and a return type:

```c
int add(int a, int b) {
    return a + b;
}
// name: add | parameters: int a, int b | return type: int
```

- A function has a body: a sequence of statements delimited by `{}` and ends with a `return` statement. For non-void functions, the return must come last.

- If you don't assign the return value to a variable, it is lost (same as in Python).

### Declaration versus Implementation

- You can declare a function without implementing it:

```c
int g(int x); // declaration only — just the signature, no body

int f(int x) {
    return g(x) + 1; // f can call g because g is declared above
}

int g(int x) { // full implementation of g, defined later
    return x * 2;
}
```

# What Happens When You Call a Program in Your Terminal

1. When the system starts a program, it creates a **process**. A program is just an executable file in the file system, while a process is a running instance of a program. Multiple processes can run the same program simultaneously. When the system starts a process, it loads the program in memory and calls its `main` function, giving it two parameters: the number of arguments on the command line (`int argc`), and the arguments themselves (`char* argv[]`) — the 0th argument is the path to the program.

# Local Variables and Parameters

- A variable defined in a function body is called a **local variable**.

- Local variables and parameters exist only during an invocation (i.e. up to the next return instruction).

- For that, C manages what we call **frames**. A call frame is a piece of memory that contains the local variables and parameters of a function. It is allocated when the function starts and released when it returns. Variables are stored locally — if you call a helper function from inside another, the variables declared in the caller do not exist inside the helper:

```c
void helper() {
    int x = 10; // x only exists while helper() is running
    printf("%d\n", x);
}

int main(int argc, char* argv[]) {
    helper();
    // x does not exist here — it was local to helper()
    return 0;
}
```

# Execution and Call Frames

- When the program starts: allocate a call frame for `main`, install the arguments, activate the frame of `main`.

- When `main` calls another function, a new frame is allocated for that function. After the invocation, the function is just a value. The frames are like a stack.

- If a function calls itself, a new frame is dedicated for each call ⟹ new local variables for each call:

```c
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1); // each call gets its own frame with its own n
}

int main(int argc, char* argv[]) {
    printf("%d\n", factorial(5)); // prints 120
    return 0;
}
```

- If the stack grows past a threshold, a **stack overflow** occurs.

# Global Variables

- A global variable is defined outside any function, and it exists during the whole duration of the process and it can be read and written from any function — but if the same name is declared inside a function, that local declaration takes priority.

## To Execute a Process

- **Step 1:** The operating system locates the program in the file system.

- **Step 2:** It allocates memory for machine code (text segment) and for global data (data segment).

- **Step 3:** It loads (copies) the machine code and initialized global data into those allocated memory segments.

- **Step 4:** Allocates memory for the call frames (the stack).

- **Step 5:** Initializes two registers: the stack pointer (`%sp`) at the end of the stack, and the program counter (`%pc`) at the beginning of the machine code of `main`.

- **Step 6:** Moves `%sp` to make room for the call frame of `main` and installs the arguments.

- **Step 7:** Lets the processor execute the code.

- Each time the code returns from a function, the machine code moves `%sp` accordingly. When you arrive at `return 0`, the frame of `main` disappears.

```markdown
# Pointers

- When you declare a pointer (a variable whose value is an address):

```c
type* var;
```

Example:

```c
int x = 27;
```

- A variable is nothing but an address. In RAM, the above is something like `0x00001EF4`. The content is `27` (int). `&x` gives the address of the variable, `0x00001EF4`. A pointer is a variable whose content is an address.

Example:

```c
int* a;
a = &x;
```

- This means `a` is a variable that stores the address of `x`. Now the value of `a` is the address of `x` (e.g. `0x00001EF4`).

# Address of a Variable

- To retrieve the address of a variable, prefix it with `&` and print it using `"%p"` in printf:

```c
int a = 0x42;
printf("a is at %p\n", &a);
```

- To **dereference** a pointer: `*var` gives the value stored at the address contained in `var`. So:

```c
*a  // equals the value of x (27), not the address
```

- If you modify `*a`, you modify the value of `x` itself. This is significant on the call stack: normally, passing a variable to a function only gives that function a local copy. But if you pass the **address** of a variable instead, the function can write to that address directly — reaching into a different call frame and modifying the original. This is how C functions can have side effects on variables that live outside them.

- To declare a pointer: `type* name;`

## An Example of Using a Pointer

```c
int divide(int* p, int a, int b) {
    if (b == 0) {
        return -1;
    } else {
        *p = a / b;
        return 0;
    }
}

int main(int argc, char* argv[]) {
    int res;
    int err = divide(&res, 33, 0);
    if (err != 0) {
        printf("An error occurred\n");
    }
    return 0;
}
```

- Here, `divide` can't just return two things (the result and the error code), so instead it takes a pointer `p` and writes the result directly to `res` in `main`'s frame via `*p = a / b`. The return value is reserved for the error code.
```