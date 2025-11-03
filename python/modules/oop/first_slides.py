# variable mutable and  immutable
# immutable -> type cannot be changed after assignment
class CatchingException:
    def catch_exception(func: callable):  # callable tell that we expect func as returning type
        try:
            func()
        except Exception as exception:
            print(exception)


if __name__ == '__main__':

    x = 5
    print(x)
    y = x
    try:
        im = str(x)
        print(im, type(im))
    except Exception as exc:
        print(exc)

    list1 = [1, 2, 3]
    list1[0] = "fajnie"  # it can be changed after assignment
    print(list1)
    # NoneType arguments
    var = None


    def fun_taking_argument(arg: None) -> bool:  # returning type
        if isinstance(arg, type(None)) or arg is None:
            return arg is None
        else:
            return False


    print(fun_taking_argument(var))


    # frozentype
    def type_frozenset():
        my_set = frozenset([1, 4, 4, 5, 12, 6])
        for i in my_set:
            print(my_set)
            try:
                my_set[2] = 51
            except Exception as exc:
                raise Exception(f"It's immutable , you cannot change the variable inside \nMessage: {exc} ")

    catch_object = CatchingException()
    catch_object.catch_exception(type_frozenset)  # you have to execute with referance to the function

    import collections


    def show_namedTuple_attributues(tuple_list: list[collections.namedtuple]):
        for element in tuple_list:
            print(f"Name: {element.name}, "
                  f"\t Age: {element.age}"
                  f"\t Status: {element.status}")


    def typeNamedTuple() -> None:
        Person = collections.namedtuple(
            'Person', ['name', 'age', 'status']
        )
        person1 = Person('Anna', 12, 'available')
        person2 = Person(name='Maciek', age=57, status='idle')
        show_namedTuple_attributues([person1, person2])


    typeNamedTuple()


    # show namedTuple
    def check_operators_is_and_equals() -> int:
        a = [1, 2, 3]
        b = [1, 2, 3]
        if a is b:  # check if the objects are the same objects  in memory
            return 12
        else:
            return int(a == b)  # not the same in memory but the same elements


    print(check_operators_is_and_equals())


    def list_dict_comprehension_revise(value: int) -> list or dict:
        list_comp = [element ** 2 for element in range(5)]
        dict_comp = {element: element ** 2 for element in range(5)}
        # from strings
        text = "______hellow,## WORLD!"
        mixed_data = [1, "apple", True, 3.14, "banana", False]
        uppercase = [char.upper() for char in text if char.isalpha()]
        only_strings = {char: text.count(char) for char in set(text) if char.isalpha()}
        print(uppercase)
        print(f"{only_strings= }")
        # zmienimay klucz i wartosc
        original_dict = {"a": 1, "b": 2, "c": 3}
        modified_dict = {
            value: key + "_modified" for key, value in original_dict.items()
        }
        print(f"{modified_dict= }")
        return list_comp if value == 1 else dict_comp


    print(list_dict_comprehension_revise(1))
    print(list_dict_comprehension_revise(2))


    # named arguments -> arguments passed by named no matter on which position they are declared
    def divide_fun(dividend, divisor):
        return dividend / divisor


    result = divide_fun(divisor=12, dividend=51)
    print(result)


    def named_position_arg_combination(age, name, second, third):
        print(f"{str.upper(name)=} + {age=} + {second =} + {third}")


    named_position_arg_combination(12, "gol", third="i like it ", second="what's")
