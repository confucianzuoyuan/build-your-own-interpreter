# MonkeyLang 基本语法

## 使用`let`关键字进行变量绑定

```js
// Integers & arithmetic expressions...
let version = 1 + (50 / 2) - (8 * 3);

// ... and strings
let name = "The Monkey programming language";

// ... booleans
let isMonkeyFastNow = true;

// ... arrays & hash maps
let people = [{"name": "Anna", "age": 24}, {"name": "Bob", "age": 99}];
```

## 函数定义的语法

```js
// User-defined functions...
let getName = fn(person) { person["name"]; };
getName(people[0]); // => "Anna"
getName(people[1]); // => "Bob"

// and built-in functions
puts(len(people))  // prints: 2
```

## 条件语句以及如何返回值，并且支持递归。

```js
let fibonacci = fn(x) {
  if (x == 0) {
    0
  } else {
    if (x == 1) {
      return 1;
    } else {
      fibonacci(x - 1) + fibonacci(x - 2);
    }
  }
};
```

## 支持闭包

```js
// `newAdder` returns a closure that makes use of the free variables `a` and `b`:
let newAdder = fn(a, b) {
    fn(c) { a + b + c };
};
// This constructs a new `adder` function:
let adder = newAdder(1, 2);

adder(8); // => 11
```

