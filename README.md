<h1 align="center"> Bear </h1>
<p align="center">Bear Language Specification</p>

> Here you can see my process of making a language (I hope :)  

A Concatenative language. Everything is based around "transformation" of data.

# Other

A basic program: Add `1` to each element of a list.
(In code: `.` - `this` or `current` or whatever)
```fsharp
.. -> theList -> map { [1, .] -> @Add } -> ..
```
Maps `theList` to sum of a list of 1 and current element (eg. `[[1, 2], [3, 1]] -> [3, 4]`) `@Add` adds first two elements of a list in the input. In general, `@` `Operator` does something on first two elements on a list.

Example code:
```fsharp

//============[ lisp example ]============//

import Symbol // For makeSymbolIn and SymbolContext

const myContext: SymbolContext;

parse -> trim -> [head, .] -> & {
  	.0 -> ( [., '('] -> equals ) = [parseInside, .] -> & {
		[')', .1 -> head] -> @Equal = .0
		 _  -> throw "Expected ')'"
	};

  	.0 -> isalpha = ${
		* { head -> :@isAlpha } { <$ head |> tail }
	} -> collect -> string -> makeSymbolIn myContext;

	.0 -> [([., '-'] -> @Equal), isdigit] -> @Or = ${
		* { head -> :@isAlpha } { <$ head |> tail }
	} -> collect -> string -> number;

   	true = (["Unexpected character: '", ., "'."] -> @Concat) -> !Error -> throw;
};

exec -> & {
  typeof List = *(.0 -> exec -> :cast Func) .1: // '*' makes calling an expression possible
  typeof Symbol = myContext;
  typeof Number = .;
  true = (["Unknown type: '", ., "'."] -> @Concat) -> !Error -> throw;
};

lisp -> parse -> exec;

//============[ Hello World ]============//
hello -> void -> "Hello, World!" -> stdout;

//============[ Calculator ]============//
// use match same as here, because I cant change the lisp one.
math -> [.0, .1, .2] -> & { tail -> true = @(.0 -> operator) };
// or with syntax sugar:
math -> [.1, .2] |> @(.0 -> toOperator)
```

`a |> b` is `a -> & { true = b }`

### Imperative
* `%{...}` - Imperative code block. Input is not discarded.
* `X %:= Y` - Set `X` to `X -> Y`
* `<%` return

### Types
* `{{...}}` - Type block. Eg. `{{ name: Type; name2: Type2; method -> ...; new -> constructor;  }}`
* `:X` - Instance member
* `:.` - self, this, instance

### Generators
* `${...}` - Generator block. `<$` is used to generate an element.
* `collect` is used to "collect" all elements into a list.
* `* { 1... } { 2... }` is basically a while loop. Something like `var output; while(1...) { output = output -> 2... } return output;`

### Strings
* `string` converts a list into a string. Eg. `['a', 'b'] -> "ab"`
* `toString` converts Lists, Numbers, Strings, Chars (implict) into strings. Eg `49 -> "49"; ['a', 'b'] -> "['a','b']"; 'x' -> "x"; "abc" -> "abc"`. 
  Otherwise tries to use `@String`, 
  else `:toString`,
  else `:@toString`,
  else `getType |> :toString`,
  else `getType |> :@toString`,
  and finally `cast String`,
  if none work, throws `!CastError/String/`.

## ...
```fsharp
makeSymbolIn ctx -> ctx |> :symbolTable |> & {
	:has = !DuplicateSymbol -> throw; //? Warning: "!DuplicateSymbol" receives input! To remove this warning add ". ->" in front of "!DuplicateSymbol".
	:full = void -> !OutOfMemoryError -> throw;
	true = :@Put;
}

type SymbolContext => {{
	symbolTable: Map/Any/;
	parent: SymbolContext;
	new -> %{ //??? (by default) Warning: Imperative code block shouldn't be used. 
		:symbolTable %:= init;
		:parent %:= null;
		<% :.;
	}
}};

```

A bunch of ideas! Errors: `!Error`, Access of things: `:Something`, or unary operator access `:@Operator`, Generics: `Type/OtherType, AnotherType/` (Errors are also types).
:D

Implementation?
for example: `TransparentArrow : Arrow { void Move(Obj prev, Obj next) { next.Input = prev; next.Exec(prev.Previous); } }`
and `BasicArrow : Arrow { void Move(Obj prev, Obj next) { next.Input = prev; next.Exec(prev); } }`

# Specification

## Syntax:

> TODO!  
Weird form...
```
identifier ::= [a-zA-Z_][a-zA-Z0-9_]*
number ::= -?[0-9]+(\.[0-9]+[fdlFDL]

expression | '(' expression ')'   -> Expression
           | '[' list ']'         -> List
	   | '{' expression '}'         -> Block
	   | '${' expression '}'        -> Block(gen: true)
	   | '{{' type '}}'       -> TypeBlock
	   | '%{' imperative '}'  -> Imperative
	   | expression '->' expression -> BasicArrow
	   | expression '|>' expression -> TransparentArrow
	   | '&' '{' selectors '}' -> Match
	   
atom | identifier       -> Identifier
     | number           -> Number
     | '.'              -> Dot
     | ':' identifier   -> Select
     | '@' identifier   -> Operator
     | ':@' identifier  -> SelectOperator
     
```

