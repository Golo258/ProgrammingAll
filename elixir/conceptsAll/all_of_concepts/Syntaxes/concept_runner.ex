defmodule Services.ConceptRunner do
    alias Models.TaskModel, as: MTask
    alias Concepts.ElixirSyntax, as: ESyntax
    alias Concepts.Collections
    alias Rectangle
    alias Circle
    alias Shape
    alias MacroUse

    def run_concepts do
        task_list = init_task_list()
        IO.inspect(task_list)
        Collections.creating_inserting()
        Collections.operations()
        show_concepts()
    end

    defp show_concepts() do
        returned_value = ESyntax.SimpleModule.present_args("Simple text")
        ESyntax.SimpleModule.present_args("Text", 12, :gold)
        IO.puts("Returned value: #{returned_value}")
        ESyntax.SimpleModule.pattern_matching()
        ESyntax.SimpleModule.conditional_construction()
        ESyntax.SimpleModule.pipes_usage()
        protocol_usage()
        ESyntax.SimpleModule.execute_comprehensions()
        IO.puts("\n\n")
        MacroUse.hello(:alice)
        MacroUse.hello(:bob)
        Collections.map_examples()
        Collections.tuple_struct_example()
    end

    defp init_task_list do
        task1 = MTask.new(1, "First Task", "Task 1 description", :pending)
        task2 = MTask.new(2, "Second Task", "Task 2 desc")
        task_list = [task1, task2]
        # return changed version
        List.insert_at(task_list, 2, MTask.new(3, "Third one", "The last one"))
    end

    def protocol_usage do
        rect = %Rectangle{width: 5, height: 10}
        rect_shape = Shape.area(rect)

        circle = %Circle{radius: 12}
        circle_shape = Shape.area(circle)
        IO.inspect(rect_shape, label: "Rectangle shape")
        IO.inspect(circle_shape, label: "Circle shape")
    end
end
